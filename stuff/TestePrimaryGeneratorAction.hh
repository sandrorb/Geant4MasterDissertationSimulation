//
// $Id: ExN01PrimaryGeneratorAction.hh,v 1.5 2006/06/29 17:47:17 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//

#ifndef TestePrimaryGeneratorAction_h
#define TestePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;

class TestePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
	TestePrimaryGeneratorAction();
    ~TestePrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  private:
    G4ParticleGun* particleGun;
};

#endif


