/**
 * @file /ECal_MT/include/EventAction.hh
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of ECal's Event action class for a particle from start till leaving the world (event).
 * Latest updates of project can be found in README file.
 **/

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "Run.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
    void SetHitNumber(){detectorHit++;}
  private:
    G4int detectorHit;
};

#endif

/// End of file

    
