/**
 * @file /DB_EMCal/include/PhysicsList.hh
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's physics list class for definition of physics.
 * Latest updates of project can be found in README file.
 **/

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4Threading.hh"
#include "G4LossTableManager.hh"
#include "G4ProcessManager.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpMieHG.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"
#include "G4Decay.hh"

#include "G4EmProcessOptions.hh"
#include "G4MscStepLimitType.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"


class G4Cerenkov;
class G4Scintillation;
class G4OpAbsorption;
class G4OpRayleigh;
class G4OpMieHG;
class G4OpBoundaryProcess;

class PhysicsList: public G4VModularPhysicsList
{
public:
  PhysicsList(G4String PhysList, G4int fCut);
  virtual ~PhysicsList();

  virtual void ConstructParticle();
  virtual void ConstructProcess();
          void ConstructOp();
            
  void AddPhysicsList(const G4String& name);
  void SetVerbose(G4int);
  
  virtual void SetCuts();

private:

  G4VPhysicsConstructor* fEmPhysicsList;
  G4VPhysicsConstructor* fDecay;
  static G4ThreadLocal G4int fVerboseLevel;
  static G4ThreadLocal G4int fMaxNumPhotonStep;

  static G4ThreadLocal G4Cerenkov* fCerenkovProcess;
  static G4ThreadLocal G4Scintillation* fScintillationProcess;
  static G4ThreadLocal G4OpAbsorption* fAbsorptionProcess;
  static G4ThreadLocal G4OpRayleigh* fRayleighScatteringProcess;
  static G4ThreadLocal G4OpMieHG* fMieHGScatteringProcess;
  static G4ThreadLocal G4OpBoundaryProcess* fBoundaryProcess;
    
  int scut;
      
  void SetBuilderList0(G4bool flagHP = false);
  void SetBuilderList1(G4bool flagHP = false);
  void SetBuilderList2();

  G4double fCutForGamma;
  G4double fCutForElectron;
  G4double fCutForPositron;
  G4double fCutForProton;
  G4double fCutForParticle;

  G4VPhysicsConstructor*  fParticleList;
  std::vector<G4VPhysicsConstructor*>  fHadronPhys;

protected:
  G4ParticleTable* theParticleTable = G4ParticleTable::GetParticleTable();
  G4ParticleTable::G4PTblDicIterator* theParticleIterator = theParticleTable->GetIterator();
};

#endif

/// End of file

