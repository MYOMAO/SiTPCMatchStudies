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

void MatchRunAna(){
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


	TH1D * SiXUM[NRuns];
	TH1D * SiYUM[NRuns];
	TH1D * SiZUM[NRuns];
	TH1D * SiXM[NRuns];
	TH1D * SiYM[NRuns];
	TH1D * SiZM[NRuns];


	TH1D * TPCXUM[NRuns];
	TH1D * TPCYUM[NRuns];
	TH1D * TPCZUM[NRuns];
	TH1D * TPCXM[NRuns];
	TH1D * TPCYM[NRuns];
	TH1D * TPCZM[NRuns];

	TH1D * SiXZCUM[NRuns];
	TH1D * SiYZCUM[NRuns];
	TH1D * SiZZCUM[NRuns];
	TH1D * SiXZCM[NRuns];
	TH1D * SiYZCM[NRuns];
	TH1D * SiZZCM[NRuns];


	TH1D * TPCXZCUM[NRuns];
	TH1D * TPCYZCUM[NRuns];
	TH1D * TPCZZCUM[NRuns];
	TH1D * TPCXZCM[NRuns];
	TH1D * TPCYZCM[NRuns];
	TH1D * TPCZZCM[NRuns];


	for(int q = 0; q < NRuns; q++){



		SiXUM[q] = new TH1D(Form("SiXUM_%d",q),"",100,-2,2);
		SiXUM[q]->GetXaxis()->SetTitle("Silicon Seed x (cm)");
		SiXUM[q]->GetYaxis()->SetTitle("Number of Silicon Seed");
		SiXUM[q]->GetXaxis()->CenterTitle();
		SiXUM[q]->GetYaxis()->CenterTitle();
		SiXUM[q]->SetMarkerStyle(20);
		SiXUM[q]->SetMarkerSize(1);
		SiXUM[q]->SetMarkerColor(q+1);
		SiXUM[q]->SetLineColor(q+1);

		SiYUM[q] = new TH1D(Form("SiYUM_%d",q),"",100,-2,2);
		SiYUM[q]->GetXaxis()->SetTitle("Silicon Seed y (cm)");
		SiYUM[q]->GetYaxis()->SetTitle("Number of Silicon Seed");
		SiYUM[q]->GetXaxis()->CenterTitle();
		SiYUM[q]->GetYaxis()->CenterTitle();
		SiYUM[q]->SetMarkerStyle(20);
		SiYUM[q]->SetMarkerSize(1);
		SiYUM[q]->SetMarkerColor(q+1);
		SiYUM[q]->SetLineColor(q+1);


		SiZUM[q] = new TH1D(Form("SiZUM_%d",q),"",50,-15,15);
		SiZUM[q]->GetXaxis()->SetTitle("Silicon Seed z (cm)");
		SiZUM[q]->GetYaxis()->SetTitle("Number of Silicon Seed");
		SiZUM[q]->GetXaxis()->CenterTitle();
		SiZUM[q]->GetYaxis()->CenterTitle();
		SiZUM[q]->SetMarkerStyle(20);
		SiZUM[q]->SetMarkerSize(1);
		SiZUM[q]->SetMarkerColor(q+1);
		SiZUM[q]->SetLineColor(q+1);


		TPCXUM[q] = new TH1D(Form("TPCUM_%d",q),"",100,-10,10);
		TPCXUM[q]->GetXaxis()->SetTitle("TPC Seed x (cm)");
		TPCXUM[q]->GetYaxis()->SetTitle("Number of Silicon Seed");
		TPCXUM[q]->GetXaxis()->CenterTitle();
		TPCXUM[q]->GetYaxis()->CenterTitle();
		TPCXUM[q]->SetMarkerStyle(20);
		TPCXUM[q]->SetMarkerSize(1);
		TPCXUM[q]->SetMarkerColor(q+1);
		TPCXUM[q]->SetLineColor(q+1);

		TPCYUM[q] = new TH1D(Form("TPCYUM_%d",q),"",100,-10,10);
		TPCYUM[q]->GetXaxis()->SetTitle("TPC Seed y (cm)");
		TPCYUM[q]->GetYaxis()->SetTitle("Number of Silicon Seed");
		TPCYUM[q]->GetXaxis()->CenterTitle();
		TPCYUM[q]->GetYaxis()->CenterTitle();
		TPCYUM[q]->SetMarkerStyle(20);
		TPCYUM[q]->SetMarkerSize(1);
		TPCYUM[q]->SetMarkerColor(q+1);
		TPCYUM[q]->SetLineColor(q+1);


		TPCZUM[q] = new TH1D(Form("TPCZUM_%d",q),"",100,-100,100);
		TPCZUM[q]->GetXaxis()->SetTitle("TPC Seed z (cm)");
		TPCZUM[q]->GetYaxis()->SetTitle("Number of Silicon Seed");
		TPCZUM[q]->GetXaxis()->CenterTitle();
		TPCZUM[q]->GetYaxis()->CenterTitle();
		TPCZUM[q]->SetMarkerStyle(20);
		TPCZUM[q]->SetMarkerSize(1);
		TPCZUM[q]->SetMarkerColor(q+1);
		TPCZUM[q]->SetLineColor(q+1);




		SiXM[q] = (TH1D *) SiXUM[q]->Clone(Form("SiXM_%d",q));
		SiYM[q] = (TH1D *) SiYUM[q]->Clone(Form("SiYM_%d",q));
		SiZM[q] = (TH1D *) SiZUM[q]->Clone(Form("SiZM_%d",q));

		
		SiXZCUM[q] = (TH1D *) SiXUM[q]->Clone(Form("SiXZCUM_%d",q));
		SiYZCUM[q] = (TH1D *) SiYUM[q]->Clone(Form("SiYZCUM_%d",q));
		SiZZCUM[q] = (TH1D *) SiZUM[q]->Clone(Form("SiZCZUM_%d",q));


		SiXZCM[q] = (TH1D *) SiXUM[q]->Clone(Form("SiXZCM_%d",q));
		SiYZCM[q] = (TH1D *) SiYUM[q]->Clone(Form("SiYZCM_%d",q));
		SiZZCM[q] = (TH1D *) SiZUM[q]->Clone(Form("SiZCZM_%d",q));
	


		TPCXM[q] = (TH1D *) TPCXUM[q]->Clone(Form("TPCXM_%d",q));
		TPCYM[q] = (TH1D *) TPCYUM[q]->Clone(Form("TPCYM_%d",q));
		TPCZM[q] = (TH1D *) TPCZUM[q]->Clone(Form("TPCZM_%d",q));

		TPCXZCUM[q] = (TH1D *) TPCXUM[q]->Clone(Form("TPCXZCUM_%d",q));
		TPCYZCUM[q] = (TH1D *) TPCYUM[q]->Clone(Form("TPCYZCUM_%d",q));
		TPCZZCUM[q] = (TH1D *) TPCZUM[q]->Clone(Form("TPCZCZUM_%d",q));



		TPCXZCM[q] = (TH1D *) TPCXUM[q]->Clone(Form("TPCXZCM_%d",q));
		TPCYZCM[q] = (TH1D *) TPCYUM[q]->Clone(Form("TPCYZCM_%d",q));
		TPCZZCM[q] = (TH1D *) TPCZUM[q]->Clone(Form("TPCZCZM_%d",q));


		DeltaXZCUM[q] = new TH1D(Form("DeltaXZCUM_%d",q),"",100,-10,10);
		DeltaXZCUM[q]->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
		DeltaXZCUM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaXZCUM[q]->GetXaxis()->CenterTitle();
		DeltaXZCUM[q]->GetYaxis()->CenterTitle();
		DeltaXZCUM[q]->SetMarkerStyle(20);
		DeltaXZCUM[q]->SetMarkerSize(1);
		DeltaXZCUM[q]->SetMarkerColor(q+1);
		DeltaXZCUM[q]->SetLineColor(q+1);

		DeltaYZCUM[q] = new TH1D(Form("DeltaYZCUM_%d",q),"",100,-10,10);
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


		DeltaXZCM[q] = new TH1D(Form("DeltaZZCUM_%d",q),"",100,-10,10);
		DeltaXZCM[q]->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
		DeltaXZCM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaXZCM[q]->GetXaxis()->CenterTitle();
		DeltaXZCM[q]->GetYaxis()->CenterTitle();
		DeltaXZCM[q]->SetMarkerStyle(20);
		DeltaXZCM[q]->SetMarkerSize(1);
		DeltaXZCM[q]->SetMarkerColor(q+1);
		DeltaXZCM[q]->SetLineColor(q+1);

		DeltaYZCM[q] = new TH1D(Form("DeltaYZCM_%d",q),"",100,-10,10);
		DeltaYZCM[q]->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
		DeltaYZCM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaYZCM[q]->GetXaxis()->CenterTitle();
		DeltaYZCM[q]->GetYaxis()->CenterTitle();
		DeltaYZCM[q]->SetMarkerStyle(20);
		DeltaYZCM[q]->SetMarkerSize(1);
		DeltaYZCM[q]->SetMarkerColor(q+1);
		DeltaYZCM[q]->SetLineColor(q+1);

		DeltaZZCM[q] = new TH1D(Form("DeltaZZCM_%d",q),"",100,-100,100);
		DeltaZZCM[q]->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
		DeltaZZCM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaZZCM[q]->GetXaxis()->CenterTitle();
		DeltaZZCM[q]->GetYaxis()->CenterTitle();
		DeltaZZCM[q]->SetMarkerStyle(20);
		DeltaZZCM[q]->SetMarkerSize(1);
		DeltaZZCM[q]->SetMarkerColor(q+1);
		DeltaZZCM[q]->SetLineColor(q+1);



		DeltaPhiZCM[q] = new TH1D(Form("DeltaPhiZCM_%d",q),"",100,-3.2,3.2);
		DeltaPhiZCM[q]->GetXaxis()->SetTitle("Silicon Seed #phi - TPC Seed #phi: #Delta #phi (rad)");
		DeltaPhiZCM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaPhiZCM[q]->GetXaxis()->CenterTitle();
		DeltaPhiZCM[q]->GetYaxis()->CenterTitle();
		DeltaPhiZCM[q]->SetMarkerStyle(20);
		DeltaPhiZCM[q]->SetMarkerSize(1);
		DeltaPhiZCM[q]->SetMarkerColor(q+1);
		DeltaPhiZCM[q]->SetLineColor(q+1);

		DeltaEtaZCM[q] = new TH1D(Form("DeltaEtaZCM_%d",q),"",100,-3,3);
		DeltaEtaZCM[q]->GetXaxis()->SetTitle("Silicon Seed #eta - TPC Seed #eta: #Delta #eta");
		DeltaEtaZCM[q]->GetYaxis()->SetTitle("Number of Seed Pairs");
		DeltaEtaZCM[q]->GetXaxis()->CenterTitle();
		DeltaEtaZCM[q]->GetYaxis()->CenterTitle();
		DeltaEtaZCM[q]->SetMarkerStyle(20);
		DeltaEtaZCM[q]->SetMarkerSize(1);
		DeltaEtaZCM[q]->SetMarkerColor(q+1);
		DeltaEtaZCM[q]->SetLineColor(q+1);




		DeltaXUM[q] = (TH1D *) DeltaXZCUM[q]->Clone(Form("DeltaXUM_%d",q));
		DeltaYUM[q] = (TH1D *) DeltaYZCUM[q]->Clone(Form("DeltaYUM_%d",q));
		DeltaZUM[q] = (TH1D *) DeltaZZCUM[q]->Clone(Form("DeltaZUM_%d",q));

		DeltaXM[q] = (TH1D *) DeltaXZCM[q]->Clone(Form("DeltaXM_%d",q));
		DeltaYM[q] = (TH1D *) DeltaYZCM[q]->Clone(Form("DeltaYM_%d",q));
		DeltaZM[q] = (TH1D *) DeltaZZCM[q]->Clone(Form("DeltaZM_%d",q));


		DeltaPhiM[q] = (TH1D *) DeltaPhiZCM[q]->Clone(Form("DeltaPhiM_%d",q));
		DeltaPhiUM[q] = (TH1D *) DeltaPhiZCM[q]->Clone(Form("DeltaPhiUM_%d",q));
		DeltaPhiZCUM[q] = (TH1D *) DeltaPhiZCM[q]->Clone(Form("DeltaPhiZCUM_%d",q));

		DeltaEtaM[q] = (TH1D *) DeltaEtaZCM[q]->Clone(Form("DeltaEtaM_%d",q));
		DeltaEtaUM[q] = (TH1D *) DeltaEtaZCM[q]->Clone(Form("DeltaEtaUM_%d",q));
		DeltaEtaZCUM[q] = (TH1D *) DeltaEtaZCM[q]->Clone(Form("DeltaEtaZCUM_%d",q));

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

		float pt;

		int NEvents = SeedAna->GetEntries();

		NEvents = 200;



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
		//	cout << "Pass 1" << endl;

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

				//	dphi = TMath::ATan2(siseedy->at(j),siseedx->at(j)) - TMath::ATan2(tpcseedy->at(k),tpcseedx->at(k)); 

/*
					sixcal = siseedx->at(j);
					siycal = siseedy->at(j);
					sizcal = siseedz->at(j);
					sirhocal = sqrt(sixcal * sixcal + siycal * siycal);
					sircal = sqrt(sixcal * sixcal + siycal * siycal + sizcal * sizcal);
					tpcxcal = tpcseedx->at(k);
					tpcycal = tpcseedy->at(k);
					tpczcal = tpcseedz->at(k);
					tpcrhocal = sqrt(tpcxcal * tpcxcal + tpcycal * tpcycal);
					tpcrcal = sqrt(tpcxcal * tpcxcal + tpcycal * tpcycal + tpczcal * tpczcal);
					sieta = TMath::Log(sirhocal/(sircal - sizcal));
					tpceta = TMath::Log(tpcrhocal/(tpcrcal - tpczcal));
*/


					sieta =  siseedeta->at(j);
					tpceta =  tpcseedeta->at(k);
		
					dphi = siseedphi->at(j) -  tpcseedeta->at(k); 

					deta = sieta - tpceta;



					DeltaXUM[q]->Fill(dx);
					DeltaYUM[q]->Fill(dy);
					DeltaZUM[q]->Fill(dz);
					DeltaPhiUM[q]->Fill(dphi);
					DeltaEtaUM[q]->Fill(deta);


					SiXUM[q]->Fill(sixcal);
					SiYUM[q]->Fill(siycal);
					SiZUM[q]->Fill(sizcal);


					TPCXUM[q]->Fill(tpcxcal);
					TPCYUM[q]->Fill(tpcycal);
					TPCZUM[q]->Fill(tpczcal);

					//	pt = sqrt(tpcseedpx->at(k) * tpcseedpx->at(k) + tpcseedpy->at(k) * tpcseedpy->at(k));


					if(crossing->at(j) == 0){

						DeltaXZCUM[q]->Fill(dx);
						DeltaYZCUM[q]->Fill(dy);
						DeltaZZCUM[q]->Fill(dz);
						DeltaPhiZCUM[q]->Fill(dphi);
						DeltaEtaZCUM[q]->Fill(deta);

						SiXZCUM[q]->Fill(sixcal);
						SiYZCUM[q]->Fill(siycal);
						SiZZCUM[q]->Fill(sizcal);


						TPCXZCUM[q]->Fill(tpcxcal);
						TPCYZCUM[q]->Fill(tpcycal);
						TPCZZCUM[q]->Fill(tpczcal);


						//siseedsizezc++;
						//		tpcseedsizezc++;

					}




				}



			}


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

			for(int j = 0; j < svtxsiseedsize; j++){



				dx = svtxsiseedx->at(j) - svtxtpcseedx->at(j);
				dy = svtxsiseedy->at(j) - svtxtpcseedy->at(j);
				dz = svtxsiseedz->at(j) - svtxtpcseedz->at(j);

			//	dphi = TMath::ATan2(svtxsiseedy->at(j),svtxsiseedx->at(j)) - TMath::ATan2(svtxtpcseedy->at(j),svtxtpcseedx->at(j)); 



				dpx = svtxsiseedpx->at(j) - svtxtpcseedpx->at(j);
				dpy = svtxsiseedpy->at(j) - svtxtpcseedpy->at(j);
				dpz = svtxsiseedpz->at(j) - svtxtpcseedpz->at(j);

				/*
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

				*/


				sieta =  svtxsiseedeta->at(j);	
				tpceta =  svtxtpcseedeta->at(j);
		
				dphi = svtxsiseedphi->at(j) -  svtxtpcseedeta->at(j); 
				deta = sieta - tpceta;



				//cout << "Pass 3" << endl;

				DeltaXM[q]->Fill(dx);
				DeltaYM[q]->Fill(dy);
				DeltaZM[q]->Fill(dz);
				DeltaPhiM[q]->Fill(dphi);
				DeltaEtaM[q]->Fill(deta);

				//cout << "Pass 3.2" << endl;

				
				SiXM[q]->Fill(sixcal);
				SiYM[q]->Fill(siycal);
				SiZM[q]->Fill(sizcal);

				//cout << "Pass 3.5" << endl;

				TPCXM[q]->Fill(tpcxcal);
				TPCYM[q]->Fill(tpcycal);
				TPCZM[q]->Fill(tpczcal);

				//	cout << "Pass 4" << endl;


				if(svtxcrossing->at(j) == 0){

					DeltaXZCM[q]->Fill(dx);
					DeltaYZCM[q]->Fill(dy);
					DeltaZZCM[q]->Fill(dz);
					DeltaPhiZCM[q]->Fill(dphi);
					DeltaEtaZCM[q]->Fill(deta);

				
					SiXZCM[q]->Fill(sixcal);
					SiYZCM[q]->Fill(siycal);
					SiZZCM[q]->Fill(sizcal);
	
					TPCXZCM[q]->Fill(tpcxcal);
					TPCYZCM[q]->Fill(tpcycal);
					TPCZZCM[q]->Fill(tpczcal);

					//cout << "svtxcrossing->at(j) = " << svtxcrossing->at(j) << endl;
					svtxsiseedsizezc++;
					svtxsiseedxzc.push_back(svtxsiseedx->at(j));
					svtxtpcseedxzc.push_back(svtxtpcseedx->at(j));

				}



			}




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

		}

	}




	TFile * fout = new TFile("Analysis.root","RECREATE");
	fout->cd();




	TLegend * leg  = new TLegend(0.15,0.72,0.50,0.88,NULL,"brNDC");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.040);
	leg->SetTextFont(42);
	leg->SetFillStyle(0);
	leg->SetLineWidth(3);


	for(int q = 0; q < NRuns; q++){

		DeltaXUM[q]->Write();
		leg->AddEntry(DeltaXZCUM[q],Form("Run: %d",RunNumber[q]),"LP");
		DeltaXUM[q]->Scale(1.0/DeltaXZCUM[q]->Integral());

		if(q == 0) DeltaXUM[q]->Draw("ep");
		if(q > 0) DeltaXUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/X/DeltaXUM.png");


	for(int q = 0; q < NRuns; q++){
	
		DeltaXM[q]->Write();



	//	leg->AddEntry(DeltaXM[q],Form("Run: %d",RunNumber[q]),"LP");
		DeltaXM[q]->Scale(1.0/DeltaXM[q]->Integral());

		if(q == 0) DeltaXM[q]->Draw("ep");
		if(q > 0) DeltaXM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/X/DeltaXM.png");

	for(int q = 0; q < NRuns; q++){
		DeltaXZCUM[q]->Write();
	

//		leg->AddEntry(DeltaXZCUM[q],Form("Run: %d",RunNumber[q]),"LP");
		DeltaXZCUM[q]->Scale(1.0/DeltaXZCUM[q]->Integral());

		if(q == 0) DeltaXZCUM[q]->Draw("ep");
		if(q > 0) DeltaXZCUM[q]->Draw("epSAME");
	
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/X/DeltaXZCUM.png");


	for(int q = 0; q < NRuns; q++){
	

		DeltaXZCM[q]->Write();

	//	leg->AddEntry(DeltaXZCM[q],Form("Run: %d",RunNumber[q]),"LP");
		DeltaXZCM[q]->Scale(1.0/DeltaXZCM[q]->Integral());
		
		DeltaXZCM[q]->SetMaximum(0.4);

		if(q == 0) DeltaXZCM[q]->Draw("ep");
		if(q > 0) DeltaXZCM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/X/DeltaXZCM.png");


	for(int q = 0; q < NRuns; q++){
	

		DeltaYUM[q]->Write();
		
		DeltaYUM[q]->SetMaximum(0.4);


		DeltaYUM[q]->Scale(1.0/DeltaYUM[q]->Integral());
	
		if(q == 0) DeltaYUM[q]->Draw("ep");
		if(q > 0) DeltaYUM[q]->Draw("epSAME");

	}

	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Y/DeltaYUM.png");

	for(int q = 0; q < NRuns; q++){
	
		DeltaYZCUM[q]->Write();


		DeltaYZCUM[q]->Scale(1.0/DeltaYZCUM[q]->Integral());
	
		if(q == 0) DeltaYZCUM[q]->Draw("ep");
		if(q > 0) DeltaYZCUM[q]->Draw("epSAME");

	}

	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Y/DeltaYZCUM.png");


	for(int q = 0; q < NRuns; q++){
	
		DeltaYM[q]->Write();
		
		DeltaYM[q]->Scale(1.0/DeltaYM[q]->Integral());
	
		if(q == 0) DeltaYM[q]->Draw("ep");
		if(q > 0) DeltaYM[q]->Draw("epSAME");

	}

	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Y/DeltaYM.png");



	for(int q = 0; q < NRuns; q++){
	
		DeltaYZCM[q]->Write();
	
		if(q == 0) DeltaYZCM[q]->Draw("ep");
		if(q > 0) DeltaYZCM[q]->Draw("epSAME");
		DeltaYZCM[q]->Scale(1.0/DeltaYZCM[q]->Integral());

	}

	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Y/DeltaYZCM.png");


	for(int q = 0; q < NRuns; q++){
	
		DeltaZUM[q]->Write();

		DeltaZUM[q]->Scale(1.0/DeltaZUM[q]->Integral());
	
		if(q == 0) DeltaZUM[q]->Draw("ep");
		if(q > 0) DeltaZUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Z/DeltaZUM.png");


	for(int q = 0; q < NRuns; q++){

		DeltaZZCUM[q]->Write();
		

		DeltaZZCUM[q]->Scale(1.0/DeltaZZCUM[q]->Integral());
	
		if(q == 0) DeltaZZCUM[q]->Draw("ep");
		if(q > 0) DeltaZZCUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Z/DeltaZZCUM.png");


	for(int q = 0; q < NRuns; q++){
	
		DeltaZM[q]->Write();
		

		if(q == 0) DeltaZM[q]->Draw("ep");
		if(q > 0) DeltaZM[q]->Draw("epSAME");
		DeltaZM[q]->Scale(1.0/DeltaZM[q]->Integral());
	
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Z/DeltaZM.png");


	for(int q = 0; q < NRuns; q++){
	
		DeltaZZCM[q]->Write();

		DeltaZZCM[q]->Scale(1.0/DeltaZZCM[q]->Integral());
	
		if(q == 0) DeltaZZCM[q]->Draw("ep");
		if(q > 0) DeltaZZCM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Z/DeltaZZCM.png");



	for(int q = 0; q < NRuns; q++){
	
		DeltaPhiZCUM[q]->Write();

		DeltaPhiZCUM[q]->Scale(1.0/DeltaPhiZCUM[q]->Integral());
	
		if(q == 0) DeltaPhiZCUM[q]->Draw("ep");
		if(q > 0) DeltaPhiZCUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Phi/DeltaPhiZCUM.png");


	for(int q = 0; q < NRuns; q++){
	
		DeltaPhiZCM[q]->Write();
		
		DeltaPhiZCM[q]->Scale(1.0/DeltaPhiZCM[q]->Integral());

		if(q == 0) DeltaPhiZCM[q]->Draw("ep");
		if(q > 0) DeltaPhiZCM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Phi/DeltaPhiZCM.png");


	for(int q = 0; q < NRuns; q++){
	
		DeltaPhiUM[q]->Write();

		DeltaPhiUM[q]->Scale(1.0/DeltaPhiUM[q]->Integral());
	
		if(q == 0) DeltaPhiUM[q]->Draw("ep");
		if(q > 0) DeltaPhiUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Phi/DeltaPhiUM.png");


	for(int q = 0; q < NRuns; q++){
		DeltaPhiM[q]->Write();
		DeltaPhiM[q]->Scale(1.0/DeltaPhiM[q]->Integral());
	
		if(q == 0) DeltaPhiM[q]->Draw("ep");
		if(q > 0) DeltaPhiM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Phi/DeltaPhiM.png");


	for(int q = 0; q < NRuns; q++){
		
		DeltaEtaUM[q]->Write();

		DeltaEtaUM[q]->Scale(1.0/DeltaEtaUM[q]->Integral());
	
		if(q == 0) DeltaEtaUM[q]->Draw("ep");
		if(q > 0) DeltaEtaUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Eta/DeltaEtaUM.png");


	for(int q = 0; q < NRuns; q++){

	
		DeltaEtaM[q]->Write();
		DeltaEtaM[q]->Scale(1.0/DeltaEtaM[q]->Integral());
		
		if(q == 0) DeltaEtaM[q]->Draw("ep");
		if(q > 0) DeltaEtaM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Eta/DeltaEtaM.png");


	for(int q = 0; q < NRuns; q++){
		DeltaEtaZCUM[q]->Write();
		DeltaEtaZCUM[q]->Scale(1.0/DeltaEtaZCUM[q]->Integral());
	
		if(q == 0) DeltaEtaZCUM[q]->Draw("ep");
		if(q > 0) DeltaEtaZCUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Eta/DeltaEtaZCUM.png");


	for(int q = 0; q < NRuns; q++){
		DeltaEtaZCM[q]->Write();
		DeltaEtaZCM[q]->Scale(1.0/DeltaEtaZCM[q]->Integral());
	
		if(q == 0) DeltaEtaZCM[q]->Draw("ep");
		if(q > 0) DeltaEtaZCM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/Eta/DeltaEtaZCM.png");



	//Individual si/tpc xyz

	for(int q = 0; q < NRuns; q++){

		SiXUM[q]->Write();
	//	leg->AddEntry(SiXUM[q],Form("Run: %d",RunNumber[q]),"LP");
		SiXUM[q]->Scale(1.0/SiXUM[q]->Integral());

		if(q == 0) SiXUM[q]->Draw("ep");
		if(q > 0) SiXUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/SiX/SiXUM.png");

	for(int q = 0; q < NRuns; q++){

		SiYUM[q]->Write();
	//	leg->AddEntry(SiYUM[q],Form("Run: %d",RunNumber[q]),"LP");
		SiYUM[q]->Scale(1.0/SiYUM[q]->Integral());

		if(q == 0) SiYUM[q]->Draw("ep");
		if(q > 0) SiYUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/SiY/SiYUM.png");

	for(int q = 0; q < NRuns; q++){

		SiZUM[q]->Write();
	//	leg->AddEntry(SiZUM[q],Form("Run: %d",RunNumber[q]),"LP");
		SiZUM[q]->Scale(1.0/SiZUM[q]->Integral());

		if(q == 0) SiZUM[q]->Draw("ep");
		if(q > 0) SiZUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/SiZ/SiZUM.png");



	for(int q = 0; q < NRuns; q++){

		SiXZCUM[q]->Write();
	//	leg->AddEntry(SiXUM[q],Form("Run: %d",RunNumber[q]),"LP");
		SiXZCUM[q]->Scale(1.0/SiXZCUM[q]->Integral());

		if(q == 0) SiXZCUM[q]->Draw("ep");
		if(q > 0) SiXZCUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/SiX/SiXZCUM.png");

	for(int q = 0; q < NRuns; q++){

		SiYZCUM[q]->Write();
	//	leg->AddEntry(SiYUM[q],Form("Run: %d",RunNumber[q]),"LP");
		SiYZCUM[q]->Scale(1.0/SiYZCUM[q]->Integral());

		if(q == 0) SiYZCUM[q]->Draw("ep");
		if(q > 0) SiYZCUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/SiY/SiYZCUM.png");

	for(int q = 0; q < NRuns; q++){

		SiZZCUM[q]->Write();
	//	leg->AddEntry(SiZUM[q],Form("Run: %d",RunNumber[q]),"LP");
		SiZZCUM[q]->Scale(1.0/SiZZCUM[q]->Integral());

		if(q == 0) SiZZCUM[q]->Draw("ep");
		if(q > 0) SiZZCUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/SiZ/SiZZCUM.png");


	//TPC


	for(int q = 0; q < NRuns; q++){

		TPCXUM[q]->Write();
	//	leg->AddEntry(TPCXUM[q],Form("Run: %d",RunNumber[q]),"LP");
		TPCXUM[q]->Scale(1.0/TPCXUM[q]->Integral());

		if(q == 0) TPCXUM[q]->Draw("ep");
		if(q > 0) TPCXUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/TPCX/TPCXUM.png");

	for(int q = 0; q < NRuns; q++){

		TPCYUM[q]->Write();
	//	leg->AddEntry(TPCYUM[q],Form("Run: %d",RunNumber[q]),"LP");
		TPCYUM[q]->Scale(1.0/TPCYUM[q]->Integral());

		if(q == 0) TPCYUM[q]->Draw("ep");
		if(q > 0) TPCYUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/TPCY/TPCYUM.png");

	for(int q = 0; q < NRuns; q++){

		TPCZUM[q]->Write();
	//	leg->AddEntry(TPCZUM[q],Form("Run: %d",RunNumber[q]),"LP");
		TPCZUM[q]->Scale(1.0/TPCZUM[q]->Integral());

		if(q == 0) TPCZUM[q]->Draw("ep");
		if(q > 0) TPCZUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/TPCZ/TPCZUM.png");



	for(int q = 0; q < NRuns; q++){

		TPCXZCUM[q]->Write();
	//	leg->AddEntry(TPCXUM[q],Form("Run: %d",RunNumber[q]),"LP");
		TPCXZCUM[q]->Scale(1.0/TPCXZCUM[q]->Integral());

		if(q == 0) TPCXZCUM[q]->Draw("ep");
		if(q > 0) TPCXZCUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/TPCX/TPCXZCUM.png");

	for(int q = 0; q < NRuns; q++){

		TPCYZCUM[q]->Write();
	//	leg->AddEntry(TPCYUM[q],Form("Run: %d",RunNumber[q]),"LP");
		TPCYZCUM[q]->Scale(1.0/TPCYZCUM[q]->Integral());

		if(q == 0) TPCYZCUM[q]->Draw("ep");
		if(q > 0) TPCYZCUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/TPCY/TPCYZCUM.png");

	for(int q = 0; q < NRuns; q++){

		TPCZZCUM[q]->Write();
	//	leg->AddEntry(TPCZUM[q],Form("Run: %d",RunNumber[q]),"LP");
		TPCZZCUM[q]->Scale(1.0/TPCZZCUM[q]->Integral());

		if(q == 0) TPCZZCUM[q]->Draw("ep");
		if(q > 0) TPCZZCUM[q]->Draw("epSAME");
		
	}
	leg->Draw("SAME");
	c->SaveAs("PlotMUM/TPCZ/TPCZZCUM.png");



	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);

	cout << "duration: " << duration.count() << " s" << endl;

	fout->Close();
	
}

