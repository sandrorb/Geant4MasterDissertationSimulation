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
//  ID = SDMan->GetCollectionID("myDetector/eDep");

  std::string detectorName;
  for (size_t i = 0; i<50; i++){
	  detectorName = "myDetector" + static_cast<std::ostringstream*>( &(std::ostringstream() << i) )->str();
	  myID[i] = SDMan->GetCollectionID(detectorName + "/eDep");
	  //std::cout << detectorName + "/eDep" << std::endl;
	  //std::cout << "myID[" << i << "] = " << myID[i] << std::endl;
  }

  timeAtBeginOfEvent = time(0);

}

Run::~Run()
{;}

void Run::RecordEvent(const G4Event* evt) {

  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if (!HCE) return;

	// Usando funcao dessa classe herdada da mae G4Run
  	// G4cout << "Numero de eventos a serem processados: " << this->GetNumberOfEventToBeProcessed() - numberOfEvent  << G4endl;
	// numberOfEvent is a G4int member of G4Run
  numberOfEvent++;

  timeAtEndOfEvent = time(0);
  if ( (numberOfEvent % 1000) == 0) {
	  numEventsToGo = this->numberOfEventToBeProcessed - numberOfEvent;
	  timeToGo = ( (timeAtEndOfEvent - timeAtBeginOfEvent)/ ((double)numberOfEvent) ) * numEventsToGo;
	  timeToGoMinutos = (int)(timeToGo/60);
	  timeToGoSegundos = timeToGo - (timeToGoMinutos * 60);
	  G4cout << "Tempo previsto para termino: " << timeToGoMinutos << " minutos e " << timeToGoSegundos << " segundos" << G4endl;
  }

 // G4THitsMap<G4double>* evtMap;

  for (size_t i = 0; i<50; i++) {
	  G4THitsMap<G4double>* evtMap = (G4THitsMap<G4double>*)(  HCE->GetHC(myID[i])  );
	  energySum[i] += (*evtMap);
  }


//  for (G4int i = 0; i<50; i++) {
//	  G4THitsMap<G4double>* evtMap = (G4THitsMap<G4double>*)(HCE->GetHC(myID[i]));
//
//	  std::cout << "AAAAAAAAAAAAAAAAntes do Iterator" << std::endl;
//	  std::map<G4int, G4double*>::iterator itr = evtMap->GetMap()->begin();
//	  std::cout << "DDDDDDDDDDDDDDDDDEPOIS do Iterator" << std::endl;

//	  for(; itr != evtMap->GetMap()->end(); itr++) {
//		  myEnergy[i] = myEnergy[i] + *(itr->second);
//		  //std::cout << myEnergy[i] << std::endl;
//	  }
//  }


  //energySum += *evtMap;

//      G4cout << energySum.GetName() << G4endl;
}


G4double Run::GetTotal(const G4THitsMap<G4double> &map) const {

  G4double total = 0.;
  std::map<G4int,G4double*>::iterator itr = map.GetMap()->begin();

  for(; itr != map.GetMap()->end(); itr++) {
	  total += *(itr->second);
  }

  return total;
}



  
