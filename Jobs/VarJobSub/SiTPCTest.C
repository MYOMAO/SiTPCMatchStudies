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
#include <Trkr_RecoInit.C>
#include <Trkr_Clustering.C>
#include <Trkr_Reco.C>

#include <ffamodules/CDBInterface.h>
#include <fun4all/Fun4AllDstInputManager.h>
#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllOutputManager.h>
#include <fun4all/Fun4AllRunNodeInputManager.h>
#include <fun4all/Fun4AllServer.h>

#include <eventdisplay/TrackerEventDisplay.h>
#include <phool/recoConsts.h>
#include <trackingqa/InttClusterQA.h>

#include <trackingqa/MicromegasClusterQA.h>

#include <trackingqa/MvtxClusterQA.h>

#include <trackingdiagnostics/TrackResiduals.h>
#include <trackingdiagnostics/TrkrNtuplizer.h>
#include <trackingqa/TpcClusterQA.h>
#include <trackreco/AzimuthalSeeder.h>

#include "/direct/sphenix+tg+tg01/hf/zshi/ClusMatchAll/coresoftware/offline/QA/SiTPCMatching/SiTPCMatchAna.h"


#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libffamodules.so)
R__LOAD_LIBRARY(libmvtx.so)
R__LOAD_LIBRARY(libintt.so)
R__LOAD_LIBRARY(libtpc.so)
R__LOAD_LIBRARY(libsitpcmatchana.so)

void SiTPCTest()
{

  
  //std::string infile = "/direct/sphenix+tg+tg01/hf/zshi/SeedMatchFileLowIntensity/DST/DSTSeedSofar_" + std::to_string(Run) + "_" + std::to_string(Seg) + ".root";
	
  std::string infile = "DSTSeedSofar.root";
  auto se = Fun4AllServer::instance();
  se->Verbosity(2);
  auto rc = recoConsts::instance();
//  rc->set_IntFlag("RUNNUMBER", 47502);

  Enable::CDB = true;
  rc->set_StringFlag("CDB_GLOBALTAG", "ProdA_2024");
  rc->set_uint64Flag("TIMESTAMP", 6);


  //ACTSGEOM::tpotMisalignment = 100.;

  std::string geofile = CDBInterface::instance()->getUrl("Tracking_Geometry");
  Fun4AllRunNodeInputManager *ingeo = new Fun4AllRunNodeInputManager("GeoIn");
  ingeo->AddFile(geofile);
  se->registerInputManager(ingeo);

  G4MAGNET::magfield_rescale = 1;

  std::cout << "Inite Bro -> Svtx input ZZ will improve" << std::endl;
 // Tracking_Reco();

  ACTSGEOM::ActsGeomInit();

  ACTSGEOM::mvtxMisalignment = 100;
  ACTSGEOM::inttMisalignment = 100.;

  auto hitsin = new Fun4AllDstInputManager("InputManager");
//  Fun4AllInputManager *infile = new Fun4AllDstInputManager("Infile");
  hitsin->fileopen(infile);
  se->registerInputManager(hitsin);


  SiTPCMatchAna * SiTPCTest = new SiTPCMatchAna("SiTPCTest");

  se->registerSubsystem(SiTPCTest);
  

  int nEvents = -1;

  se->run(nEvents);
  se->End();
  se->PrintTimer();

  delete se;
  std::cout << "Finished" << std::endl;
  gSystem->Exit(0);
}
