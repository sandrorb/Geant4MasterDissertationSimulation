/**
 * @author Sandro Boschetti, August 30, 2012
 */

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

#include "MyRandom.hh"
#include <pthread.h>

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
  particleGun->SetParticleEnergy(0.140*MeV);
  particleGun->SetParticlePosition(G4ThreeVector(2.6*m, 0.0, 0.0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	MyRandom *myRand = new MyRandom();

	G4double randX = myRand->getRandomNumber();
	G4double randY = myRand->getRandomNumber();
	G4double randZ = myRand->getRandomNumber();

	G4double px = 2 * randX - 1;
	G4double py = 2 * randY - 1;
	G4double pz = 2 * randZ - 1;

	G4ThreeVector v(px, py, pz);

	particleGun->SetParticleMomentumDirection(v);
	particleGun->GeneratePrimaryVertex(anEvent);
}


