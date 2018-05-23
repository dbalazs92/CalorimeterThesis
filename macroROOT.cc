/**
 * @file /EMCal_MT/macroROOT.cc
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

void macroROOT(){
	
	string name1,name2, particleName, procN, preName, postName;
	char jel;
	Double_t prekinE, postkinE, preX, preY, preZ, postX, postY, postZ, postTime, edep;
	Int_t trackID;
	
	auto f = TFile::Open("data.root","RECREATE");
	ifstream in1("xdatax.txt");
	
	TTree *tree = new TTree("T","Data from text file");
	
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
		tree->Fill();
	}
	
	tree->Print();
	in1.close();
	f->Write();
}
