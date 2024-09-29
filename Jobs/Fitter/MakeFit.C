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
void MakeFit(int Run, int Seg)
{


	std::cout << "Now I also go with the Atcs Fit Work flow on the matched Seeds -> Worked?" << std::endl;

	std::string infile = Form("/direct/sphenix+tg+tg01/hf/zshi/SeedMatchFileAllNew/DST/DSTSeedSofar_%d_%d.root",Run,Seg);

	int runnumber = Run;
	int segment = Seg;



	ACTSGEOM::mvtxMisalignment = 100;
	ACTSGEOM::inttMisalignment = 100.;
	ACTSGEOM::tpotMisalignment = 100.;

	auto se = Fun4AllServer::instance();
	se->Verbosity(2);
	auto rc = recoConsts::instance();
	rc->set_IntFlag("RUNNUMBER", runnumber);
	rc->set_IntFlag("RUNSEGMENT", segment);

	Enable::CDB = true;
	rc->set_StringFlag("CDB_GLOBALTAG", "ProdA_2024");
	rc->set_uint64Flag("TIMESTAMP", runnumber);
	std::string geofile = CDBInterface::instance()->getUrl("Tracking_Geometry");

	Fun4AllRunNodeInputManager *ingeo = new Fun4AllRunNodeInputManager("GeoIn");
	ingeo->AddFile(geofile);
	se->registerInputManager(ingeo);

	std::cout << "Using infile: " << infile  << std::endl;

	auto hitsin = new Fun4AllDstInputManager("InputManager");
	hitsin->fileopen(infile);
	// hitsin->AddFile(inputMbd);
	se->registerInputManager(hitsin);

	auto deltazcorr = new PHTpcDeltaZCorrection;
	deltazcorr->Verbosity(0);
	se->registerSubsystem(deltazcorr);

	// perform final track fit with ACTS
	auto actsFit = new PHActsTrkFitter;
	actsFit->Verbosity(0);
	actsFit->commissioning(G4TRACKING::use_alignment);
	// in calibration mode, fit only Silicons and Micromegas hits
	actsFit->fitSiliconMMs(G4TRACKING::SC_CALIBMODE);
	actsFit->setUseMicromegas(G4TRACKING::SC_USE_MICROMEGAS);
	actsFit->set_pp_mode(TRACKING::pp_mode);
	actsFit->set_use_clustermover(true);  // default is true for now
	actsFit->useActsEvaluator(false);
	actsFit->useOutlierFinder(false);
	actsFit->setFieldMap(G4MAGNET::magfield_tracking);
	se->registerSubsystem(actsFit);

	auto cleaner = new PHTrackCleaner();
	cleaner->Verbosity(0);
	se->registerSubsystem(cleaner);

	if (G4TRACKING::SC_CALIBMODE)
	{
		/*
		 * in calibration mode, calculate residuals between TPC and fitted tracks,
		 * store in dedicated structure for distortion correction
		 */
		auto residuals = new PHTpcResiduals;
		const TString tpc_residoutfile = "PhTpcResiduals.root";
		residuals->setOutputfile(tpc_residoutfile.Data());
		residuals->setUseMicromegas(G4TRACKING::SC_USE_MICROMEGAS);

		// matches Tony's analysis
		residuals->setMinPt( 0.2 );

		// reconstructed distortion grid size (phi, r, z)
		residuals->setGridDimensions(36, 48, 80);
		se->registerSubsystem(residuals);
	}



	auto finder = new PHSimpleVertexFinder;
	finder->Verbosity(0);
	finder->setDcaCut(0.5);
	finder->setTrackPtCut(-99999.);
	finder->setBeamLineCut(1);
	finder->setTrackQualityCut(1000000000);
	finder->setNmvtxRequired(3);
	finder->setOutlierPairCut(0.1);
	se->registerSubsystem(finder);




	auto resid = new TrackResiduals("TrackResiduals");
	resid->outfileName("TrackResidTree.root");
	resid->alignment(false);


	Fun4AllOutputManager *out = new Fun4AllDstOutputManager("out", "DSTACTSFitted.root");
	se->registerOutputManager(out);

	int nEvents = 10;

	se->run(nEvents);
	se->End();
	se->PrintTimer();

	delete se;
	std::cout << "Finished" << std::endl;
	gSystem->Exit(0);
}
