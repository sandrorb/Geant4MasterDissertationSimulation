//
// $Id: ExN01DetectorConstruction.hh,v 1.6 2006/06/29 17:47:13 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//

#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;
class MyMaterial;

#include "G4VUserDetectorConstruction.hh"


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

	DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct();

    // by Sandro Boschetti
    G4VPhysicalVolume* getWordVolume();
    G4VPhysicalVolume* getCube();

  private:
    
    // Logical volumes
    //

    MyMaterial* myMaterial;

    G4LogicalVolume* experimentalHall_log;
    G4LogicalVolume* shielding_log;
    G4LogicalVolume* cube_log;
    G4LogicalVolume* detector_log[40];

    // Physical volumes
    //
    G4VPhysicalVolume* experimentalHall_phys;
    G4VPhysicalVolume* shielding_phys;
    G4VPhysicalVolume* cube_phys;
    G4VPhysicalVolume* detector_phys[40];

};

#endif

