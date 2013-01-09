/**
 *
 * @author Sandro Boschetti, August 28, 2012
 *
 * This class is based in the Geant4's Example 07 class.
 *
 */


#include "RunAction.hh"
#include "Run.hh"

#include "G4RegionStore.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"

//#include "G4VSteppingVerbose.hh"
//#include "ExN07SteppingVerbose.hh"

RunAction::RunAction() {;}

RunAction::~RunAction() {;}

/**
 * This is the connection between RunAction and Run classes.
 */
G4Run* RunAction::GenerateRun() {
	return new Run;
}

void RunAction::BeginOfRunAction(const G4Run*) {

}

void RunAction::EndOfRunAction(const G4Run* aRun) {

  const Run* theRun = (const Run*)aRun;
//  G4double nEvt = (G4double)(theRun->GetNumberOfEvent());
//  G4cout << "Numero de Eventos: " << nEvt << G4endl;

//  G4cout << "Deposited Energy: " << G4BestUnit(theRun->GetTotalEnergyDeposited(),"Energy") << G4endl;
  G4cout << "Deposited Energy: " << theRun->GetTotalEnergyDeposited()/MeV << " MeV" << G4endl;
  G4cout << "Number of Events: " << theRun->GetNumberOfEvent() << G4endl;
}

