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

//  G4String detName[6] = {"Calor-A_abs","Calor-A_gap","Calor-B_abs","Calor-B_gap","Calor-C_abs","Calor-C_gap"};
//  G4String primNameSum[6] = {"eDep","nGamma","nElectron","nPositron","trackLength","nStep"};
//  G4String primNameMin[3] = {"minEkinGamma","minEkinElectron","minEkinPositron"};
//  G4String paraName[3] = {"Calor-AP_para","Calor-BP_para","Calor-CP_para"};

  G4SDManager* SDMan = G4SDManager::GetSDMpointer();
  ID = SDMan->GetCollectionID("mySrBDetector/eDep");

  // est‡ declarado no .hh
  //G4THitsMap<G4double> energySum;

//  G4String fullName;

//  size_t i,j;
//  for(i=0;i<6;i++)
//  {
//    for(j=0;j<6;j++)
//    {
//      fullName = detName[i]+"/"+primNameSum[j];
//      colIDSum[i][j] = SDMan->GetCollectionID(fullName);
//    }
//    for(j=0;j<3;j++)
//    {
//      fullName = detName[i]+"/"+primNameMin[j];
//      colIDMin[i][j] = SDMan->GetCollectionID(fullName);
//    }
//  }
//  for(i=0;i<3;i++)
//  {
//    for(j=0;j<6;j++)
//    {
//      fullName = paraName[i]+"/"+primNameSum[j];
//      colIDPara[i][j] = SDMan->GetCollectionID(fullName);
//    }
//  }
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



  
