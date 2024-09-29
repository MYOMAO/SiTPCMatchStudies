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

void QuickAnaMUM(){
    auto start = high_resolution_clock::now();

	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();


	c->SetLeftMargin(0.14);


//	TString infiles = {"/Users/zhaozhongshi/Desktop/TempDownload/SiTPCMatchFiles/SeedAna_Svtx.root"};
	TString infiles = {"/Users/zhaozhongshi/Desktop/TempDownload/SiTPCMatchFiles/Run53285.root"};

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



	bool IsLaserEvt;
		
	TTree * SeedAna = (TTree *) fin->Get("SeedAna");
	SeedAna->SetBranchAddress("event",&event);
	SeedAna->SetBranchAddress("IsLaserEvt",&IsLaserEvt);

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


	SeedAna->SetBranchAddress("siseedeta",&siseedeta);
	SeedAna->SetBranchAddress("tpcseedeta",&tpcseedeta);
	SeedAna->SetBranchAddress("siseedphi",&siseedphi);
	SeedAna->SetBranchAddress("tpcseedphi",&tpcseedphi);

	SeedAna->SetBranchAddress("svtxsiseedeta",&svtxsiseedeta);
	SeedAna->SetBranchAddress("svtxtpcseedeta",&svtxtpcseedeta);
	SeedAna->SetBranchAddress("svtxsiseedphi",&svtxsiseedphi);
	SeedAna->SetBranchAddress("svtxtpcseedphi",&svtxtpcseedphi);

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




	TH1D * DeltaQUM = new TH1D("DeltaQUM","",5,-2.5,2.5);
	DeltaQUM->GetXaxis()->SetTitle("Silicon Seed Q - TPC Seed Q: #Delta Q");
	DeltaQUM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaQUM->GetXaxis()->CenterTitle();
	DeltaQUM->GetYaxis()->CenterTitle();
	DeltaQUM->SetMarkerStyle(20);
	DeltaQUM->SetMarkerSize(1);
	DeltaQUM->SetMarkerColor(1);
	DeltaQUM->SetLineColor(1);



	TH1D * DeltaXZCUM = new TH1D("DeltaXZCUM","",100,-5,5);
	DeltaXZCUM->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
	DeltaXZCUM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaXZCUM->GetXaxis()->CenterTitle();
	DeltaXZCUM->GetYaxis()->CenterTitle();
	DeltaXZCUM->SetMarkerStyle(20);
	DeltaXZCUM->SetMarkerSize(1);
	DeltaXZCUM->SetMarkerColor(1);
	DeltaXZCUM->SetLineColor(1);

	TH1D * DeltaYZCUM = new TH1D("DeltaYZCUM","",100,-5,5);
	DeltaYZCUM->GetXaxis()->SetTitle("Silicon Seed y - TPC Seed y: #Delta y (cm)");
	DeltaYZCUM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaYZCUM->GetXaxis()->CenterTitle();
	DeltaYZCUM->GetYaxis()->CenterTitle();
	DeltaYZCUM->SetMarkerStyle(20);
	DeltaYZCUM->SetMarkerSize(1);
	DeltaYZCUM->SetMarkerColor(1);
	DeltaYZCUM->SetLineColor(1);

	TH1D * DeltaZZCUM = new TH1D("DeltaZZCUM","",100,-100,100);
	DeltaZZCUM->GetXaxis()->SetTitle("Silicon Seed z - TPC Seed z: #Delta z (cm)");
	DeltaZZCUM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaZZCUM->GetXaxis()->CenterTitle();
	DeltaZZCUM->GetYaxis()->CenterTitle();
	DeltaZZCUM->SetMarkerStyle(20);
	DeltaZZCUM->SetMarkerSize(1);
	DeltaZZCUM->SetMarkerColor(1);
	DeltaZZCUM->SetLineColor(1);


	TH1D * DeltaXZCM = new TH1D("DeltaXZCUM","",100,-5,5);
	DeltaXZCM->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
	DeltaXZCM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaXZCM->GetXaxis()->CenterTitle();
	DeltaXZCM->GetYaxis()->CenterTitle();
	DeltaXZCM->SetMarkerStyle(20);
	DeltaXZCM->SetMarkerSize(1);
	DeltaXZCM->SetMarkerColor(2);
	DeltaXZCM->SetLineColor(2);

	TH1D * DeltaYZCM = new TH1D("DeltaYZCUM","",100,-5,5);
	DeltaYZCM->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
	DeltaYZCM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaYZCM->GetXaxis()->CenterTitle();
	DeltaYZCM->GetYaxis()->CenterTitle();
	DeltaYZCM->SetMarkerStyle(20);
	DeltaYZCM->SetMarkerSize(1);
	DeltaYZCM->SetMarkerColor(2);
	DeltaYZCM->SetLineColor(2);

	TH1D * DeltaZZCM = new TH1D("DeltaZZCM","",100,-100,100);
	DeltaZZCM->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
	DeltaZZCM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaZZCM->GetXaxis()->CenterTitle();
	DeltaZZCM->GetYaxis()->CenterTitle();
	DeltaZZCM->SetMarkerStyle(20);
	DeltaZZCM->SetMarkerSize(1);
	DeltaZZCM->SetMarkerColor(2);
	DeltaZZCM->SetLineColor(2);



	TH1D * DeltaPhiZCM = new TH1D("DeltaPhiZCM","",100,-3.2,3.2);
	DeltaPhiZCM->GetXaxis()->SetTitle("Silicon Seed #phi - TPC Seed #phi: #Delta #phi (cm)");
	DeltaPhiZCM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaPhiZCM->GetXaxis()->CenterTitle();
	DeltaPhiZCM->GetYaxis()->CenterTitle();
	DeltaPhiZCM->SetMarkerStyle(20);
	DeltaPhiZCM->SetMarkerSize(1);
	DeltaPhiZCM->SetMarkerColor(2);
	DeltaPhiZCM->SetLineColor(2);

	TH1D * DeltaEtaZCM = new TH1D("DeltaEtaZCM","",100,-2,2);
	DeltaEtaZCM->GetXaxis()->SetTitle("Silicon Seed #phi - TPC Seed #phi: #Delta #eta (cm)");
	DeltaEtaZCM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaEtaZCM->GetXaxis()->CenterTitle();
	DeltaEtaZCM->GetYaxis()->CenterTitle();
	DeltaEtaZCM->SetMarkerStyle(20);
	DeltaEtaZCM->SetMarkerSize(1);
	DeltaEtaZCM->SetMarkerColor(2);
	DeltaEtaZCM->SetLineColor(2);




	TH1D * DeltaQZCUM = (TH1D *) DeltaQUM->Clone("DeltaQZCUM");
	TH1D * DeltaQM = (TH1D *) DeltaQUM->Clone("DeltaQM");
	TH1D * DeltaQZCM = (TH1D *) DeltaQUM->Clone("DeltaQZCM");


	TH1D * DeltaXUM = (TH1D *) DeltaXZCUM->Clone("DeltaXUM");
	TH1D * DeltaYUM = (TH1D *) DeltaYZCUM->Clone("DeltaYUM");
	TH1D * DeltaZUM = (TH1D *) DeltaZZCUM->Clone("DeltaZUM");

	TH1D * DeltaXM = (TH1D *) DeltaXZCM->Clone("DeltaXM");
	TH1D * DeltaYM = (TH1D *) DeltaYZCM->Clone("DeltaYM");
	TH1D * DeltaZM = (TH1D *) DeltaZZCM->Clone("DeltaZM");


	TH1D * DeltaPhiM = (TH1D *) DeltaPhiZCM->Clone("DeltaPhiM");
	TH1D * DeltaPhiUM = (TH1D *) DeltaPhiZCM->Clone("DeltaPhiUM");
	TH1D * DeltaPhiZCUM = (TH1D *) DeltaPhiZCM->Clone("DeltaPhiZCUM");
	
	TH1D * DeltaEtaM = (TH1D *) DeltaEtaZCM->Clone("DeltaEtaM");
	TH1D * DeltaEtaUM = (TH1D *) DeltaEtaZCM->Clone("DeltaEtaUM");
	TH1D * DeltaEtaZCUM = (TH1D *) DeltaEtaZCM->Clone("DeltaEtaZCUM");



	TH1D * DeltaPxUM = new TH1D("DeltaPxUM","",100,-5,5);
	DeltaPxUM->GetXaxis()->SetTitle("Silicon Seed px - TPC Seed px: #Delta px (GeV/c)");
	DeltaPxUM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaPxUM->GetXaxis()->CenterTitle();
	DeltaPxUM->GetYaxis()->CenterTitle();
	DeltaPxUM->SetMarkerStyle(20);
	DeltaPxUM->SetMarkerSize(1);
	DeltaPxUM->SetMarkerColor(1);
	DeltaPxUM->SetLineColor(1);


	TH1D * DeltaPxZCUM = (TH1D *) DeltaPxUM->Clone("DeltaPxZCUM");
	TH1D * DeltaPxM = (TH1D *) DeltaPxUM->Clone("DeltaPxM");
	TH1D * DeltaPxZCM = (TH1D *) DeltaPxUM->Clone("DeltaPxZCM");







	TH1D * DeltaPyUM = new TH1D("DeltaPyUM","",100,-5,5);
	DeltaPyUM->GetXaxis()->SetTitle("Silicon Seed py - TPC Seed py: #Delta py (GeV/c)");
	DeltaPyUM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaPyUM->GetXaxis()->CenterTitle();
	DeltaPyUM->GetYaxis()->CenterTitle();
	DeltaPyUM->SetMarkerStyle(20);
	DeltaPyUM->SetMarkerSize(1);
	DeltaPyUM->SetMarkerColor(1);
	DeltaPyUM->SetLineColor(1);


	TH1D * DeltaPyZCUM = (TH1D *) DeltaPyUM->Clone("DeltaPyZCUM");
	TH1D * DeltaPyM = (TH1D *) DeltaPyUM->Clone("DeltaPyM");
	TH1D * DeltaPyZCM = (TH1D *) DeltaPyUM->Clone("DeltaPyZCM");


	TH1D * DeltaPzUM = new TH1D("DeltaPzUM","",100,-10,10);
	DeltaPzUM->GetXaxis()->SetTitle("Silicon Seed pz - TPC Seed py: #Delta pz (GeV/c)");
	DeltaPzUM->GetYaxis()->SetTitle("Number of Seed Pairs");
	DeltaPzUM->GetXaxis()->CenterTitle();
	DeltaPzUM->GetYaxis()->CenterTitle();
	DeltaPzUM->SetMarkerStyle(20);
	DeltaPzUM->SetMarkerSize(1);
	DeltaPzUM->SetMarkerColor(1);
	DeltaPzUM->SetLineColor(1);

	TH1D * DeltaPzZCUM = (TH1D *) DeltaPzUM->Clone("DeltaPzZCUM");
	TH1D * DeltaPzM = (TH1D *) DeltaPzUM->Clone("DeltaPzM");
	TH1D * DeltaPzZCM = (TH1D *) DeltaPzUM->Clone("DeltaPzZCM");




	float dx;
	float dy;
	float dz;
	int dq;
	float dphi;
	float dpx;
	float dpy;
	float dpz;
	float deta;

	float pt;

	int NEvents = SeedAna->GetEntries();

	//NEvents = nevt;

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

	//NEvents = nevt;

	for(int i = 0; i < NEvents; i++){

		if(i%100==0) cout << "Now Working on Event: " << i << "   Out of Total Event: " << NEvents << endl;

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
		
				deta = siseedeta->at(j) - tpcseedeta->at(k);
				dphi = siseedphi->at(j) - tpcseedphi->at(k);

	

			//	cout << "dq = " << dq << endl;

			//	dphi = TMath::ATan2(siseedy->at(j),siseedx->at(j)) - TMath::ATan2(tpcseedy->at(k),tpcseedx->at(k)); 

				DeltaXUM->Fill(dx);
				DeltaYUM->Fill(dy);
				DeltaZUM->Fill(dz);
				DeltaPhiUM->Fill(dphi);
				DeltaEtaUM->Fill(deta);
		
				DeltaPxUM->Fill(dpx);
				DeltaPyUM->Fill(dpy);
				DeltaPzUM->Fill(dpz);

				DeltaQUM->Fill(dq);


				pt = sqrt(tpcseedpx->at(k) * tpcseedpx->at(k) + tpcseedpy->at(k) * tpcseedpy->at(k));

				DeltaQPt->Fill(pt);
				if(dq != 0) DeltaQPtNZEff->Fill(pt);


				if(crossing->at(j) == 0){
					DeltaXZCUM->Fill(dx);
					DeltaYZCUM->Fill(dy);
					DeltaZZCUM->Fill(dz);
					DeltaPhiZCUM->Fill(dphi);
					DeltaEtaZCUM->Fill(deta);
					
				
					DeltaPxZCUM->Fill(dpx);
					DeltaPyZCUM->Fill(dpy);
					DeltaPzZCUM->Fill(dpz);
					DeltaQZCUM->Fill(dq);


					DeltaQPtZC->Fill(pt);
					if(dq != 0) DeltaQPtZCNZEff->Fill(pt);

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


	
			deta = svtxsiseedeta->at(j) - svtxtpcseedeta->at(j);
			dphi = svtxsiseedphi->at(j) - svtxtpcseedphi->at(j);

				
			dpx = svtxsiseedpx->at(j) - svtxtpcseedpx->at(j);
			dpy = svtxsiseedpy->at(j) - svtxtpcseedpy->at(j);
			dpz = svtxsiseedpz->at(j) - svtxtpcseedpz->at(j);

			dq = svtxsiseedcharge->at(j) - svtxtpcseedcharge->at(j);


			DeltaXM->Fill(dx);
			DeltaYM->Fill(dy);
			DeltaZM->Fill(dz);
			DeltaPhiM->Fill(dphi);
			DeltaEtaM->Fill(deta);
			
			DeltaPxM->Fill(dpx);
			DeltaPyM->Fill(dpy);
			DeltaPzM->Fill(dpz);

			DeltaQM->Fill(dq);


			if(svtxcrossing->at(j) == 0){
				DeltaXZCM->Fill(dx);
				DeltaYZCM->Fill(dy);
				DeltaZZCM->Fill(dz);
				DeltaPhiZCM->Fill(dphi);
				DeltaEtaZCM->Fill(deta);
				

			
				DeltaPxZCM->Fill(dpx);
				DeltaPyZCM->Fill(dpy);
				DeltaPzZCM->Fill(dpz);
				DeltaQZCM->Fill(dq);
	
				
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


	}





	TLegend * leg  = new TLegend(0.15,0.72,0.50,0.88,NULL,"brNDC");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.040);
	leg->SetTextFont(42);
	leg->SetFillStyle(0);
	leg->SetLineWidth(3);

	leg->AddEntry(DeltaXZCUM,"TPC - Silicon Seed Before Matching","LP");
	leg->AddEntry(DeltaXZCM,"TPC - Silicon Seed After Matching","LP");


	DeltaXUM->Scale(1.0/DeltaXUM->Integral());
	DeltaXM->Scale(1.0/DeltaXM->Integral());
	DeltaXUM->Draw("ep");
	DeltaXM->Draw("epSAME");
	leg->Draw("SAME");
	DeltaXUM->SetMaximum(0.08);
	c->SaveAs("PlotMUM/DeltaX.png");


	DeltaYUM->Scale(1.0/DeltaYUM->Integral());
	DeltaYM->Scale(1.0/DeltaYM->Integral());
	DeltaYUM->Draw("ep");
	DeltaYM->Draw("epSAME");
	leg->Draw("SAME");	
	DeltaYUM->SetMaximum(0.08);

	c->SaveAs("PlotMUM/DeltaY.png");


	DeltaZUM->Scale(1.0/DeltaZUM->Integral());
	DeltaZM->Scale(1.0/DeltaZM->Integral());
	DeltaZUM->Draw("ep");
	DeltaZM->Draw("epSAME");
	leg->Draw("SAME");	
	DeltaZUM->SetMaximum(0.08);

	c->SaveAs("PlotMUM/DeltaZ.png");


	cout << "DeltaXZCUM -> Integral() = " << DeltaXZCUM->Integral()  << endl;
	DeltaXZCUM->Scale(1.0/DeltaXZCUM->Integral());
	DeltaXZCM->Scale(1.0/DeltaXZCM->Integral());
	DeltaXZCUM->Draw("ep");
	DeltaXZCM->Draw("epSAME");
	leg->Draw("SAME");
	DeltaXZCUM->SetMaximum(0.08);
	c->SaveAs("PlotMUM/DeltaXZC.png");


	DeltaYZCUM->Scale(1.0/DeltaYZCUM->Integral());
	DeltaYZCM->Scale(1.0/DeltaYZCM->Integral());
	DeltaYZCUM->Draw("ep");
	DeltaYZCM->Draw("epSAME");
	leg->Draw("SAME");	
	DeltaYZCUM->SetMaximum(0.08);

	c->SaveAs("PlotMUM/DeltaYZC.png");


	DeltaZZCUM->Scale(1.0/DeltaZZCUM->Integral());
	DeltaZZCM->Scale(1.0/DeltaZZCM->Integral());
	DeltaZZCUM->Draw("ep");
	DeltaZZCM->Draw("epSAME");
	leg->Draw("SAME");	
	DeltaZZCUM->SetMaximum(0.08);

	c->SaveAs("PlotMUM/DeltaZZC.png");

	DeltaPhiUM->SetMarkerColor(kBlack);
	DeltaPhiM->SetMarkerColor(kRed);


	DeltaPhiUM->Scale(1.0/DeltaPhiUM->Integral());
	DeltaPhiM->Scale(1.0/DeltaPhiM->Integral());
	DeltaPhiUM->Draw("ep");
	DeltaPhiM->Draw("epSAME");
	leg->Draw("SAME");
	DeltaPhiUM->SetMaximum(0.08);
	c->SaveAs("PlotMUM/DeltaPhi.png");



	DeltaEtaUM->Scale(1.0/DeltaEtaUM->Integral());
	DeltaEtaM->Scale(1.0/DeltaEtaM->Integral());
	DeltaEtaUM->Draw("ep");
	DeltaEtaM->Draw("epSAME");
	leg->Draw("SAME");	
	DeltaEtaUM->SetMaximum(0.2);

	c->SaveAs("PlotMUM/DeltaEta.png");




	SiMatchSeedCorr->Draw("colz");
	c->SaveAs("PlotMUM/SiMatchSeedCorr.png");

	TPCMatchSeedCorr->Draw("colz");
	c->SaveAs("PlotMUM/TPCMatchSeedCorr.png");


	SiMatchSeedCorrZC->Draw("colz");
	c->SaveAs("PlotMUM/SiMatchSeedCorrZC.png");

	SiTPCCorr->Draw("COLZ");

	c->SaveAs("PlotMUM/SiTPCCorr.png");



	
	TLegend * leg2  = new TLegend(0.45,0.72,0.90,0.88,NULL,"brNDC");
	leg2->SetBorderSize(0);
	leg2->SetTextSize(0.040);
	leg2->SetTextFont(42);
	leg2->SetFillStyle(0);
	leg2->SetLineWidth(3);



	SiUsedStat->SetLineWidth(2);
	SiUsedStatZC->SetLineWidth(2);


	leg2->AddEntry(SiUsedStat,"No Crossing Cut","LP");
	leg2->AddEntry(SiUsedStatZC,"Crossing = 0","LP");



	SiUsedStat->Scale(1.0/SiUsedStat->Integral());
	SiUsedStatZC->Scale(1.0/SiUsedStatZC->Integral());

	SiUsedStat->SetLineColor(kRed);
	SiUsedStatZC->SetLineColor(kBlue);
	SiUsedStatZC->SetMaximum(1);
	SiUsedStatZC->Draw("hist");		
	SiUsedStat->Draw("histSAME");

	leg2->Draw("SAME");

	c->SaveAs("PlotMUM/SiUsedStat.png");

	TPCUsedStat->SetLineWidth(2);
	TPCUsedStatZC->SetLineWidth(2);


	TPCUsedStat->Scale(1.0/TPCUsedStat->Integral());
	TPCUsedStatZC->Scale(1.0/TPCUsedStatZC->Integral());
	TPCUsedStatZC->SetMaximum(1);

	TPCUsedStat->SetLineColor(kRed);
	TPCUsedStatZC->SetLineColor(kBlue);
	TPCUsedStatZC->Draw("hist");	
	TPCUsedStat->Draw("histSAME");
	leg2->Draw("SAME");

	c->SaveAs("PlotMUM/TPCUsedStat.png");



	DeltaPhiZCUM->SetMarkerColor(kBlack);
	DeltaPhiZCM->SetMarkerColor(kRed);


	DeltaPhiZCUM->Scale(1.0/DeltaPhiZCUM->Integral());
	DeltaPhiZCM->Scale(1.0/DeltaPhiZCM->Integral());
	DeltaPhiZCUM->Draw("ep");
	DeltaPhiZCM->Draw("epSAME");
	leg->Draw("SAME");
	DeltaPhiUM->SetMaximum(0.08);
	c->SaveAs("PlotMUM/DeltaPhiZC.png");

	DeltaPxZCUM->Scale(1.0/DeltaPxZCUM->Integral());
	DeltaPxZCM->Scale(1.0/DeltaPxZCM->Integral());
	
	DeltaPxZCM->SetMarkerColor(kRed);


	DeltaPxZCUM->Draw("ep");

	DeltaPxZCM->Draw("epSAME");
	leg->Draw("SAME");
	DeltaPxZCUM->SetMaximum(0.08);
	c->SaveAs("PlotMUM/New/DeltaPxZCUM.png");

	DeltaPxUM->Scale(1.0/DeltaPxUM->Integral());
	DeltaPxM->Scale(1.0/DeltaPxM->Integral());

	DeltaPxM->SetMarkerColor(kRed);

	DeltaPxUM->Draw("ep");
	DeltaPxM->Draw("epSAME");
	leg->Draw("SAME");
	DeltaPxUM->SetMaximum(0.08);
	c->SaveAs("PlotMUM/New/DeltaPxUM.png");



	DeltaPyZCUM->Scale(1.0/DeltaPyZCUM->Integral());
	DeltaPyZCM->Scale(1.0/DeltaPyZCM->Integral());

	DeltaPyZCM->SetMarkerColor(kRed);
	

	DeltaPyZCUM->Draw("ep");
	DeltaPyZCM->Draw("epSAME");
	leg->Draw("SAME");
	DeltaPyZCUM->SetMaximum(0.08);
	c->SaveAs("PlotMUM/New/DeltaPyZCUM.png");

	DeltaPyUM->Scale(1.0/DeltaPyUM->Integral());
	DeltaPyM->Scale(1.0/DeltaPyM->Integral());
	DeltaPyM->SetMarkerColor(kRed);


	DeltaPyUM->Draw("ep");
	DeltaPyM->Draw("epSAME");
	leg->Draw("SAME");
	DeltaPyUM->SetMaximum(0.08);
	c->SaveAs("PlotMUM/New/DeltaPyUM.png");




	DeltaPzZCUM->Scale(1.0/DeltaPzZCUM->Integral());
	DeltaPzZCM->Scale(1.0/DeltaPzZCM->Integral());

	DeltaPzZCM->SetMarkerColor(kRed);
	

	DeltaPzZCUM->Draw("ep");
	DeltaPzZCM->Draw("epSAME");
	leg->Draw("SAME");
	DeltaPzZCUM->SetMaximum(0.08);
	c->SaveAs("PlotMUM/New/DeltaPzZCUM.png");

	DeltaPzUM->Scale(1.0/DeltaPzUM->Integral());
	DeltaPzM->Scale(1.0/DeltaPzM->Integral());
	DeltaPzM->SetMarkerColor(kRed);


	DeltaPzUM->Draw("ep");
	DeltaPzM->Draw("epSAME");
	leg->Draw("SAME");
	DeltaPyUM->SetMaximum(0.08);
	c->SaveAs("PlotMUM/New/DeltaPzUM.png");

//	DeltaQM->SetMarkerColor(kRed);
//	DeltaQUM->SetMarkerColor(kBlack);
	
	DeltaQM->SetMarkerColor(kRed);
	DeltaQM->SetLineColor(kRed);


	DeltaQUM->Scale(1.0/DeltaQUM->Integral());
	DeltaQM->Scale(1.0/DeltaQM->Integral());
	DeltaQUM->Draw("ep");
	DeltaQM->Draw("epSAME");
	leg->Draw("SAME");
	

	DeltaQUM->SetMaximum(1.0);
	c->SaveAs("PlotMUM/New/DeltaQ.png");




	DeltaQZCM->SetMarkerColor(kRed);
	DeltaQZCM->SetLineColor(kRed);
	
//	DeltaQZCUM->SetMarkerColor(kBlack);
	
	DeltaQZCUM->Scale(1.0/DeltaQZCUM->Integral());
	DeltaQZCM->Scale(1.0/DeltaQZCM->Integral());
	DeltaQZCUM->Draw("ep");
	DeltaQZCM->Draw("epSAME");
	leg->Draw("SAME");


	DeltaQZCUM->SetMaximum(1.0);
	c->SaveAs("PlotMUM/New/DeltaQZC.png");

	DeltaQPt->Sumw2();
	DeltaQPtZC->Sumw2();
	DeltaQPtNZEff->Sumw2();
	DeltaQPtZCNZEff->Sumw2();

	DeltaQPtNZEff->Divide(DeltaQPt);
	DeltaQPtZCNZEff->Divide(DeltaQPtZC);

	DeltaQPtNZEff->SetLineColor(kBlack);
	DeltaQPtZCNZEff->SetLineColor(kRed);
	



	TLegend * leg3  = new TLegend(0.15,0.72,0.50,0.88,NULL,"brNDC");
	leg3->SetBorderSize(0);
	leg3->SetTextSize(0.040);
	leg3->SetTextFont(42);
	leg3->SetFillStyle(0);
	leg3->SetLineWidth(3);


	leg3->AddEntry(DeltaQPtNZEff,"All Crossing","LP");
	leg3->AddEntry(DeltaQPtZCNZEff,"Crossing = 0","LP");

	DeltaQPtNZEff->Draw("ep");
	DeltaQPtZCNZEff->Draw("epSAME");
	leg3->Draw("SAME");

	DeltaQPtNZEff->SetMaximum(1);

	c->SaveAs("PlotMore/DeltaQPtNZEff.png");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    cout << "duration: " << duration.count() << " s" << endl;

}
