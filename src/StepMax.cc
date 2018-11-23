/**
 * @file /ECal_MT/include/StepMax.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of ECal's StepMax source code for steps limitation.
 * Latest updates of project can be found in README file.
 **/

#include "StepMax.hh"

/// Constructor of Stepmax

StepMax::StepMax(const G4String& processName)
 : G4VDiscreteProcess(processName),fMaxChargedStep(DBL_MAX)
{
}

/// Destructor of Stepmax

StepMax::~StepMax() { }

/// Checking if particle is applicable or not by PDG charge

G4bool StepMax::IsApplicable(const G4ParticleDefinition& particle)
{
  return (particle.GetPDGCharge() != 0. && !particle.IsShortLived());
}

/// Setting Maximum of steps

void StepMax::SetMaxStep(G4double step) 
{
  fMaxChargedStep = step;
}

/// Get Physical Interaction Length from post step

G4double StepMax::PostStepGetPhysicalInteractionLength( const G4Track&,
                                                   G4double,
                                                   G4ForceCondition* condition )
{
  *condition = NotForced; /// condition is set to "Not Forced"

  return fMaxChargedStep;
}

/// Initializing particle change by post step

G4VParticleChange* StepMax::PostStepDoIt(const G4Track& aTrack, const G4Step&)
{
   aParticleChange.Initialize(aTrack); /// do nothing
   return &aParticleChange;
}

/// End of file

