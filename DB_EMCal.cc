/**
 * @file /DB_EMCal/DB_EMCal.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's main function. 
 * Latest updates of project can be found in README file.
 **/
 
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "QGSP_BIC_HP.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "Randomize.hh"
#include "QGSP_BIC.hh"

/**
 * @brief Start of main function
 * 
 * @param	argc		Number of command line arguments
 * @param	NoE 		Command line argument for Number of events 
 * @param	Energy 		Command line argument for Kinetic energy of particle
 * @param	PhysList 	Command line argument for Hadronic physics list
 * @param	Particle	Command line argument for type of Particle
 * 
 **/

int main(int argc,char** argv)
{
  
  /// parameter from command line
  unsigned int NoE=0;
  G4double Energy=0.0;
  G4String PhysList="QGSP_BERT";
  G4String Particle="gamma";
  
  if (argc==5)
  {  
    NoE=atoi(argv[1]);
    Energy=atof(argv[2]);
    PhysList=argv[3];
    Particle=argv[4];
    
  }
  
  
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  unsigned nthreads = 2;
  runManager->SetNumberOfThreads(nthreads);
  
#else
  G4RunManager* runManager = new G4RunManager;
#endif
  
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList(PhysList));
  runManager->SetUserInitialization(new ActionInitialization(Energy, Particle));

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc==5)
  {   
    /// batch
   runManager->Initialize();
   runManager->BeamOn(NoE);
   
  }
  else
  { 
    /// interactive
    G4UIExecutive* ui = 0;
    
    if ( argc == 1 )
    {
      ui = new G4UIExecutive(argc, argv);
    }
    
    UImanager->ApplyCommand("/control/execute gui.mac");
    ui->SessionStart();
    delete ui;
  }
  
  
  delete visManager; 
  delete runManager;
}

/// End of file
