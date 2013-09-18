//
// $Id: ExN01PhysicsList.hh,v 1.6 2006/06/29 17:47:15 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//
//

#ifndef TestePhysicsList_h
#define TestePhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class TestePhysicsList: public G4VUserPhysicsList
{
  public:
	TestePhysicsList();
    ~TestePhysicsList();

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

};

#endif

