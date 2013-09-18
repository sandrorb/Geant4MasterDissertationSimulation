/**
 * @author Sandro Boschetti, January 9th, 2013
 * @version 0.5
 * About the author: http://about.me/sandrorb
 * Source Repository: https://github.com/sandrorb/Geant4MasterDissertationSimulation
 *
 * This ONGOING C++ project, which uses GEANT4.9.3.p02 Toolkit from CERN,
 * has been designed and implemented by Sandro Boschetti. This project
 * is part of my master's dissertation at PCTN/UFMG - http://nuclear.ufmg.br.
 *
 * Master's Dissertation Advisor: Antonella Lombardi Costa.
 *
 * Geant4 is a toolkit for the simulation of the passage of particles
 * through matter - http://geant4.cern.ch.
 *
 * CERN: The European Organization for Nuclear Research - http://www.cern.ch.
 *
 */


#include <iostream>
#include <ctime> // Used to get time to calculate duration simulation.

#include "G4RunManager.hh" // This class must be instantiated by the user. It controls the whole simulation.
#include "G4UImanager.hh"

/*
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

#include "globals.hh"
#include <string>
#include <sstream>

void setupUIProgramatically(G4UImanager *UI);

/**
 * This is the main routine, i.e., the entry point for the program simulation.It's
 * based on the example N01 from Geant4.9.3.p02.
 *
 */
int main(G4int argc, char** argv) {

	// The first thing that must be done in the main() is to create an instance of G4RunManager class.
	G4RunManager* runManager = new G4RunManager;

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
	 * @code
	 * 	DetectorConstruction* detector = new DetectorConstruction;
	 * 	runManager->SetUserInitialization(detector);
	 * @endcode
	 * UserDetectorConstruction is one of the three mandatory classes for
	 * GEANT4 simulation that the user must implement.
	 */
//	G4VUserDetectorConstruction* detector = new DetectorConstruction;
	DetectorConstruction* detector = new DetectorConstruction;
	runManager->SetUserInitialization(detector);

	/**
	 * @code
	 * 	G4VUserPhysicsList* physics = new PhysicsList;
	 * 	runManager->SetUserInitialization(physics);
	 * @endcode
	 * G4VUserPhysicsList is one of the three mandatory classes for
	 * GEANT4 simulation that the user must implement.
	 */
	G4VUserPhysicsList* physics = new PhysicsList;
	runManager->SetUserInitialization(physics);

	/**
	 * @code
	 * 	G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction;
	 * 	runManager->SetUserAction(gen_action);
	 * @endcode
	 * G4VUserPrimaryGeneratorAction is one of the three mandatory classes for
	 * GEANT4 simulation that the user must implement.
	 */
	G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction;
	runManager->SetUserAction(gen_action);

	/**
	 * @code
	 * G4UserRunAction* run_action = new RunAction;
	 * @endcode
	 *  Adding user action
	 */
	G4UserRunAction* run_action = new RunAction;
	runManager->SetUserAction(run_action);

	/*
	 * Initialize G4 kernel
	 */
	runManager->Initialize();


	/**
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
	 *		delete myapp;
	 *@endcode
	 *
	 */
	//G4UIExecutive* session = new G4UIExecutive(argc, argv);

	/**
	 * @code
	 * G4UImanager* UI = G4UImanager::GetUIpointer();
	 * @endcode
	 * Singleton class and its constructor must not be called by the user.
	 * This object controls the command manipulation and the user interface(s).
	 *
	 * Using G4UImanager object it is possible to set a variety of
	 * information for the simulation.
	 *
	 */
//	G4UImanager* UI = G4UImanager::GetUIpointer();

	/**
	 * @code
	 * setupUIProgramatically(UI);
	 * @endcode
	 * Local function implemented for a sake of organization.
	 * This function sets up some UI characteristics.
	 */
//	setupUIProgramatically(UI);

	 // This gets the actual time. Used to compute the simulation time.
	time_t timeAtBegin = time(0);

	G4int numberOfEvent = 1000;
	runManager->BeamOn(numberOfEvent);

	time_t timeAtEnd = time(0);
	G4cout << "Simulation started at: " << timeAtBegin << G4endl << "Simlulation ended at:: " << timeAtEnd << G4endl;
	G4cout << "Time interval in minutes: " << (timeAtEnd - timeAtBegin) / 60.0 << G4endl;
	G4cout << "\7\7\7\7";

//	G4String command = "/control/execute ";
//	G4String fileName = "myMacro.mac"; //arrgv[1];
//	UI->ApplyCommand(command+fileName);

	/*
	 * Related to G4UIExecutive class
	 */
	// Starts interactive session
//	session->SessionStart();
//	delete session;

	#ifdef G4VIS_USE
		delete visManager;
	#endif

	delete runManager;

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
	UI->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 45 45");
	//UI->ApplyCommand("/vis/scene/endOfEventAction accumulate 20");
	//UI->ApplyCommand("/vis/scene/add/axes 0 0 0 5 m"); // x, y, z, comprimento, unidade
	UI->ApplyCommand("/vis/viewer/zoom 1.2");

	//UI->ApplyCommand("/vis/drawView");
	//UI->ApplyCommand("/vis/scene/add/trajectories smooth");
	//UI->ApplyCommand("/vis/scene/add/hits");
	//UI->ApplyCommand("/tracking/storeTrajectory");
	//UI->ApplyCommand("/vis/viewer/set/style surface"); //wireframe or surface
	//UI->ApplyCommand("/tracking/storeTrajectory 20");
	UI->ApplyCommand("/vis/scene/endOfEventAction accumulate 30");
}
