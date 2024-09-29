/*
 * This macro shows a minimum working example of running the tracking
 * hit unpackers with some basic seeding algorithms to try to put together
 * tracks. There are some analysis modules run at the end which package
 * hits, clusters, and clusters on tracks into trees for analysis.
 */

#include <fun4all/Fun4AllUtils.h>
#include <G4_ActsGeom.C>
#include <G4_Global.C>
#include <G4_Magnet.C>
#include <G4_Mbd.C>
#include <GlobalVariables.C>
#include <QA.C>
#include <Trkr_Clustering.C>
#include <Trkr_Reco.C>
#include <Trkr_RecoInit.C>
#include <Trkr_TpcReadoutInit.C>

#include <ffamodules/CDBInterface.h>

#include <fun4all/Fun4AllDstInputManager.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllOutputManager.h>
#include <fun4all/Fun4AllRunNodeInputManager.h>
#include <fun4all/Fun4AllServer.h>

#include <phool/recoConsts.h>

#include <cdbobjects/CDBTTree.h>

#include <tpccalib/PHTpcResiduals.h>

#include <trackingqa/InttClusterQA.h>
#include <trackingqa/MicromegasClusterQA.h>
#include <trackingqa/MvtxClusterQA.h>
#include <trackingqa/TpcClusterQA.h>

#include <trackingdiagnostics/TrackResiduals.h>
#include <trackingdiagnostics/TrkrNtuplizer.h>
#include <trackingdiagnostics/KshortReconstruction.h>

#include <trackermillepedealignment/AlignmentDefs.h>
#include <trackermillepedealignment/HelicalFitter.h>

#include <stdio.h>

	R__LOAD_LIBRARY(libfun4all.so)
	R__LOAD_LIBRARY(libffamodules.so)
	R__LOAD_LIBRARY(libphool.so)
	R__LOAD_LIBRARY(libcdbobjects.so)
	R__LOAD_LIBRARY(libmvtx.so)
	R__LOAD_LIBRARY(libintt.so)
	R__LOAD_LIBRARY(libtpc.so)
	R__LOAD_LIBRARY(libmicromegas.so)
	R__LOAD_LIBRARY(libTrackingDiagnostics.so)
R__LOAD_LIBRARY(libtrackingqa.so)
	void Fun4All_FieldOnAllTrackers(
			const int nEvents = 100000,
			const std::string tpcfilename = "DST_BEAM_run2pp_new_2023p013-00041989-0000.root",
			const std::string tpcdir = "/sphenix/lustre01/sphnxpro/commissioning/slurp/tpcbeam/run_00041900_00042000/",
			const std::string outfilename = "clusters_seeds",
			bool convertSeeds =false)
{
	// override the input value for now
	//  convertSeeds = false;
	bool silicon_only = false;
	bool do_alignment = false;
    bool MatchingSiTPC = true;
	//TRACKING::pp_mode = true;
	TRACKING::tpc_zero_supp = true;
	TRACKING::pp_extended_readout_time = 50000;  // ns
    TRACKING::pp_mode = true;
	
	std::string inputtpcRawHitFile = tpcdir + tpcfilename;
	//std::string inputtpcRawHitFile = "/sphenix/tg/tg01/hf/cdean/streamingTests/siliconOnly/20240814/DST_siliconStreaming_run00050897.root";


	G4TRACKING::convert_seeds_to_svtxtracks = convertSeeds;
	std::cout << "Converting to seeds : " << G4TRACKING::convert_seeds_to_svtxtracks << std::endl;
	std::pair<int, int>
		runseg = Fun4AllUtils::GetRunSegment(tpcfilename);
	int runnumber = runseg.first;
	int segment = runseg.second;

	TpcReadoutInit( runnumber );
	std::cout<< " run: " << runnumber
		<< " samples: " << TRACKING::reco_tpc_maxtime_sample
		<< " pre: " << TRACKING::reco_tpc_time_presample
		<< " vdrift: " << G4TPC::tpc_drift_velocity_reco
		<< std::endl;

	// distortion calibration mode
	/*
	 * set to true to enable residuals in the TPC with
	 * TPC clusters not participating to the ACTS track fit
	 */
	G4TRACKING::SC_CALIBMODE = false;

	ACTSGEOM::mvtxMisalignment = 100;
	ACTSGEOM::inttMisalignment = 100.;
	ACTSGEOM::tpotMisalignment = 100.;
	TString outfile = outfilename + "clusters_tracks_" + runnumber + "-" + segment + ".root";
	std::string theOutfile = outfile.Data();
	auto se = Fun4AllServer::instance();
	se->Verbosity(1);
	auto rc = recoConsts::instance();
	rc->set_IntFlag("RUNNUMBER", runnumber);

	Enable::CDB = true;
	rc->set_StringFlag("CDB_GLOBALTAG", "ProdA_2024");
	rc->set_uint64Flag("TIMESTAMP", runnumber);
	std::string geofile = CDBInterface::instance()->getUrl("Tracking_Geometry");

	Fun4AllRunNodeInputManager *ingeo = new Fun4AllRunNodeInputManager("GeoIn");
	ingeo->AddFile(geofile);
	se->registerInputManager(ingeo);

	CDBInterface *cdb = CDBInterface::instance();
	std::string tpc_dv_calib_dir = cdb->getUrl("TPC_DRIFT_VELOCITY");
	if (tpc_dv_calib_dir.empty())
	{
		std::cout << "No calibrated TPC drift velocity for Run " << runnumber << ". Use default value " << G4TPC::tpc_drift_velocity_reco << " cm/ns" << std::endl;
	}
	else
	{
		CDBTTree *cdbttree = new CDBTTree(tpc_dv_calib_dir);
		cdbttree->LoadCalibrations();
		G4TPC::tpc_drift_velocity_reco = cdbttree->GetSingleFloatValue("tpc_drift_velocity");
		std::cout << "Use calibrated TPC drift velocity for Run " << runnumber << ": " << G4TPC::tpc_drift_velocity_reco << " cm/ns" << std::endl;
	}

	G4TPC::ENABLE_MODULE_EDGE_CORRECTIONS = true;
	//to turn on the default static corrections, enable the two lines below
	G4TPC::ENABLE_STATIC_CORRECTIONS = true;
	G4TPC::ENABLE_AVERAGE_CORRECTIONS = false; 
    G4TPC::average_correction_filename = string(getenv("CALIBRATIONROOT")) + "/distortion_maps/average_minus_static_distortion_inverted_10-new.root";
/*
	if(TPCCorrOpt == 1 || TPCCorrOpt == 4 || TPCCorrOpt == 5 || TPCCorrOpt == 7) G4TPC::ENABLE_MODULE_EDGE_CORRECTIONS = true;
	//to turn on the default static corrections, enable the two lines below
	if(TPCCorrOpt == 2 || TPCCorrOpt == 4||  TPCCorrOpt == 6 || TPCCorrOpt == 7) G4TPC::ENABLE_STATIC_CORRECTIONS = true;
	if(TPCCorrOpt == 3 || TPCCorrOpt == 5 ||  TPCCorrOpt == 6|| TPCCorrOpt == 7) G4TPC::ENABLE_AVERAGE_CORRECTIONS = true; 
	std::cout << "Added Enable Average Corr" << std::endl;
	if(TPCCorrOpt == 3) 	std::cout << "Use G4TPCed" << std::endl;
*/
	G4TPC::DISTORTIONS_USE_PHI_AS_RADIANS = false;


	G4MAGNET::magfield_rescale = 1;
	TrackingInit();

	auto hitsin = new Fun4AllDstInputManager("InputManager");
	hitsin->fileopen(inputtpcRawHitFile);
	// hitsin->AddFile(inputMbd);
	se->registerInputManager(hitsin);

	Mvtx_HitUnpacking();
	Intt_HitUnpacking();
	if(!silicon_only)
	{      
		Tpc_HitUnpacking();
		Micromegas_HitUnpacking();
	}

	Mvtx_Clustering();
	Intt_Clustering();


	if(!silicon_only)
	{  
		auto tpcclusterizer = new TpcClusterizer;
		tpcclusterizer->Verbosity(0);
		tpcclusterizer->set_do_hit_association(G4TPC::DO_HIT_ASSOCIATION);
		tpcclusterizer->set_rawdata_reco();
		se->registerSubsystem(tpcclusterizer);

		std::cout << "TPC Laser Studies - Ben" << std::endl;


		Tpc_LaserEventIdentifying();

		std::cout << "TPC Laser Studies - Done Ben" << std::endl;

		Micromegas_Clustering();
	}

	silicon_Seeding->seedAnalysis(false);
	auto silicon_Seeding = new PHActsSiliconSeeding;
	silicon_Seeding->Verbosity(0);
	std::cout << "set search INTT  -> Nope -> Tony Setup Yes" << std::endl;
	
	// these get us to about 83% INTT > 1
	silicon_Seeding->setinttRPhiSearchWindow(1.0);
	silicon_Seeding->setinttZSearchWindow(7.0);
	silicon_Seeding->seedAnalysis(false);
	se->registerSubsystem(silicon_Seeding);


	auto merger = new PHSiliconSeedMerger;
	merger->Verbosity(0);
	se->registerSubsystem(merger);

	/*
	 * Tpc Seeding
	 */
	if(!silicon_only)
	{
		auto seeder = new PHCASeeding("PHCASeeding");
		double fieldstrength = std::numeric_limits<double>::quiet_NaN();  // set by isConstantField if constant
		bool ConstField = isConstantField(G4MAGNET::magfield_tracking, fieldstrength);
		if (ConstField)
		{
			seeder->useConstBField(true);
			seeder->constBField(fieldstrength);
		}
		else
		{
			seeder->set_field_dir(-1 * G4MAGNET::magfield_rescale);
			seeder->useConstBField(false);
			seeder->magFieldFile(G4MAGNET::magfield_tracking);  // to get charge sign right
		}
		seeder->Verbosity(0);
		seeder->SetLayerRange(7, 55);
		seeder->SetSearchWindow(2.,0.05); // z-width and phi-width, default in macro at 1.5 and 0.05
		seeder->SetClusAdd_delta_window(3.0,0.06); //  (0.5, 0.005) are default; sdzdr_cutoff, d2/dr2(phi)_cutoff
		seeder->SetNClustersPerSeedRange(6,6); // default is 6, 6
		seeder->SetMinHitsPerCluster(0);
		seeder->SetMinClustersPerTrack(3);
		seeder->useFixedClusterError(true);
		seeder->set_pp_mode(TRACKING::pp_mode);
		se->registerSubsystem(seeder);


		// expand stubs in the TPC using simple kalman filter
		auto cprop = new PHSimpleKFProp("PHSimpleKFProp");
		cprop->set_field_dir(G4MAGNET::magfield_rescale);
		if (ConstField)
		{
			cprop->useConstBField(true);
			cprop->setConstBField(fieldstrength);
		}
		else
		{
			cprop->magFieldFile(G4MAGNET::magfield_tracking);
			cprop->set_field_dir(-1 * G4MAGNET::magfield_rescale);
		}
		cprop->useFixedClusterError(true);
		cprop->set_max_window(5.);
		cprop->Verbosity(0);
		cprop->set_pp_mode(TRACKING::pp_mode);
		se->registerSubsystem(cprop);

		if (TRACKING::pp_mode)
		{
			// for pp mode, apply preliminary distortion corrections to TPC clusters before crossing is known
			// and refit the trackseeds. Replace KFProp fits with the new fit parameters in the TPC seeds.
			auto prelim_distcorr = new PrelimDistortionCorrection;
			prelim_distcorr->set_pp_mode(TRACKING::pp_mode);
			prelim_distcorr->Verbosity(0);
			se->registerSubsystem(prelim_distcorr);
		}
	}


	if(MatchingSiTPC){
	
		std::cout << "Doing Match TPC with Silicon Seeds" << std::endl;
		/*
		 * Track Matching between silicon and TPC
		 */
		// The normal silicon association methods
		// Match the TPC track stubs from the CA seeder to silicon track stubs from PHSiliconTruthTrackSeeding
		auto silicon_match = new PHSiliconTpcTrackMatching;
		silicon_match->Verbosity(0);
		silicon_match->set_test_windows_printout(true); //print out ntuples for QA check
		silicon_match->set_x_search_window(2.);
		silicon_match->set_y_search_window(2.);
		silicon_match->set_z_search_window(5.);
		silicon_match->set_phi_search_window(0.2);
		silicon_match->set_eta_search_window(0.1);
		//silicon_match->set_use_old_matching(true);
		//silicon_match->set_pp_mode(true);
   	    silicon_match->set_pp_mode(TRACKING::pp_mode);
		se->registerSubsystem(silicon_match);

		// Match TPC track stubs from CA seeder to clusters in the micromegas layers
		auto mm_match = new PHMicromegasTpcTrackMatching;
		mm_match->Verbosity(0);
		mm_match->set_rphi_search_window_lyr1(0.4);
		mm_match->set_rphi_search_window_lyr2(13.0);
		mm_match->set_z_search_window_lyr1(26.0);
		mm_match->set_z_search_window_lyr2(0.4);

		mm_match->set_min_tpc_layer(38);             // layer in TPC to start projection fit
		mm_match->set_test_windows_printout(false);  // used for tuning search windows only
		se->registerSubsystem(mm_match);

	}

    auto converter = new TrackSeedTrackMapConverter;
    // Default set to full SvtxTrackSeeds. Can be set to
    // SiliconTrackSeedContainer or TpcTrackSeedContainer
    converter->setTrackSeedName("SvtxTrackSeedContainer");
    converter->setFieldMap(G4MAGNET::magfield_tracking);
    converter->Verbosity(0);
    se->registerSubsystem(converter);

	Fun4AllOutputManager *out = new Fun4AllDstOutputManager("out", "DSTSeedSofar.root");
	se->registerOutputManager(out);


	std::string hfbinstring = outfilename+"helical_out_"+std::to_string(runnumber)+"-"+std::to_string(segment)+".bin";
	std::string hfsteerstring = outfilename+"helical_steer_"+std::to_string(runnumber)+"-"+std::to_string(segment)+".txt";
	std::string hfntpstring = outfilename+"helical_ntuple_"+std::to_string(runnumber)+"-"+std::to_string(segment)+".root";
	std::cout << hfbinstring << "  " << hfsteerstring << "  " << hfntpstring << std::endl;

	if(do_alignment)
	{
		auto hf = new HelicalFitter();
		hf->set_silicon_track_map_name("SiliconTrackSeedContainer");
		hf->Verbosity(0);
		hf->set_datafile_name(hfbinstring);
		hf->set_steeringfile_name(hfsteerstring);
		hf->set_mvtx_grouping(AlignmentDefs::mvtxGrp::snsr);
		hf->set_intt_grouping(AlignmentDefs::inttGrp::lad);
		hf->set_tpc_grouping(AlignmentDefs::tpcGrp::tp);
		hf->set_layer_param_fixed(0, 0);
		hf->set_layer_param_fixed(0, 1);
		hf->set_layer_param_fixed(0, 2);
		hf->set_layer_param_fixed(1, 0);
		hf->set_layer_param_fixed(1, 1);
		hf->set_layer_param_fixed(1, 2);
		hf->set_layer_param_fixed(2, 0);
		hf->set_layer_param_fixed(2, 1);
		hf->set_layer_param_fixed(2, 2);  
		hf->set_layer_param_fixed(3, 0);
		hf->set_layer_param_fixed(3, 1);
		hf->set_layer_param_fixed(3, 2);  
		hf->set_layer_param_fixed(4, 0);
		hf->set_layer_param_fixed(4, 1);
		hf->set_layer_param_fixed(4, 2);
		hf->set_layer_param_fixed(5, 0);
		hf->set_layer_param_fixed(5, 1);
		hf->set_layer_param_fixed(5, 2);
		hf->set_layer_param_fixed(6, 0);
		hf->set_layer_param_fixed(6, 1);
		hf->set_layer_param_fixed(6, 2);
		hf->set_intt_layer_fixed(3);
		hf->set_intt_layer_fixed(4);
		hf->set_use_event_vertex(true);
		hf->set_vertex_param_fixed(0);
		hf->set_vertex_param_fixed(1);
		hf->set_ntuplefile_name(hfntpstring);
		hf->set_fitted_subsystems(false, true, true);  // silicon, tpc, all
		se->registerSubsystem(hf);

	}
	//auto ntuplizer = new TrkrNtuplizer("TrkrNtuplizer");
	//se->registerSubsystem(ntuplizer);

	// Fun4AllOutputManager *out = new Fun4AllDstOutputManager("out", "/sphenix/tg/tg01/hf/jdosbo/tracking_development/Run24/Beam/41626/hitsets.root");
	// se->registerOutputManager(out);
	if (Enable::QA)
	{
		se->registerSubsystem(new MvtxClusterQA);
		se->registerSubsystem(new InttClusterQA);
		se->registerSubsystem(new TpcClusterQA);
		se->registerSubsystem(new MicromegasClusterQA);
	}
	se->run(nEvents);
	se->End();
	se->PrintTimer();

	if (Enable::QA)
	{
		TString qaname = theOutfile + "_qa.root";
		std::string qaOutputFileName(qaname.Data());
		QAHistManagerDef::saveQARootFile(qaOutputFileName);
	}

	delete se;
	std::cout << "Finished" << std::endl;
	gSystem->Exit(0);
}
