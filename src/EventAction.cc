
/**
 * @file /ECal_MT/src/EventAction.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of ECal's Event action source code for a particle from start till leaving the world (event).
 * Latest updates of project can be found in README file.
 **/

#include "EventAction.hh"

/**
 * @brief Constructor of Event action
 * 
 * @param detectorHit 	Counter for photons in Detector
 * 
 **/

EventAction::EventAction()
: G4UserEventAction(), detectorHit(0)
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
}

/// End of file
