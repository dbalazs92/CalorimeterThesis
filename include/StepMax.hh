/**
 * @file /ECal_MT/include/StepMax.hh
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of ECal's StepMax class for steps limitation.
 * Latest updates of project can be found in README file.
 **/

#ifndef StepMax_h
#define StepMax_h 1

#include "globals.hh"
#include "G4VDiscreteProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"

class StepMax : public G4VDiscreteProcess
{
public:

  StepMax(const G4String& processName = "UserMaxStep");
  virtual ~StepMax();

  virtual G4bool IsApplicable(const G4ParticleDefinition&);

  void SetMaxStep(G4double);

  G4double GetMaxStep() {return fMaxChargedStep;};

  virtual G4double 
  PostStepGetPhysicalInteractionLength(const G4Track& track,
                                       G4double previousStepSize,
                                       G4ForceCondition* condition);

  virtual G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

  virtual G4double GetMeanFreePath(const G4Track&,G4double,G4ForceCondition*)
  {return DBL_MAX;};    

private:

  G4double fMaxChargedStep;
};

#endif

/// End of file


