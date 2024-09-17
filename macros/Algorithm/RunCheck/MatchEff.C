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
#include "TCanvas.h"
#include "TStyle.h"
//#include "LinkDef.h"
#include "TLegend.h"
#include <chrono>  // Correct header for high_resolution_clock

using namespace std;
using namespace std::chrono;

using std::cout;
using std::endl;

void MatchEff(){
	auto start = high_resolution_clock::now();

	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();


	c->SetLeftMargin(0.14);


	//const int NRuns = 5;
	//int RunNumber[NRuns] = {51616,51837,52271,52288,52613};


	//	const int NRuns = 4;
	//	int RunNumber[NRuns] = {51616,52271,52286,52288};
	const int NRuns = 2;
	int RunNumber[NRuns] = {51616,52288};


	for(int q = 0; q < NRuns; q++){


		TString infiles = Form("RootFiles/SeedAna_Svtx_%d.root",RunNumber[q]);
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



		std::vector<float> * siseedeta = 0;
		std::vector<float> * siseedphi = 0;

		std::vector<float> * tpcseedeta = 0;		
		std::vector<float> * tpcseedphi = 0;

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




		std::vector<float> * svtxsiseedeta = 0;
		std::vector<float> * svtxsiseedphi = 0;

		std::vector<float> * svtxtpcseedeta = 0;		
		std::vector<float> * svtxtpcseedphi = 0;


		TTree * SeedAna = (TTree *) fin->Get("SeedAna");
		SeedAna->SetBranchAddress("event",&event);

		SeedAna->SetBranchAddress("crossing",&crossing);
		SeedAna->SetBranchAddress("siseedx",&siseedx);
		SeedAna->SetBranchAddress("siseedy",&siseedy);
		SeedAna->SetBranchAddress("siseedz",&siseedz);

		SeedAna->SetBranchAddress("siseedphi",&siseedphi);
		SeedAna->SetBranchAddress("siseedeta",&siseedeta);


		SeedAna->SetBranchAddress("tpcseedx",&tpcseedx);
		SeedAna->SetBranchAddress("tpcseedy",&tpcseedy);
		SeedAna->SetBranchAddress("tpcseedz",&tpcseedz);



		SeedAna->SetBranchAddress("tpcseedphi",&tpcseedphi);
		SeedAna->SetBranchAddress("tpcseedeta",&tpcseedeta);



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




		SeedAna->SetBranchAddress("svtxsiseedphi",&svtxsiseedphi);
		SeedAna->SetBranchAddress("svtxsiseedeta",&svtxsiseedeta);


		SeedAna->SetBranchAddress("svtxtpcseedphi",&svtxtpcseedphi);
		SeedAna->SetBranchAddress("svtxtpcseedeta",&svtxtpcseedeta);



		float dx;
		float dy;
		float dz;
		int dq;
		float dphi;
		float dpx;
		float dpy;
		float dpz;

		float sieta;
		float siphi;
		float tpceta;
		float tpcphi;
		float deta;

		float pt;

		int NEvents = SeedAna->GetEntries();




		NEvents = 200;



		TH1D * NPairHis = new TH1D("NPairHis","",200,0,100000);
		TH1D * NPairHisZC = new TH1D("NPairHisZC","",200,0,200);
		TH1D * NPairZCutHis = new TH1D("NPairZCutHis","",200,0,1000);
		TH1D * NPairZCutHisZC = new TH1D("NPairZCutHis","",100,0,100);
		TH1D * NPairMatchedHis = new TH1D("NPairMatched","",100,0,100);
		TH1D * NPairMatchedHisZC = new TH1D("NPairMatchedZC","",10,0,10);


		//	NEvents = 4000;

		for(int i = 0; i < NEvents; i++){


			int NPair = 0; 
			int NPairZCut = 0;
			int NMatchedPair = 0;




			int NPairZC = 0; 
			int NPairZCutZC = 0;
			int NMatchedPairZC = 0;


			if(i%10==0) cout << "Now Working on Event: " << i << "   Out of Total Event: " << NEvents << endl;

			SeedAna->GetEntry(i);
			siseedsize = siseedx->size();
			tpcseedsize = tpcseedy->size();


			NPair = siseedsize * tpcseedsize;


			int siseedsizezc = 0;
			//	int tpcseedsizezc = 0;


			//		cout << "siseedx->size() = " << siseedx->size()  << "      siseedy->size() = " << siseedy->size() <<  "     siseedz->size() = " << siseedz->size()  << endl;
			//		cout << "tpcseedx->size() = " << tpcseedx->size()  << "      tpcseedy->size() = " << tpcseedy->size() <<  "     tpcseedz->size() = " << tpcseedz->size()  << endl;


			for(int j = 0; j < siseedsize; j++){

				if(crossing->at(j) == 0){

					siseedsizezc++;

				}
			}
			//	cout << "Pass 1" << endl;

			NPairZC = siseedsizezc * tpcseedsize;

			NPairHis->Fill(NPair);
			NPairHisZC->Fill(NPairZC);

			for(int j = 0; j < siseedsize; j++){



				//	if(crossing->at(j) != 0) continue;

				for(int k = 0; k < tpcseedsize; k++){

					//	cout << "j = " << j << "   k = " << k << endl;

					dx = siseedx->at(j) - tpcseedx->at(k);
					dy = siseedy->at(j) - tpcseedy->at(k);
					dz = siseedz->at(j) - tpcseedz->at(k);

					dpx = siseedpx->at(j) - tpcseedpx->at(k);
					dpy = siseedpy->at(j) - tpcseedpy->at(k);
					dpz = siseedpz->at(j) - tpcseedpz->at(k);

					dq = siseedcharge->at(j) - tpcseedcharge->at(k);



					sieta =  siseedeta->at(j);
					tpceta =  tpcseedeta->at(k);

					dphi = siseedphi->at(j) -  tpcseedeta->at(k); 

					deta = sieta - tpceta;


					if(abs(dz) < 10){


						NPairZCut++;
					}



					if(crossing->at(j) == 0){






						if(abs(dz) < 10){


							NPairZCutZC++;
						}



						//siseedsizezc++;
						//		tpcseedsizezc++;

					}




				}



			}


			NPairZCutHis->Fill(NPairZCut);		
			NPairZCutHisZC->Fill(NPairZCutZC);


			//cout << "Pass 2" << endl;

			//	if(1 > 0) continue;
			//		SiTPCCorr->Fill(siseedsize,tpcseedsize);

			svtxsiseedsize = svtxsiseedx->size();
			svtxtpcseedsize = svtxtpcseedy->size();

			//cout << "siseedsize = " << siseedsize << "  tpcseedsize = " << tpcseedsize << "    svtxsiseedsize " << svtxsiseedsize << endl;

			//	cout << "svtxsiseedsize = " << svtxsiseedsize << "  svtxtpcseedsize = " << svtxtpcseedsize << endl;

			//		SiMatchSeedCorr->Fill(siseedsize,svtxsiseedsize);
			//		TPCMatchSeedCorr->Fill(tpcseedsize,svtxsiseedsize);

			//	SiMatchSeedCorr->Fill();

			int svtxsiseedsizezc = 0;

			std::vector<float> svtxsiseedxzc;
			std::vector<float> svtxtpcseedxzc;


			NPairMatchedHis->Fill(svtxsiseedsize);		


			for(int j = 0; j < svtxsiseedsize; j++){



				dx = svtxsiseedx->at(j) - svtxtpcseedx->at(j);
				dy = svtxsiseedy->at(j) - svtxtpcseedy->at(j);
				dz = svtxsiseedz->at(j) - svtxtpcseedz->at(j);

				//	dphi = TMath::ATan2(svtxsiseedy->at(j),svtxsiseedx->at(j)) - TMath::ATan2(svtxtpcseedy->at(j),svtxtpcseedx->at(j)); 



				dpx = svtxsiseedpx->at(j) - svtxtpcseedpx->at(j);
				dpy = svtxsiseedpy->at(j) - svtxtpcseedpy->at(j);
				dpz = svtxsiseedpz->at(j) - svtxtpcseedpz->at(j);



				sieta =  svtxsiseedeta->at(j);	
				tpceta =  svtxtpcseedeta->at(j);

				dphi = svtxsiseedphi->at(j) -  svtxtpcseedeta->at(j); 
				deta = sieta - tpceta;
				//	cout << "Pass 4" << endl;


				if(svtxcrossing->at(j) == 0){


					svtxsiseedsizezc++;
					svtxsiseedxzc.push_back(svtxsiseedx->at(j));
					svtxtpcseedxzc.push_back(svtxtpcseedx->at(j));

				}



			}

			NPairMatchedHisZC->Fill(svtxsiseedsizezc);		



			//SiMatchSeedCorrZC->Fill(siseedsizezc,svtxsiseedsizezc);

			//	TPCMatchSeedCorrZC->Fill(tpcseedsizezc,svtxsiseedsizezc);

			/*

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
			//	cout << "Pass 5" << endl;


			cout << "Run: " << RunNumber[q] << "   Event = " << i << "   NPair =  " << NPair << "   NPairZC: " << NPairZC << "   NPairZCut =  " << NPairZCut << "   NPairZCutZC " << NPairZCutZC << "   svtxsiseedsize =  " << svtxsiseedsize << "    svtxsiseedsizezc = " << svtxsiseedsizezc << endl;
		}

		c->cd();
		NPairHis->Draw("ep");

		c->SaveAs("PlotStat/NPairHis.png");

		NPairHisZC->Draw("ep");

		c->SaveAs("PlotStat/NPairHisZC.png");



		NPairZCutHis->Draw("ep");

		c->SaveAs(Form("PlotStat/%d/NPairZCutHis.png",RunNumber[q]));


		NPairZCutHisZC->Draw("ep");
		c->SaveAs(Form("PlotStat/%d/NPairZCutHisZC.png",RunNumber[q]));




		NPairMatchedHis->Draw("ep");

		c->SaveAs(Form("PlotStat/%d/NPairMatchedHis.png",RunNumber[q]));


		NPairMatchedHisZC->Draw("ep");
		c->SaveAs(Form("PlotStat/%d/NPairMatchedHisZC.png",RunNumber[q]));



	}




	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);

	cout << "duration: " << duration.count() << " s" << endl;



}

