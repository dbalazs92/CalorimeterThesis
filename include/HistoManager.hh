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


#include "g4root.hh"

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


const G4int fMaxHisto = 4;


class HistoManager
{
  public:
    HistoManager();
   ~HistoManager();
   
    void Book(G4String fileName);
    void Save();

    void FillHisto(G4int id, G4double x, G4double y, G4double z, G4double value);
         
};

/// End of file

#endif

