/**
 * @author  Sandro Boschetti, August 30, 2012
 *
 */

#include "DetectorConstruction.hh"
#include "MyMaterial.hh"

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

/**
 * This is the constructor class member used to construct the "DetectorConstruction" object.
 * Some DetectorConstruction class variable are initialized.
 * In this case, "{;}", no implementation has been set.
 */
DetectorConstruction::DetectorConstruction()
 :  myMaterial(0), experimentalHall_log(0), shielding_log(0), cube_log(0),
    experimentalHall_phys(0), shielding_phys(0), cube_phys(0)
{ }

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

	MyMaterial* myMaterial = new MyMaterial;
	G4Material* air = myMaterial->getAir();  // Used to fill the World Volume
//	G4Material* lead = myMaterial->getPb();
	G4Material* water = myMaterial->getWater();
	G4Material* beryllium = new G4Material("Beryllium", 4.0, 9.012182*g/mole, 1.8480*g/cm3);

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
  experimentalHall_phys = new G4PVPlacement(0,                // Rota��o
		  	  	  	  	  	  	  	  G4ThreeVector(),		  // Origem
                                      experimentalHall_log,   // Seu volume l�gico
                                      "expHall",			  // Seu nome
                                      0,					  // Seu volume m�e. Neste caso o ponteiro � nulo por tratar-se do World Volume
                                      false,				  // Nenhuma opera��o booleana
                                      0);					  // Its copy number

// Maybe, these variables must be out in the header file
  const G4int numOfSlabs = 100;
  G4String detector_box_name[numOfSlabs];
  G4String detector_log_name[numOfSlabs];
  G4String detector_phys_name[numOfSlabs];
  G4double detector_position[numOfSlabs];
  G4Box* detector_box[numOfSlabs];
  G4LogicalVolume* detector_log[numOfSlabs];
  G4VPhysicalVolume* detector_phys[numOfSlabs];

  G4double slabThickness = 0.024242424*mm;
//  G4double slabThickness = 0.03*mm;

/* This creates several slices of beryllium and put each one in the top of the other */
  for (int i = 0; i < numOfSlabs; ++i) {
	  detector_box_name[i]  = "detector_box_"  + static_cast<std::ostringstream*>( &(std::ostringstream() << i) )->str();
	  detector_log_name[i]  = "detector_log_"  + static_cast<std::ostringstream*>( &(std::ostringstream() << i) )->str();
	  detector_phys_name[i] = "detector_phys_" + static_cast<std::ostringstream*>( &(std::ostringstream() << i) )->str();
	  detector_box[i] = new G4Box(detector_box_name[i], 500.0*mm, slabThickness/2.0, 500.0*mm);
//	  detector_box[i] = new G4Box(detector_box_name[i], 500.0*mm, 0.5*mm, 500.0*mm);
	  detector_log[i] = new G4LogicalVolume(detector_box[i], beryllium, detector_log_name[i], 0, 0, 0);
//	  detector_position[i] = - (slabThickness/2.0) - (i * slabThickness);
	  detector_position[i] = - i * slabThickness;
//	  detector_position[i] = - 0.5*mm - i * 1.0*mm;
	  detector_phys[i] = new G4PVPlacement(0,
			  	  	  	  	  G4ThreeVector(0.0*cm, detector_position[i], 0.0*cm),
			  	  	  	  	  detector_log[i],
			  	  	  	  	  detector_phys_name[i],
			  	  	  	  	  experimentalHall_log,
			  	  	  	  	  false,
			  	  	  	  	  0);
  }


  /* End of Volumes construction */


/*
 * Here I set the Sensitive Detector used to accumulate the energy deposited in one specific slice.
 * There is a bunch of things that must be UNDERSTOOD here.
 */

  // G4SDParticleFilter* gammaFilter = new G4SDParticleFilter("gammaFilter", "gamma");
  G4VPrimitiveScorer* primitive = new G4PSEnergyDeposit("eDep");

  G4MultiFunctionalDetector* myScorer = new G4MultiFunctionalDetector("myDetector");
  myScorer->RegisterPrimitive(primitive);

  G4SDManager::GetSDMpointer()->AddNewDetector(myScorer);
  detector_log[49]->SetSensitiveDetector(myScorer);
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

//  G4VPrimitiveSensitivity* totalDose = new G4PSDoseDeposit(�TotalDose�);
//  myScorer->Register(totalDose);

//  cubo_log->SetSensitiveDetector(myScorer);

//  MyDetector* myDetector = new MyDetector("myDetector");
//  G4SDManager::GetSDMpointer()->AddNewDetector(myDetector);
//  cubo_log->SetSensitiveDetector(myDetector);


//  G4SDParticleWithEnergyFilter* pkinEFilter = new G4SDParticleWithEnergyFilter("gammaE filter",50.0*keV,55.0*keV); 
//  pkinEFilter->add("gamma");
//  pkinEFilter->show();




/* Thin Pb layer used for a previous experiment */
/*
  G4double block_x = 0.1*mm;
  G4double block_y = 50.0*cm;
  G4double block_z = 50.0*cm;
  // Isso � o que se chama de s�lido. Cada s�lido pode necessitar de um
  // conjunto espec�fico de dados para a sua cria��o
  G4Box* detectorBlock_box = new G4Box("detectorBlock_box", block_x, block_y, block_z);

  // Volume l�gico
  // Ainda tenho que entender os �ltimos tr�s argumentos
  detector_log = new G4LogicalVolume(detectorBlock_box, lead, "detector_log", 0, 0, 0);

  //detector_log->SetVisAttributes(G4VisAttributes::Invisible);
  detector_log->SetVisAttributes(G4Colour(1.0, 0.0, 0.0));

  G4double blockPos_x = 1.0*m;
  G4double blockPos_y = 0.0*m;
  G4double blockPos_z = 0.0*m;
  detector_phys = new G4PVPlacement(0,
             	 	 	G4ThreeVector(blockPos_x,blockPos_y,blockPos_z),
             	 	 	detector_log,
             	 	 	"detectorBlock",
             	 	 	experimentalHall_log,  // Volume m�e.
             	 	 	false,
             	 	 	0);
*/

/* Small cube of lead used as a detector for my inverse-square law */
//  G4Box* cube_box = new G4Box("cube_box", 20.0*cm, 20.0*cm, 20.0*cm);
//  cube_log = new G4LogicalVolume(cube_box, water, "cube_log", 0, 0, 0);
//  cube_log->SetVisAttributes(G4Colour(1.0, 0.0, 0.0));
//  cube_phys = new G4PVPlacement(0,
//             	 	 	G4ThreeVector( 0.0*m, 0.0*m, 0.0*m),
//             	 	 	cube_log,
//             	 	 	"cube",
//             	 	 	experimentalHall_log,  // Volume m�e.
//             	 	 	false,
//             	 	 	0);

