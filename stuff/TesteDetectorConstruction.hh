//
// $Id: ExN01DetectorConstruction.hh,v 1.6 2006/06/29 17:47:13 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//

#ifndef TesteDetectorConstruction_H
#define TesteDetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

class TesteDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

	TesteDetectorConstruction();
    ~TesteDetectorConstruction();

    G4VPhysicalVolume* Construct();

  private:
    
    // Logical volumes
    //
    G4LogicalVolume* experimentalHall_log;
    G4LogicalVolume* tracker_log;
    G4LogicalVolume* calorimeterBlock_log;
    G4LogicalVolume* calorimeterLayer_log;

    // Physical volumes
    //
    G4VPhysicalVolume* experimentalHall_phys;
    G4VPhysicalVolume* calorimeterLayer_phys;
    G4VPhysicalVolume* calorimeterBlock_phys;
    G4VPhysicalVolume* tracker_phys;
};

#endif

