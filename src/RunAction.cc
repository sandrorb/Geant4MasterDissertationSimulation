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
 * This is te connection between RunAction and Run classes.
 */
G4Run* RunAction::GenerateRun() {
	return new Run;
}

void RunAction::BeginOfRunAction(const G4Run*) {
//  ExN07SteppingVerbose* sv = (ExN07SteppingVerbose*)(G4VSteppingVerbose::GetInstance());
//  sv->InitializeTimers();

	//const ExN07Run* theRun = (const ExN07Run*)aRun;

}

void RunAction::EndOfRunAction(const G4Run* aRun) {

//  static G4String regName[3] = {"Calor-A","Calor-B","Calor-C"};
//
  const Run* theRun = (const Run*)aRun;
//  G4double nEvt = (G4double)(theRun->GetNumberOfEvent());
//  G4cout << "Numero de Eventos: " << nEvt << G4endl;

  G4cout << "Energia depositada: " << G4BestUnit(theRun->GetTotalEnergyDeposited(),"Energy") << G4endl;
//  G4cout << "Energia depositada: " << theRun->GetTotalEnergyDeposited()*MeV << G4endl;

//  for(size_t i=0;i<3;i++)
//  {
//    size_t ih1 = 2*i;
//    size_t ih2 = 2*i+1;
//
//    G4Region* region = G4RegionStore::GetInstance()->GetRegion(regName[i]);
//    G4ProductionCuts* cuts = region->GetProductionCuts();
//    G4cout << "Region : " << region->GetName() << G4endl;
//    G4cout << " Production thresholds :" << G4endl << "   "
//           << " gamma " << G4BestUnit(cuts->GetProductionCut("gamma"),"Length")
//           << "    e- " << G4BestUnit(cuts->GetProductionCut("e-"),"Length")
//           << "    e+ " << G4BestUnit(cuts->GetProductionCut("e+"),"Length")
//           << G4endl;
//    G4cout << " Energy deposition in an event :" << G4endl << "   "
//           << " Absorber " << G4BestUnit((theRun->GetTotalE(ih1))/nEvt,"Energy")
//           << "      Gap " << G4BestUnit((theRun->GetTotalE(ih2))/nEvt,"Energy")
//           << G4endl;
//    G4cout << " Number of secondaries in an event :" << G4endl << "   "
//           << " gamma in Absorber " << (theRun->GetNGamma(ih1))/nEvt
//           << "    in Gap " << (theRun->GetNGamma(ih2))/nEvt << G4endl << "   "
//           << " e-    in Absorber " << (theRun->GetNElectron(ih1))/nEvt
//           << "    in Gap " << (theRun->GetNElectron(ih2))/nEvt << G4endl << "   "
//           << " e+    in Absorber " << (theRun->GetNPositron(ih1))/nEvt
//           << "    in Gap " << (theRun->GetNPositron(ih2))/nEvt << G4endl;
//    G4cout << " Minimum kinetic energy of generated secondaries :" << G4endl << "   "
//           << " gamma in Absorber " << G4BestUnit(theRun->GetEMinGamma(ih1),"Energy")
//           << "    in Gap " << G4BestUnit(theRun->GetEMinGamma(ih2),"Energy")
//           << G4endl << "   "
//           << " e-    in Absorber " << G4BestUnit(theRun->GetEMinElectron(ih1),"Energy")
//           << "    in Gap " << G4BestUnit(theRun->GetEMinElectron(ih2),"Energy")
//           << G4endl << "   "
//           << " e+    in Absorber " << G4BestUnit(theRun->GetEMinPositron(ih1),"Energy")
//           << "    in Gap " << G4BestUnit(theRun->GetEMinPositron(ih2),"Energy")
//           << G4endl;
//    G4cout << " Total track length of e+/e- in an event :" << G4endl << "   "
//           << " Absorber " << G4BestUnit((theRun->GetTotalL(ih1))/nEvt,"Length")
//           << "      Gap " << G4BestUnit((theRun->GetTotalL(ih2))/nEvt,"Length")
//           << G4endl;
//    G4cout << " Total number of steps of e+/e- in an event :" << G4endl << "   "
//           << " Absorber " << (theRun->GetNStep(ih1))/nEvt
//           << "      Gap " << (theRun->GetNStep(ih2))/nEvt
//           << G4endl;
//    G4cout
//    << "------------------------------------------------------------" << G4endl;
//    G4cout << "Scores in parallel geometry" << G4endl;
//    G4cout << "layer   eDep/evt  nGamma/evt nElec/evt  nPosi/evt  stpLen/evt nStep/evt"
//           << G4endl;
//    for(size_t k=0;k<20;k++)
//    {
//      G4cout << std::setw(8) << k;
//      for(size_t j=0;j<6;j++)
//      { G4cout << " " << std::setw(10) << (theRun->GetParaValue(i,j,k))/nEvt; }
//      G4cout << G4endl;
//    }
//    G4cout
//    << "############################################################" << G4endl;
//  }
//  G4cout << "CPU Time spent by each region" << G4cout;
//  ExN07SteppingVerbose* sv = (ExN07SteppingVerbose*)(G4VSteppingVerbose::GetInstance());
//  sv->Report();
}

