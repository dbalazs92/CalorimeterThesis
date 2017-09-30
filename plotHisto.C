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


void plotHisto()
{
  gROOT->Reset();
  
  // Draw histos filled by Geant4 simulation 
  //   
  TFile *f = new TFile("DB_EMCal.root");
  TCanvas  * c10 = new TCanvas("c10","Live display",1200,600);
  c10->Divide(2,1);
  
  TH2D* hist1 = (TH2D*)f->Get("TH2D");
  
  TH1D* hist2 = (TH1D*)f->Get("TH1D");
  
  
  c10->cd(1);
  hist1->Draw("colz");
  c10->cd(2);
  hist2->Draw("hist");
    
}  
