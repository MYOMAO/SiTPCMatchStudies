#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TH2.h"
#include "TAxis.h"
#include "TF1.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TVector2.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TRandom.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
//#include "/usr/local/include/eigen3/Eigen/Dense"


using namespace std;

using std::cout;
using std::endl;

void CheckCorr(){

	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();


	c->SetLeftMargin(0.14);


	TString infiles = {"/Users/zhaozhongshi/Desktop/TempDownload/SiTPCMatchFiles/SeedAna_Svtx.root"};
	TFile * fin = new TFile(infiles.Data());
	fin->cd();

	int NRun = 3;
	int NSeg = 36;
	int IncTPCSeed = 0;
	int IncSiSeed = 0;
	int IncMatchedTrack = 0;

	int NEventZC = 0;

	int IncSiSeedZC = 0;
	int IncMatchedTrackZC = 0;

	int TotalReuseSiSeed = 0;
	int TotalReuseTPCSeed = 0;

	int TotalReuseSiSeedZC = 0;
	int TotalReuseTPCSeedZC = 0;


	int event;
	int siseedsize;
	int tpcseedsize;
	std::vector<int> * crossing = 0;
	std::vector<float> * siseedx = 0;
	std::vector<float> * siseedy = 0;
	std::vector<float> * siseedz = 0;

	std::vector<float> * tpcseedx = 0;
	std::vector<float> * tpcseedy = 0;
	std::vector<float> * tpcseedz = 0;

	std::vector<float> * siseedpx = 0;
	std::vector<float> * siseedpy = 0;
	std::vector<float> * siseedpz = 0;

	std::vector<float> * tpcseedpx = 0;
	std::vector<float> * tpcseedpy = 0;
	std::vector<float> * tpcseedpz = 0;

	int svtxsiseedsize;
	int svtxtpcseedsize;
	std::vector<int> * svtxcrossing = 0;
	std::vector<float> * svtxsiseedx = 0;
	std::vector<float> * svtxsiseedy = 0;
	std::vector<float> * svtxsiseedz = 0;

	std::vector<float> * svtxtpcseedx = 0;
	std::vector<float> * svtxtpcseedy = 0;
	std::vector<float> * svtxtpcseedz = 0;

	std::vector<float> * svtxsiseedpx = 0;
	std::vector<float> * svtxsiseedpy = 0;
	std::vector<float> * svtxsiseedpz = 0;

	std::vector<float> * svtxtpcseedpx = 0;
	std::vector<float> * svtxtpcseedpy = 0;
	std::vector<float> * svtxtpcseedpz = 0;

	std::vector<float> * siseedcharge = 0;
	std::vector<float> * tpcseedcharge = 0;

	std::vector<float> * svtxsiseedcharge = 0;
	std::vector<float> * svtxtpcseedcharge = 0;


	std::vector<int> * ntpc = 0;
	std::vector<int> * nmaps = 0;
	std::vector<int> * nintt = 0;


	TTree * SeedAna = (TTree *) fin->Get("SeedAna");
	SeedAna->SetBranchAddress("event",&event);

	SeedAna->SetBranchAddress("crossing",&crossing);
	SeedAna->SetBranchAddress("siseedx",&siseedx);
	SeedAna->SetBranchAddress("siseedy",&siseedy);
	SeedAna->SetBranchAddress("siseedz",&siseedz);

	SeedAna->SetBranchAddress("tpcseedx",&tpcseedx);
	SeedAna->SetBranchAddress("tpcseedy",&tpcseedy);
	SeedAna->SetBranchAddress("tpcseedz",&tpcseedz);

	SeedAna->SetBranchAddress("siseedpx",&siseedpx);
	SeedAna->SetBranchAddress("siseedpy",&siseedpy);
	SeedAna->SetBranchAddress("siseedpz",&siseedpz);

	SeedAna->SetBranchAddress("tpcseedpx",&tpcseedpx);
	SeedAna->SetBranchAddress("tpcseedpy",&tpcseedpy);
	SeedAna->SetBranchAddress("tpcseedpz",&tpcseedpz);

	SeedAna->SetBranchAddress("siseedcharge",&siseedcharge);
	SeedAna->SetBranchAddress("tpcseedcharge",&tpcseedcharge);


	SeedAna->SetBranchAddress("svtxsiseedcharge",&svtxsiseedcharge);
	SeedAna->SetBranchAddress("svtxtpcseedcharge",&svtxtpcseedcharge);



	SeedAna->SetBranchAddress("svtxcrossing",&svtxcrossing);
	SeedAna->SetBranchAddress("svtxsiseedx",&svtxsiseedx);
	SeedAna->SetBranchAddress("svtxsiseedy",&svtxsiseedy);
	SeedAna->SetBranchAddress("svtxsiseedz",&svtxsiseedz);

	SeedAna->SetBranchAddress("svtxtpcseedx",&svtxtpcseedx);
	SeedAna->SetBranchAddress("svtxtpcseedy",&svtxtpcseedy);
	SeedAna->SetBranchAddress("svtxtpcseedz",&svtxtpcseedz);

	SeedAna->SetBranchAddress("svtxsiseedpx",&svtxsiseedpx);
	SeedAna->SetBranchAddress("svtxsiseedpy",&svtxsiseedpy);
	SeedAna->SetBranchAddress("svtxsiseedpz",&svtxsiseedpz);

	SeedAna->SetBranchAddress("svtxtpcseedpx",&svtxtpcseedpx);
	SeedAna->SetBranchAddress("svtxtpcseedpy",&svtxtpcseedpy);
	SeedAna->SetBranchAddress("svtxtpcseedpz",&svtxtpcseedpz);


	SeedAna->SetBranchAddress("ntpc",&ntpc);
	SeedAna->SetBranchAddress("nmaps",&nmaps);
	SeedAna->SetBranchAddress("nintt",&nintt);


	TH2D * MVTXINTTCorr = new TH2D("MVTXINTTCorr","",50,2,100,50,2,50);
	MVTXINTTCorr->GetXaxis()->SetTitle("Number of MVTX Clusters");
	MVTXINTTCorr->GetYaxis()->SetTitle("Number of INTT Clusters");
	MVTXINTTCorr->GetXaxis()->CenterTitle();
	MVTXINTTCorr->GetYaxis()->CenterTitle();


	TH2D * MVTXINTTCorrZC = new TH2D("MVTXINTTCorrZC","",50,2,100,50,2,50);
	MVTXINTTCorrZC->GetXaxis()->SetTitle("Number of MVTX Clusters");
	MVTXINTTCorrZC->GetYaxis()->SetTitle("Number of INTT Clusters");
	MVTXINTTCorrZC->GetXaxis()->CenterTitle();
	MVTXINTTCorrZC->GetYaxis()->CenterTitle();


	int NEvent = SeedAna->GetEntries();


	int NMVTXTotal = 0;
	int NINTTTotal = 0;
	int NTPCTotal = 0;

	int NMVTXTotalZC = 0;
	int NINTTTotalZC = 0;
	int NTPCTotalZC = 0;

	for(int i = 0; i < NEvent; i++){
	
		if(i%100==0) cout << "Now Working on Event: " << i << "   Out of Total Event: " << NEvent << endl;

		SeedAna->GetEntry(i);
		siseedsize = siseedx->size();
		tpcseedsize = tpcseedy->size();

		int siseedsizezc = 0;
		//	int tpcseedsizezc = 0;

		int NZC = 0;


		//		cout << "siseedx->size() = " << siseedx->size()  << "      siseedy->size() = " << siseedy->size() <<  "     siseedz->size() = " << siseedz->size()  << endl;
		//		cout << "tpcseedx->size() = " << tpcseedx->size()  << "      tpcseedy->size() = " << tpcseedy->size() <<  "     tpcseedz->size() = " << tpcseedz->size()  << endl;

		IncSiSeed = IncSiSeed + siseedsize;
		IncTPCSeed = IncTPCSeed + tpcseedsize;

		for(int j = 0; j < siseedsize; j++){

			if(crossing->at(j) == 0){

				siseedsizezc++;

			}
		}
		IncSiSeedZC = IncSiSeedZC + siseedsizezc;


		NMVTXTotal = 0;
		NINTTTotal = 0;
		NTPCTotal = 0;
		NMVTXTotalZC = 0;
		NINTTTotalZC = 0;
		NTPCTotalZC = 0;

		for(int j = 0; j < siseedsize; j++){


			NMVTXTotal = NMVTXTotal + nmaps->at(j);
			NINTTTotal = NINTTTotal + nintt->at(j);

			//	if(crossing->at(j) != 0) continue;

				
			if(crossing->at(j) == 0){

				NMVTXTotalZC = NMVTXTotalZC + nmaps->at(j);
				NINTTTotalZC = NINTTTotalZC + nintt->at(j);
		
			}

			for(int k = 0; k < tpcseedsize; k++){

				//	cout << "j = " << j << "   k = " << k << endl;

				
			//	NTPCTotal = NTPCTotal + ntpc->at(k);







				if(crossing->at(j) == 0){

					//siseedsizezc++;
					//		tpcseedsizezc++;
					NZC++;

				}

			


			}



		}


		MVTXINTTCorr->Fill(NMVTXTotal,NINTTTotal);
		MVTXINTTCorrZC->Fill(NMVTXTotalZC,NINTTTotalZC);
		
	}



	MVTXINTTCorr->Draw("COLZ");
	c->SaveAs("CorrPlot/MVTXINTTCorr.png");

	MVTXINTTCorrZC->Draw("COLZ");
	c->SaveAs("CorrPlot/MVTXINTTCorrZC.png");


}
