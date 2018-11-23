/**
 * @file /ECal_MT/include/Run.hh
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of ECal's run class for threads.
 * Latest updates of project can be found in README file.
 **/
 
#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "globals.hh"

class Run : public G4Run
{
public:
  Run();
  virtual ~Run();

  virtual void Merge(const G4Run*);
  
};

#endif

/// End of file

