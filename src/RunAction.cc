/**
 * @file /DB_EMCal/src/RunAction.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's run action source code for RunAction global.
 * Latest updates of project can be found in README file.
 **/

#include "RunAction.hh"

/// @brief Constructor of Run

RunAction::RunAction(HistoManager* histo)
: G4UserRunAction(), fHisto(histo)
{   
}

/// @brief Destructor of Run

RunAction::~RunAction()
{}

/// @brief Generation of Runs

G4Run* RunAction::GenerateRun()
{
  return new Run; 
}

/// @brief Start of Run action

void RunAction::BeginOfRunAction(const G4Run*)
{
}

/// @brief End of Run action

void RunAction::EndOfRunAction(const G4Run*)
{
  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  fHisto->Save();
}

/// End of file
