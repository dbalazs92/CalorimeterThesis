/**
 * @file /DB_EMCal/src/PhysicsList.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's physics list source code for definition of physics.
 * Latest updates of project can be found in README file.
 **/

#include "PhysicsList.hh"
#include "globals.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmStandardPhysicsGS.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4EmStandardPhysicsWVI.hh"
#include "G4EmStandardPhysicsGS.hh"
#include "G4EmStandardPhysicsSS.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4ChargeExchangePhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4NeutronCrossSectionXS.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4IonPhysics.hh"
#include "G4EmExtraPhysics.hh"

#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsFTFP_BERT_TRV.hh"
#include "G4HadronPhysicsFTF_BIC.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_FTFP_BERT.hh"
#include "G4HadronPhysicsQGS_BIC.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

G4ThreadLocal G4int PhysicsList::fVerboseLevel = 1;
G4ThreadLocal G4int PhysicsList::fMaxNumPhotonStep = 40;
G4ThreadLocal G4Cerenkov* PhysicsList::fCerenkovProcess = 0;
G4ThreadLocal G4Scintillation* PhysicsList::fScintillationProcess = 0;
G4ThreadLocal G4OpAbsorption* PhysicsList::fAbsorptionProcess = 0;
G4ThreadLocal G4OpRayleigh* PhysicsList::fRayleighScatteringProcess = 0;
G4ThreadLocal G4OpMieHG* PhysicsList::fMieHGScatteringProcess = 0;
G4ThreadLocal G4OpBoundaryProcess* PhysicsList::fBoundaryProcess = 0;

/**
 * @brief Constructor of Physics list
 * 
 * @param inPhysList	Name of Hadronic physics list
 * 
 **/

PhysicsList::PhysicsList(G4String inPhysList, G4int fCut)
 : G4VModularPhysicsList(),fEmPhysicsList(0),fDecay(0)
{
  fCutForParticle=1000;

  scut=fCut;

  G4LossTableManager::Instance();
  defaultCutValue = fCutForParticle*micrometer;
  fCutForGamma     = defaultCutValue;
  fCutForElectron  = defaultCutValue;
  fCutForPositron  = defaultCutValue;
  fCutForProton    = defaultCutValue;
  fCutForElectron  = defaultCutValue;
  SetVerboseLevel(1);


  AddPhysicsList("emstandard_opt0");
  AddPhysicsList(inPhysList);
  fDecay = new G4DecayPhysics();
  
  fParticleList = new G4DecayPhysics("decays"); /// Particles
  
  G4LossTableManager::Instance(); 
}

/// @brief Destructor of Physics list

PhysicsList::~PhysicsList()
{
  delete fDecay;
  delete fParticleList;
  delete fEmPhysicsList;
  for(size_t i=0; i<fHadronPhys.size(); i++) {
    delete fHadronPhys[i];
  }
}

/// @brief Void for Particle construction

void PhysicsList::ConstructParticle()
{
  fParticleList->ConstructParticle();
   
  fEmPhysicsList->ConstructParticle();
  fDecay->ConstructParticle();
  
  G4BosonConstructor bConstructor;
  bConstructor.ConstructParticle();

  G4LeptonConstructor lConstructor;
  lConstructor.ConstructParticle();

  G4MesonConstructor mConstructor;
  mConstructor.ConstructParticle();

  G4BaryonConstructor rConstructor;
  rConstructor.ConstructParticle();

  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();
}

/// @brief Void for Physics construction

void PhysicsList::ConstructProcess()
{
    if (verboseLevel > -1) {
      G4cout << "PhysicsList::ConstructProcess start" << G4endl;
    }
    
    /// transportation
    
    AddTransportation();
    ConstructOp();

    /// electromagnetic physics list
    
    fEmPhysicsList->ConstructProcess();

    /// decay process
    
    fDecay->ConstructProcess();

    
    G4double lowEnergyEnd=1000*eV;
      
      /// Deexcitation
      G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
      de->SetFluo(false);
      de->SetAuger(false);
      de->SetPIXE(false);

      switch(scut){
      case 0:
        fCutForParticle=pow(10,2);
        de->SetFluo(true);
        de->SetAuger(true);
        de->SetPIXE(true);
        lowEnergyEnd=1*keV;
        break;

      case 1:
        fCutForParticle=pow(10,2);
        de->SetFluo(true);
        de->SetAuger(false);
        de->SetPIXE(false);
        lowEnergyEnd=10*keV;
        break;

      case 2:
        fCutForParticle=pow(10,3);
        de->SetFluo(true);
        de->SetAuger(false);
        de->SetPIXE(false);
        lowEnergyEnd=100*keV;
        break;

      case 3:
        fCutForParticle=pow(10,3);
        de->SetFluo(false);
        de->SetAuger(false);
        de->SetPIXE(false);
        lowEnergyEnd=100*keV;
        break;

      }

    G4LossTableManager::Instance()->SetAtomDeexcitation(de);
    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowEnergyEnd, 1*GeV);

    G4EmProcessOptions emOptions;

    emOptions.SetMinEnergy(100*eV);
    emOptions.SetMaxEnergy(100*TeV);
    emOptions.SetDEDXBinning(12*10);
    emOptions.SetLambdaBinning(12*10);


    emOptions.SetMscStepLimitation(fUseSafety);
    emOptions.SetStepFunction(0.2, 100*um);
    
    SetCuts();
    
    fParticleList->ConstructProcess();
    for(size_t i=0; i<fHadronPhys.size(); i++) {
    fHadronPhys[i]->ConstructProcess();
  }

}

/// @brief Adding Hadronic physics list

void PhysicsList::AddPhysicsList(const G4String& name)
{
  if (verboseLevel>0) {
    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
  }
  if (name == "emstandard_opt0") {
  
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics();
    
  } else if (name == "emstandard_opt1") {

    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option1();

  } else if (name == "emstandard_opt2") {

    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option2();

  } else if (name == "emstandard_opt3") {

    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option3();

  } else if (name == "emstandard_opt4") {

    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option4();

  } else if (name == "emstandardWVI") {

    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysicsWVI();

  } else if (name == "emstandardGS") {

    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysicsGS();

  
  } else if (name == "emstandardSS") {

    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysicsSS();

  
  } else if (name == "empenelope") {

    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmPenelopePhysics();

  
  } else if (name == "emlivermore") {

    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmLivermorePhysics();
  }
    else if (name == "emlowenergy") {

    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmLowEPPhysics();

  } else if (name == "FTFP_BERT_EMV") {

    AddPhysicsList("emstandard_opt1");
    AddPhysicsList("FTFP_BERT");

  } else if (name == "FTFP_BERT_EMX") {

    AddPhysicsList("emstandard_opt2");
    AddPhysicsList("FTFP_BERT");

  } else if (name == "FTFP_BERT_EMY") {

    AddPhysicsList("emstandard_opt3");
    AddPhysicsList("FTFP_BERT");

  } else if (name == "FTFP_BERT_EMZ") {

    AddPhysicsList("emstandard_opt4");
    AddPhysicsList("FTFP_BERT");

  } else if (name == "FTFP_BERT") {

    SetBuilderList0(false);
    fHadronPhys.push_back( new G4HadronPhysicsFTFP_BERT());

  } else if (name == "FTFP_BERT_TRV") {

    AddPhysicsList("emstandardGS");
    SetBuilderList1(false);
    fHadronPhys.push_back( new G4HadronPhysicsFTFP_BERT_TRV());

  } else if (name == "FTF_BIC") {

    SetBuilderList0(false);
    fHadronPhys.push_back( new G4HadronPhysicsFTF_BIC());

  } else if (name == "QBBC") {

    AddPhysicsList("emstandard_opt0");
    SetBuilderList2();
    fHadronPhys.push_back( new G4HadronInelasticQBBC());

  } else if (name == "QGSP_BERT") {

    SetBuilderList0(false);
    fHadronPhys.push_back( new G4HadronPhysicsQGSP_BERT());

  } else if (name == "QGSP_FTFP_BERT") {

    SetBuilderList0(false);
    fHadronPhys.push_back( new G4HadronPhysicsQGSP_FTFP_BERT());

  } else if (name == "QGSP_FTFP_BERT_EMV") {

    AddPhysicsList("emstandard_opt1");
    AddPhysicsList("QGSP_FTFP_BERT");

  } else if (name == "QGSP_BERT_EMV") {

    AddPhysicsList("emstandard_opt1");
    AddPhysicsList("QGSP_BERT");

  } else if (name == "QGSP_BERT_EMX") {

    AddPhysicsList("emstandard_opt2");
    AddPhysicsList("QGSP_BERT");

  } else if (name == "QGSP_BERT_HP") {

    SetBuilderList0(true);
    fHadronPhys.push_back( new G4HadronPhysicsQGSP_BERT_HP());

  } else if (name == "QGSP_BIC") {

    SetBuilderList0(false);
    fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC());

  } else if (name == "QGSP_BIC_EMY") {

    AddPhysicsList("emstandard_opt3");
    SetBuilderList0(false);
    fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC());

  } else if (name == "QGS_BIC") {

    SetBuilderList0(false);
    fHadronPhys.push_back( new G4HadronPhysicsQGS_BIC());

  } else if (name == "QGSP_BIC_HP") {

    SetBuilderList0(true);
    fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC_HP());

  } else {

    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">"
           << " is not defined"
           << G4endl;
  }
}

/// @brief Defining Optical physics processes

void PhysicsList::ConstructOp()
{
  fCerenkovProcess = new G4Cerenkov("Cerenkov");
  fCerenkovProcess->SetMaxNumPhotonsPerStep(fMaxNumPhotonStep);
  fCerenkovProcess->SetMaxBetaChangePerStep(10.0);
  fCerenkovProcess->SetTrackSecondariesFirst(true);
  fScintillationProcess = new G4Scintillation("Scintillation");
  fScintillationProcess->SetScintillationYieldFactor(1.);
  fScintillationProcess->SetTrackSecondariesFirst(true);
  fAbsorptionProcess = new G4OpAbsorption();
  fRayleighScatteringProcess = new G4OpRayleigh();
  fMieHGScatteringProcess = new G4OpMieHG();
  fBoundaryProcess = new G4OpBoundaryProcess();

  fCerenkovProcess->SetVerboseLevel(fVerboseLevel);
  fScintillationProcess->SetVerboseLevel(fVerboseLevel);
  fAbsorptionProcess->SetVerboseLevel(fVerboseLevel);
  fRayleighScatteringProcess->SetVerboseLevel(fVerboseLevel);
  fMieHGScatteringProcess->SetVerboseLevel(fVerboseLevel);
  fBoundaryProcess->SetVerboseLevel(fVerboseLevel);

  /// Use Birks Correction in the Scintillation process
  if(G4Threading::IsMasterThread())
  {
    G4EmSaturation* emSaturation =
              G4LossTableManager::Instance()->EmSaturation();
      fScintillationProcess->AddSaturation(emSaturation);
  }

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    if (fCerenkovProcess->IsApplicable(*particle)) {
      pmanager->AddProcess(fCerenkovProcess);
      pmanager->SetProcessOrdering(fCerenkovProcess,idxPostStep);
    }
    if (fScintillationProcess->IsApplicable(*particle)) {
      pmanager->AddProcess(fScintillationProcess);
      pmanager->SetProcessOrderingToLast(fScintillationProcess, idxAtRest);
      pmanager->SetProcessOrderingToLast(fScintillationProcess, idxPostStep);
    }
    if (particleName == "opticalphoton") {
      G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
      pmanager->AddDiscreteProcess(fAbsorptionProcess);
      pmanager->AddDiscreteProcess(fRayleighScatteringProcess);
      pmanager->AddDiscreteProcess(fMieHGScatteringProcess);
      pmanager->AddDiscreteProcess(fBoundaryProcess);
    }
  }
}
/// @brief Setting Verbose

void PhysicsList::SetVerbose(G4int verbose)
{
  fVerboseLevel = verbose;

  fCerenkovProcess->SetVerboseLevel(fVerboseLevel);
  fScintillationProcess->SetVerboseLevel(fVerboseLevel);
  fAbsorptionProcess->SetVerboseLevel(fVerboseLevel);
  fRayleighScatteringProcess->SetVerboseLevel(fVerboseLevel);
  fMieHGScatteringProcess->SetVerboseLevel(fVerboseLevel);
  fBoundaryProcess->SetVerboseLevel(fVerboseLevel);
}

/// @brief Hadronic build list #0

void PhysicsList::SetBuilderList0(G4bool flagHP)
{
  fHadronPhys.push_back( new G4EmExtraPhysics(verboseLevel));
  if(flagHP) {
    fHadronPhys.push_back( new G4HadronElasticPhysicsHP(verboseLevel) );
  } else {
    fHadronPhys.push_back( new G4HadronElasticPhysics(verboseLevel) );
  }
  fHadronPhys.push_back( new G4StoppingPhysics(verboseLevel));
  fHadronPhys.push_back( new G4IonPhysics(verboseLevel));
  fHadronPhys.push_back( new G4NeutronTrackingCut(verboseLevel));
}

/// @brief Hadronic build list #1

void PhysicsList::SetBuilderList1(G4bool flagHP)
{
  fHadronPhys.push_back( new G4EmExtraPhysics(verboseLevel));
  if(flagHP) {
    fHadronPhys.push_back( new G4HadronElasticPhysicsHP(verboseLevel) );
  } else {
    fHadronPhys.push_back( new G4HadronHElasticPhysics(verboseLevel) );
  }
  fHadronPhys.push_back( new G4StoppingPhysics(verboseLevel));
  fHadronPhys.push_back( new G4IonPhysics(verboseLevel));
  fHadronPhys.push_back( new G4NeutronTrackingCut(verboseLevel));
}

/// @brief Hadronic build list #2

void PhysicsList::SetBuilderList2()
{
  fHadronPhys.push_back( new G4EmExtraPhysics(verboseLevel));
  fHadronPhys.push_back( new G4HadronElasticPhysicsXS(verboseLevel) );
  fHadronPhys.push_back( new G4StoppingPhysics(verboseLevel));
  fHadronPhys.push_back( new G4IonPhysics(verboseLevel));
  fHadronPhys.push_back( new G4NeutronTrackingCut(verboseLevel));
}

/// @brief Setting cuts universally

void PhysicsList::SetCuts()
{

  if (verboseLevel >0)
  {
    G4cout << "PhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }

  SetCutValue(fCutForGamma, "gamma"); /// set cut values for gamma at first and for e- second and next for e+,
  SetCutValue(fCutForElectron, "e-"); /// because some processes for e+/e- need cut values for gamma
  SetCutValue(fCutForPositron, "e+");
  SetCutValue(fCutForProton, "proton");

  if (verboseLevel>0) { DumpCutValuesTable(); }
}


/// End of file
