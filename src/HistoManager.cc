/**
 * @file /DB_EMCal/src/HistoManager.hh
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's Histo manager class for collecting data. 
 * Latest updates of project can be found in README file.
 **/

#include "HistoManager.hh"

/// @brief Constructor of Histo manager

HistoManager::HistoManager()
:fRootFile(0)
{
  fileName = "DB_EMCal.root";
}

/// @brief Destructor of Histo manager

HistoManager::~HistoManager()
{
  if (fRootFile) delete fRootFile;
}

/// @brief Creating Histograms

void HistoManager::Book()
{
   fRootFile = new TFile(fileName,"RECREATE");
  
  hist1 = new TH1D("TH1D","Energy deposit",160,0,160);
  hist2 = new TH2D("TH2D","Detector (photon)",500,-2,2,500,-2,2);
}

/// @brief Writing out data to .root file 

void HistoManager::Save()
{ 
  if (! fRootFile) return;
  
  fRootFile->Write();       /// Writing the histograms to the file
  fRootFile->Close();       /// and closing the tree (and the file)
  
  G4cout << "\n----> Histograms are saved\n" << G4endl;
}

/// @brief Filling histograms

void HistoManager::FillHisto(G4int id, G4double x, G4double y, G4double z, G4double value)
{
  if(id==1)
  {
	  hist1->Fill(z,value);
  }
  else
  {
	  hist2->Fill(x,y,value);
  }
}

/// End of file


