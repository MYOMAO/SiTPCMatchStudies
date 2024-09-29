#include "TROOT.h"
#include "TH1D.h"
#include "TTree.h"
#include "TH2D.h"
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
#include <vector>
#include "TStyle.h"
#include "TCanvas.h"



using namespace std;

using std::cout;
using std::endl;

void PlotClusSpecial(){

	gStyle->SetOptStat(0);

	TCanvas * c = new TCanvas("c","c",600,600);
	c->cd();


	c->SetLeftMargin(0.14);


	const int NFiles = 1;
	//	TString infiles[NFiles] = {"SeedAna_Ross.root"};
	TString infiles[NFiles] = {"Test.root"};

	TH2D * Unmatched = new TH2D("Unmatched","",200,-80,80,200,-80,80);
	Unmatched->GetXaxis()->SetTitle("x (cm)");
	Unmatched->GetYaxis()->SetTitle("y (cm)");
	Unmatched->GetXaxis()->CenterTitle();
	Unmatched->GetYaxis()->CenterTitle();
	Unmatched->GetYaxis()->SetTitleOffset(1.4);
	Unmatched->SetMarkerSize(2);


	TH2D * Matched = new TH2D("Matched","",200,-80,80,200,-80,80);
	Matched->GetXaxis()->SetTitle("x (cm)");
	Matched->GetYaxis()->SetTitle("y (cm)");
	Matched->GetXaxis()->CenterTitle();
	Matched->GetYaxis()->CenterTitle();
	Matched->GetYaxis()->SetTitleOffset(1.4);
	Matched->SetMarkerSize(2);


	TH2D * SvtxMatchedOpp = new TH2D("SvtxMatchedOpp","",200,-80,80,200,-80,80);
	SvtxMatchedOpp->GetXaxis()->SetTitle("x (cm)");
	SvtxMatchedOpp->GetYaxis()->SetTitle("y (cm)");
	SvtxMatchedOpp->GetXaxis()->CenterTitle();
	SvtxMatchedOpp->GetYaxis()->CenterTitle();
	SvtxMatchedOpp->GetYaxis()->SetTitleOffset(1.4);
	SvtxMatchedOpp->SetMarkerSize(2);


	int Color[NFiles] = {1};
	int Color2[NFiles] = {2};

	for(int q = 0; q < 1; q++){

		//	cout << "Pass Before" << endl;
		TFile * fin = new TFile(infiles[q].Data());
		fin->cd();
		//		cout << "File Opened" << endl;


		int event;
		int siseedsize;
		int tpcseedsize;
		std::vector<int> * crossing = 0;
		std::vector<int> * svtxcrossing = 0;

		std::vector<float> * siseedx = 0;
		std::vector<float> * siseedy = 0;
		std::vector<float> * siseedz = 0;

		//	int event2;
		std::vector<float> * tpcseedx = 0;
		std::vector<float> * tpcseedy = 0;
		std::vector<float> * tpcseedz = 0;



		std::vector<float> * siseedcharge = 0;
		std::vector<float> * tpcseedcharge = 0;


		float dx;
		float dy;
		float dz;

		int dq;

		std::vector<std::vector<float> > * siclusposx = 0;
		std::vector<std::vector<float> > * siclusposy = 0;
		std::vector<std::vector<float> > * tpcclusposx = 0;
		std::vector<std::vector<float> > * tpcclusposy = 0;



		std::vector<float> * svtxsiseedcharge = 0;
		std::vector<float> * svtxtpcseedcharge = 0;


		std::vector<std::vector<float> > * svtxsiclusposx = 0;
		std::vector<std::vector<float> > * svtxsiclusposy = 0;
		std::vector<std::vector<float> > * svtxtpcclusposx = 0;
		std::vector<std::vector<float> > * svtxtpcclusposy = 0;


		//TBranch *bsubjetPt=0;

		cout << "Branch Set" << endl;

		TTree * SeedAna = (TTree *) fin->Get("SeedAna");
		SeedAna->SetBranchAddress("event",&event);
		SeedAna->SetBranchAddress("siseedsize",&siseedsize);
		SeedAna->SetBranchAddress("tpcseedsize",&tpcseedsize);

		SeedAna->SetBranchAddress("crossing",&crossing);
		SeedAna->SetBranchAddress("siseedx",&siseedx);
		SeedAna->SetBranchAddress("siseedy",&siseedy);
		SeedAna->SetBranchAddress("siseedz",&siseedz);

		SeedAna->SetBranchAddress("tpcseedx",&tpcseedx);
		SeedAna->SetBranchAddress("tpcseedy",&tpcseedy);
		SeedAna->SetBranchAddress("tpcseedz",&tpcseedz);


		SeedAna->SetBranchAddress("siclusposx",&siclusposx);
		SeedAna->SetBranchAddress("siclusposy",&siclusposy);
		SeedAna->SetBranchAddress("tpcclusposx",&tpcclusposx);
		SeedAna->SetBranchAddress("tpcclusposy",&tpcclusposy);

		SeedAna->SetBranchAddress("siseedcharge",&siseedcharge);
		SeedAna->SetBranchAddress("tpcseedcharge",&tpcseedcharge);

		SeedAna->SetBranchAddress("svtxsiseedcharge",&svtxsiseedcharge);
		SeedAna->SetBranchAddress("svtxtpcseedcharge",&svtxtpcseedcharge);

		SeedAna->SetBranchAddress("svtxcrossing",&svtxcrossing);


		SeedAna->SetBranchAddress("svtxsiclusposx",&svtxsiclusposx);
		SeedAna->SetBranchAddress("svtxsiclusposy",&svtxsiclusposy);
		SeedAna->SetBranchAddress("svtxtpcclusposx",&svtxtpcclusposx);
		SeedAna->SetBranchAddress("svtxtpcclusposy",&svtxtpcclusposy);


		int EvtMatch = 46;

		//	cout << "Pass Branch" << endl;

		int NEvents = 50;

		for(int i = 0; i < NEvents; i++){


			cout << "i = " << i << endl;
			SeedAna->GetEntry(i);
			siseedsize = siseedx->size();
			tpcseedsize = tpcseedy->size();


			for(int j = 0; j < siseedsize; j++){

	




			}



	

		}








	}

	c->cd();
	Matched->Draw("p");
	c->SaveAs("Matched_New.png");


	c->cd();
	Unmatched->Draw("p");
	c->SaveAs("Unmatched_New.png");


	c->cd();
	SvtxMatchedOpp->Draw("p");
	c->SaveAs("SvtxMatchedOpp.png");


}


int main(int argc, char *argv[])
{
	if((argc != 1))
	{
		std::cout << "Wrong number of inputs" << std::endl;
		return 1;
	}

	if(argc == 1)
		PlotClus();
	return 0;
}
