#ifndef _GDMLDETECTORCONSTRUCTION_H_

#define _GDMLDETECTORCONSTRUCTION_H_

/**
 * @file
 * @brief Define detector geometry via GDML
*/

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4GlobalMagFieldMessenger;

class GDMLDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    GDMLDetectorConstruction(G4VPhysicalVolume* setWorld = 0);
    virtual ~GDMLDetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();


    // get methods
    //
    const G4VPhysicalVolume* GetMeterPV() const;
    G4LogicalVolume* GetMeterLV() const;

  private:
    G4VPhysicalVolume* World;
    static G4ThreadLocal G4GlobalMagFieldMessenger* fMagFieldMessenger; 

};

// inline functions

inline const G4VPhysicalVolume* GDMLDetectorConstruction::GetMeterPV() const { 
  G4VPhysicalVolume* dose_box_PV = G4PhysicalVolumeStore::GetInstance()->GetVolume("dose_box_PV");
  return dose_box_PV;
}

inline G4LogicalVolume* GDMLDetectorConstruction::GetMeterLV() const { 
  G4LogicalVolume* dose_box_LV = G4LogicalVolumeStore::GetInstance()->GetVolume("dose_box_LV");
  return dose_box_LV; 
}

#endif