/**
 * @file /DB_EMCal/src/EventAction.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's Event action source code for a particle from start till leaving the world (event).
 * Latest updates of project can be found in README file.
 **/

#include "EventAction.hh"

/// @brief Constructor of Event action

EventAction::EventAction(HistoManager* histo)
: G4UserEventAction(), fHistoManager(histo)
{} 

/// @brief Destructor of Event action

EventAction::~EventAction()
{}

/**
 * @brief Beginning of event
 * 
 * @param Current event
 * 
 **/

void EventAction::BeginOfEventAction(const G4Event*)
{
}

/**
 * @brief End of event
 * 
 * @param Current event
 * 
 **/

void EventAction::EndOfEventAction(const G4Event*)
{   
  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun()); /// accumulate statistics in DERun
}


/// End of file
