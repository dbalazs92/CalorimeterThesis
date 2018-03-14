/**
 * @file /EMCal_MT/plotHisto.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/10/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's ROOT macro for Analysis. 
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

void plotHisto(Int_t det){
	
	string name1,name2, particleName, procN, preName, postName;
	char jel;
	Int_t trackID;
	Double_t prekinE, postkinE, preX, preY, preZ, postX, postY, postZ, postTime, edep;
	
	TCanvas  * cX = new TCanvas("Canvas","Results",1200,600);
	auto h1 = new TH1D("TH1D", "Energy deposit", 100, 0, 27);
	auto h2 = new TH1D("TH1D2", "Time", 50, 0, 10);
	auto localhist = new TH2D("TH2D", "Local", 300, -2, 2, 300, 2, 2);
	auto localhist2 = new TH2D("TH2D2", "Shower", 150, 0, 31, 300, -2, 2);
	// det=1 -> Time and Local , det=<else> -> Energy and Shower
    
	ifstream in1("xdatax.txt");
	
	while(!in1.eof()){
		in1>>name2>>jel>>name1>>particleName>>procN>>trackID>>edep>>postkinE>>preX>>preY>>preZ>>postX>>postY>>postZ>>preName>>postName>>postTime;
		if((preName!="fiberCover")&&(preName!="fiberInterior")&&(postName!="fiberCover")&&(postName!="fiberInterior")){
		h1->Fill(postZ,edep);
		localhist2->Fill(postZ,postY,1);}
		if(postName=="Detector") 
		{
			h2->Fill(postTime, 1);
			localhist->Fill(postX,postY,1);
		}
	}
	
	cX->Divide(2,1);
	if(det==1)
	{
	cX->cd(1);
	localhist->GetXaxis()->SetTitle("X (cm)");
    localhist->GetYaxis()->SetTitle("Y (cm)");
    localhist->Draw("colz");
    cX->cd(2);
    h2->GetXaxis()->SetTitle("Time (s)");
    h2->GetYaxis()->SetTitle("No. of detector hits");
    h2->Draw();	
	}
	else
	{
	cX->cd(1);
	h1->GetXaxis()->SetTitle("Z (cm)");
    h1->GetYaxis()->SetTitle("Energy (keV)");
    h1->Draw();
    cX->cd(2);
    localhist2->GetXaxis()->SetTitle("Z (cm)");
    localhist2->GetYaxis()->SetTitle("Y (cm)");
    localhist2->Draw("colz");
	}
	in1.close();
	
}
