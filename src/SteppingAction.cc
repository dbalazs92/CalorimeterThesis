/**
 * @file /EMCal_MT/src/SteppingAction.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's Stepping action source code for steps of simulation.
 * Latest updates of project can be found in README file.
 **/

#include "SteppingAction.hh"


/// Constructor of Stepping action

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fLite(false)
{}

/// Destructor of Stepping action

SteppingAction::~SteppingAction()
{}

/// User Stepping action for collecting datas from steps

void SteppingAction::UserSteppingAction(const G4Step* fStep)
{

  G4double edepStep = fStep->GetTotalEnergyDeposit();
  G4Track * fTrack = fStep->GetTrack();
  G4int trackID=fTrack->GetTrackID();
  G4int tID=fEventAction->GetTempID();

  //G4double preTime = fStep->GetPreStepPoint()->GetLocalTime();
  G4double postTime = fStep->GetPostStepPoint()->GetLocalTime();

  if(fTrack->GetTrackStatus()!=fAlive) { return; } /// check if it is alive

  G4ParticleDefinition *particle=fTrack->GetDefinition();

  G4VPhysicalVolume* prevolume  =
    fStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4VPhysicalVolume* postvolume  =
    fStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume();

  G4double preX = fStep->GetPreStepPoint()->GetPosition().x();
  G4double preY = fStep->GetPreStepPoint()->GetPosition().y();
  G4double preZ  = fStep->GetPreStepPoint()->GetPosition().z();
  G4double prekinE  = fStep->GetPreStepPoint()->GetKineticEnergy();

  G4double postX = fStep->GetPostStepPoint()->GetPosition().x();
  G4double postY = fStep->GetPostStepPoint()->GetPosition().y();
  G4double postZ = fStep->GetPostStepPoint()->GetPosition().z();
  G4double postkinE  = fStep->GetPostStepPoint()->GetKineticEnergy();

  ///G4int copynum = fStep->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber();
  ///G4int copynumpre = fStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

  ///G4ThreeVector momentumdirection = fTrack->GetMomentumDirection();
  ///G4double theta = momentumdirection.theta();

  G4String particleName = particle->GetParticleName();
  G4String preName=prevolume->GetName();
  G4String postName=postvolume->GetName();
  G4String procN;

  if(fTrack->GetCreatorProcess()!=0) {
    procN = fTrack->GetCreatorProcess()->GetProcessName();
      if (postName == "World") {
        fTrack->SetTrackStatus(fStopAndKill);
      }
	if((edepStep!=0)||(postName == "Detector")){
      if(fLite==false)
		{
	G4cout << "CalDat " << particleName << " " << procN << " " << trackID << " " << edepStep / MeV << " "
             << postkinE / eV << " " << preX / cm << " " << preY / cm << " " << preZ / cm
             << " " << postX / cm << " " << postY / cm << " " << postZ / cm << " " << preName << " " << postName << " "
             << postTime / ns << G4endl;
		}
		else
		{
	G4cout << "CalDat " << particleName << " " << procN << " " << edepStep / MeV << " "
             << preX / cm << " " << preY / cm << " " << preZ / cm
             << " " << postX / cm << " " << postY / cm << " " << postZ / cm << " " << preName << " " << postName
			<< G4endl;
		}}
      //fEventAction->SetTempID(trackID);
      if (postName == "Detector"){
		   G4cout << "CalHit" << postX / cm << " " << postY / cm << " " << postZ / cm <<G4endl;
		   fEventAction->SetHitNumber();
		   fTrack->SetTrackStatus(fStopAndKill); 
		   }
    }

}

/// End of file

