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
using namespace std::chrono;

using std::cout;
using std::endl;

void MatchRunAna(int nevt){
	auto start = high_resolution_clock::now();

	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();


	c->SetLeftMargin(0.14);


	const int NRuns = 5;

	int RunNumber[NRuns] = {51616,51865,52266,52288,52613};


	TH1D * DeltaXUM[NRuns];
	TH1D * DeltaYUM[NRuns];
	TH1D * DeltaZUM[NRuns];
	TH1D * DeltaXM[NRuns];
	TH1D * DeltaYM[NRuns];
	TH1D * DeltaZM[NRuns];


	TH1D * DeltaXZCUM[NRuns];
	TH1D * DeltaYZCUM[NRuns];
	TH1D * DeltaZZCUM[NRuns];
	TH1D * DeltaXZCM[NRuns];
	TH1D * DeltaYZCM[NRuns];
	TH1D * DeltaZZCM[NRuns];



	TH1D * DeltaPhiZCUM[NRuns];
	TH1D * DeltaEtaZCUM[NRuns];
	TH1D * DeltaPhiZCM[NRuns];
	TH1D * DeltaEtaZCM[NRuns];
	TH1D * DeltaPhiUM[NRuns];
	TH1D * DeltaEtaUM[NRuns];
	TH1D * DeltaPhiM[NRuns];
	TH1D * DeltaEtaM[NRuns];


	for(int q = 0; q < NRuns; q++){



		DeltaXZCUM[q] = new TH1D(Form("DeltaXZCUM_%d",q),"",100,-5,5);
		DeltaXZCUM[q]->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
		DeltaXZCUM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaXZCUM[q]->GetXaxis()->CenterTitle();
		DeltaXZCUM[q]->GetYaxis()->CenterTitle();
		DeltaXZCUM[q]->SetMarkerStyle(20);
		DeltaXZCUM[q]->SetMarkerSize(1);
		DeltaXZCUM[q]->SetMarkerColor(q+1);
		DeltaXZCUM[q]->SetLineColor(q+1);

		DeltaYZCUM[q] = new TH1D(Form("DeltaYZCUM_%d",q),"",100,-5,5);
		DeltaYZCUM[q]->GetXaxis()->SetTitle("Silicon Seed y - TPC Seed y: #Delta y (cm)");
		DeltaYZCUM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaYZCUM[q]->GetXaxis()->CenterTitle();
		DeltaYZCUM[q]->GetYaxis()->CenterTitle();
		DeltaYZCUM[q]->SetMarkerStyle(20);
		DeltaYZCUM[q]->SetMarkerSize(1);
		DeltaYZCUM[q]->SetMarkerColor(q+1);
		DeltaYZCUM[q]->SetLineColor(q+1);

		DeltaZZCUM[q] = new TH1D(Form("DeltaZZCUM_%d",q),"",100,-100,100);
		DeltaZZCUM[q]->GetXaxis()->SetTitle("Silicon Seed z - TPC Seed z: #Delta z (cm)");
		DeltaZZCUM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaZZCUM[q]->GetXaxis()->CenterTitle();
		DeltaZZCUM[q]->GetYaxis()->CenterTitle();
		DeltaZZCUM[q]->SetMarkerStyle(20);
		DeltaZZCUM[q]->SetMarkerSize(1);
		DeltaZZCUM[q]->SetMarkerColor(q+1);
		DeltaZZCUM[q]->SetLineColor(q+1);


		DeltaXZCM[q] = new TH1D(Form("DeltaZZCUM_%d",q),"",100,-5,5);
		DeltaXZCM[q]->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
		DeltaXZCM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaXZCM[q]->GetXaxis()->CenterTitle();
		DeltaXZCM[q]->GetYaxis()->CenterTitle();
		DeltaXZCM[q]->SetMarkerStyle(20);
		DeltaXZCM[q]->SetMarkerSize(1);
		DeltaXZCM[q]->SetMarkerColor(2);
		DeltaXZCM[q]->SetLineColor(2);

		DeltaYZCM[q] = new TH1D("DeltaYZCUM","",100,-5,5);
		DeltaYZCM[q]->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
		DeltaYZCM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaYZCM[q]->GetXaxis()->CenterTitle();
		DeltaYZCM[q]->GetYaxis()->CenterTitle();
		DeltaYZCM[q]->SetMarkerStyle(20);
		DeltaYZCM[q]->SetMarkerSize(1);
		DeltaYZCM[q]->SetMarkerColor(q+1);
		DeltaYZCM[q]->SetLineColor(q+1);

		DeltaZZCM[q] = new TH1D("DeltaZZCM","",100,-100,100);
		DeltaZZCM[q]->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
		DeltaZZCM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaZZCM[q]->GetXaxis()->CenterTitle();
		DeltaZZCM[q]->GetYaxis()->CenterTitle();
		DeltaZZCM[q]->SetMarkerStyle(20);
		DeltaZZCM[q]->SetMarkerSize(1);
		DeltaZZCM[q]->SetMarkerColor(q+1);
		DeltaZZCM[q]->SetLineColor(q+1);



		DeltaPhiZCM[q] = new TH1D("DeltaPhiZCM","",100,-3.2,3.2);
		DeltaPhiZCM[q]->GetXaxis()->SetTitle("Silicon Seed #phi - TPC Seed #phi: #Delta #phi (cm)");
		DeltaPhiZCM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaPhiZCM[q]->GetXaxis()->CenterTitle();
		DeltaPhiZCM[q]->GetYaxis()->CenterTitle();
		DeltaPhiZCM[q]->SetMarkerStyle(20);
		DeltaPhiZCM[q]->SetMarkerSize(1);
		DeltaPhiZCM[q]->SetMarkerColor(q+1);
		DeltaPhiZCM[q]->SetLineColor(q+1);

		DeltaEtaZCM[q] = new TH1D("DeltaEtaZCM","",100,-2,2);
		DeltaEtaZCM[q]->GetXaxis()->SetTitle("Silicon Seed #phi - TPC Seed #phi: #Delta #eta (cm)");
		DeltaEtaZCM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaEtaZCM[q]->GetXaxis()->CenterTitle();
		DeltaEtaZCM[q]->GetYaxis()->CenterTitle();
		DeltaEtaZCM[q]->SetMarkerStyle(20);
		DeltaEtaZCM[q]->SetMarkerSize(1);
		DeltaEtaZCM[q]->SetMarkerColor(q+1);
		DeltaEtaZCM[q]->SetLineColor(q+1);




		DeltaXUM[q] = (TH1D *) DeltaXZCUM[q]->Clone("DeltaXUM");
		DeltaYUM[q] = (TH1D *) DeltaYZCUM[q]->Clone("DeltaYUM");
		DeltaZUM[q] = (TH1D *) DeltaZZCUM[q]->Clone("DeltaZUM");

		DeltaXM[q] = (TH1D *) DeltaXZCM[q]->Clone("DeltaXM");
		DeltaYM[q] = (TH1D *) DeltaYZCM[q]->Clone("DeltaYM");
		DeltaZM[q] = (TH1D *) DeltaZZCM[q]->Clone("DeltaZM");


		DeltaPhiM = (TH1D *) DeltaPhiZCM->Clone("DeltaPhiM");
		DeltaPhiUM = (TH1D *) DeltaPhiZCM->Clone("DeltaPhiUM");
		DeltaPhiZCUM = (TH1D *) DeltaPhiZCM->Clone("DeltaPhiZCUM");

		DeltaEtaM = (TH1D *) DeltaEtaZCM->Clone("DeltaEtaM");
		DeltaEtaUM = (TH1D *) DeltaEtaZCM->Clone("DeltaEtaUM");
		DeltaEtaZCUM = (TH1D *) DeltaEtaZCM->Clone("DeltaEtaZCUM");

		/*

		   DeltaPxUM = new TH1D("DeltaPxUM","",100,-5,5);
		   DeltaPxUM->GetXaxis()->SetTitle("Silicon Seed px - TPC Seed px: #Delta px (GeV/c)");
		   DeltaPxUM->GetYaxis()->SetTitle("Number of Seed Pairs");
		   DeltaPxUM->GetXaxis()->CenterTitle();
		   DeltaPxUM->GetYaxis()->CenterTitle();
		   DeltaPxUM->SetMarkerStyle(20);
		   DeltaPxUM->SetMarkerSize(1);
		   DeltaPxUM->SetMarkerColor(1);
		   DeltaPxUM->SetLineColor(1);


		   DeltaPxZCUM = (TH1D *) DeltaPxUM->Clone("DeltaPxZCUM");
		   DeltaPxM = (TH1D *) DeltaPxUM->Clone("DeltaPxM");
		   DeltaPxZCM = (TH1D *) DeltaPxUM->Clone("DeltaPxZCM");







		   DeltaPyUM = new TH1D("DeltaPyUM","",100,-5,5);
		   DeltaPyUM->GetXaxis()->SetTitle("Silicon Seed py - TPC Seed py: #Delta py (GeV/c)");
		   DeltaPyUM->GetYaxis()->SetTitle("Number of Seed Pairs");
		   DeltaPyUM->GetXaxis()->CenterTitle();
		   DeltaPyUM->GetYaxis()->CenterTitle();
		   DeltaPyUM->SetMarkerStyle(20);
		   DeltaPyUM->SetMarkerSize(1);
		   DeltaPyUM->SetMarkerColor(1);
		   DeltaPyUM->SetLineColor(1);


		   DeltaPyZCUM = (TH1D *) DeltaPyUM->Clone("DeltaPyZCUM");
		   DeltaPyM = (TH1D *) DeltaPyUM->Clone("DeltaPyM");
		   DeltaPyZCM = (TH1D *) DeltaPyUM->Clone("DeltaPyZCM");


		   DeltaPzUM = new TH1D("DeltaPzUM","",100,-10,10);
		   DeltaPzUM->GetXaxis()->SetTitle("Silicon Seed pz - TPC Seed py: #Delta pz (GeV/c)");
		   DeltaPzUM->GetYaxis()->SetTitle("Number of Seed Pairs");
		   DeltaPzUM->GetXaxis()->CenterTitle();
		   DeltaPzUM->GetYaxis()->CenterTitle();
		   DeltaPzUM->SetMarkerStyle(20);
		   DeltaPzUM->SetMarkerSize(1);
		   DeltaPzUM->SetMarkerColor(1);
		   DeltaPzUM->SetLineColor(1);

		   DeltaPzZCUM = (TH1D *) DeltaPzUM->Clone("DeltaPzZCUM");
		   DeltaPzM = (TH1D *) DeltaPzUM->Clone("DeltaPzM");
		   DeltaPzZCM = (TH1D *) DeltaPzUM->Clone("DeltaPzZCM");

*/

	}


	for(int q = 0; q < NRuns; q++){


		TString infiles = Form("/Users/zhaozhongshi/Desktop/TempDownload/SiTPCMatchFiles/SeedAna_Svtx_%d.root",RunNumber[q]);
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

		std::vector<float> * siseedcharge = 0;
		std::vector<float> * tpcseedcharge = 0;

		std::vector<float> * svtxsiseedcharge = 0;
		std::vector<float> * svtxtpcseedcharge = 0;

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






		float dx;
		float dy;
		float dz;
		int dq;
		float dphi;
		float dpx;
		float dpy;
		float dpz;

		float pt;

		int NEvents = SeedAna->GetEntries();

		NEvents = nevt;

		TH2D * SiMatchSeedCorr = new TH2D("SiMatchSeedCorr","",100,0,500,100,0,500);
		SiMatchSeedCorr->GetXaxis()->SetTitle("Total Silicon Seeds");
		SiMatchSeedCorr->GetYaxis()->SetTitle("Matched Track (Silicon + TPC) Seeds");

		SiMatchSeedCorr->GetXaxis()->CenterTitle();
		SiMatchSeedCorr->GetYaxis()->CenterTitle();
		SiMatchSeedCorr->GetYaxis()->SetTitleOffset(1.4);


		TH2D * TPCMatchSeedCorr = new TH2D("TPCMatchSeedCorr","",100,0,800,100,0,500);
		TPCMatchSeedCorr->GetXaxis()->SetTitle("Total TPC Seeds");	
		TPCMatchSeedCorr->GetYaxis()->SetTitle("Matched Track (Silicon + TPC) Seeds");
		TPCMatchSeedCorr->GetXaxis()->CenterTitle();
		TPCMatchSeedCorr->GetYaxis()->CenterTitle();
		TPCMatchSeedCorr->GetYaxis()->SetTitleOffset(1.4);



		TH2D * SiMatchSeedCorrZC = new TH2D("SiMatchSeedCorrZC","",100,0,50,100,0,50);
		SiMatchSeedCorrZC->GetXaxis()->SetTitle("Total Silicon Seeds");
		SiMatchSeedCorrZC->GetYaxis()->SetTitle("Matched Track (Silicon + TPC) Seeds");

		SiMatchSeedCorrZC->GetXaxis()->CenterTitle();
		SiMatchSeedCorrZC->GetYaxis()->CenterTitle();
		SiMatchSeedCorrZC->GetYaxis()->SetTitleOffset(1.4);



		TH2D * SiTPCCorr = new TH2D("SiTPCCorr","",100,0,500,100,0,500);
		SiTPCCorr->GetXaxis()->SetTitle("Total Silicon Seeds");
		SiTPCCorr->GetYaxis()->SetTitle("Total TPC Seeds");
		SiTPCCorr->GetXaxis()->CenterTitle();
		SiTPCCorr->GetYaxis()->CenterTitle();
		SiTPCCorr->GetYaxis()->SetTitleOffset(1.4);


		TH1D * SiUsedStat = new TH1D("SiUsedStat","",10,-0.5,9.5);
		SiUsedStat->GetXaxis()->SetTitle("Number of Time the Same Silicon Seed matched with a TPC Seed");
		SiUsedStat->GetYaxis()->SetTitle("Fractions");
		SiUsedStat->GetXaxis()->CenterTitle();
		SiUsedStat->GetYaxis()->CenterTitle();
		SiUsedStat->GetYaxis()->SetTitleOffset(1.4);

		TH1D * TPCUsedStat = new TH1D("TPCUsedStat","",10,-0.5,9.5);
		TPCUsedStat->GetXaxis()->SetTitle("Number of Time the Same TPC Seed used in A Silicon Seed");
		TPCUsedStat->GetYaxis()->SetTitle("Fractions");
		TPCUsedStat->GetXaxis()->CenterTitle();
		TPCUsedStat->GetYaxis()->CenterTitle();
		TPCUsedStat->GetYaxis()->SetTitleOffset(1.4);


		TH1D * SiUsedStatZC = new TH1D("SiUsedStatZC","",10,-0.5,9.5);
		SiUsedStatZC->GetXaxis()->SetTitle("Number of Time the Same Silicon Seed matched with a TPC Seed");
		SiUsedStatZC->GetYaxis()->SetTitle("Fractions");
		SiUsedStatZC->GetXaxis()->CenterTitle();
		SiUsedStatZC->GetYaxis()->CenterTitle();
		SiUsedStatZC->GetYaxis()->SetTitleOffset(1.4);

		TH1D * TPCUsedStatZC = new TH1D("TPCUsedStatZC","",10,-0.5,9.5);
		TPCUsedStatZC->GetXaxis()->SetTitle("Number of Time the Same TPC Seed used in A Silicon Seed");
		TPCUsedStatZC->GetYaxis()->SetTitle("Fractions");
		TPCUsedStatZC->GetXaxis()->CenterTitle();
		TPCUsedStatZC->GetYaxis()->CenterTitle();
		TPCUsedStatZC->GetYaxis()->SetTitleOffset(1.4);

		TH1D * DeltaQPt = new TH1D("DeltaQPt","",100,0,10);
		DeltaQPt->GetXaxis()->SetTitle("Silicon-TPC Matched Svtx Track p_{T} (GeV/c)");
		DeltaQPt->GetYaxis()->SetTitle("Fraction of #Delta Q != 0");
		DeltaQPt->GetXaxis()->CenterTitle();
		DeltaQPt->GetYaxis()->CenterTitle();
		DeltaQPt->GetYaxis()->SetTitleOffset(1.4);
		TH1D * DeltaQPtZ = (TH1D *) DeltaQPt->Clone("DeltaQPtZ");
		TH1D * DeltaQPtNZEff = (TH1D *) DeltaQPt->Clone("DeltaQPtNZEff");


		TH1D * DeltaQPtZC =  new TH1D("DeltaQPtZC","",100,0,10);
		DeltaQPtZC->GetXaxis()->SetTitle("Silicon-TPC Matched Svtx Track p_{T} (GeV/c)");
		DeltaQPtZC->GetYaxis()->SetTitle("Fraction of #Delta Q != 0");
		DeltaQPtZC->GetXaxis()->CenterTitle();
		DeltaQPtZC->GetYaxis()->CenterTitle();
		DeltaQPtZC->GetYaxis()->SetTitleOffset(1.4);

		TH1D * DeltaQPtZCZ = (TH1D *) DeltaQPtZC->Clone("DeltaQPtZCZ");
		TH1D * DeltaQPtZCNZEff = (TH1D *) DeltaQPtZC->Clone("DeltaQPtZCNZEff");


		float sieta;
		float tpceta;
		float deta;

		float sixcal;
		float siycal;
		float sizcal;
		float sircal;
		float sirhocal;

		float tpcxcal;
		float tpcycal;
		float tpczcal;
		float tpcrcal;
		float tpcrhocal;


		//	NEvents = 4000;

		for(int i = 0; i < NEvents; i++){

			if(i%10==0) cout << "Now Working on Event: " << i << "   Out of Total Event: " << NEvents << endl;

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


					//	cout << "dq = " << dq << endl;

					dphi = TMath::ATan2(siseedy->at(j),siseedx->at(j)) - TMath::ATan2(tpcseedy->at(k),tpcseedx->at(k)); 


					sixcal = siseedx->at(j);
					siycal = siseedy->at(j);
					sizcal = siseedz->at(j);
					sirhocal = sqrt(sixcal * sixcal + siycal * siycal);
					sircal = sqrt(sixcal * sixcal + siycal * siycal + sizcal * sizcal);
					tpcxcal = tpcseedpx->at(k);
					tpcycal = tpcseedpy->at(k);
					tpczcal = tpcseedpz->at(k);
					tpcrhocal = sqrt(tpcxcal * tpcxcal + tpcycal * tpcycal);
					tpcrcal = sqrt(tpcxcal * tpcxcal + tpcycal * tpcycal + tpczcal * tpczcal);
					sieta = TMath::Log(sirhocal/(sircal - sizcal));
					tpceta = TMath::Log(tpcrhocal/(tpcrcal - tpczcal));


					deta = sieta - tpceta;



					DeltaXUM[q]->Fill(dx);
					DeltaYUM[q]->Fill(dy);
					DeltaZUM[q]->Fill(dz);
					DeltaPhiUM[q]->Fill(dphi);
					DeltaEtaUM[q]->Fill(deta);




					//	pt = sqrt(tpcseedpx->at(k) * tpcseedpx->at(k) + tpcseedpy->at(k) * tpcseedpy->at(k));


					if(crossing->at(j) == 0){

						DeltaXZCUM[q]->Fill(dx);
						DeltaYZCUM[q]->Fill(dy);
						DeltaZZCUM[q]->Fill(dz);
						DeltaPhiZCUM[q]->Fill(dphi);
						DeltaEtaZCUM[q]->Fill(deta);



						//siseedsizezc++;
						//		tpcseedsizezc++;

					}




				}



			}


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

				sixcal = svtxsiseedx->at(j);
				siycal = svtxsiseedy->at(j);
				sizcal = svtxsiseedz->at(j);
				sirhocal = sqrt(sixcal * sixcal + siycal * siycal);
				sircal = sqrt(sixcal * sixcal + siycal * siycal + sizcal * sizcal);



				tpcxcal = svtxtpcseedx->at(j);
				tpcycal = svtxtpcseedy->at(j);
				tpczcal = svtxtpcseedz->at(j);
				tpcrhocal = sqrt(tpcxcal * tpcxcal + tpcycal * tpcycal);
				tpcrcal = sqrt(tpcxcal * tpcxcal + tpcycal * tpcycal + tpczcal * tpczcal);

				sieta = TMath::Log(sirhocal/(sircal - sizcal));
				tpceta = TMath::Log(tpcrhocal/(tpcrcal - tpczcal));
			
				deta = sieta - tpceta;


				DeltaXM[q]->Fill(dx);
				DeltaYM[q]->Fill(dy);
				DeltaZM[q]->Fill(dz);
				DeltaPhiM[q]->Fill(dphi);
				DeltaEtaM[q]->Fill(deta);

				if(svtxcrossing->at(j) == 0){

					DeltaXZCM[q]->Fill(dx);
					DeltaYZCM[q]->Fill(dy);
					DeltaZZCM[q]->Fill(dz);
					DeltaPhiZCM[q]->Fill(dphi);
					DeltaEtaZCM[q]->Fill(deta);

					//cout << "svtxcrossing->at(j) = " << svtxcrossing->at(j) << endl;
					svtxsiseedsizezc++;
					svtxsiseedxzc.push_back(svtxsiseedx->at(j));
					svtxtpcseedxzc.push_back(svtxtpcseedx->at(j));

				}



			}




			SiMatchSeedCorrZC->Fill(siseedsizezc,svtxsiseedsizezc);

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

		}

	}





	TLegend * leg  = new TLegend(0.15,0.72,0.50,0.88,NULL,"brNDC");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.040);
	leg->SetTextFont(42);
	leg->SetFillStyle(0);
	leg->SetLineWidth(3);


	for(int q = 0; q < NRuns; q++){
	

		leg->AddEntry(DeltaXZCUM[q],Form("Run: %d",RunNumber[q]),"LP");

		if(q == 0) DeltaXUM[q]->Draw("ep");
		if(q > 0) DeltaXUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/X/DeltaXUM.png");


	for(int q = 0; q < NRuns; q++){
	

		leg->AddEntry(DeltaXM[q],Form("Run: %d",RunNumber[q]),"LP");

		if(q == 0) DeltaXM[q]->Draw("ep");
		if(q > 0) DeltaXM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/X/DeltaXM.png");

	for(int q = 0; q < NRuns; q++){
	

		leg->AddEntry(DeltaXZCUM[q],Form("Run: %d",RunNumber[q]),"LP");

		if(q == 0) DeltaXZCUM[q]->Draw("ep");
		if(q > 0) DeltaXZCuM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/X/DeltaXZCUM.png");


	for(int q = 0; q < NRuns; q++){
	

		leg->AddEntry(DeltaXZCM[q],Form("Run: %d",RunNumber[q]),"LP");

		if(q == 0) DeltaXZCM[q]->Draw("ep");
		if(q > 0) DeltaXZCM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/X/DeltaXZCM.png");


	for(int q = 0; q < NRuns; q++){
	
	
		if(q == 0) DeltaYUM[q]->Draw("ep");
		if(q > 0) DeltaYUM[q]->Draw("epSAME");

	}

	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Y/DeltaYUM.png");

	for(int q = 0; q < NRuns; q++){
	
	
		if(q == 0) DeltaYZCUM[q]->Draw("ep");
		if(q > 0) DeltaYZCUM[q]->Draw("epSAME");

	}

	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Y/DeltaYZCUM.png");


	for(int q = 0; q < NRuns; q++){
	
	
		if(q == 0) DeltaYM[q]->Draw("ep");
		if(q > 0) DeltaYM[q]->Draw("epSAME");

	}

	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Y/DeltaYM.png");



	for(int q = 0; q < NRuns; q++){
	
	
		if(q == 0) DeltaYZCM[q]->Draw("ep");
		if(q > 0) DeltaYZCM[q]->Draw("epSAME");

	}

	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Y/DeltaYZCM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaZUM[q]->Draw("ep");
		if(q > 0) DeltaZUM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Z/DeltaZUM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaZZCUM[q]->Draw("ep");
		if(q > 0) DeltaZZCUM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Z/DeltaZZCUM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaZM[q]->Draw("ep");
		if(q > 0) DeltaZM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Z/DeltaZM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaZZCM[q]->Draw("ep");
		if(q > 0) DeltaZZCM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Z/DeltaZZCM.png");



	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaPhiZCUM[q]->Draw("ep");
		if(q > 0) DeltaPhiZCUM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Phi/DeltaPhiZCUM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaPhiZCM[q]->Draw("ep");
		if(q > 0) DeltaPhiZCM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Phi/DeltaPhiZCM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaPhiUM[q]->Draw("ep");
		if(q > 0) DeltaPhiUM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Phi/DeltaPhiUM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaPhiM[q]->Draw("ep");
		if(q > 0) DeltaPhiM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Phi/DeltaPhiM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaEtaUM[q]->Draw("ep");
		if(q > 0) DeltaEtaUM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Eta/DeltaEtaUM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaEtaM[q]->Draw("ep");
		if(q > 0) DeltaEtaM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Eta/DeltaEtaM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaEtaZCUM[q]->Draw("ep");
		if(q > 0) DeltaEtaZCUM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Eta/DeltaEtaZCUM.png");


	for(int q = 0; q < NRuns; q++){
	
		if(q == 0) DeltaEtaZCM[q]->Draw("ep");
		if(q > 0) DeltaEtaZCM[q]->Draw("epSAME");
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Eta/DeltaEtaZCM.png");






	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);

	cout << "duration: " << duration.count() << " s" << endl;
}
