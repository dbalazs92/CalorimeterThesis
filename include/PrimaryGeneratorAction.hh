/**
 * @file /EMCal_MT/include/PrimaryGeneratorAction.hh
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's primary generator class to define particle, energy, momentum, position.
 * Latest updates of project can be found in README file.
 **/

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction(G4double E0, G4String Particle, G4int Fiber);    
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);         
  
  private:
    G4ParticleGun*  fParticleGun; /// pointer for G4 gun class
    G4double fEnergy;
    G4String fParticle;
    G4int 	 fFiber;
    G4bool 	 fBoxMuller;

};

#endif

/// End of file

