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

  numberOfEvent++;

  timeAtEndOfEvent = time(0);
  if ( (numberOfEvent % 5000) == 0) {
	  numEventsToGo = this->numberOfEventToBeProcessed - numberOfEvent;
	  timeToGo = ( (timeAtEndOfEvent - timeAtBeginOfEvent)/ ((double)numberOfEvent) ) * numEventsToGo;
	  timeToGoMinutos = (int)(timeToGo/60);
	  timeToGoSegundos = timeToGo - (timeToGoMinutos * 60);
	  G4cout << "Termino em:" << std::setw(4) << timeToGoMinutos << " min e"
			 << std::setw(3) << timeToGoSegundos << " seg. "
			 << "Eventos restantes:" << std::setw(8) << numEventsToGo
			 << G4endl;
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



  
