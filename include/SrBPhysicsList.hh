//
// $Id: ExN01PhysicsList.hh,v 1.6 2006/06/29 17:47:15 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//
//

#ifndef SrBPhysicsList_h
#define SrBPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class SrBPhysicsList: public G4VUserPhysicsList
{
  public:
	SrBPhysicsList();
    ~SrBPhysicsList();

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

};

#endif

