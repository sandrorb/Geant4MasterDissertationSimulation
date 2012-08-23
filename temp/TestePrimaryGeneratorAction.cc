//
// $Id: ExN01PrimaryGeneratorAction.cc,v 1.6 2006/06/29 17:47:23 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//

#include "TestePrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

TestePrimaryGeneratorAction::TestePrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="geantino"));
  particleGun->SetParticleEnergy(1.0*GeV);
  particleGun->SetParticlePosition(G4ThreeVector(-2.0*m, 0.0, 0.0));
}

TestePrimaryGeneratorAction::~TestePrimaryGeneratorAction()
{
  delete particleGun;
}

void TestePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4int i = anEvent->GetEventID() % 3;
  G4ThreeVector v(1.0,0.0,0.0);
  switch(i)
  {
    case 0:
      break;
    case 1:
      v.setY(0.1);
      break;
    case 2:
      v.setZ(0.1);
      break;
  }
  particleGun->SetParticleMomentumDirection(v);
  particleGun->GeneratePrimaryVertex(anEvent);
}


