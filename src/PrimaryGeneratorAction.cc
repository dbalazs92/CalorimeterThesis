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

/** @brief Constructor of Primary generator action
 *
 *  @param E0 		Kinetic energy of particle
 *  @param Particle Type of particle
 * 
 **/

PrimaryGeneratorAction::PrimaryGeneratorAction(G4double E0, G4String Particle)
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),fParticle(Particle),fEnergy(E0)
{
  G4int n_particle = 1;   ///particles per event
  rad = 0.048*mm;     ///radius
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable(); /// default particle kinematic
  G4ParticleDefinition* particle = particleTable->FindParticle(fParticle);
  fParticleGun->SetParticleDefinition(particle);
  
  if(rad==0.0){fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));}

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

  fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
  fParticleGun->GeneratePrimaryVertex(anEvent);
  if(rad!=0.0)
  {
	G4double  ux, uy, uz, a, b;
	a=G4UniformRand();
	b=G4UniformRand();
	if(a>0.5){ux = rad*G4UniformRand();}
	else{ux = -rad*G4UniformRand();}
	if(b>0.5){uy = rad*G4UniformRand();}
	else{uy = -rad*G4UniformRand();}
	uz = 1.0;///cosTheta;
	G4ThreeVector Pi_random_axis(ux,uy,uz);
	
	fParticleGun->SetParticleMomentumDirection(Pi_random_axis);
  }
}

/// End of file

