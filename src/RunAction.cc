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
	G4cout << "\n\n\n\n\n\n\n\n"; // some screen cleaning for simulation user info.
	G4cout << "Simulation Started!!!\n";
}

void RunAction::EndOfRunAction(const G4Run* aRun) {

  const Run* theRun = (const Run*)aRun;
//  G4double nEvt = (G4double)(theRun->GetNumberOfEvent());
//  G4cout << "Numero de Eventos: " << nEvt << G4endl;

//  G4cout << "Deposited Energy: " << G4BestUnit(theRun->GetTotalEnergyDeposited(),"Energy") << G4endl;
//  G4cout << "Deposited Energy: " << theRun->GetTotalEnergyDeposited()/MeV << " MeV" << G4endl;

//  G4double densidadeBe = 1.848*g/cm3;
//  G4double ro_for_Be_1033keV = 0.554*g/cm2;
//  G4double ro_for_Be_1033keV_em_cm = ro_for_Be_1033keV / densidadeBe;
//  G4double deltaZ = 0.02 * ro_for_Be_1033keV_em_cm / ro_for_Be_1033keV_em_cm;
  G4double deltaZ = 0.02;

  G4cout << "Energy in MeV" << G4endl;
  for (G4int i = 0; i<50; i++) {
	  G4cout << i * deltaZ + (deltaZ / 2) << "    " << theRun->GetMyTotalEnergyDeposited(i)/MeV << G4endl;
  }


//  G4cout << "myEnergy        : " << theRun->GetMyTotalEnergyDeposited(49)/MeV << " MeV" << G4endl;
  G4cout << "Number of Events: " << theRun->GetNumberOfEvent() << G4endl;
}

