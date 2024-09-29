// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef MVTXRAWHITQA_H
#define MVTXRAWHITQA_H

#include <fun4all/SubsysReco.h>
#include <trackbase/TrkrDefs.h>

#include <ffarawobjects/MvtxRawHitContainer.h>
#include <ffarawobjects/MvtxRawHit.h>

#include <TH1.h>
#include <TH2.h>
#include <TProfile2D.h>
#include <TH3.h>

#include <string>
#include <vector>

using namespace std;

class SiTPCMatchAna : public SubsysReco
{
 public:
  SiTPCMatchAna(const std::string& name = "SiTPCMatchAna");

  ~SiTPCMatchAna() override = default;

  int InitRun(PHCompositeNode* topNode) override;
  int process_event(PHCompositeNode* topNode) override;
  int EndRun();

  int End(PHCompositeNode *topNode) override;
  
 private:

  PHG4CylinderGeomContainer * geantGeom_MVTX;
  ActsGeometry * actsGeom;
  int NMVTXLayer = 3;	
  
  TH1D * NHitStat; 
  TFile * fout;
  TFile * foutEvt;


//  TFile * fout = NULL;  
   //TTree * MissingChip = NULL;
  int layerindex;
  int staveindex;
  int chipindex;
  int event;
  int TrackletID;
  float SiSeedEta;
  float SiSeedPt;


  TTree * EvtAna;
  //TTree * SiSeedAna = NULL;
  //TTree * TPCSeedAna = NULL;
  TTree * SeedAna;

  int TotalTracklets;
  int TwoClusTracklets;

  int TotalClus;
  int TotalClusAssoc;

  int nmapscount;
  int ninttcount;
  int ntpccount;
  int nsvtxcount;

  vector<int> nmaps;
  vector<int> nintt;
  vector<int> ntpc;
//  vector<int> nsvtx;


  int siseedsize;
  int tpcseedsize;
 // int svtxseedsize;

  vector<int> siseedid;
  vector<int> tpcseedid;
  vector<int> crossing;

  vector<float> siseedx;
  vector<float> siseedy;
  vector<float> siseedz;

  vector<float> siseedpx;
  vector<float> siseedpy;
  vector<float> siseedpz;

  vector<float> siseedphi;
  vector<float> siseedeta;


  vector<float> tpcseedx;
  vector<float> tpcseedy;
  vector<float> tpcseedz;

  vector<float> tpcseedpx;
  vector<float> tpcseedpy;
  vector<float> tpcseedpz;

  
  vector<float> tpcseedphi;
  vector<float> tpcseedeta;


  vector<int> svtxseedid;
  vector<int> svtxcrossing;

  vector<float> svtxsiseedx;
  vector<float> svtxsiseedy;
  vector<float> svtxsiseedz;

  vector<float> svtxsiseedpx;
  vector<float> svtxsiseedpy;
  vector<float> svtxsiseedpz;


  
  vector<float> svtxsiseedphi;
  vector<float> svtxsiseedeta;


  vector<int> svtxtpcseedid;
  vector<float> svtxtpcseedx;
  vector<float> svtxtpcseedy;
  vector<float> svtxtpcseedz;

  vector<float> svtxtpcseedpx;
  vector<float> svtxtpcseedpy;
  vector<float> svtxtpcseedpz;

  
  vector<float> svtxtpcseedphi;
  vector<float> svtxtpcseedeta;


  vector<int> svtxnmaps;
  vector<int> svtxnintt;
  vector<int> svtxntpc;


  //Charge
  vector<float> siseedcharge;
  vector<float> tpcseedcharge;
 
  vector<float> svtxsiseedcharge;
  vector<float> svtxtpcseedcharge;



  int svtxsiseedsize;
  int svtxtpcseedsize;

	
  bool IsLaserEvt;

  float chipphi;
  float chipz;

  float chisq;
  int ndf;
  float quality;
/*

  vector<float> tpcseedx;
  vector<float> tpcseedy;
  vector<float> tpcseedz;

  vector<float> tpcseedpx;
  vector<float> tpcseedpy;
  vector<float> t#include <stdlib.h>pcseedpz;
*/
//  vector<int> VertexCrossing;




  vector<vector<float>> siclusposx;
  vector<vector<float>> siclusposy;
  vector<vector<float>> siclusposz;

  vector<vector<int>> intttimebucketvec;



  vector<vector<float>> tpcclusposx;
  vector<vector<float>> tpcclusposy;
  vector<vector<float>> tpcclusposz;


  vector<vector<float>> svtxsiclusposx;
  vector<vector<float>> svtxsiclusposy;
  vector<vector<float>> svtxsiclusposz;

  vector<vector<int>> svtxintttimebucketvec;



  vector<vector<float>> svtxtpcclusposx;
  vector<vector<float>> svtxtpcclusposy;
  vector<vector<float>> svtxtpcclusposz;


  vector<float> svtxtrackphi;
  vector<float> svtxtracketa;  
  vector<float> svtxtrackpt;
  vector<float> svtxtrackpx;
  vector<float> svtxtrackpy;
  vector<float> svtxtrackpz;
  vector<float> svtxtrackx;
  vector<float> svtxtracky;
  vector<float> svtxtrackz;

  vector<int> svtxtrackcharge;
  vector<int> svtxtrackndf;
  vector<float> svtxtrackchisq;
  
/*
  int Ntracks;
  int Vx;
  int Vy;
  int Vz;
  int m_nvertices;

  double x_miss;
  double y_miss;
  double z_miss;
	
  int layerfired;
  int stavefired;
  int chipfired;
  float chipphifired;
  float chipzfired;

  int vtxId;
 
  float vtxX;
  float vtxY;
  float vtxZ;

  int nmaps_uniqlay;
  int intt_uniqlay;
*/
  int mvtxclusmax = 4;
  int inttclusmax = 10;
	

  int TotalSiSeedClus;
  int TotalTPCSeedClus;

  int TotalSiSeedClusAssoc;
  int TotalTPCSeedClusAssoc;

  int TotalSiSeed;
  int TotalTPCSeed;


  int TotalSiSeedZero;
  int TotalTPCSeedZero;


  int TotalMatchedSeed;
  int TotalMatchedSeedZero;


  //  std::vector<int> ClusIdVec; 
  //std::vector<uint64_t> ClusKeyVec; 

};

#endif  // MVTXRAWHITQA_H
