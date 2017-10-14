/**
 * @file /EMCal_MT/src/Run.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's run source code for threads.
 * Latest updates of project can be found in README file.
 **/


#include "Run.hh"

/// @brief Constructor of Run

Run::Run()
: G4Run()
{
} 

/// @brief Destructor of Run

Run::~Run()
{} 
 
/// @brief Void Merge

void Run::Merge(const G4Run* run)
{
  const Run* localRun = static_cast<const Run*>(run);

  G4Run::Merge(run); 
}

/// End of file


