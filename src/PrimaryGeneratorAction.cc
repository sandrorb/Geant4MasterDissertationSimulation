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
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
//  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
  particleGun->SetParticleEnergy(10.0*MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

/**
 * "Half" isotropically generated primary events from a point source.
 */
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

//	http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides/ForApplicationDeveloper/html/ch08s04.html
//	/vis/viewer/set/viewpointThetaPhi [theta] [phi] [deg|rad]
//  Arguments "theta" and "phi" are polar and azimuthal camera angles, respectively. The default unit is "degree".

/* This is a "half" isotropically point source. It seems working. */
	G4double theta = pi + (pi/10.0) * G4UniformRand();
	G4double   phi = twopi * G4UniformRand();
	G4double px = std::sin(theta) * std::cos(phi);
	G4double py = - std::abs(std::cos(theta));
	G4double pz = std::sin(theta) * std::sin(phi);

/* This is the source location. This can be set at PrimaryGeneratorAction() method */
	G4double posX = 0.0*cm;
	G4double posY = 100*cm;
	G4double posZ = 0.0*cm;

	G4ThreeVector v(px, py, pz);

	/* This can be set at PrimaryGeneratorAction() method */
	particleGun->SetParticlePosition(G4ThreeVector(posX, posY, posZ));

	particleGun->SetParticleMomentumDirection(v);
	particleGun->GeneratePrimaryVertex(anEvent);
}

/* Flat unidirectional source. A 5x5 cm at 100 cm above the phantom surface.  */
//	G4double widthX = 5.0*cm;
//	G4double widthZ = 5.0*cm;
//	G4double posX = widthX * G4UniformRand() - widthX/2.0;
//	G4double posY = 100*cm;
//	G4double posZ = widthZ * G4UniformRand() - widthZ/2.0;
//	G4double px = 0;
//	G4double py = -1;
//	G4double pz = 0;

/* This is a point source (???) */
//	G4double theta = pi * G4UniformRand();
//	G4double   phi = pi2 * G4UniformRand();
//	G4double px = std::sin(theta) * std::cos(phi);
//	G4double py = std::cos(theta);
//	G4double pz = std::sin(theta) * std::sin(phi);

/* I haven't be able to make this work */
//	G4double px = (0.5 * G4UniformRand()) / 0.5;
//	G4double py = (0.5 * G4UniformRand()) / 0.5;
//	G4double pz = (0.5 * G4UniformRand()) / 0.5;
//	G4double norm = std::sqrt(px*px + py*py + pz*pz);
//	px = px / norm;
//	py = py / norm;
//	px = pz / norm;

/* This was my first isotropic point source. I think this is wrong. */
//	MyRandom *myRand = new MyRandom();
//	G4double randX = myRand->getRandomNumber();
//	G4double randY = myRand->getRandomNumber();
//	G4double randZ = myRand->getRandomNumber();
//	G4double px = 2 * randX - 1;
//	G4double py = 2 * randY - 1;
//	G4double pz = 2 * randZ - 1;


