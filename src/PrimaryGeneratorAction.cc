// Sandro Boschetti

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
  //particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="geantino"));
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
  particleGun->SetParticleEnergy(0.140*MeV);
//  particleGun->SetParticlePosition(G4ThreeVector(Teste::teste, 0.0, 0.0));
  particleGun->SetParticlePosition(G4ThreeVector(0.5*m, 0.0, 0.0));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

//void PrimaryGeneratorAction::setSourcePosition(G4double pos){
//	this->sourcePosition = pos;
//}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
//  G4int i = anEvent->GetEventID() % 3;
//  G4ThreeVector v(1.0,0.0,0.0);
//  switch(i)
//  {
//    case 0:
//      break;
//    case 1:
//      v.setY(0.1);
//      break;
//    case 2:
//      v.setZ(0.1);
//      break;
//  }

	//SrBRandom *teste = new SrBRandom();

	MyRandom *myRand = new MyRandom();

	G4double randX = myRand->getRandomNumber();
	G4double randY = myRand->getRandomNumber();
	G4double randZ = myRand->getRandomNumber();

	G4double px = 2 * randX - 1;
	G4double py = 2 * randY - 1;
	G4double pz = 2 * randZ - 1;

	G4ThreeVector v(px, py, pz);

//	G4double py = (2 * teste->getRandomNumber() - 1) * 0.1;
//	G4double pz = (2 * teste->getRandomNumber() - 1) * 0.1;
//	G4ThreeVector v(1.0, py, pz);
//	G4ThreeVector v(1.0, 0.0, 0.0);
	//sleep(1);

  particleGun->SetParticleMomentumDirection(v);
  particleGun->GeneratePrimaryVertex(anEvent);
}


