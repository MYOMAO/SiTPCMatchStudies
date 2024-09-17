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

void QuickAnaMatch(){

	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();


	c->SetLeftMargin(0.14);


	TString infiles = {"SeedAna_Svtx.root"};
	TFile * fin = new TFile(infiles.Data());
	fin->cd();



	int event;
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

//	NEvents = 1000;

	TH1D * DeltaQPt = new TH1D("DeltaQPt","",50,0,5);
	DeltaQPt->GetXaxis()->SetTitle("Silicon-TPC Matched Svtx Track p_{T} (GeV/c)");
	DeltaQPt->GetYaxis()->SetTitle("Fraction of |#Delta Q| = 2");
	DeltaQPt->GetXaxis()->CenterTitle();
	DeltaQPt->GetYaxis()->CenterTitle();
	DeltaQPt->GetYaxis()->SetTitleOffset(1.4);
	
	DeltaQPt->SetMarkerSize(1);
	DeltaQPt->SetMarkerStyle(20);
	DeltaQPt->SetMarkerColor(1);
	DeltaQPt->SetLineColor(1);

	TH1D * DeltaQPtZ = (TH1D *) DeltaQPt->Clone("DeltaQPtZ");
	TH1D * DeltaQPtNZEff = (TH1D *) DeltaQPt->Clone("DeltaQPtNZEff");

	
	TH1D * DeltaQPtZC =  new TH1D("DeltaQPtZC","",50,0,5);
	DeltaQPtZC->GetXaxis()->SetTitle("Silicon-TPC Matched Svtx Track p_{T} (GeV/c)");
	DeltaQPtZC->GetYaxis()->SetTitle("Fraction of |#Delta Q| = 2");
	DeltaQPtZC->GetXaxis()->CenterTitle();
	DeltaQPtZC->GetYaxis()->CenterTitle();
	DeltaQPtZC->GetYaxis()->SetTitleOffset(1.4);

	DeltaQPtZC->SetMarkerSize(1);
	DeltaQPtZC->SetMarkerStyle(20);
	DeltaQPtZC->SetMarkerColor(1);
	DeltaQPtZC->SetLineColor(1);



	TH1D * DeltaQPtZCZ = (TH1D *) DeltaQPtZC->Clone("DeltaQPtZCZ");
	TH1D * DeltaQPtZCNZEff = (TH1D *) DeltaQPtZC->Clone("DeltaQPtZCNZEff");



	TH1D * DeltaQPhi = new TH1D("DeltaQPhi","",50,0,5);
	DeltaQPhi->GetXaxis()->SetTitle("Silicon-TPC Matched Svtx Track #phi (rad)");
	DeltaQPhi->GetYaxis()->SetTitle("Fraction of |#Delta Q| = 2");
	DeltaQPhi->GetXaxis()->CenterTitle();
	DeltaQPhi->GetYaxis()->CenterTitle();
	DeltaQPhi->GetYaxis()->SetTitleOffset(1.4);
	
	DeltaQPhi->SetMarkerSize(1);
	DeltaQPhi->SetMarkerStyle(20);
	DeltaQPhi->SetMarkerColor(1);
	DeltaQPhi->SetLineColor(1);

	TH1D * DeltaQPhiZ = (TH1D *) DeltaQPt->Clone("DeltaQPhiZ");
	TH1D * DeltaQPhiNZEff = (TH1D *) DeltaQPt->Clone("DeltaQPhiNZEff");

	
	TH1D * DeltaQPhiZC =  new TH1D("DeltaQPtZC","",50,-3.2,3.2);
	DeltaQPhiZC->GetXaxis()->SetTitle("Silicon-TPC Matched Svtx Track #phi (rad)");
	DeltaQPhiZC->GetYaxis()->SetTitle("Fraction of |#Delta Q| = 2");
	DeltaQPhiZC->GetXaxis()->CenterTitle();
	DeltaQPhiZC->GetYaxis()->CenterTitle();
	DeltaQPhiZC->GetYaxis()->SetTitleOffset(1.4);

	DeltaQPhiZC->SetMarkerSize(1);
	DeltaQPhiZC->SetMarkerStyle(20);
	DeltaQPhiZC->SetMarkerColor(1);
	DeltaQPhiZC->SetLineColor(1);



	TH1D * DeltaQPhiZCZ = (TH1D *) DeltaQPtZC->Clone("DeltaQPhiZCZ");
	TH1D * DeltaQPhiZCNZEff = (TH1D *) DeltaQPtZC->Clone("DeltaQPhiZCNZEff");



	TH1D * DeltaQEta = new TH1D("DeltaQEta","",50,-3,3);
	DeltaQEta->GetXaxis()->SetTitle("Silicon-TPC Matched Svtx Track #eta");
	DeltaQEta->GetYaxis()->SetTitle("Fraction of |#Delta Q| = 2");
	DeltaQEta->GetXaxis()->CenterTitle();
	DeltaQEta->GetYaxis()->CenterTitle();
	DeltaQEta->GetYaxis()->SetTitleOffset(1.4);
	
	DeltaQEta->SetMarkerSize(1);
	DeltaQEta->SetMarkerStyle(20);
	DeltaQEta->SetMarkerColor(1);
	DeltaQEta->SetLineColor(1);

	TH1D * DeltaQEtaZ = (TH1D *) DeltaQEta->Clone("DeltaQEtaZ");
	TH1D * DeltaQEtaNZEff = (TH1D *) DeltaQEta->Clone("DeltaQEtaNZEff");


	TH1D * DeltaQEtaZC =  new TH1D("DeltaQEtaZC","",50,-3,3);
	DeltaQEtaZC->GetXaxis()->SetTitle("Silicon-TPC Matched Svtx Track #eta");
	DeltaQEtaZC->GetYaxis()->SetTitle("Fraction of |#Delta Q| = 2");
	DeltaQEtaZC->GetXaxis()->CenterTitle();
	DeltaQEtaZC->GetYaxis()->CenterTitle();
	DeltaQEtaZC->GetYaxis()->SetTitleOffset(1.4);

	DeltaQEtaZC->SetMarkerSize(1);
	DeltaQEtaZC->SetMarkerStyle(20);
	DeltaQEtaZC->SetMarkerColor(1);
	DeltaQEtaZC->SetLineColor(1);



	TH1D * DeltaQEtaZCZ = (TH1D *) DeltaQEtaZC->Clone("DeltaQEtaZCZ");
	TH1D * DeltaQEtaZCNZEff = (TH1D *) DeltaQEtaZC->Clone("DeltaQEtaZCNZEff");



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
	

	for(int i = 0; i < NEvents; i++){
	
		if(i%100==0) cout << "Now Working on Event: " << i << "   Out of Total Event: " << NEvents << endl;

		SeedAna->GetEntry(i);
	
		svtxsiseedsize = svtxsiseedx->size();
		svtxtpcseedsize = svtxtpcseedy->size();

		//cout << "siseedsize = " << siseedsize << "  tpcseedsize = " << tpcseedsize << "    svtxsiseedsize " << svtxsiseedsize << endl;

		//	cout << "svtxsiseedsize = " << svtxsiseedsize << "  svtxtpcseedsize = " << svtxtpcseedsize << endl;
		int svtxsiseedsizezc = 0;

		std::vector<float> svtxsiseedxzc;
		std::vector<float> svtxtpcseedxzc;

		for(int j = 0; j < svtxsiseedsize; j++){



			dx = svtxsiseedx->at(j) - svtxtpcseedx->at(j);
			dy = svtxsiseedy->at(j) - svtxtpcseedy->at(j);
			dz = svtxsiseedz->at(j) - svtxtpcseedz->at(j);

			dphi = TMath::ATan2(svtxsiseedy->at(j),svtxsiseedx->at(j)) - TMath::ATan2(svtxtpcseedy->at(j),svtxtpcseedx->at(j)); 



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

			dpx = svtxsiseedpx->at(j) - svtxtpcseedpx->at(j);
			dpy = svtxsiseedpy->at(j) - svtxtpcseedpy->at(j);
			dpz = svtxsiseedpz->at(j) - svtxtpcseedpz->at(j);

			dq = svtxsiseedcharge->at(j) - svtxtpcseedcharge->at(j);
			
			pt = sqrt(svtxtpcseedpx->at(j) * svtxtpcseedpx->at(j) + svtxtpcseedpy->at(j) * svtxtpcseedpy->at(j));


		
			DeltaQPt->Fill(pt);
			DeltaQEta->Fill(tpceta);
			if(dq != 0){
				DeltaQPtNZEff->Fill(pt);
				DeltaQEtaNZEff->Fill(tpceta);
			}


			if(svtxcrossing->at(j) == 0){
				
				//cout << "svtxcrossing->at(j) = " << svtxcrossing->at(j) << endl;
				svtxsiseedsizezc++;
		
				DeltaQPtZC->Fill(pt);
				DeltaQEtaZC->Fill(tpceta);
				
				if(dq != 0){
					DeltaQPtZCNZEff->Fill(pt);
					DeltaQEtaZCNZEff->Fill(tpceta);
				}
			}



		}



	}

	DeltaQPt->Sumw2();
	DeltaQPtZC->Sumw2();
	DeltaQPtNZEff->Sumw2();
	DeltaQPtZCNZEff->Sumw2();


	cout << "DeltaQPt->Integral() = " << DeltaQPt->Integral()  <<  "   DeltaQPtZC->Integral() = " << DeltaQPtZC->Integral() << endl;
	cout << "DeltaQPtNZEff->Integral() = " << DeltaQPtNZEff->Integral()  <<  "   DeltaQPtZCNZEff->Integral() = " << DeltaQPtZCNZEff->Integral() << endl;

	DeltaQPtNZEff->Divide(DeltaQPt);
	DeltaQPtZCNZEff->Divide(DeltaQPtZC);


	DeltaQPtZCNZEff->SetLineColor(kRed);
	DeltaQPtZCNZEff->SetMarkerColor(kRed);




	TLegend * leg3  = new TLegend(0.15,0.72,0.50,0.88,NULL,"brNDC");
	leg3->SetBorderSize(0);
	leg3->SetTextSize(0.040);
	leg3->SetTextFont(42);
	leg3->SetFillStyle(0);
	leg3->SetLineWidth(3);


	leg3->AddEntry(DeltaQPtNZEff,"All Crossing","LP");
	leg3->AddEntry(DeltaQPtZCNZEff,"Crossing = 0","LP");


	DeltaQPtNZEff->SetMinimum(0);
	DeltaQPtNZEff->SetMaximum(1);

	DeltaQPtNZEff->Draw("ep");
	DeltaQPtZCNZEff->Draw("epSAME");
	leg3->Draw("SAME");


	c->SaveAs("PlotMore/DeltaQPtNZEff.png");


	//Eta

	DeltaQEta->Sumw2();
	DeltaQEtaZC->Sumw2();
	DeltaQEtaNZEff->Sumw2();
	DeltaQEtaZCNZEff->Sumw2();


//	cout << "DeltaQPt->Integral() = " << DeltaQPt->Integral()  <<  "   DeltaQPtZC->Integral() = " << DeltaQPtZC->Integral() << endl;
//	cout << "DeltaQPtNZEff->Integral() = " << DeltaQPtNZEff->Integral()  <<  "   DeltaQPtZCNZEff->Integral() = " << DeltaQPtZCNZEff->Integral() << endl;

	DeltaQEtaNZEff->Divide(DeltaQEta);
	DeltaQEtaZCNZEff->Divide(DeltaQEtaZC);


	DeltaQEtaZCNZEff->SetLineColor(kRed);
	DeltaQEtaZCNZEff->SetMarkerColor(kRed);



	DeltaQEtaNZEff->SetMinimum(0);
	DeltaQEtaNZEff->SetMaximum(1);

	DeltaQEtaNZEff->Draw("ep");
	DeltaQEtaZCNZEff->Draw("epSAME");
	leg3->Draw("SAME");


	c->SaveAs("PlotMore/DeltaQEtaNZEff.png");

}
