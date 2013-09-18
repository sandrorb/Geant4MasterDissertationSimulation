/**
 * @author Sandro Boschetti
 *
 * This is a class based on ExN01PhysicsList.hh from Geant4.9.3.p02
 *
 */

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class PhysicsList: public G4VUserPhysicsList
{
  public:
	PhysicsList();
    ~PhysicsList();

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

};

#endif

