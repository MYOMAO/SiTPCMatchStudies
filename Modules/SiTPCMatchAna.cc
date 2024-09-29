#include <trackingdiagnostics/TrackResiduals.h>

#include <trackbase/ClusterErrorPara.h>
#include <trackbase/InttDefs.h>
#include <trackbase/MvtxDefs.h>
#include <trackbase/TpcDefs.h>
#include <trackbase/TrackFitUtils.h>
#include <trackbase/TrkrCluster.h>
#include <trackbase/TrkrClusterContainer.h>
#include <trackbase/TrkrHit.h>
#include <trackbase/TrkrHitSet.h>
#include <trackbase/TrkrHitSetContainer.h>

#include <g4detectors/PHG4CylinderGeomContainer.h>
#include <g4detectors/PHG4TpcCylinderGeom.h>
#include <g4detectors/PHG4TpcCylinderGeomContainer.h>

#include <intt/CylinderGeomIntt.h>

#include <micromegas/CylinderGeomMicromegas.h>
#include <micromegas/MicromegasDefs.h>

#include <mvtx/CylinderGeom_Mvtx.h>

#include <trackbase_historic/ActsTransformations.h>
#include <trackbase_historic/SvtxAlignmentState.h>
#include <trackbase_historic/SvtxAlignmentStateMap.h>
#include <trackbase_historic/SvtxTrack.h>
#include <trackbase_historic/SvtxTrack_v1.h>
#include <trackbase_historic/SvtxTrackMap.h>
#include <trackbase_historic/TrackAnalysisUtils.h>
#include <trackbase_historic/TrackSeed.h>
#include <trackbase_historic/TrackSeedContainer.h>
#include <tpc/LaserEventInfo.h>

#include <ffarawobjects/Gl1Packet.h>
#include <ffarawobjects/Gl1RawHit.h>
#include <tpc/TpcDistortionCorrectionContainer.h>
#include <tpc/TpcGlobalPositionWrapper.h>

#include <globalvertex/GlobalVertex.h>
#include <globalvertex/GlobalVertexMap.h>
#include <globalvertex/SvtxVertex.h>
#include <globalvertex/SvtxVertexMap.h>

#include <fun4all/Fun4AllReturnCodes.h>

#include <phool/PHCompositeNode.h>
#include <phool/PHNodeIterator.h>
#include <phool/getClass.h>

#include "SiTPCMatchAna.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TStyle.h"



#include <limits>
//____________________________________________________________________________..
SiTPCMatchAna::SiTPCMatchAna(const std::string &name)
	: SubsysReco(name)
{
	std::cout << "Used SiTPCMatchAna -> 09/28/2024 -> Added EvtAna Tree -> Change" << std::endl;	
	std::cout << "Finished" << std::endl;
}

//____________________________________________________________________________..
int SiTPCMatchAna::InitRun(PHCompositeNode *topNode)
{


	std::cout << "I am using my own module" << std::endl; 	
	foutEvt = new TFile("EvtAna_Svtx.root","RECREATE");
	foutEvt->cd();

	EvtAna = new TTree("EvtAna","EvtAna");
	EvtAna->Branch("event",&event);
	EvtAna->Branch("IsLaserEvt",&IsLaserEvt);
	
	EvtAna->Branch("TotalClus",&TotalClus);
	EvtAna->Branch("TotalSiSeedClus",&TotalSiSeedClus);
	EvtAna->Branch("TotalTPCSeedClus",&TotalTPCSeedClus);
	EvtAna->Branch("TotalSiSeed",&TotalSiSeed);
	EvtAna->Branch("TotalTPCSeed",&TotalTPCSeed);
	EvtAna->Branch("TotalSiSeedZero",&TotalSiSeedZero);
	//EvtAna->Branch("TotalTPCSeedZero",&TotalTPCSeedZero);

	//	EvtAna->Branch("TotalMatchedSiSeed",&TotalMatchedSiSeed);
	//	EvtAna->Branch("TotalMatchedTPCSeed",&TotalMatchedTPCSeed);
	//  EvtAna->Branch("TotalMatchedSiSeedZero",&TotalMatchedSiSeedZero);
	//EvtAna->Branch("TotalMatchedTPCSeedZero",&TotalMatchedTPCSeedZero);
	EvtAna->Branch("TotalMatchedSeed",&TotalMatchedSeed);
	EvtAna->Branch("TotalMatchedSeedZero",&TotalMatchedSeedZero);



	fout = new TFile("SeedAna_Svtx.root","RECREATE");
	std::cout << "OK2" << std::endl;

	fout->cd();
	std::cout << "OK3" << std::endl;




	/*

	   SiSeedAna = new TTree("SiSeedAna","SiSeedAna");
	   SiSeedAna->Branch("event",&event);
	   SiSeedAna->Branch("crossing",&crossing);
	   SiSeedAna->Branch("SeedID",&SiSeedID);

	   SiSeedAna->Branch("SiSeedEta",&SiSeedEta);
	   SiSeedAna->Branch("SiSeedPt",&SiSeedPt);

	   SiSeedAna->Branch("nmaps",&nmaps);
	   SiSeedAna->Branch("nintt",&nintt);

	   SiSeedAna->Branch("x",&seedx);
	   SiSeedAna->Branch("y",&seedy);
	   SiSeedAna->Branch("z",&seedz);
	   SiSeedAna->Branch("px",&seedpx);
	   SiSeedAna->Branch("py",&seedpy);
	   SiSeedAna->Branch("pz",&seedpz);

	//	SiSeedAna->Branch("chisq",&chisq);	
	//	SiSeedAna->Branch("ndf",&ndf);	


	SiSeedAna->Branch("ClusPosX",&ClusPosX);
	SiSeedAna->Branch("ClusPosY",&ClusPosY);
	SiSeedAna->Branch("ClusPosZ",&ClusPosZ);
	SiSeedAna->Branch("INTTTimeBucket",&INTTTimeBucketVec);



	TPCSeedAna = new TTree("TPCSeedAna","TPCSeedAna");
	TPCSeedAna->Branch("event",&event);
	TPCSeedAna->Branch("SeedID",&TPCSeedID);
	TPCSeedAna->Branch("ntpc",&ntpc);

	//	SiSeedAna->Branch("crossing",&crossing);
	TPCSeedAna->Branch("x",&tpcseedx);
	TPCSeedAna->Branch("y",&tpcseedy);
	TPCSeedAna->Branch("z",&tpcseedz);
	TPCSeedAna->Branch("px",&tpcseedpx);
	TPCSeedAna->Branch("py",&tpcseedpy);
	TPCSeedAna->Branch("pz",&tpcseedpz);

	TPCSeedAna->Branch("TPCClusPosX",&TPCClusPosX);
	TPCSeedAna->Branch("TPCClusPosY",&TPCClusPosY);
	TPCSeedAna->Branch("TPCClusPosZ",&TPCClusPosZ);

*/

	std::cout << "Define Tree" << std::endl;

	SeedAna = new TTree("SeedAna","SeedAna");

	SeedAna->Branch("event",&event);
	SeedAna->Branch("IsLaserEvt",&IsLaserEvt);

	SeedAna->Branch("siseedsize",&siseedsize);
	SeedAna->Branch("tpcseedsize",&tpcseedsize);
	//	SeedAna->Branch("svtxseedsize",&svtxseedsize);

	SeedAna->Branch("nmaps",&nmaps);
	SeedAna->Branch("nintt",&nintt);


	SeedAna->Branch("siseedid",&siseedid);
	SeedAna->Branch("crossing",&crossing);

	SeedAna->Branch("siseedx",&siseedx);
	SeedAna->Branch("siseedy",&siseedy);
	SeedAna->Branch("siseedz",&siseedz);
	SeedAna->Branch("siseedpx",&siseedpx);
	SeedAna->Branch("siseedpy",&siseedpy);
	SeedAna->Branch("siseedpz",&siseedpz);
	SeedAna->Branch("siseedcharge",&siseedcharge);

	SeedAna->Branch("siseedphi",&siseedphi);
	SeedAna->Branch("siseedeta",&siseedeta);


	SeedAna->Branch("siclusposx",&siclusposx);
	SeedAna->Branch("siclusposy",&siclusposy);
	SeedAna->Branch("siclusposz",&siclusposz);

	SeedAna->Branch("ntpc",&ntpc);

	SeedAna->Branch("tpcseedid",&tpcseedid);
	SeedAna->Branch("tpcseedx",&tpcseedx);
	SeedAna->Branch("tpcseedy",&tpcseedy);
	SeedAna->Branch("tpcseedz",&tpcseedz);
	SeedAna->Branch("tpcseedpx",&tpcseedpx);
	SeedAna->Branch("tpcseedpy",&tpcseedpy);
	SeedAna->Branch("tpcseedpz",&tpcseedpz);
	SeedAna->Branch("tpcseedcharge",&tpcseedcharge);

	SeedAna->Branch("tpcseedphi",&tpcseedphi);
	SeedAna->Branch("tpcseedeta",&tpcseedeta);



	SeedAna->Branch("tpcclusposx",&tpcclusposx);
	SeedAna->Branch("tpcclusposy",&tpcclusposy);
	SeedAna->Branch("tpcclusposz",&tpcclusposz);


	std::cout << "Added Svtx" << std::endl;
	/*
	   SeedAna->Branch("nsvtx",&nsvtx);

	   SeedAna->Branch("svtxseedid",&svtxseedid);

	   SeedAna->Branch("svtxseedx",&svtxseedx);
	   SeedAna->Branch("svtxseedy",&svtxseedy);
	   SeedAna->Branch("svtxseedz",&svtxseedz);
	   SeedAna->Branch("svtxseedpx",&svtxseedpx);
	   SeedAna->Branch("svtxseedpy",&svtxseedpy);
	   SeedAna->Branch("svtxseedpz",&svtxseedpz);

	   SeedAna->Branch("svtxclusposx",&svtxclusposx);
	   SeedAna->Branch("svtxclusposy",&svtxclusposy);
	   SeedAna->Branch("svtxclusposz",&svtxclusposz);
	   */


	SeedAna->Branch("svtxcrossing",&svtxcrossing);

	SeedAna->Branch("svtxsiseedsize",&svtxsiseedsize);
	SeedAna->Branch("svtxtpcseedsize",&svtxtpcseedsize);

	SeedAna->Branch("svtxnmaps",&svtxnmaps);
	SeedAna->Branch("svtxnintt",&svtxnintt);

	SeedAna->Branch("svtxsiseedx",&svtxsiseedx);
	SeedAna->Branch("svtxsiseedy",&svtxsiseedy);
	SeedAna->Branch("svtxsiseedz",&svtxsiseedz);
	SeedAna->Branch("svtxsiseedpx",&svtxsiseedpx);
	SeedAna->Branch("svtxsiseedpy",&svtxsiseedpy);
	SeedAna->Branch("svtxsiseedpz",&svtxsiseedpz);
	SeedAna->Branch("svtxsiseedcharge",&svtxsiseedcharge);


	SeedAna->Branch("svtxsiseedphi",&svtxsiseedphi);
	SeedAna->Branch("svtxsiseedeta",&svtxsiseedeta);

	SeedAna->Branch("svtxsiclusposx",&svtxsiclusposx);
	SeedAna->Branch("svtxsiclusposy",&svtxsiclusposy);
	SeedAna->Branch("svtxsiclusposz",&svtxsiclusposz);

	SeedAna->Branch("svtxntpc",&svtxntpc);

	SeedAna->Branch("svtxtpcseedid",&svtxtpcseedid);
	SeedAna->Branch("svtxtpcseedx",&svtxtpcseedx);
	SeedAna->Branch("svtxtpcseedy",&svtxtpcseedy);
	SeedAna->Branch("svtxtpcseedz",&svtxtpcseedz);
	SeedAna->Branch("svtxtpcseedpx",&svtxtpcseedpx);
	SeedAna->Branch("svtxtpcseedpy",&svtxtpcseedpy);
	SeedAna->Branch("svtxtpcseedpz",&svtxtpcseedpz);
	SeedAna->Branch("svtxtpcseedcharge",&svtxtpcseedcharge);


	SeedAna->Branch("svtxtpcseedphi",&svtxtpcseedphi);
	SeedAna->Branch("svtxtpcseedeta",&svtxtpcseedeta);


	SeedAna->Branch("svtxtpcclusposx",&svtxtpcclusposx);
	SeedAna->Branch("svtxtpcclusposy",&svtxtpcclusposy);
	SeedAna->Branch("svtxtpcclusposz",&svtxtpcclusposz);


	SeedAna->Branch("svtxtracketa",&svtxtracketa);
	SeedAna->Branch("svtxtrackphi",&svtxtrackphi);
	SeedAna->Branch("svtxtrackpt",&svtxtrackpt);
	SeedAna->Branch("svtxtrackpx",&svtxtrackpx);
	SeedAna->Branch("svtxtrackpy",&svtxtrackpy);
	SeedAna->Branch("svtxtrackpz",&svtxtrackpz);
	SeedAna->Branch("svtxtrackx",&svtxtrackx);
	SeedAna->Branch("svtxtracky",&svtxtracky);
	SeedAna->Branch("svtxtrackz",&svtxtrackz);
	SeedAna->Branch("svtxtrackcharge",&svtxtrackcharge);	
	SeedAna->Branch("svtxtrackchisq",&svtxtrackchisq);
	SeedAna->Branch("svtxtrackndf",&svtxtrackndf);




	geantGeom_MVTX =  findNode::getClass<PHG4CylinderGeomContainer>(topNode, "CYLINDERGEOM_MVTX");
	actsGeom = findNode::getClass<ActsGeometry>(topNode, "ActsGeometry");
	topNode->print();

	event = 0;

	std::cout << "I am using my own module ok" << std::endl; 	

	return Fun4AllReturnCodes::EVENT_OK;
}

//____________________________________________________________________________..
int SiTPCMatchAna::process_event(PHCompositeNode *topNode)
{
	std::cout << "Using SiTPC Ana Method" << std::endl; 	



	//	topNode->print();
	//	auto trackmap = findNode::getClass<SvtxTrackSeed_v1>(topNode, "SvtxTrackSeed_v1");

	auto _si_seeds = findNode::getClass<TrackSeedContainer>(topNode, "SiliconTrackSeedContainer");
	auto _tpc_seeds = findNode::getClass<TrackSeedContainer>(topNode, "TpcTrackSeedContainer");
	auto _svtx_seeds = findNode::getClass<TrackSeedContainer>(topNode, "SvtxTrackSeedContainer");

	auto clustermap = findNode::getClass<TrkrClusterContainer>(topNode, "TRKR_CLUSTER");
	auto geometry = findNode::getClass<ActsGeometry>(topNode, "ActsGeometry");
	auto _trackmap = findNode::getClass<SvtxTrackMap>(topNode, "SvtxTrackMap");
	//	auto _vertexmap = findNode::getClass<SvtxVertexMap>(topNode, "SvtxVertexMap");

	auto _laserEventInfo = findNode::getClass<LaserEventInfo>(topNode, "LaserEventInfo"); //Addint Laser Event Info


	IsLaserEvt = _laserEventInfo->isLaserEvent();

	if (!_trackmap)
	{
		std::cout << " SvtxTrackMap node not found on node tree"   <<  std::endl;
		return Fun4AllReturnCodes::ABORTEVENT;

	}

	TotalClus = 0;
	TotalSiSeedClus = 0;
	TotalTPCSeedClus = 0;

	//TotalClusAssoc = 0;
	TotalSiSeedClusAssoc = 0;
	TotalTPCSeedClusAssoc = 0;

	for (auto &hsk : clustermap->getHitSetKeys(TrkrDefs::TrkrId::mvtxId))
	{
		auto range = clustermap->getClusters(hsk);
		for (auto iter = range.first; iter != range.second; ++iter)
		{
			TotalSiSeedClus++;
		}
	}

	for (auto &hsk : clustermap->getHitSetKeys(TrkrDefs::TrkrId::inttId))
	{
		auto range = clustermap->getClusters(hsk);
		for (auto iter = range.first; iter != range.second; ++iter)
		{
			TotalSiSeedClus++;
		}
	}


	for (auto &hsk : clustermap->getHitSetKeys(TrkrDefs::TrkrId::tpcId))
	{

		auto range = clustermap->getClusters(hsk);
		for (auto iter = range.first; iter != range.second; ++iter)
		{
			TotalTPCSeedClus++;
		}
	}


	//	for (TrackSeedContainer::ConstIter siseed_iter = siseed_beg; siseed_iter != siseed_end; ++siseed_iter){  //Looping through tracklets


	if (!_si_seeds)
	{
		std::cerr << PHWHERE << " ERROR: Can't find SiliconTrackSeedContainer" << std::endl;

	}

	if (!_tpc_seeds)
	{
		std::cerr << PHWHERE << " ERROR: Can't find TPCTrackSeedContainer" << std::endl;

	}

	if (!_svtx_seeds)
	{
		std::cerr << PHWHERE << " ERROR: Can't find SvtxTrackSeedContainer" << std::endl;

	}



	//	siseedsize = _si_seeds->size();
	//	tpcseedsize = _tpc_seeds->size();

	//	svtxseedsize = _svtx_seeds->size();



	//	std::cout << "svtxseedsize = " << svtxseedsize << std::endl;

	//	std::cout << "svtxseedmapsize = " << svtxseedmapsize << std::endl;


	//	TrackSeedContainer::ConstIter siseed_beg = _si_seeds->begin();
	//	TrackSeedContainer::ConstIter siseed_end = _si_seeds->end();

	TotalSiSeedZero = 0;

	siseedsize = 0;
	tpcseedsize = 0;
	//svtxseedsize = 0;

	for (auto siseed_iter = _si_seeds->begin(); siseed_iter != _si_seeds->end(); ++siseed_iter){ //preferred loop

		//	for (const auto &siseed : *_si_seeds)
		//	{
		int id = _si_seeds->index(siseed_iter);

		TrackSeed *siseed = _si_seeds->get(id);
		if (!siseed)
		{
			//std::cout << "No Si Seed" << std::endl;
			continue;
		}
		if(std::isnan(siseed->get_x()) || std::isnan(siseed->get_y()) || std::isnan(siseed->get_z())) continue;

		siseedsize++;

		siseedid.push_back(id);

		nmapscount = 0;
		ninttcount = 0;


		siseedx.push_back(siseed->get_x());
		siseedy.push_back(siseed->get_y());
		siseedz.push_back(siseed->get_z());

		siseedpx.push_back(siseed->get_px());
		siseedpy.push_back(siseed->get_py());
		siseedpz.push_back(siseed->get_pz());

		crossing.push_back(siseed->get_crossing());
		siseedcharge.push_back(siseed->get_charge());
		siseedphi.push_back(siseed->get_phi());
		siseedeta.push_back(siseed->get_eta());

		if(siseed->get_crossing() == 0) TotalSiSeedZero++;

		TrackSeed::ClusterKeyIter cluskeybegin = siseed->begin_cluster_keys();
		TrackSeed::ClusterKeyIter cluskeyend = siseed->end_cluster_keys();


		std::vector<int> INTTTimeBucketTemp;
		std::vector<float> siclusxtemp;
		std::vector<float> siclusytemp;
		std::vector<float> siclusztemp;

		for (TrackSeed::ClusterKeyIter cluskey = cluskeybegin; cluskey != cluskeyend; ++cluskey){ //looping through clusters


			TrkrCluster* cluster = clustermap->findCluster(*cluskey);
			Acts::Vector3 global = geometry->getGlobalPosition(*cluskey, cluster);  


			//	int INTTTimeBucket = 0;

			if(TrkrDefs::getTrkrId(*cluskey) == TrkrDefs::inttId){
				INTTTimeBucketTemp.push_back(InttDefs::getTimeBucketId(*cluskey));
				ninttcount++;
			}
			if(TrkrDefs::getTrkrId(*cluskey) == TrkrDefs::mvtxId){
				INTTTimeBucketTemp.push_back(-99999);

				nmapscount++;
			}





			float x = global[0];
			float y = global[1];
			float z = global[2];

			//		intttimebucketvec.push_back(INTTTimeBucketTemp);
			siclusxtemp.push_back(x);
			siclusytemp.push_back(y);
			siclusztemp.push_back(z);


		}

		//SiSeedAna->Fill();

		siclusposx.push_back(siclusxtemp);
		siclusposy.push_back(siclusytemp);
		siclusposz.push_back(siclusztemp);

		nmaps.push_back(nmapscount);
		nintt.push_back(ninttcount);
	
		TotalSiSeedClusAssoc = nmapscount + ninttcount;
	}




	for (auto tpcseed_iter = _tpc_seeds->begin(); tpcseed_iter != _tpc_seeds->end(); ++tpcseed_iter)
	{

		//for (const auto &tpcseed : *_tpc_seeds)
		//{

		int id = _tpc_seeds->index(tpcseed_iter);
		TrackSeed *tpcseed = _tpc_seeds->get(id);
		if (!tpcseed)
		{
			continue;
		}

		if(std::isnan(tpcseed->get_x()) || std::isnan(tpcseed->get_y()) || std::isnan(tpcseed->get_z())) continue;

		tpcseedid.push_back(id);

		tpcseedsize++;
		ntpccount = 0;



		tpcseedx.push_back(tpcseed->get_x());
		tpcseedy.push_back(tpcseed->get_y());
		tpcseedz.push_back(tpcseed->get_z());

		tpcseedpx.push_back(tpcseed->get_px());
		tpcseedpy.push_back(tpcseed->get_py());
		tpcseedpz.push_back(tpcseed->get_pz());
		tpcseedcharge.push_back(tpcseed->get_charge());
		tpcseedphi.push_back(tpcseed->get_phi());
		tpcseedeta.push_back(tpcseed->get_eta());


		TrackSeed::ClusterKeyIter cluskeybegin = tpcseed->begin_cluster_keys();
		TrackSeed::ClusterKeyIter cluskeyend = tpcseed->end_cluster_keys();


		std::vector<float> tpcclusxtemp;
		std::vector<float> tpcclusytemp;
		std::vector<float> tpcclusztemp;

		for (TrackSeed::ClusterKeyIter cluskey = cluskeybegin; cluskey != cluskeyend; ++cluskey){ //looping through clusters

			TrkrCluster* cluster = clustermap->findCluster(*cluskey);
			Acts::Vector3 global = geometry->getGlobalPosition(*cluskey, cluster);  




			float x = global[0];
			float y = global[1];
			float z = global[2];


			tpcclusxtemp.push_back(x);
			tpcclusytemp.push_back(y);
			tpcclusztemp.push_back(z);



			ntpccount++;

		}
		/*
		   TPCSeedAna->Fill();
		   */

		ntpc.push_back(ntpccount);

		tpcclusposx.push_back(tpcclusxtemp);
		tpcclusposy.push_back(tpcclusytemp);
		tpcclusposz.push_back(tpcclusztemp);

	
		TotalTPCSeedClusAssoc = ntpccount;
	}

	//	std::cout << "Now I use svtx track matched and get seed" << std::endl;

	//	std::cout << " _trackmap->size() = " <<  _trackmap->size()  << std::endl;

	//	for (auto svtxseed_iter = _svtx_seeds->begin(); svtxseed_iter != _svtx_seeds->end(); ++svtxseed_iter)
	//	{

	TotalTPCSeed = tpcseedx.size();
	TotalSiSeed = siseedx.size();



	TotalMatchedSeed = 0;
	TotalMatchedSeedZero = 0;

	//	std::cout << "Pass 0" << std::endl;

	for (auto& iter : *_trackmap)
	{
		//std::cout << "Pass 1" << std::endl;
		//cout << itrack << " of " << _trackmap->size();
		SvtxTrack* track = iter.second;
		//std::cout << "Pass 2" << std::endl;

		//std::cout << "Inside svtx seed" << std::endl;	
		nsvtxcount = 0;

		//std::cout << "Pass 3" << std::endl;

		//int id = 0;

		//		int id = _svtx_seeds->index(svtxseed_iter);
		if (!track)
		{
			std::cout << "No Svtx Track?" << std::endl;
			continue;
		}
		//svtxseed = _svtx_seeds->get(id);

		//	svtxseedid.push_back(id);
		/*
		   std::cout << "------------ Print Out Why - Before All ------------" << std::endl;


		   std::cout << "track->get_charge() = " << track->get_charge() << "   track->get_eta() = " << track->get_eta() << "   track->get_px() = " << track->get_px()  << "   track->get_chisq() = " << track->get_chisq() << "   track->get_ndf() = " << track->get_ndf() << std::endl;


		   std::cout << "------------ Done ------------" << std::endl;
		   */
		//	std::cout << "svtxseed->get_x() = " << svtxseed->get_x() << std::endl;

		TotalMatchedSeed++;
		//	if(std::isnan(siseed->get_x()) || std::isnan(siseed->get_y()) || std::isnan(siseed->get_z())) continue;
		TrackSeed* siseed = track->get_silicon_seed();

		//std::cout << "Pass 4" << std::endl;

		//		int id = _si_seeds->index(siseed_iter);

		//		TrackSeed *siseed = _si_seeds->get(id);
		if (!siseed)
		{
			//			std::cout << "No Si Seed" << std::endl;
			continue;
		}
		//		if(std::isnan(siseed->get_x()) || std::isnan(siseed->get_y()) || std::isnan(siseed->get_z())) continue;

		siseedsize++;

		//siseedid.push_back(id);

		nmapscount = 0;
		ninttcount = 0;


		svtxsiseedx.push_back(siseed->get_x());
		svtxsiseedy.push_back(siseed->get_y());
		svtxsiseedz.push_back(siseed->get_z());

		svtxsiseedpx.push_back(siseed->get_px());
		svtxsiseedpy.push_back(siseed->get_py());
		svtxsiseedpz.push_back(siseed->get_pz());

		svtxcrossing.push_back(siseed->get_crossing());
		//std::cout << "Pass 5" << std::endl;

		svtxsiseedcharge.push_back(siseed->get_charge());	
		svtxsiseedphi.push_back(siseed->get_phi());
		svtxsiseedeta.push_back(siseed->get_eta());

		if(siseed->get_crossing() == 0) TotalMatchedSeedZero++;

		TrackSeed::ClusterKeyIter cluskeybegin = siseed->begin_cluster_keys();
		TrackSeed::ClusterKeyIter cluskeyend = siseed->end_cluster_keys();


		std::vector<int> svtxINTTTimeBucketTemp;
		std::vector<float> svtxsiclusxtemp;
		std::vector<float> svtxsiclusytemp;
		std::vector<float> svtxsiclusztemp;
		//std::cout << "Pass 6" << std::endl;

		for (TrackSeed::ClusterKeyIter cluskey = cluskeybegin; cluskey != cluskeyend; ++cluskey){ //looping through clusters


			TrkrCluster* cluster = clustermap->findCluster(*cluskey);
			Acts::Vector3 global = geometry->getGlobalPosition(*cluskey, cluster);  


			//	int INTTTimeBucket = 0;

			if(TrkrDefs::getTrkrId(*cluskey) == TrkrDefs::inttId){
				svtxINTTTimeBucketTemp.push_back(InttDefs::getTimeBucketId(*cluskey));
				ninttcount++;
			}
			if(TrkrDefs::getTrkrId(*cluskey) == TrkrDefs::mvtxId){
				svtxINTTTimeBucketTemp.push_back(-99999);

				nmapscount++;
			}





			float x = global[0];
			float y = global[1];
			float z = global[2];

			//		intttimebucketvec.push_back(INTTTimeBucketTemp);
			svtxsiclusxtemp.push_back(x);
			svtxsiclusytemp.push_back(y);
			svtxsiclusztemp.push_back(z);


		}
		//		std::cout << "Pass 7" << std::endl;

		//SiSeedAna->Fill();

		svtxsiclusposx.push_back(svtxsiclusxtemp);
		svtxsiclusposy.push_back(svtxsiclusytemp);
		svtxsiclusposz.push_back(svtxsiclusztemp);

		svtxnmaps.push_back(nmapscount);
		svtxnintt.push_back(ninttcount);






		//	for (auto tpcseed_iter = _tpc_seeds->begin(); tpcseed_iter != _tpc_seeds->end(); ++tpcseed_iter)
		//	{

		TrackSeed* tpcseed = track->get_tpc_seed();

		//TotalMatchedTPCSeed++;

		//	int id = _tpc_seeds->index(tpcseed_iter);
		//	TrackSeed *tpcseed = _tpc_seeds->get(id);
		//	tpcseedid.push_back(id);
		//		if(std::isnan(tpcseed->get_x()) || std::isnan(tpcseed->get_y()) || std::isnan(tpcseed->get_z())) continue;


		if (!tpcseed)
		{

			//			std::cout << "No TPC Seed" << std::endl;
			continue;
		}



		svtxtpcseedsize++;
		ntpccount = 0;



		svtxtpcseedx.push_back(tpcseed->get_x());
		svtxtpcseedy.push_back(tpcseed->get_y());
		svtxtpcseedz.push_back(tpcseed->get_z());

		svtxtpcseedpx.push_back(tpcseed->get_px());
		svtxtpcseedpy.push_back(tpcseed->get_py());
		svtxtpcseedpz.push_back(tpcseed->get_pz());
		svtxtpcseedcharge.push_back(tpcseed->get_charge());
		svtxtpcseedphi.push_back(tpcseed->get_phi());
		svtxtpcseedeta.push_back(tpcseed->get_eta());


		TrackSeed::ClusterKeyIter tpccluskeybegin = tpcseed->begin_cluster_keys();
		TrackSeed::ClusterKeyIter tpccluskeyend = tpcseed->end_cluster_keys();


		std::vector<float> svtxtpcclusxtemp;
		std::vector<float> svtxtpcclusytemp;
		std::vector<float> svtxtpcclusztemp;

		for (TrackSeed::ClusterKeyIter cluskey = tpccluskeybegin; cluskey != tpccluskeyend; ++cluskey){ //looping through clusters

			TrkrCluster* cluster = clustermap->findCluster(*cluskey);
			Acts::Vector3 global = geometry->getGlobalPosition(*cluskey, cluster);  




			float x = global[0];
			float y = global[1];
			float z = global[2];


			svtxtpcclusxtemp.push_back(x);
			svtxtpcclusytemp.push_back(y);
			svtxtpcclusztemp.push_back(z);



			ntpccount++;

		}
		/*
		   TPCSeedAna->Fill();
		   */

		svtxntpc.push_back(ntpccount);

		svtxtpcclusposx.push_back(svtxtpcclusxtemp);
		svtxtpcclusposy.push_back(svtxtpcclusytemp);
		svtxtpcclusposz.push_back(svtxtpcclusztemp);


		svtxtrackcharge.push_back(track->get_charge());
		svtxtracketa.push_back(track->get_eta());
		svtxtrackphi.push_back(track->get_phi());
		svtxtrackpt.push_back(track->get_pt());
		svtxtrackpx.push_back(track->get_px());
		svtxtrackpy.push_back(track->get_py());
		svtxtrackpz.push_back(track->get_pz());
		svtxtrackx.push_back(track->get_x());
		svtxtracky.push_back(track->get_y());
		svtxtrackz.push_back(track->get_z());

		svtxtrackndf.push_back(track->get_ndf());
		svtxtrackchisq.push_back(track->get_chisq());



	}





	EvtAna->Fill();


	SeedAna->Fill();
	crossing.clear();

	siseedid.clear();
	siseedx.clear();
	siseedy.clear();
	siseedz.clear();
	siseedpx.clear();
	siseedpy.clear();
	siseedpz.clear();
	siseedcharge.clear();

	siseedphi.clear();
	siseedeta.clear();


	tpcseedid.clear();
	tpcseedx.clear();
	tpcseedy.clear();
	tpcseedz.clear();
	tpcseedpx.clear();
	tpcseedpy.clear();
	tpcseedpz.clear();
	tpcseedcharge.clear();


	tpcseedphi.clear();
	tpcseedeta.clear();


	siclusposx.clear();
	siclusposy.clear();
	siclusposz.clear();
	intttimebucketvec.clear();


	tpcclusposx.clear();
	tpcclusposy.clear();
	tpcclusposz.clear();


	nmaps.clear();
	nintt.clear();
	ntpc.clear();
	//	nsvtx.clear();


	svtxcrossing.clear();

	//	svtxsiseedid.clear();
	svtxsiseedx.clear();
	svtxsiseedy.clear();
	svtxsiseedz.clear();
	svtxsiseedpx.clear();
	svtxsiseedpy.clear();
	svtxsiseedpz.clear();
	svtxsiseedcharge.clear();
	svtxsiseedphi.clear();
	svtxsiseedeta.clear();


	svtxsiclusposx.clear();
	svtxsiclusposy.clear();
	svtxsiclusposz.clear();


	//	svtxtpcseedid.clear();
	svtxtpcseedx.clear();
	svtxtpcseedy.clear();
	svtxtpcseedz.clear();
	svtxtpcseedpx.clear();
	svtxtpcseedpy.clear();
	svtxtpcseedpz.clear();
	svtxtpcseedcharge.clear();

	svtxnmaps.clear();
	svtxnintt.clear();
	svtxntpc.clear();

	svtxtpcclusposx.clear();
	svtxtpcclusposy.clear();
	svtxtpcclusposz.clear();

	svtxtpcseedeta.clear();
	svtxtpcseedphi.clear();



	svtxtracketa.clear();
	svtxtrackphi.clear();
	svtxtrackpt.clear();
	svtxtrackpx.clear();
	svtxtrackpy.clear();
	svtxtrackpz.clear();
	svtxtrackx.clear();
	svtxtracky.clear();
	svtxtrackz.clear();
	svtxtrackcharge.clear();
	svtxtrackndf.clear();
	svtxtrackchisq.clear();


	//EvtAna->Fill();
	event++;


	std::cout << "Finished with Svtx" << std::endl;

	return Fun4AllReturnCodes::EVENT_OK;
	}

	//____________________________________________________________________________..
	int SiTPCMatchAna::EndRun()
	{

		return Fun4AllReturnCodes::EVENT_OK;
	}

	//____________________________________________________________________________..
	int SiTPCMatchAna::End(PHCompositeNode * /*unused*/) { 

		std::cout << "ending" << std::endl;


		foutEvt->cd();
		EvtAna->Write();
		foutEvt->Close();


		fout->cd();
		//EvtAna->Write();
		SeedAna->Write();
		//	TPCSeedAna->Write();

		fout->Close();

		//	std::cout  << "Total Tracklets: " << TotalTracklets << "   TwoClusTracklets: " << TwoClusTracklets << std::endl;
		return Fun4AllReturnCodes::EVENT_OK; 
	}




