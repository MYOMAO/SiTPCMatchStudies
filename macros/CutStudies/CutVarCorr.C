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

void CutVarCorr(){
    auto start = high_resolution_clock::now();

	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();
	
	c->SetLogz();

	c->SetLeftMargin(0.14);
	c->SetRightMargin(0.14);


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

	TH2D * DeltaXYCorr = new TH2D("DeltaXYCorr","",100,-10,10,100,-10,10);
	DeltaXYCorr->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
	DeltaXYCorr->GetYaxis()->SetTitle("Silicon Seed y - TPC Seed y: #Delta y (cm)");
	DeltaXYCorr->GetXaxis()->CenterTitle();
	DeltaXYCorr->GetYaxis()->CenterTitle();


	TH2D * DeltaYZCorr = new TH2D("DeltaYZCorr","",100,-10,10,100,-200,200);
	DeltaYZCorr->GetXaxis()->SetTitle("Silicon Seed y - TPC Seed y: #Delta y (cm)");
	DeltaYZCorr->GetYaxis()->SetTitle("Silicon Seed z - TPC Seed z: #Delta z (cm)");
	DeltaXYCorr->GetXaxis()->CenterTitle();
	DeltaYZCorr->GetYaxis()->CenterTitle();


	TH2D * DeltaXZCorr = new TH2D("DeltaXZCorr","",100,-10,10,100,-200,200);
	DeltaXZCorr->GetXaxis()->SetTitle("Silicon Seed x - TPC Seed x: #Delta x (cm)");
	DeltaXZCorr->GetYaxis()->SetTitle("Silicon Seed z - TPC Seed z: #Delta z (cm)");
	DeltaXZCorr->GetXaxis()->CenterTitle();
	DeltaXZCorr->GetYaxis()->CenterTitle();




	TH2D * DeltaPhiZCorr = new TH2D("DeltaPhiZCorr","",100,-6.4,6.4,100,-200,200);
	DeltaPhiZCorr->GetXaxis()->SetTitle("Silicon Seed #phi - TPC Seed x: #Delta #phi");
	DeltaPhiZCorr->GetYaxis()->SetTitle("Silicon Seed z - TPC Seed z: #Delta z (cm)");
	DeltaPhiZCorr->GetXaxis()->CenterTitle();
	DeltaPhiZCorr->GetYaxis()->CenterTitle();


	TH2D * DeltaRZCorr = new TH2D("DeltaRZCorr","",100,0,20,100,-200,200);
	DeltaRZCorr->GetXaxis()->SetTitle("Silicon Seed r - TPC Seed r: #Delta r");
	DeltaRZCorr->GetYaxis()->SetTitle("Silicon Seed z - TPC Seed z: #Delta z (cm)");
	DeltaRZCorr->GetXaxis()->CenterTitle();
	DeltaRZCorr->GetYaxis()->CenterTitle();



	TH2D * DeltaXYCorrZC = (TH2D *) DeltaXYCorr->Clone("DeltaXYCorrZC");
	TH2D * DeltaXZCorrZC = (TH2D *) DeltaXZCorr->Clone("DeltaXZCorrZC");
	TH2D * DeltaYZCorrZC = (TH2D *) DeltaYZCorr->Clone("DeltaYZCorrZC");
	TH2D * DeltaPhiZCorrZC = (TH2D *) DeltaPhiZCorr->Clone("DeltaPhiZCorrZC");
	TH2D * DeltaRZCorrZC = (TH2D *) DeltaRZCorr->Clone("DeltaRZCorrZC");



	TH2D * DeltaXYCorrOC = (TH2D *) DeltaXYCorr->Clone("DeltaXYCorrOC");
	TH2D * DeltaXZCorrOC = (TH2D *) DeltaXZCorr->Clone("DeltaXZCorrOC");
	TH2D * DeltaYZCorrOC = (TH2D *) DeltaYZCorr->Clone("DeltaYZCorrOC");
	TH2D * DeltaPhiZCorrOC = (TH2D *) DeltaPhiZCorr->Clone("DeltaPhiZCorrOC");
	TH2D * DeltaRZCorrOC = (TH2D *) DeltaRZCorr->Clone("DeltaRZCorrOC");

	float dx;
	float dy;
	float dz;
	int dq;
	float dphi;
	float dpx;
	float dpy;
	float dpz;
	float deta;
	float dr;

	float pt;

	int NEvents = SeedAna->GetEntries();

	//NEvents = 1000;

	for(int i = 0; i < NEvents; i++){

		if(i%100==0) cout << "Now Working on Event: " << i << "   Out of Total Event: " << NEvents << endl;

		SeedAna->GetEntry(i);
		siseedsize = siseedx->size();
		tpcseedsize = tpcseedy->size();
	
		if(IsLaserEvt) continue;

		//cout << "siseedsize = " << siseedsize << "   tpcseedsize = " << tpcseedsize << endl;

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
/*
				float six = siseedx->at(j);
				float siy = siseedy->at(j);

				float tpcx = tpcseedx->at(k);
				float tpcy = tpcseedy->at(k);
			
				float sir = sqrt(six * six + siy * siy);
				float tpcr = sqrt(tpcx * tpcx + tpcy * tpcy);
*/

				dr = sqrt(dx * dx + dy * dy);

				pt = sqrt(tpcseedpx->at(k) * tpcseedpx->at(k) + tpcseedpy->at(k) * tpcseedpy->at(k));

				DeltaXYCorr->Fill(dx,dy);
				DeltaXZCorr->Fill(dx,dz);
				DeltaYZCorr->Fill(dy,dz);
				DeltaPhiZCorr->Fill(dphi,dz);
				DeltaRZCorr->Fill(dr,dz);

				if(crossing->at(j) == 0){


					//siseedsizezc++;
					//		tpcseedsizezc++;

					DeltaXYCorrZC->Fill(dx,dy);
					DeltaXZCorrZC->Fill(dx,dz);
					DeltaYZCorrZC->Fill(dy,dz);
					DeltaPhiZCorrZC->Fill(dphi,dz);
					DeltaRZCorrZC->Fill(dr,dz);

		

				}else{
				
					if(crossing->at(j) < 1000){


						DeltaXYCorrOC->Fill(dx,dy);
						DeltaXZCorrOC->Fill(dx,dz);
						DeltaYZCorrOC->Fill(dy,dz);
						DeltaPhiZCorrOC->Fill(dphi,dz);
						DeltaRZCorrOC->Fill(dr,dz);



					}


				}


				

			}



		}


	}
	
	c->cd();

	DeltaXYCorr->Draw("COLZ");
	c->SaveAs("PlotCorr/All/DeltaXYCorr.png");
	DeltaXZCorr->Draw("COLZ");
	c->SaveAs("PlotCorr/All/DeltaXZCorr.png");
	DeltaYZCorr->Draw("COLZ");
	c->SaveAs("PlotCorr/All/DeltaYZCorr.png");
	DeltaRZCorr->Draw("COLZ");
	c->SaveAs("PlotCorr/All/DeltaRZCorr.png");
	DeltaPhiZCorr->Draw("COLZ");
	c->SaveAs("PlotCorr/All/DeltaPhiZCorr.png");



	DeltaXYCorrZC->Draw("COLZ");
	c->SaveAs("PlotCorr/ZC/DeltaXYCorrZC.png");
	DeltaXZCorrZC->Draw("COLZ");
	c->SaveAs("PlotCorr/ZC/DeltaXZCorrZC.png");
	DeltaYZCorrZC->Draw("COLZ");
	c->SaveAs("PlotCorr/ZC/DeltaYZCorrZC.png");
	DeltaRZCorrZC->Draw("COLZ");
	c->SaveAs("PlotCorr/ZC/DeltaRZCorrZC.png");
	DeltaPhiZCorrZC->Draw("COLZ");
	c->SaveAs("PlotCorr/ZC/DeltaPhiZCorrZC.png");

		
	DeltaXYCorrOC->Draw("COLZ");
	c->SaveAs("PlotCorr/OC/DeltaXYCorrOC.png");
	DeltaXZCorrOC->Draw("COLZ");
	c->SaveAs("PlotCorr/OC/DeltaXZCorrOC.png");
	DeltaYZCorrOC->Draw("COLZ");
	c->SaveAs("PlotCorr/OC/DeltaYZCorrOC.png");
	DeltaRZCorrOC->Draw("COLZ");
	c->SaveAs("PlotCorr/OC/DeltaRZCorrOC.png");
	DeltaPhiZCorrOC->Draw("COLZ");
	c->SaveAs("PlotCorr/OC/DeltaPhiZCorrOC.png");



}
