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

void CheckCut(){

	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();


	c->SetLeftMargin(0.14);


	TString infiles = {"/Users/zhaozhongshi/Desktop/TempDownload/SiTPCMatchFiles/Test.root"};
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

	std::vector<float> * siseedphi = 0;
	std::vector<float> * tpcseedphi = 0;

	std::vector<float> * siseedeta = 0;
	std::vector<float> * tpcseedeta = 0;

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


	bool IsLaserEvt; 

	TTree * SeedAna = (TTree *) fin->Get("SeedAna");
	SeedAna->SetBranchAddress("event",&event);
	SeedAna->SetBranchAddress("IsLaserEvt",&IsLaserEvt);

	SeedAna->SetBranchAddress("crossing",&crossing);
	SeedAna->SetBranchAddress("siseedx",&siseedx);
	SeedAna->SetBranchAddress("siseedy",&siseedy);
	SeedAna->SetBranchAddress("siseedz",&siseedz);
	//SeedAna->SetBranchAddress("siseedphi",&siseedphi);

	SeedAna->SetBranchAddress("tpcseedx",&tpcseedx);
	SeedAna->SetBranchAddress("tpcseedy",&tpcseedy);
	SeedAna->SetBranchAddress("tpcseedz",&tpcseedz);

	SeedAna->SetBranchAddress("tpcseedphi",&tpcseedphi);
	SeedAna->SetBranchAddress("siseedphi",&siseedphi);
	SeedAna->SetBranchAddress("tpcseedeta",&tpcseedeta);
	SeedAna->SetBranchAddress("siseedeta",&siseedeta);

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
	

	int NEvent = SeedAna->GetEntries();

	int NTrackBeforeCut = 0;
	int NTrackAfterCut = 0;
	int NTrackAfterPosOnly = 0;
	int tpcseedsizeNew = 0;




	for(int i = 0; i < NEvent; i++){
	
		if(i%100==0) cout << "Now Working on Event: " << i << "   Out of Total Event: " << NEvent << endl;

		SeedAna->GetEntry(i);
		siseedsize = siseedx->size();
		tpcseedsize = tpcseedy->size();




		NTrackBeforeCut = 0;
		NTrackAfterCut = 0;
		NTrackAfterPosOnly = 0;
		tpcseedsizeNew = 0;

		int siseedsizezc = 0;
		//	int tpcseedsizezc = 0;

		int NZC = 0;


		//		cout << "siseedx->size() = " << siseedx->size()  << "      siseedy->size() = " << siseedy->size() <<  "     siseedz->size() = " << siseedz->size()  << endl;
		//		cout << "tpcseedx->size() = " << tpcseedx->size()  << "      tpcseedy->size() = " << tpcseedy->size() <<  "     tpcseedz->size() = " << tpcseedz->size()  << endl;

		IncSiSeed = IncSiSeed + siseedsize;
		//IncTPCSeed = IncTPCSeed + tpcseedsize;

		for(int j = 0; j < siseedsize; j++){

			if(crossing->at(j) == 0){

				if(!IsLaserEvt) siseedsizezc++;

			}
		}

		IncSiSeedZC = IncSiSeedZC + siseedsizezc;

			
		for(int k = 0; k < tpcseedsize; k++){

				float tpcz = tpcseedz->at(k);
			//	if(abs(tpcz) > 40 || abs(tpcz) < 20) tpcseedsizeNew++;
	
				if(!IsLaserEvt) tpcseedsizeNew++;

		}


		for(int j = 0; j < siseedsize; j++){



			//	if(crossing->at(j) != 0) continue;

			for(int k = 0; k < tpcseedsize; k++){

				float dx = siseedx->at(j) - tpcseedx->at(k);
				float dy = siseedy->at(j) - tpcseedy->at(k);
				float dz = siseedz->at(j) - tpcseedz->at(k);

				float dpx = siseedpx->at(j) - tpcseedpx->at(k);
				float dpy = siseedpy->at(j) - tpcseedpy->at(k);
				float dpz = siseedpz->at(j) - tpcseedpz->at(k);

				float dphi = siseedphi->at(j) - tpcseedphi->at(k); 
				float deta = siseedeta->at(j) - tpcseedeta->at(k); 

				//	cout << "j = " << j << "   k = " << k << endl;
				if(abs(dx) < 2 && abs(dy) < 2 && fabs(deta)  < 0.1 && ( (fabs(fabs(dphi) - 2.0 * M_PI) < 0.2) || fabs(dphi) < 0.2) )  NTrackAfterCut++; //Use Cut
				if(abs(dx) < 2 && abs(dy) < 2 && abs(dz) < 10  )  NTrackAfterPosOnly++; //Use Cut

				
	


			

				if(crossing->at(j) == 0){

					//siseedsizezc++;
					//		tpcseedsizezc++;
					NZC++;
					//if(goodtpcseed) 

				
				}

			

				IncTPCSeed++;

			}



		}




		svtxsiseedsize = svtxsiseedx->size();
		svtxtpcseedsize = svtxtpcseedy->size();

	
		cout << "Event: " << i  << "   Total TPC Seeds:  " << tpcseedsize << "   Good TPC Seeds:  " << tpcseedsizeNew << "     SvtxMatched - NTracks:  My Cut:  " << NTrackAfterCut << "   NTrackAfterPosOnly:  " << NTrackAfterPosOnly << "   Official Joe Cut:  " << svtxsiseedsize << endl;
		

	//	IncMatchedTrack = IncMatchedTrack + svtxsiseedsize;

		//	SiMatchSeedCorr->Fill();

		int svtxsiseedsizezc = 0;

		std::vector<float> svtxsiseedxzc;
		std::vector<float> svtxtpcseedxzc;

		for(int j = 0; j < svtxsiseedsize; j++){




			if(svtxcrossing->at(j) == 0){

				float tpcz = svtxtpcseedz->at(j);


				if(!IsLaserEvt) IncMatchedTrackZC++;
				
			}

                  
			if(!IsLaserEvt) IncMatchedTrack++;
	


		}





		//	TPCMatchSeedCorrZC->Fill(tpcseedsizezc,svtxsiseedsizezc);



		// Map to store the count of each element
		std::map<float, int> siseedused;

		// Count the occurrences of each element
		for (float num : *svtxsiseedx) {
			siseedused[num]++;
		}

		// Print out each element and its count
		for (const auto& pair : siseedused) {
			//std::cout << "Element: " << pair.first << ", Count: " << pair.second << std::endl;
			int Count = pair.second;
			if(Count > 1) TotalReuseSiSeed++;
		//	SiUsedStat->Fill(Count);

		}



		// Map to store the count of each element
		std::map<float, int> tpcseedused;

		// Count the occurrences of each element
		for (float num : *svtxtpcseedx) {
			tpcseedused[num]++;
		}

		// Print out each element and its count
		for (const auto& pair : tpcseedused) {
			//std::cout << "Element: " << pair.first << ", Count: " << pair.second << std::endl;
			int Count = pair.second;
			if(Count > 1) TotalReuseTPCSeed++;

			
	//		TPCUsedStat->Fill(Count);

		}


	// Map to store the count of each element
		std::map<float, int> siseedusedzc;

		// Count the occurrences of each element
		for (float num : svtxsiseedxzc) {
			siseedusedzc[num]++;
		}

		// Print out each element and its count
		for (const auto& pair : siseedusedzc) {
			//std::cout << "Element: " << pair.first << ", Count: " << pair.second << std::endl;
			int Count = pair.second;
			if(Count > 1) TotalReuseSiSeedZC++;
			
	//		SiUsedStatZC->Fill(Count);

		}



		// Map to store the count of each element
		std::map<float, int> tpcseedusedzc;

		// Count the occurrences of each element
		for (float num : svtxtpcseedxzc) {
			tpcseedusedzc[num]++;
		}

		// Print out each element and its count
		for (const auto& pair : tpcseedusedzc) {
			//std::cout << "Element: " << pair.first << ", Count: " << pair.second << std::endl;
			int Count = pair.second;
			if(Count > 1) TotalReuseTPCSeedZC++;
			
	//		TPCUsedStatZC->Fill(Count);

		}


		if(NZC > 0 ) NEventZC++;
		
	}

	float CurrSetupEff = 0;
	float CurrSetupEffZC = 0;

	CurrSetupEff = float(IncMatchedTrack)/float(IncTPCSeed);
	CurrSetupEffZC = float(IncMatchedTrackZC)/float(IncSiSeedZC);

	cout << "----------------------- Summary of Analysis -----------------------" << endl;

	cout << "Global Info: Number of Runs: " << NRun << "   Number of Segments: " << NSeg << "   Number of Events: " << NEvent << "    Number of Events with Zero Crosing " << NEventZC << endl;
	cout << "Unmatched Track Seed Info: Number of Siseeds: " << IncSiSeed  << " Zero Crossing Siseeds : " <<  IncSiSeedZC << "   Number of IncTPCSeed: " << IncTPCSeed << endl;
	cout << "Matched Track Seed Info: Number of Tracks: " << IncMatchedTrack  << " Zero Crossing Tracks : " <<  IncMatchedTrackZC << endl;
	cout << "TotalReuse: Silicon Seeds: " << TotalReuseSiSeed  << "   TotalReuseTPCSeed: " <<  TotalReuseTPCSeed << endl;
	cout << "TotalReuse at Zero Crossing: Silicon Seeds: " << TotalReuseSiSeedZC  << "   TotalReuseTPCSeed: " <<  TotalReuseTPCSeedZC << endl;
	
	cout << "Matching Efficiency Without Crossing: " << CurrSetupEff << "   Matching Efficiency at Crossing = 0: " << CurrSetupEffZC << endl;
	
	cout << "----------------------- End of Summary -----------------------" << endl;

}
