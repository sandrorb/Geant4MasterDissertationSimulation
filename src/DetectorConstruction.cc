/**
 * @author  Sandro Boschetti, August 30, 2012
 */

#include "DetectorConstruction.hh"
#include "MyMaterial.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh" // usado para pegar materiais j� cadastrados no Geant4
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

DetectorConstruction::DetectorConstruction()
 :  experimentalHall_log(0), detector_log(0), cubo_log(0),
    experimentalHall_phys(0), detector_phys(0), cubo_phys(0),
    myMaterial(0)
{;}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

	MyMaterial* myMaterial = new MyMaterial;
	G4Material* air = myMaterial->getAir();
	G4Material* lead = myMaterial->getPb();


  /************ Begin of Volumes construction ************/

  // Experimental hall (world volume)
  // Beam line along x axis

  G4double expHall_x = 3.5*m;
  G4double expHall_y = 1.0*m;
  G4double expHall_z = 1.0*m;
  G4Box* experimentalHall_box = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);

  /**
   * A LogicalVolume is some geometry figure, like a G4Box, fulfilled with some material.
   */
  experimentalHall_log = new G4LogicalVolume(experimentalHall_box, air, "expHall_log",0,0,0);

  /**
   * A PhysicalVolume is a LogicalVolume put in place.
   */
  experimentalHall_phys = new G4PVPlacement(0,                // Rota��o
		  	  	  	  	  	  	  	  G4ThreeVector(),		  // Origem
                                      experimentalHall_log,   // Seu volume l�gico
                                      "expHall",			  // Seu nome
                                      0,					  // Seu volume m�e. Neste caso o ponteiro � nulo por tratar-se do World Volume
                                      false,				  // Nenhuma opera��o booleana
                                      0);					  // Its copy number


  // Thin Pb layer used for a previous experiment
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



  // Small cube of lead used as a detector for my inverse-square law
  G4Box* cubo_box = new G4Box("cubo_box", 1.0*cm, 1.0*cm, 1.0*cm);
  cubo_log = new G4LogicalVolume(cubo_box, lead, "cubo_log", 0, 0, 0);
  cubo_log->SetVisAttributes(G4Colour(1.0, 0.0, 0.0));
  cubo_phys = new G4PVPlacement(0,
             	 	 	G4ThreeVector( 3.0*m, 0.0*m, 0.0*m),
             	 	 	cubo_log,
             	 	 	"cubo",
             	 	 	experimentalHall_log,  // Volume m�e.
             	 	 	false,
             	 	 	0);

  /* End of Volumes construction */


/**
 * Here I set the Sensitive Detector used to accumulate radiation dose.
 * There is a bunch of things that must be UNDERSTOOD here.
 */

  // G4SDParticleFilter* gammaFilter = new G4SDParticleFilter("gammaFilter", "gamma");
  G4VPrimitiveScorer* primitive = new G4PSEnergyDeposit("eDep");

  G4MultiFunctionalDetector* myScorer = new G4MultiFunctionalDetector("mySrBDetector");
  myScorer->RegisterPrimitive(primitive);

  G4SDManager::GetSDMpointer()->AddNewDetector(myScorer);
  cubo_log->SetSensitiveDetector(myScorer);

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

