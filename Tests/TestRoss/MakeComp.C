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



void MakeComp(){


	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();


	c->SetLeftMargin(0.14);


	const int NOpt = 8;



	TH1D * DeltaX[NOpt]; 
	TH1D * DeltaY[NOpt]; 
	TH1D * DeltaZ[NOpt]; 



	float tpcx;
	float six;
	float tpcy;
	float siy;
	float tpcz;
	float siz;

	float dx;
	float dy;
	float dz;

	for(int i = 0; i < NOpt; i++){
	
		//if(i == 5) continue;

		DeltaX[i] = new TH1D(Form("DeltaX_%d",i),"",100,-5,5);
		DeltaX[i]->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed y: #Delta x (cm)");
		DeltaX[i]->GetYaxis()->SetTitle("Normalized Number of Seed Pairs");
		DeltaX[i]->GetXaxis()->CenterTitle();
		DeltaX[i]->GetYaxis()->CenterTitle();
		DeltaX[i]->SetMarkerStyle(20);
		DeltaX[i]->SetMarkerSize(1);
		DeltaX[i]->SetMarkerColor(i+1);
		DeltaX[i]->SetLineColor(i+1);

		DeltaY[i] = new TH1D(Form("DeltaY_%d",i),"",100,-5,5);
		DeltaY[i]->GetXaxis()->SetTitle("Silicon Seed y - TPC Seed y: #Delta y (cm)");
		DeltaY[i]->GetYaxis()->SetTitle("Normalized Number of Seed Pairs");
		DeltaY[i]->GetXaxis()->CenterTitle();
		DeltaY[i]->GetYaxis()->CenterTitle();
		DeltaY[i]->SetMarkerStyle(20);
		DeltaY[i]->SetMarkerSize(1);
		DeltaY[i]->SetMarkerColor(i+1);
		DeltaY[i]->SetLineColor(i+1);

		DeltaZ[i] = new TH1D(Form("DeltaZ_%d",i),Form("DeltaZ_%d",i),100,-100,100);
		DeltaZ[i]->GetXaxis()->SetTitle("Silicon Seed z - TPC Seed y: #Delta z (cm)");
		DeltaZ[i]->GetYaxis()->SetTitle("Normalized Number of Seed Pairs");
		DeltaZ[i]->GetXaxis()->CenterTitle();
		DeltaZ[i]->GetYaxis()->CenterTitle();
		DeltaZ[i]->SetMarkerStyle(20);
		DeltaZ[i]->SetMarkerSize(1);
		DeltaZ[i]->SetMarkerColor(i+1);
		DeltaZ[i]->SetLineColor(i+1);



		TFile * fin = new TFile(Form("NewFile/track_match_%d.root",i));

		fin->cd();

		TTree * track_match = (TTree *) fin->Get("track_match");
		
//		track_match->Print();
		
		
		track_match->SetBranchAddress("tpcx",&tpcx);
		track_match->SetBranchAddress("six",&six);
		track_match->SetBranchAddress("tpcy",&tpcy);
		track_match->SetBranchAddress("siy",&siy);
		track_match->SetBranchAddress("tpcz",&tpcz);
		track_match->SetBranchAddress("siz",&siz);



		int NEntries = track_match->GetEntries();


			for(int j = 0; j < NEntries; j++){


				track_match->GetEntry(j);


				dx = six - tpcx;
				dy = siy - tpcy;
				dz = siz - tpcz;

				DeltaX[i]->Fill(dx);
				DeltaY[i]->Fill(dy);
				DeltaZ[i]->Fill(dz);


			}	



			//track_match->Project(Form("DeltaZ_%d",i),"siz - tpcz","");

			cout << "DeltaZ[i]->Integral() = " << DeltaZ[i]->Integral() << endl;
				




	}




	TLegend * leg3  = new TLegend(0.15,0.7,0.60,0.88,NULL,"brNDC");
	leg3->SetBorderSize(0);
	leg3->SetTextSize(0.040);
	leg3->SetTextFont(42);
	leg3->SetFillStyle(0);
	leg3->SetLineWidth(3);


	int NoTPCCorr = DeltaZ[0]->Integral();
	int TPCCorr = DeltaZ[7]->Integral();


	DeltaX[7]->SetMarkerColor(kRed);
	DeltaX[7]->SetLineColor(kRed);

	DeltaY[7]->SetMarkerColor(kRed);
	DeltaY[7]->SetLineColor(kRed);

	DeltaZ[7]->SetMarkerColor(kRed);
	DeltaZ[7]->SetLineColor(kRed);

	leg3->AddEntry(DeltaX[0],"Without TPC Corrections","LP");
//	leg3->AddEntry("",Form("Total TPC Seeds = %d",NoTPCCorr),"");
	
//	leg3->AddEntry(DeltaX[7],Form("With TPC Correction: Total TPC Seeds = %d",TPCCorr),"LP");

	leg3->AddEntry(DeltaX[7],"With TPC Corrections","LP");
//	leg3->AddEntry("",Form("Total TPC Seeds = %d",TPCCorr),"");


	c->cd();

	for(int i = 0; i < NOpt; i++){
	

			
		DeltaX[i]->Scale(1.0/DeltaX[i]->Integral());
		DeltaY[i]->Scale(1.0/DeltaY[i]->Integral());
		DeltaZ[i]->Scale(1.0/DeltaZ[i]->Integral());


	
		if(i == 0){  
			DeltaX[i]->SetMinimum(0.0);	
			DeltaX[i]->SetMaximum(0.04);					
			DeltaX[i]->Draw("ep");
		}
		if(i == 7) DeltaX[i]->Draw("epSame");

	}

	leg3->Draw("SAME");
	c->SaveAs("Plots/DeltaX.png");


	for(int i = 0; i < NOpt; i++){
	

		if(i == 0){		
			DeltaY[i]->SetMinimum(0.0);	
			DeltaY[i]->SetMaximum(0.04);		
			DeltaY[i]->Draw("ep");
		}
		
		if(i == 7) DeltaY[i]->Draw("epSame");

	}

	leg3->Draw("SAME");
	c->SaveAs("Plots/DeltaY.png");


	for(int i = 0; i < NOpt; i++){


		if(i == 0){
			DeltaZ[i]->SetMinimum(0.0);	
			DeltaZ[i]->SetMaximum(0.1);		
			DeltaZ[i]->Draw("ep");

		}
		
		if(i == 7) DeltaZ[i]->Draw("epSame");

	}

	leg3->Draw("SAME");
	c->SaveAs("Plots/DeltaZ.png");





}

