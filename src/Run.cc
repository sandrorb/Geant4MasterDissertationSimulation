/**
 *
 * @author Sandro Boschetti, August 28, 2012
 *
 * This class is based in the Geant4's Example 07 class.
 *
 */

#include "Run.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"

Run::Run() {

  G4SDManager* SDMan = G4SDManager::GetSDMpointer();
  ID = SDMan->GetCollectionID("mySrBDetector/eDep");

}

Run::~Run()
{;}

void Run::RecordEvent(const G4Event* evt) {

  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if (!HCE) return;

	// Usando funcao dessa classe herdada da mae G4Run
//	G4cout << "Numero de eventos a serem processados: " << this->GetNumberOfEventToBeProcessed() - numberOfEvent  << G4endl;
	// numberOfEvent eh campo G4int de G4Run
	numberOfEvent++;

      G4THitsMap<G4double>* evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(ID));
      energySum += *evtMap;

//      G4cout << energySum << G4endl;
}


G4double Run::GetTotal(const G4THitsMap<G4double> &map) const {

  G4double tot = 0.;
  std::map<G4int,G4double*>::iterator itr = map.GetMap()->begin();

  for(; itr != map.GetMap()->end(); itr++) {
	  tot += *(itr->second);
  }

  return tot;
}



  
