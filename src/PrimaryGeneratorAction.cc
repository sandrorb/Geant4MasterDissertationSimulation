/**
 * @author Sandro Boschetti, August 30, 2012
 */

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh" // for sin and cos, etc.

#include "MyRandom.hh"
#include <pthread.h>

#include "G4PhysicalConstants.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
//  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
//  particleGun->SetParticleEnergy(0.140*MeV);
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
  particleGun->SetParticleEnergy(1.033*MeV);  // 0.521*MeV ou 1.033 MeV
//  particleGun->SetParticlePosition(G4ThreeVector(0.0, 1.0*m, 0.0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

/**
 * Isotropically generated primary events from a point source.
 */
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

/* This is a point source */
//	G4double theta = pi * G4UniformRand();
//	G4double   phi = pi2 * G4UniformRand();
//	G4double px = std::sin(theta) * std::cos(phi);
//	G4double py = std::cos(theta);
//	G4double pz = std::sin(theta) * std::sin(phi);

/* Flat unidirectional source. A 5x5 cm at 100 cm above the phantom surface.  */
	G4double widthX = 5.0*cm;
	G4double widthZ = 5.0*cm;
	G4double posX = widthX * G4UniformRand() - widthX/2.0;
	G4double posY = 100*cm;
	G4double posZ = widthZ * G4UniformRand() - widthZ/2.0;
	G4double px = 0;
	G4double py = -1;
	G4double pz = 0;

	G4ThreeVector v(px, py, pz);

	particleGun->SetParticlePosition(G4ThreeVector(posX, posY, posZ));

	particleGun->SetParticleMomentumDirection(v);
	particleGun->GeneratePrimaryVertex(anEvent);
}

/* This was my first isotropic point source. I think this is wrong. */
//	MyRandom *myRand = new MyRandom();
//	G4double randX = myRand->getRandomNumber();
//	G4double randY = myRand->getRandomNumber();
//	G4double randZ = myRand->getRandomNumber();
//	G4double px = 2 * randX - 1;
//	G4double py = 2 * randY - 1;
//	G4double pz = 2 * randZ - 1;


