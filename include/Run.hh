/**
 * @file /DB_EMCal/include/Run.hh
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's run class for threads.
 * Latest updates of project can be found in README file.
 **/
 
#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "globals.hh"
#include "HistoManager.hh"

class Run : public G4Run
{
public:
  Run();
  virtual ~Run();
  
  virtual void Merge(const G4Run*);
  void Fill(G4int id, G4double x, G4double y, G4double z, G4double value);
  void Save();
  
private:
  HistoManager*  histo;
};

#endif

/// End of file

