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

void Match(){

	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();


	c->SetLeftMargin(0.14);


	TString infiles = {"SeedAna_Svtx.root"};
	TFile * fin = new TFile(infiles.Data());
	fin->cd();



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




	//Matching Metric dr^2 = dx^2 + dy^2


	float dx;
	float dy;
	float dz;
	float dpx;
	float dpy;
	float dpz;


	

	int NEvents = SeedAna->GetEntries();


	NEvents = 1;

	for(int i = 0; i < NEvents; i++){


		SeedAna->GetEntry(i);
		siseedsize = siseedx->size();
		tpcseedsize = tpcseedy->size();

		int siseedsizezc = 0;
		//	int tpcseedsizezc = 0;


		//		cout << "siseedx->size() = " << siseedx->size()  << "      siseedy->size() = " << siseedy->size() <<  "     siseedz->size() = " << siseedz->size()  << endl;
		//		cout << "tpcseedx->size() = " << tpcseedx->size()  << "      tpcseedy->size() = " << tpcseedy->size() <<  "     tpcseedz->size() = " << tpcseedz->size()  << endl;


		for(int j = 0; j < siseedsize; j++){

			if(crossing->at(j) == 0){

				siseedsizezc++;

			}
		}

		float dr;
		int idx = 0;
		int idy = 0;


		//	std::vector<std::vector<float>> RMatrix;


		const int NSiSeedZC = siseedsizezc;
		const int NTPCSeed = tpcseedsize;

		cout << "NSiSeedZC = " << NSiSeedZC << endl;

		float DeltaR[NSiSeedZC][NTPCSeed];
		float DeltaZ[NSiSeedZC][NTPCSeed];
		float DeltaPhi[NSiSeedZC][NTPCSeed];

		float Deltapx[NSiSeedZC][NTPCSeed];
		float Deltapy[NSiSeedZC][NTPCSeed];
		float Deltapz[NSiSeedZC][NTPCSeed];


		int ZCIndex = 0;



		std::vector<int> SiIndexUnPaired;
		std::vector<int> TPCIndexUnPaired;

		int SiSeedIndexZC = 0;


		for(int j = 0; j < siseedsize; j++){


			//	if(crossing->at(j) != 0) continue;

			float dr_min = 100;

	//		cout << "SiIndexUnPaired.size() = " << SiIndexUnPaired.size() << endl;

			if(crossing->at(j) == 0){
			
				cout << "Inside crossing " << endl;
				SiIndexUnPaired.push_back(SiSeedIndexZC);

				for(int k = 0; k < tpcseedsize; k++){

					//	cout << "j = " << j << "   k = " << k << endl;

					dx = siseedx->at(j) - tpcseedx->at(k);
					dy = siseedy->at(j) - tpcseedy->at(k);
					dz = siseedz->at(j) - tpcseedz->at(k);

					dpx = siseedpx->at(j) - tpcseedpx->at(k);
					dpy = siseedpy->at(j) - tpcseedpy->at(k);
					dpz = siseedpz->at(j) - tpcseedpz->at(k);


					dr = sqrt(dx * dx + dy * dy);

					dphi = TMath::ATan2(siseedy->at(j),siseedx->at(j)) - TMath::ATan2(tpcseedy->at(k),tpcseedx->at(k)); 
					/*

					   if(dr_min > dr){

					   dr_min = dr; 

					   BestMatchTPCSeed[ZCIndex] = k;

					   }
					//RVector.push_back(dr);
					*/
					cout << "dr = " << dr << endl;
					DeltaR[SiSeedIndexZC][k] = dr;
					DeltaZ[SiSeedIndexZC][k] = dr;
					DeltaPhi[SiSeedIndexZC][k] = dphi;
			
					Deltapx[SiSeedIndexZC][k] = dpx;
					Deltapy[SiSeedIndexZC][k] = dpy;
					Deltapz[SiSeedIndexZC][k] = dpz;


					TPCIndexUnPaired.push_back(k);
				}

				SiSeedIndexZC++;


			}

		}


		int NSiRemain = NSiSeedZC;


		cout << "OK here" << endl;

		while(SiIndexUnPaired.size() > 0){


			int siindexpaired = -1;
			int tpcindexpaired = -1;

			float dr_glo_min = 100;

		    for (int j : SiIndexUnPaired) {


				for(int k : TPCIndexUnPaired){

					//cout << NSiRemain << endl;
				 

					float dr = DeltaR[j][k];

					if(dr_glo_min > dr){

						dr_glo_min = dr;
						siindexpaired = j;
						tpcindexpaired = k;

					}
					
				}

			}

	
			cout << "SiIndexUnPaired = " << SiIndexUnPaired.size() << "   siindexpaired = " << siindexpaired << "   tpcindexpaired =  " << tpcindexpaired << "   dr_glo_min = " << dr_glo_min << endl;
	
			cout << "dz = " << DeltaZ[siindexpaired][tpcindexpaired]  << "   dphi = " << DeltaPhi[siindexpaired][tpcindexpaired] << "   dpx =  " << Deltapx[siindexpaired][tpcindexpaired]  << "   dpy = " << Deltapy[siindexpaired][tpcindexpaired] << "   dpz = " << Deltapz[siindexpaired][tpcindexpaired] << endl;
	
	//		SiIndexUnPaired.erase(siindexpaired);
	//		TPCIndexUnPaired.erase(tpcindexpaired);

			SiIndexUnPaired.erase(std::remove(SiIndexUnPaired.begin(), SiIndexUnPaired.end(), siindexpaired), SiIndexUnPaired.end());	
			TPCIndexUnPaired.erase(std::remove(TPCIndexUnPaired.begin(), TPCIndexUnPaired.end(), tpcindexpaired), TPCIndexUnPaired.end());

			
		}



		/*
		   SiTPCCorr->Fill(siseedsize,tpcseedsize);

		   svtxsiseedsize = svtxsiseedx->size();
		   svtxtpcseedsize = svtxtpcseedy->size();

		//cout << "siseedsize = " << siseedsize << "  tpcseedsize = " << tpcseedsize << "    svtxsiseedsize " << svtxsiseedsize << endl;

		//	cout << "svtxsiseedsize = " << svtxsiseedsize << "  svtxtpcseedsize = " << svtxtpcseedsize << endl;

		SiMatchSeedCorr->Fill(siseedsize,svtxsiseedsize);
		TPCMatchSeedCorr->Fill(tpcseedsize,svtxsiseedsize);

		//	SiMatchSeedCorr->Fill();

		int svtxsiseedsizezc = 0;

		std::vector<float> svtxsiseedxzc;
		std::vector<float> svtxtpcseedxzc;

		for(int j = 0; j < svtxsiseedsize; j++){



		dx = svtxsiseedx->at(j) - svtxtpcseedx->at(j);
		dy = svtxsiseedy->at(j) - svtxtpcseedy->at(j);
		dz = svtxsiseedz->at(j) - svtxtpcseedz->at(j);

		dphi = TMath::ATan2(svtxsiseedy->at(j),svtxsiseedx->at(j)) - TMath::ATan2(svtxtpcseedy->at(j),svtxtpcseedx->at(j)); 



		dpx = svtxsiseedpx->at(j) - svtxtpcseedpx->at(j);
		dpy = svtxsiseedpy->at(j) - svtxtpcseedpy->at(j);
		dpz = svtxsiseedpz->at(j) - svtxtpcseedpz->at(j);




		if(svtxcrossing->at(j) == 0){

		//cout << "svtxcrossing->at(j) = " << svtxcrossing->at(j) << endl;
		svtxsiseedsizezc++;
		svtxsiseedxzc.push_back(svtxsiseedx->at(j));
		svtxtpcseedxzc.push_back(svtxtpcseedx->at(j));

		}



		}




		SiMatchSeedCorrZC->Fill(siseedsizezc,svtxsiseedsizezc);
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
		SiUsedStat->Fill(Count);

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
		TPCUsedStat->Fill(Count);

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
		SiUsedStatZC->Fill(Count);

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
		TPCUsedStatZC->Fill(Count);

	}
	*/

	}



}
