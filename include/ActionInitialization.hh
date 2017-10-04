/**
 * @file /DB_EMCal/include/ActionInitialization.hh
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's action initialization class. 
 * Latest updates of project can be found in README file.
 **/

#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "HistoManager.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(G4double e0, G4String Particle, HistoManager*);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
  
  private:
	G4double fEnergy;
	G4String fParticle;
	HistoManager* fHisto;
};

#endif

/// End of file
    
