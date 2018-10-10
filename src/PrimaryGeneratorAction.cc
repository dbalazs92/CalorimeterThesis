/**
 * @file /EMCal_MT/src/PrimaryGeneratorAction.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's primary generator source code to define particle, energy, momentum, position.
 * Latest updates of project can be found in README file.
 **/

#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <cstdlib>

/** @brief Constructor of Primary generator action
 *
 *  @param E0 		Kinetic energy of particle
 *  @param Particle Type of particle
 * 
 **/

PrimaryGeneratorAction::PrimaryGeneratorAction(G4double E0, G4String Particle, G4int Fiber)
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),fParticle(Particle),fEnergy(E0), fFiber(Fiber), fBoxMuller(false)
{
  G4int n_particle = 1;   ///particles per event
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable(); /// default particle kinematic
  G4ParticleDefinition* particle = particleTable->FindParticle(fParticle);
  fParticleGun->SetParticleDefinition(particle);
  
  if(fBoxMuller==false){fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));}

  fParticleGun->SetParticleEnergy(fEnergy*GeV);
}

/// @brief Destructor of Primary generator action

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

/// @brief Generation of Primary Particles 

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	if(fBoxMuller==true)
	{
	G4double phi, r,rRand,ux,uy;
	phi=((double)rand()/(double)RAND_MAX)*M_PI*2;
	rRand=((double)rand()/(double)RAND_MAX);
	r=0.87*(fFiber/2)*rRand;  
	ux=r*cos(phi);
	uy=r*sin(phi);  
	fParticleGun->SetParticlePosition(G4ThreeVector(ux,uy,0));
	fParticleGun->GeneratePrimaryVertex(anEvent);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
	}
	else
	{
	fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
    fParticleGun->GeneratePrimaryVertex(anEvent);
	}
}

/// End of file

