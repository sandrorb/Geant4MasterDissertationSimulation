/**
 * @author Sandro Boschetti
 * @version 0.1
 *
 * This is the main routine, i.e., the entry point for the program simulation. It's
 * based on the example N01 from Geant4.9.3.p02.
 *
 */


#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "SrBDetectorConstruction.hh"
//#include "SrBPhysicsList.hh"
#include "ExN02PhysicsList.hh"
#include "SrBPrimaryGeneratorAction.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//for sleep(seconds) function
//#include <pthread.h>

//#include "SrBRandom.hh"


void setupUIProgramaticaly(G4UImanager *UI);

/**
 * Entry point function for the whole simulation.
 */
int main(G4int argc, char** argv) {

	/**
	 * The first thing that must be done in the main() is create an instance of
	 * G4RunManager class.
	 */
	G4RunManager* runManager = new G4RunManager;
	//runManager->SetUserAction(new BeamTestEventAction);

	/**
	 * G4VisManager is a singleton and an abstract class and the user must derive
	 * and implement its virtual function RegisterGraphicsSystems(). It's intended
	 * to be used for graphical UI purposes.
	 *
	 * G4VisExecutive is a concrete Visualization Manager that implements the
	 * virtual functions RegisterGraphicsSystems and RegisterModelFactories which
	 * are executed when you Initialise() OR Initialize().
	 */
	#ifdef G4VIS_USE
		// Visualization manager construction
		G4VisManager* visManager = new G4VisExecutive;
		visManager->Initialize();
	#endif

	/**
	 * UserDetectorConstruction is one of the three mandatory classes for
	 * GEANT4 simulation that the user must implement.
	 */
	G4VUserDetectorConstruction* detector = new SrBDetectorConstruction;
	runManager->SetUserInitialization(detector);

	/**
	 * G4VUserPhysicsList is one of the three mandatory classes for
	 * GEANT4 simulation that the user must implement.
	 */
	G4VUserPhysicsList* physics = new ExN02PhysicsList;
	runManager->SetUserInitialization(physics);

	/**
	 * G4VUserPrimaryGeneratorAction is one of the three mandatory classes for
	 * GEANT4 simulation that the user must implement.
	 */
	G4VUserPrimaryGeneratorAction* gen_action = new SrBPrimaryGeneratorAction;
	runManager->SetUserAction(gen_action);

	/**
	 * Initialize G4 kernel
	 */
	runManager->Initialize();

	/**
	 *	This class helps automatic instantiation of user session
	 *	according to your environment variable like G4UI_USE_XXX.
	 *
	 *	Usage in main():
	 *		...
	 *		#include "G4UIExecutive.hh"
	 *		int main(int argc, char** argv) {
	 *		...
	 *		G4UIExecutive* myapp = new G4UIExecutive(argc, argv);
	 *		if (session->IsGUI())
	 *		// Do any extra for a GUI session
	 *
	 *		myapp-> SessionStart();
	 *		...
	 *		delete myapp;
	 *
	 */
	G4UIExecutive* session = new G4UIExecutive(argc, argv);

	/**
	 * Using G4UImanager object it is possible to set a variety of
	 * information for the simulation.
	 */


	/**
	 * Singleton class and its constructor must not be called by the user.
	 * This object controls the command manipulation and the user interface(s).
	 */
	G4UImanager* UI = G4UImanager::GetUIpointer();

	setupUIProgramaticaly(UI);
	G4int numberOfEvent = 30;
	runManager->BeamOn(numberOfEvent);

//	G4String command = "/control/execute ";
//	G4String fileName = "myMacro.mac"; //argv[1];
//	UI->ApplyCommand(command+fileName);


	/**
	 * Related to G4UIExecutive class
	 */
	session->SessionStart();
	delete session;

	delete runManager;

	return 0;
}


void setupUIProgramaticaly(G4UImanager *UI){
	UI->ApplyCommand("/vis/open OGLIX");
	//UI->ApplyCommand("/vis/drawView");
	UI->ApplyCommand("/vis/drawVolume");
	//UI->ApplyCommand("/vis/scene/add/volume");
	UI->ApplyCommand("/vis/scene/add/trajectories");
	UI->ApplyCommand("/vis/scene/add/hits");
	//UI->ApplyCommand("/vis/viewer/set/hiddenEdge 0");
	UI->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 50 20");
	//UI->ApplyCommand("/vis/scene/endOfEventAction accumulate 20");
	//UI->ApplyCommand("/vis/scene/add/axes 0 0 0 5 m"); // x, y, z, comprimento, unidade
	UI->ApplyCommand("/vis/viewer/zoom 1.3");

	//UI->ApplyCommand("/vis/drawView");
	//UI->ApplyCommand("/vis/scene/add/trajectories smooth");
	//UI->ApplyCommand("/vis/scene/add/hits");
	//UI->ApplyCommand("/tracking/storeTrajectory");
	//UI->ApplyCommand("/vis/viewer/set/style surface"); //wireframe or surface
	//UI->ApplyCommand("/tracking/storeTrajectory 20");
	UI->ApplyCommand("/vis/scene/endOfEventAction accumulate 30");
}


//void teste(){
//
//	SrBRandom *teste = new SrBRandom();
//
//	for (int i=0; i<10; i++){
//		//G4cout << "Numero aleatorio: " << G4UniformRand() << G4endl;
//		G4cout << "Numero aleatorio: " << teste->getRandomNumber() <<  G4endl;
//	}
//}


