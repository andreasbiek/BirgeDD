//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: BirgeDDDetectorConstruction.hh $
// 
/// \file BirgeDDDetectorConstruction.hh
/// \brief Definition of the BirgeDDDetectorConstruction class

#ifndef BirgeDDDetectorConstruction_h
#define BirgeDDDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Cache.hh"
#include "OxCryoMaterials.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class G4VPhysicalVolume;
class OxCryoMaterials;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;
class G4Event;

class BirgeDDDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    BirgeDDDetectorConstruction();
    virtual ~BirgeDDDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    G4Material* FindMaterial(G4String);


    // get methods
    //
    const G4VPhysicalVolume* GetMeterPV() const;
    G4LogicalVolume* GetMeterLV() const;

  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
    G4VPhysicalVolume* ConstructVolumes();
    OxCryoMaterials* materialConstruction;
    G4Material* mate;

    G4String fDetector;
    G4double fOffset;
    
    G4LogicalVolume*   WorldLV;       // pointers
    G4VPhysicalVolume* WorldPV;
    
    G4LogicalVolume* z_wall_LV;
    G4VPhysicalVolume* z_wall_PV_1;
    G4VPhysicalVolume* z_wall_PV_2;
    
    G4LogicalVolume*  x_wall_short_LV;
    G4VPhysicalVolume*  x_wall_short_PV;
    
    G4LogicalVolume* x_wall_long_LV;
    G4VPhysicalVolume* x_wall_long_PV;
    
    G4LogicalVolume* y_wall_left_LV;
    G4VPhysicalVolume* y_wall_left_PV; 
    
    G4LogicalVolume* y_wall_right_LV;
    G4VPhysicalVolume* y_wall_right_PV;
    
    G4LogicalVolume* x_wall_adj_door_LV;
    G4VPhysicalVolume* x_wall_adj_door_PV;
    
    G4LogicalVolume* cupboard_LV;
    G4VPhysicalVolume* cupboard_PV;
    
    G4LogicalVolume* pump_room_LV;
    G4VPhysicalVolume* pump_room_PV;
    
    G4LogicalVolume* platform_pillar_LV;
    G4VPhysicalVolume* platform_pillar_PV;
    
    G4LogicalVolume* platform_LV;
    G4VPhysicalVolume* platform_PV;
    
    G4LogicalVolume* soil_space_LV;
    G4VPhysicalVolume* soil_space_PV;
    
    G4LogicalVolume* dose_box_LV;
    G4VPhysicalVolume* dose_box_PV;
        
/*    G4LogicalVolume*   DetLV;
    G4VPhysicalVolume* DetPV;*/
  
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger

    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

// inline functions

inline const G4VPhysicalVolume* BirgeDDDetectorConstruction::GetMeterPV() const { 
  return dose_box_PV; 
}

inline G4LogicalVolume* BirgeDDDetectorConstruction::GetMeterLV() const { 
  return dose_box_LV; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

