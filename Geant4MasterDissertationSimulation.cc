/**
 * @author Sandro Boschetti, August 24, 2012
 * @version 0.2
 *
 * This is the main routine, i.e., the entry point for the program simulation. It's
 * based on the example N01 from Geant4.9.3.p02.
 *
 */

#include <ctime> // Used to get time to calculate duration simulation.

#include "G4RunManager.hh" // This class must be instatiated by the user. It controls the whole simulation.
#include "G4UImanager.hh"

/**
 * List of classes that must be implemented by the user.
 */
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

#ifdef G4VIS_USE
	#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
	#include "G4UIExecutive.hh"
#endif

//for sleep(seconds) function
#include <pthread.h>

void setupUIProgramatically(G4UImanager *UI);

/**
 * Entry point function for the whole simulation.
 */
int main(G4int argc, char** argv) {

	/**
	 * This gets the actual time for simulation duration computation.
	 */
	time_t timeAtBegin = time(0);

	/*
	 * The first thing that must be done in the main() is create an instance of
	 * G4RunManager class.
	 */
	G4RunManager* runManager = new G4RunManager;
	//runManager->SetUserAction(new BeamTestEventAction);

	/*
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


	/*
	 * UserDetectorConstruction is one of the three mandatory classes for
	 * GEANT4 simulation that the user must implement.
	 */
//	G4VUserDetectorConstruction* detector = new DetectorConstruction;
	DetectorConstruction* detector = new DetectorConstruction;
	runManager->SetUserInitialization(detector);

	/*
	 * G4VUserPhysicsList is one of the three mandatory classes for
	 * GEANT4 simulation that the user must implement.
	 */
	G4VUserPhysicsList* physics = new PhysicsList;
	runManager->SetUserInitialization(physics);

	/*
	 * G4VUserPrimaryGeneratorAction is one of the three mandatory classes for
	 * GEANT4 simulation that the user must implement.
	 */
	G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction;
	runManager->SetUserAction(gen_action);

	/**
	 *  Adding user action
	 */
	G4UserRunAction* run_action = new RunAction;
	runManager->SetUserAction(run_action);

	/*
	 * Initialize G4 kernel
	 */
	runManager->Initialize();


	/*
	 *	This class helps automatic instantiation of user session
	 *	according to your environment variable like G4UI_USE_XXX.
	 *@code
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
	 *		delete myapp;@endcode
	 *
	 */
	G4UIExecutive* session = new G4UIExecutive(argc, argv);

	/*
	 * Using G4UImanager object it is possible to set a variety of
	 * information for the simulation.
	 */


	/*
	 * Singleton class and its constructor must not be called by the user.
	 * This object controls the command manipulation and the user interface(s).
	 */
	G4UImanager* UI = G4UImanager::GetUIpointer();

	setupUIProgramatically(UI);

//	G4int numberOfEvent = 100000000;
	G4int numberOfEvent = 30;
	runManager->BeamOn(numberOfEvent);

	/**
	 * This tanslates the physical volume
	 */
//	detector->getCube()->SetTranslation(G4ThreeVector( 0.0*m, 0.0*m, 0.0*m));
//	runManager->GeometryHasBeenModified();
//	runManager->BeamOn(numberOfEvent);


//	G4String command = "/control/execute ";
//	G4String fileName = "myMacro.mac"; //arrgv[1];
//	UI->ApplyCommand(command+fileName);


	/*
	 * Related to G4UIExecutive class
	 */
	session->SessionStart();
	delete session;

	#ifdef G4VIS_USE
		delete visManager;
	#endif

	delete runManager;


	   time_t timeAtEnd = time(0);
//	   dt = ctime(&now);
	   G4cout << "Inicio: " << timeAtBegin << G4endl << " Fim: " << timeAtEnd << G4endl;
	   G4cout << "Time interval in minutes: " << (timeAtEnd - timeAtBegin) / 60.0 << G4endl;

	return 0;
}

/**
 * This function has been implemented only for a sake of organization.
 */
void setupUIProgramatically(G4UImanager *UI){
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



