/**
 * @file /DB_EMCal/src/HistoManager.cc
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
{
}

/// @brief Destructor of Histo manager

HistoManager::~HistoManager()
{
}

/// @brief Creating Histograms

void HistoManager::Book(G4String fileName)
{
   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  
  G4bool fileOpen = analysisManager->OpenFile(fileName);
  
  analysisManager->CreateH1("TH1D","Energy deposit",160,0,160);
  analysisManager->CreateH2("TH2D","Detector (photon)",500,-2,2,500,-2,2);
}

/// @brief Writing out data to .root file 

void HistoManager::Save()
{   
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();    
  analysisManager->Write(); /// Writing the histograms to the file
  analysisManager->CloseFile(); /// and closing the tree (and the file)
   
  G4cout << "\n----> Histograms are saved\n" << G4endl;
      
  delete G4AnalysisManager::Instance();
}

/// @brief Filling histograms

void HistoManager::FillHisto(G4int id, G4double x, G4double y, G4double z, G4double value)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if(id==1)
  {
	  analysisManager->FillH1(0,z);
  }
  else
  {
	  analysisManager->FillH2(0,x,y,value);
  }
}

/// End of file


