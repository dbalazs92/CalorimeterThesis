#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "TROOT.h"
#include "TGraph.h"

void plotGraph(){
   TCanvas  * c10 = new TCanvas("c10","Results",1200,600);
   c10->Divide(2,1);
   c10->SetGrid();
   
   Double_t x[100], y[100], y2[100];
   Int_t n = 20;
   for (Int_t i=0;i<n;i++) {
     x[i] = i;
     y[i] = sin(x[i]);
     y2[i] = cos(x[i]);
   }
   TGraph* gr = new TGraph(n,x,y);
   TGraph* gr2 = new TGraph(n,x,y2);
   
   c10->cd(1);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("Szinusz");
   gr->GetXaxis()->SetTitle("X");
   gr->GetYaxis()->SetTitle("Sin(x)");
   gr->Draw("ACP");
   
   c10->cd(2);
   gr2->SetLineColor(2);
   gr2->SetLineWidth(4);
   gr2->SetMarkerColor(4);
   gr2->SetMarkerStyle(21);
   gr2->SetTitle("Koszinusz");
   gr2->GetXaxis()->SetTitle("X");
   gr2->GetYaxis()->SetTitle("Cos(x)");
   gr2->Draw("ACP");
}
