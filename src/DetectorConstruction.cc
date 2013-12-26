/**
 * @author  Sandro Boschetti, August 30, 2012
 *
 */


#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh" // Useful for getting registered materials
#include "G4VisAttributes.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VSDFilter.hh"
#include "G4PSFlatSurfaceFlux.hh"
#include "G4SDParticleFilter.hh"

//#include "G4VPrimitiveSensitivity.hh"
#include "G4PSDoseDeposit.hh"
#include "G4PSEnergyDeposit.hh"

// Used to handle string in order to make up labels for the Boxes, Log Vol and Phy Vol
#include <string>
#include <sstream>

#include "G4UserLimits.hh"

#include "DetectorConstruction.hh"
#include "MyMaterial.hh"
#include "MyUtils.hh"

/**
 * This is the constructor class member used to construct the "DetectorConstruction" object.
 * Some DetectorConstruction class variable are initialized.
 * In this case, "{;}", no implementation has been set.
 */
DetectorConstruction::DetectorConstruction()
 :  myMaterial(0), experimentalHall_log(0), shielding_log(0), cube_log(0),
    experimentalHall_phys(0), shielding_phys(0), cube_phys(0)
{  }

DetectorConstruction::~DetectorConstruction()
{ }

/**
 * This method is related to an attempt made in order to change geometry between runs.
 */
G4VPhysicalVolume * DetectorConstruction::getWordVolume() {
	return this->experimentalHall_phys;
}

/**
 * This method is related to an attempt made in order to change geometry between runs.
 */
G4VPhysicalVolume * DetectorConstruction::getCube() {
	return this->cube_phys;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {

	MyUtils * myUtils = MyUtils::getInstance();
	G4Material* phantomMaterial = myUtils->getPhantomMaterial();

	G4NistManager* man = G4NistManager::Instance();
	man->SetVerbose(1);
	G4Material* vaccum    = man->FindOrBuildMaterial("G4_Galactic");


  /************ Begin of Volumes construction ************/

  // Experimental hall (world volume)
  // Beam line along Y axis

  G4double expHall_x = 2.0*m; // from left to right ???
  G4double expHall_y = 3.0*m; // vertical
  G4double expHall_z = 2.0*m; // from back to front ???
  G4Box* experimentalHall_box = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);

/* A LogicalVolume is some geometry figure, like a G4Box, fulfilled with some material.  */
  //experimentalHall_log = new G4LogicalVolume(experimentalHall_box, air, "expHall_log",0,0,0);
  experimentalHall_log = new G4LogicalVolume(experimentalHall_box, vaccum, "expHall_log",0,0,0);

/* A PhysicalVolume is a LogicalVolume put in place. */
  experimentalHall_phys = new G4PVPlacement(0,                // Rotaï¿½ï¿½o
		  	  	  	  	  	  	  	  G4ThreeVector(),		  // Origem
                                      experimentalHall_log,   // Seu volume lï¿½gico
                                      "expHall",			  // Seu nome
                                      0,					  // Seu volume mï¿½e. Neste caso o ponteiro ï¿½ nulo por tratar-se do World Volume
                                      false,				  // Nenhuma operaï¿½ï¿½o booleana
                                      0);					  // Its copy number

// Maybe, these variables must be out in the header file
  const G4int numOfSlabs = 1000;
  G4String detector_box_name[numOfSlabs];
  G4String detector_log_name[numOfSlabs];
  G4String detector_phys_name[numOfSlabs];
  G4double detector_position[numOfSlabs];
  G4Box* detector_box[numOfSlabs];
  G4LogicalVolume* detector_log[numOfSlabs];
  G4VPhysicalVolume* detector_phys[numOfSlabs];

  // For Beryllium
  //G4double slabThickness = 0.05995671*mm; // 0,05995671mm para 1.033 MeV e 0.024242424mm para 0.521 MeV

  // For Molybdenum
  //G4double slabThickness = 0.000546693*cm;  // e- of 0.5 MeV on Mo
  //G4double slabThickness = 0.001309339*cm;  // e- of 1.0 MeV on Mo
  G4double slabThickness = myUtils->getCSDA() * myUtils->getDeltaZ();

/* This creates several slices of beryllium and put each one in the top of the other */
  for (int i = 0; i < numOfSlabs; ++i) {
	  detector_box_name[i]  = "detector_box_"  + static_cast<std::ostringstream*>( &(std::ostringstream() << i) )->str();
	  detector_log_name[i]  = "detector_log_"  + static_cast<std::ostringstream*>( &(std::ostringstream() << i) )->str();
	  detector_phys_name[i] = "detector_phys_" + static_cast<std::ostringstream*>( &(std::ostringstream() << i) )->str();
	  detector_box[i] = new G4Box(detector_box_name[i], 500.0*mm, slabThickness/2.0, 500.0*mm);
	  detector_log[i] = new G4LogicalVolume(detector_box[i], phantomMaterial, detector_log_name[i], 0, 0, 0);

//	  detector_log[i]->SetUserLimits(myUtils->getMyMaxStepLimit());

	  detector_position[i] = - slabThickness/2.0 - i * slabThickness;
	  detector_phys[i] = new G4PVPlacement(0,
			  	  	  	  	  G4ThreeVector(0.0*cm, detector_position[i], 0.0*cm),
			  	  	  	  	  detector_log[i],
			  	  	  	  	  detector_phys_name[i],
			  	  	  	  	  experimentalHall_log,
			  	  	  	  	  false,
			  	  	  	  	  0);
  }


//  G4double maxStep = 0.1*TrackerLength;
//  logicTracker->SetUserLimits(new G4UserLimits(maxStep));

  /* End of Volumes construction */


/*
 * Here I set the Sensitive Detector used to accumulate the energy deposited in one specific slice.
 * There is a bunch of things that must be UNDERSTOOD here.
 */

  // G4SDParticleFilter* gammaFilter = new G4SDParticleFilter("gammaFilter", "gamma");
//  G4VPrimitiveScorer* primitive = new G4PSEnergyDeposit("eDep");


    G4String myDetector[50];
    for (size_t i = 0; i < 50; ++i) {
  	  myDetector[i] = "myDetector" + static_cast<std::ostringstream*>( &(std::ostringstream() << i) )->str();
  	  G4MultiFunctionalDetector* det = new G4MultiFunctionalDetector(myDetector[i]);
  	  	  G4VPrimitiveScorer* primitive = new G4PSEnergyDeposit("eDep");
  	  det->RegisterPrimitive(primitive);
  	  G4SDManager::GetSDMpointer()->AddNewDetector(det);
  	  detector_log[i]->SetSensitiveDetector(det);
    }

//  G4MultiFunctionalDetector* myScorer = new G4MultiFunctionalDetector("myDetector");
//  myScorer->RegisterPrimitive(primitive);
//
//  G4SDManager::GetSDMpointer()->AddNewDetector(myScorer);
//  detector_log[49]->SetSensitiveDetector(myScorer);


//  cube_log->SetSensitiveDetector(myScorer);

  // G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  G4SDManager::GetSDMpointer()->SetVerboseLevel(0);

  return experimentalHall_phys;
}



/* Here it comes some code related to my first attempt to set the SensitiveDetector
 * for dose accumulation. I keep it here as a reminder.
 */

//  pSensitivePart = new MyDetector("/mydet");
//  G4SDManager* SDMan = G4SDManager::GetSDMpointer();
//  SDMan->AddNewDetector(pSensitivePart);
//  cubo_log->SetSensitiveDetector(pSensetivePart);

  //G4MultiFunctionalDetector* myScorer = new G4MultiFunctionalDetector("myCellScorer");

//  G4VPrimitiveSensitivity* totalDose = new G4PSDoseDeposit(ï¿½TotalDoseï¿½);
//  myScorer->Register(totalDose);

//  cubo_log->SetSensitiveDetector(myScorer);

//  MyDetector* myDetector = new MyDetector("myDetector");
//  G4SDManager::GetSDMpointer()->AddNewDetector(myDetector);
//  cubo_log->SetSensitiveDetector(myDetector);


//  G4SDParticleWithEnergyFilter* pkinEFilter = new G4SDParticleWithEnergyFilter("gammaE filter",50.0*keV,55.0*keV);
