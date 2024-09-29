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

void LaserDemo(){




	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();


	c->SetLeftMargin(0.14);


	TString infiles = {"/Users/zhaozhongshi/Desktop/TempDownload/SiTPCMatchFiles/Test.root"};
	TFile * fin = new TFile(infiles.Data());
	fin->cd();


	std::vector<float> * tpcseedx = 0;
	std::vector<float> * tpcseedy = 0;	
	std::vector<float> * tpcseedz = 0;
	bool IsLaserEvt;

	TTree * SeedAna = (TTree *) fin->Get("SeedAna");
//	SeedAna->SetBranchAddress("event",&event);
	SeedAna->SetBranchAddress("IsLaserEvt",&IsLaserEvt);

	SeedAna->SetBranchAddress("tpcseedx",&tpcseedx);
	SeedAna->SetBranchAddress("tpcseedy",&tpcseedy);
	SeedAna->SetBranchAddress("tpcseedz",&tpcseedz);
	
	int NEvents = SeedAna->GetEntries();

	TH1D * Inc = new TH1D("Inc","",200,-100,100);
	Inc->GetXaxis()->SetTitle("TPC Seed z (cm)");
	Inc->GetYaxis()->SetTitle("Number of TPC Seeds");
	Inc->GetXaxis()->CenterTitle();
	Inc->GetYaxis()->CenterTitle();
	Inc->GetYaxis()->SetTitleOffset(1.4);

	Inc->SetLineColor(kBlack);
	Inc->SetLineWidth(2);



	TH1D * IncLaser = new TH1D("IncLaser","",200,-100,100);
	IncLaser->GetXaxis()->SetTitle("TPC Seed z (cm)");
	IncLaser->GetYaxis()->SetTitle("Number of TPC Seeds");
	IncLaser->GetXaxis()->CenterTitle();
	IncLaser->GetYaxis()->CenterTitle();
	IncLaser->GetYaxis()->SetTitleOffset(1.4);

	IncLaser->SetLineColor(kRed);
	IncLaser->SetLineWidth(2);

	TH1D * IncNoLaser = new TH1D("IncNoLaser","",200,-100,100);
	IncNoLaser->GetXaxis()->SetTitle("TPC Seed z (cm)");
	IncNoLaser->GetYaxis()->SetTitle("Number of TPC Seeds");
	IncNoLaser->GetXaxis()->CenterTitle();
	IncNoLaser->GetYaxis()->CenterTitle();
	IncNoLaser->GetYaxis()->SetTitleOffset(1.4);

	IncNoLaser->SetLineColor(kBlue);
	IncNoLaser->SetLineWidth(2);



	//X and Y


	TH1D * IncX = new TH1D("IncX","",200,-100,100);
	IncX->GetXaxis()->SetTitle("TPC Seed x (cm)");
	IncX->GetYaxis()->SetTitle("Number of TPC Seeds");
	IncX->GetXaxis()->CenterTitle();
	IncX->GetYaxis()->CenterTitle();
	IncX->GetYaxis()->SetTitleOffset(1.4);

	IncX->SetLineColor(kBlack);
	IncX->SetLineWidth(2);



	TH1D * IncLaserX = new TH1D("IncLaserX","",200,-100,100);
	IncLaserX->GetXaxis()->SetTitle("TPC Seed x (cm)");
	IncLaserX->GetYaxis()->SetTitle("Number of TPC Seeds");
	IncLaserX->GetXaxis()->CenterTitle();
	IncLaserX->GetYaxis()->CenterTitle();
	IncLaserX->GetYaxis()->SetTitleOffset(1.4);

	IncLaserX->SetLineColor(kRed);
	IncLaserX->SetLineWidth(2);

	TH1D * IncNoLaserX = new TH1D("IncNoLaserX","",200,-100,100);
	IncNoLaserX->GetXaxis()->SetTitle("TPC Seed x (cm)");
	IncNoLaserX->GetYaxis()->SetTitle("Number of TPC Seeds");
	IncNoLaserX->GetXaxis()->CenterTitle();
	IncNoLaserX->GetYaxis()->CenterTitle();
	IncNoLaserX->GetYaxis()->SetTitleOffset(1.4);

	IncNoLaserX->SetLineColor(kBlue);
	IncNoLaserX->SetLineWidth(2);



	TH1D * IncY = new TH1D("IncY","",200,-100,100);
	IncY->GetXaxis()->SetTitle("TPC Seed y (cm)");
	IncY->GetYaxis()->SetTitle("Number of TPC Seeds");
	IncY->GetXaxis()->CenterTitle();
	IncY->GetYaxis()->CenterTitle();
	IncY->GetYaxis()->SetTitleOffset(1.4);

	IncY->SetLineColor(kBlack);
	IncY->SetLineWidth(2);



	TH1D * IncLaserY = new TH1D("IncLaserY","",200,-100,100);
	IncLaserY->GetXaxis()->SetTitle("TPC Seed y (cm)");
	IncLaserY->GetYaxis()->SetTitle("Number of TPC Seeds");
	IncLaserY->GetXaxis()->CenterTitle();
	IncLaserY->GetYaxis()->CenterTitle();
	IncLaserY->GetYaxis()->SetTitleOffset(1.4);

	IncLaserY->SetLineColor(kRed);
	IncLaserY->SetLineWidth(2);

	TH1D * IncNoLaserY = new TH1D("IncNoLaserY","",200,-100,100);
	IncNoLaserY->GetXaxis()->SetTitle("TPC Seed y (cm)");
	IncNoLaserY->GetYaxis()->SetTitle("Number of TPC Seeds");
	IncNoLaserY->GetXaxis()->CenterTitle();
	IncNoLaserY->GetYaxis()->CenterTitle();
	IncNoLaserY->GetYaxis()->SetTitleOffset(1.4);

	IncNoLaserY->SetLineColor(kBlue);
	IncNoLaserY->SetLineWidth(2);



	int LaserEvt = 0;
	int NoLaserEvt = 0;

	for(int i = 0; i < NEvents; i++){

		SeedAna->GetEntry(i);

		
		int TPCSeedSize = tpcseedz->size();

		for(int j = 0; j < TPCSeedSize; j++){

			float tpcx = tpcseedx->at(j);
			float tpcy = tpcseedy->at(j);			
			float tpcz = tpcseedz->at(j);

			Inc->Fill(tpcz);
			IncX->Fill(tpcx);
			IncY->Fill(tpcy);
			
			if(!IsLaserEvt){
				IncNoLaser->Fill(tpcz);
				IncNoLaserX->Fill(tpcx);
				IncNoLaserY->Fill(tpcy);
				
			}
			
			if(IsLaserEvt){
				IncLaser->Fill(tpcz);
				IncLaserX->Fill(tpcx);
				IncLaserY->Fill(tpcy);

			}
		}
	
		if(IsLaserEvt) LaserEvt++;
		if(!IsLaserEvt) NoLaserEvt++;
		
	}


	c->cd();






	TLegend * leg  = new TLegend(0.15,0.72,0.50,0.88,NULL,"brNDC");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.040);
	leg->SetTextFont(42);
	leg->SetFillStyle(0);
	leg->SetLineWidth(3);

	leg->AddEntry(Inc,Form("Total Events: %d",NEvents),"L");
	leg->AddEntry(IncLaser,Form("Total TPC Laser Events: %d",LaserEvt),"L");
	leg->AddEntry(IncNoLaser,Form("Total TPC No Laser Events: %d",NoLaserEvt),"L");


	Inc->Draw("hist");
	IncLaser->Draw("histSAME");
	IncNoLaser->Draw("histSAME");
	
	leg->Draw("SAME");

	c->SaveAs("LaserDemo/TPCSeedZ.png");

	IncX->Draw("hist");
	IncLaserX->Draw("histSAME");
	IncNoLaserX->Draw("histSAME");
	
	leg->Draw("SAME");

	c->SaveAs("LaserDemo/TPCSeedX.png");

	IncY->Draw("hist");
	IncLaserY->Draw("histSAME");
	IncNoLaserY->Draw("histSAME");
	
	leg->Draw("SAME");

	c->SaveAs("LaserDemo/TPCSeedY.png");


}
