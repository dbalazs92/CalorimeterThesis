/**
 * @file /EMCal_MT/Macro.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2018/03/23 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's ROOT macro. Creating .root file from raw datas for analysis. 
 * Latest updates of project can be found in README file.
 **/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "TROOT.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TRandom.h"
#include "TMath.h"
#include "TCanvas.h"

using namespace std;

void Macro(Double_t fiber, const char ads[], const char adsX[], const char adsY[]){
	
	gStyle->SetOptStat(0);
	
	string name1,name2, particleName, procN, preName, postName;
	char jel;
	Double_t prekinE, postkinE, preX, preY, preZ, postX, postY, postZ, postTime, edep;
	Int_t trackID;
	
	Int_t osztas=30;
	Double_t minZ=0.0,maxZ=10.512;
	Double_t l=(0.1*(fiber+1))/2;
	Int_t counter=0;
	
	auto f = TFile::Open(ads,"RECREATE");
	
	ifstream in1("data1.txt");
	
	TTree *tree = new TTree("T","Data from text file");
	TCanvas  * cX = new TCanvas("Canvas","Results",1024,768);
	auto h0 = new TH1D("TH1D0", "Energy deposit by distance", osztas, minZ, maxZ);
	auto h1 = new TH2D("TH2D1", "Lateral", osztas*5, -l, l, osztas*5, -l, l);
	
	tree->Branch("particleName",&particleName);
	tree->Branch("processName",&procN);
	tree->Branch("trackID",&trackID,"trackID/I");
	tree->Branch("preX",&preX,"preX/D");
	tree->Branch("preY",&preY,"preY/D");
	tree->Branch("preZ",&preZ,"preZ/D");
	tree->Branch("postX",&postX,"postX/D");
	tree->Branch("postY",&postY,"postY/D");
	tree->Branch("postZ",&postZ,"postZ/D");
	tree->Branch("edep",&edep,"edep/D");
	tree->Branch("preName",&preName);
	tree->Branch("postName",&postName);
	tree->Branch("postTime",&postTime,"postTime/D");
	
	while(!in1.eof())
	{
		in1>>name2>>jel>>name1>>particleName>>procN>>trackID>>edep>>postkinE>>preX>>preY>>preZ>>postX>>postY>>postZ>>preName>>postName>>postTime;
		h0->Fill(postZ-5.5, edep);
		h1->Fill(postX, postY, edep);
		if(postName=="Detector")
		{
			counter++;
		}
		tree->Fill();
	}
	tree->Print();
	in1.close();
	f->Write();
	
	Double_t x0[osztas], y0[osztas];
	for(int i=1;i<=osztas;i++)
    {
		x0[i-1]=((maxZ-minZ)/osztas)*i;
		y0[i-1]=h0->GetBinContent(i);
	}
	auto legend = new TLegend(0.75,0.7,0.9,0.9);
	TGraph *gr0 = new TGraph(osztas,x0,y0);
	gr0->SetLineColor(38);
	gr0->SetMarkerColor(38);
	gr0->SetLineWidth(3);
	gr0->Draw("acp");
	gr0->SetTitle("Energy deposit by distance; Z axis [cm]; Energy deposit [eV]");
	TImage *img = TImage::Create();
	img->FromPad(cX);
	img->WriteImage(adsX);
	h1->Draw("colz");
	TLatex t(-l-0.1,l+0.1,Form("Dp: %d",counter));
    t.Draw();
	cX->Update();
	TImage *img2 = TImage::Create();
	img2->FromPad(cX);
	img2->WriteImage(adsY);
}
