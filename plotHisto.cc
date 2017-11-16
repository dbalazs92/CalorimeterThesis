/**
 * @file /EMCal_MT/Analysis.cc
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

void plotHisto(int sel){
	
	string name1,name2, particleName, procN, preName, postName;
	char jel;
	int trackID;
	double prekinE, postkinE, preX, preY, preZ, postX, postY, postZ, postTime, edep;
	
	auto h1 = new TH1D("TH1D", "Energy", 100, 0, 27);
	auto h2 = new TH1D("TH1D2", "Time", 50, 0, 10);
	auto localhist = new TH2D("TH2D", "Local", 300, -2, 2, 300, 2, 2);
	
	TCanvas  * cX = new TCanvas("Canvas","Results",1200,600);
    
	ifstream in1("text.txt");
	
	while(!in1.eof()){
		in1>>name2>>jel>>name1>>particleName>>procN>>trackID>>edep>>postkinE>>preX>>preY>>preZ>>postX>>postY>>postZ>>preName>>postName>>postTime;
		h1->Fill(postZ,edep);
		if(postName=="Detector") 
		{
			h2->Fill(postTime, 1);
			localhist->Fill(postX,postY,1);
		}
	}
	if(sel==1)
	{ 
	cX->Divide(2,1);
	cX->cd(1);
    h1->Draw();
    cX->cd(2);
    h2->Draw();
	}
	else
	{
    cX->cd(1);
    localhist->Draw("colz");
	}
	in1.close();
	
}
