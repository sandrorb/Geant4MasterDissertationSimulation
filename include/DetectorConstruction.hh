//
// $Id: ExN01DetectorConstruction.hh,v 1.6 2006/06/29 17:47:13 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-02 $
//

#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

	DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct();
//    void setDetectorPosition(G4double pos);
    G4double detectorPosition;

  private:
    
    // Logical volumes
    //
    G4LogicalVolume* experimentalHall_log;
    G4LogicalVolume* detector_log;
    G4LogicalVolume* cubo_log;

    // Physical volumes
    //
    G4VPhysicalVolume* experimentalHall_phys;
    G4VPhysicalVolume* detector_phys;
    G4VPhysicalVolume* cubo_phys;

//    G4double detectorPosition;
};

#endif

