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

#ifndef HistoManager_h
#define HistoManager_h 1


#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TRandom.h>
#include <TMath.h>
#include <TCanvas.h>

#include "globals.hh"
#include "G4UnitsTable.hh"

class TFile;
class TTree;
class TH1D;
class TH2D;

const G4int fMaxHisto = 4;


class HistoManager
{
  public:
    HistoManager();
   ~HistoManager();
   
    void Book();
    void Save();

    void FillHisto(G4int id, G4double x, G4double y, G4double z, G4double value);
        
  private:
    G4String fileName;
    TFile*   fRootFile;
    TH1D*    hist1;
    TH2D*	 hist2;   
};

/// End of file

#endif

