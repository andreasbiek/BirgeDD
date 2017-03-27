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
// $Id: BirgeDDDetectorConstruction.cc $
// 
/// \file BirgeDDDetectorConstruction.cc
/// \brief Implementation of the BirgeDDDetectorConstruction class

#include "BirgeDDDetectorConstruction.hh"
#include "OxCryoMaterials.hh"

#include "G4tgbVolumeMgr.hh"

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4ExtrudedSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4VisExtent.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* BirgeDDDetectorConstruction::fMagFieldMessenger = 0; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BirgeDDDetectorConstruction::BirgeDDDetectorConstruction()
 : G4VUserDetectorConstruction(),
   dose_box_PV(0),
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BirgeDDDetectorConstruction::~BirgeDDDetectorConstruction()
{ 
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* BirgeDDDetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BirgeDDDetectorConstruction::DefineMaterials()
{ 
  OxCryoMaterials* nistManager = OxCryoMaterials::GetInstance();

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* BirgeDDDetectorConstruction::DefineVolumes()
{ 
    G4VisAttributes* yellowTVA = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.5));
    G4VisAttributes* redTVA = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.5));
    G4VisAttributes* greenTVA = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.5));
    G4VisAttributes* greyTVA = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.25));
    G4VisAttributes* blueTVA = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.5));
    
    static const G4double inch = 2.54*cm;
       
    // Clean old geometry, if any
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();
    
    G4NistManager* mat_man = G4NistManager::Instance(); //material mananger
    
    //inner dimensions of the room
    G4double room_inner_x = 284.*inch; //measured value
    G4double room_inner_y = 261.*inch; //measured value
    G4double room_inner_z = 148.*inch; //measured value
    
    //wall thickness of the room
    G4double room_z_wall_thickness = 10.5*inch; //thickness of the slab of the floor on the top of the room, provided by building service. The same thickness is assumed for the bottom
    G4double room_x_left_wall_thickness = 10.5*inch; //thickness of the wall facing the soil. Estimated value
    G4double room_x_right_wall_thickness = 6.*inch; //thickness of the wall to Room 257 (preparation room), provided by buidling service
    G4double room_y_back_wall_thickness = 10.5*inch; //thickness of the wall facing the soil. Estimtate value
    G4double room_y_front_wall_thickness = 5.*inch; //thickness of the wall to Room 245 (xenon room), provided by buidling service
    
    G4double spare_distance = 40*inch; //to account for the effect of the soil outside the building, and evaluate the radiation dose in the lab adjacent

    //Definition of world volume
    G4double world_x = room_inner_x + room_x_left_wall_thickness + room_x_right_wall_thickness + 2 * spare_distance;
    G4double world_y = room_inner_y + room_y_back_wall_thickness + room_y_front_wall_thickness + 2 * spare_distance;
    G4double world_z = room_inner_z + 2 * room_z_wall_thickness + 2* spare_distance;

    G4String filename = "test/cube_placement.txt";
    G4tgbVolumeMgr* volmgr = G4tgbVolumeMgr::GetInstance();
    volmgr->AddTextFile(filename);
    WorldPV = volmgr->ReadAndConstructDetector();
    WorldLV = WorldPV->GetLogicalVolume();
    
    G4Box* world_box = new G4Box("world_box", world_x/2., world_y/2., world_z/2.);
/*    G4Material* Air = mat_man -> FindOrBuildMaterial("G4_AIR");
    WorldLV = new G4LogicalVolume(world_box, Air, "WorldLV");
    WorldPV = new G4PVPlacement(0, G4ThreeVector(0,0,0), WorldLV, "WorldPV", 0, false, 0);
    WorldLV->SetVisAttributes(G4VisAttributes::Invisible);*/
  
    //Definition of all the walls of the room
    
    //Top and bottom floor
    G4Material* Concrete = mat_man->FindOrBuildMaterial("G4_CONCRETE");
    G4double room_z_wall_box_x = room_inner_x + room_x_left_wall_thickness  + room_x_right_wall_thickness +  spare_distance;
    G4double room_z_wall_box_y = room_inner_y + room_y_back_wall_thickness + room_y_front_wall_thickness + spare_distance;
    G4double room_z_wall_box_z = room_z_wall_thickness;
    G4Box* room_z_wall_box = new G4Box("z_wall", room_z_wall_box_x/2., room_z_wall_box_y/2., room_z_wall_box_z/2.);
    z_wall_LV = new G4LogicalVolume(room_z_wall_box, Concrete, "z_wall_LV");
    G4double z_wall_x_pos = spare_distance / 2.0;
    G4double z_wall_y_pos = -spare_distance / 2.0;
    G4double z_wall_z_pos_1 = room_inner_z / 2.0;
    G4double z_wall_z_pos_2 = -room_inner_z / 2.0;

    z_wall_PV_1 = new G4PVPlacement(0, G4ThreeVector(z_wall_x_pos, z_wall_y_pos, z_wall_z_pos_1), z_wall_LV, "z_wall_PV_1", WorldLV, true, 0, fCheckOverlaps);    
    z_wall_PV_2 = new G4PVPlacement(0, G4ThreeVector(z_wall_x_pos, z_wall_y_pos, z_wall_z_pos_2), z_wall_LV, "z_wall_PV_2", WorldLV, true, 1, fCheckOverlaps);
    z_wall_LV->SetVisAttributes(yellowTVA);
    
    //walls along x direction
    G4double room_inner_x_short = 230.*inch;
    G4double room_x_wall_short_length = room_inner_x_short + room_x_left_wall_thickness + room_x_right_wall_thickness;
    G4Box* room_x_wall_short_box = new G4Box("x_wall_short", room_x_wall_short_length/2, room_y_back_wall_thickness/2, (room_inner_z-room_z_wall_thickness)/2);
    x_wall_short_LV = new G4LogicalVolume(room_x_wall_short_box, Concrete, "x_wall_short_LV");
    G4double x_wall_short_x_pos = (room_inner_x_short - room_inner_x) / 2.0;
    G4double x_wall_short_y_pos = (room_inner_y + room_y_front_wall_thickness) / 2.0;
    G4double x_wall_short_z_pos = 0;
    x_wall_short_PV = new G4PVPlacement(0, G4ThreeVector(x_wall_short_x_pos, x_wall_short_y_pos, x_wall_short_z_pos), x_wall_short_LV, "x_wall_short_PV", WorldLV, false, 0, fCheckOverlaps);
    x_wall_short_LV->SetVisAttributes(yellowTVA);
    
    G4double room_x_wall_long_length = room_inner_x + room_x_left_wall_thickness + room_x_right_wall_thickness;
    G4Box* room_x_wall_long_box = new G4Box("x_wall_long", room_x_wall_long_length/2, room_y_front_wall_thickness/2, (room_inner_z-room_z_wall_thickness)/2);
    x_wall_long_LV = new G4LogicalVolume(room_x_wall_long_box, Concrete, "x_wall_long_LV");
    G4double x_wall_long_x_pos = 0;
    G4double x_wall_long_y_pos = -(room_inner_y + room_y_back_wall_thickness) / 2.0;
    G4double x_wall_long_z_pos = 0;
    x_wall_long_PV = new G4PVPlacement(0, G4ThreeVector(x_wall_long_x_pos, x_wall_long_y_pos, x_wall_long_z_pos), x_wall_long_LV, "x_wall_long_PV", WorldLV, false, 0, fCheckOverlaps);
    x_wall_long_LV->SetVisAttributes(yellowTVA);
    
    //walls along y direction
    G4Box* room_y_wall_left_box = new G4Box("y_wall_left", room_x_left_wall_thickness/2, room_inner_y/2, (room_inner_z-room_z_wall_thickness)/2);
    y_wall_left_LV = new G4LogicalVolume(room_y_wall_left_box, Concrete, "y_wall_left_LV");
    G4double y_wall_left_x_pos = -(room_inner_x + room_x_right_wall_thickness) / 2.0;
    G4double y_wall_left_y_pos = (room_y_front_wall_thickness- room_y_back_wall_thickness)/2;
    G4double y_wall_left_z_pos = 0;
    y_wall_left_PV = new G4PVPlacement(0, G4ThreeVector(y_wall_left_x_pos, y_wall_left_y_pos, y_wall_left_z_pos), y_wall_left_LV, "y_wall_left_PV", WorldLV, false, 0, fCheckOverlaps);
    y_wall_left_LV->SetVisAttributes(yellowTVA);
    
    G4double room_inner_y_short = 189.*inch;
    G4Box* room_y_wall_right_box = new G4Box("y_wall_right", room_x_right_wall_thickness/2, room_inner_y_short/2, (room_inner_z-room_z_wall_thickness)/2);
    y_wall_right_LV = new G4LogicalVolume(room_y_wall_right_box, Concrete, "y_wall_right_LV");
    G4double y_wall_right_x_pos = room_inner_x_short + (room_x_left_wall_thickness - room_inner_x) / 2.0;
    G4double y_wall_right_y_pos = (room_y_front_wall_thickness - room_y_back_wall_thickness + room_inner_y - room_inner_y_short) / 2;
    G4double y_wall_right_z_pos = 0;
    y_wall_right_PV = new G4PVPlacement(0, G4ThreeVector(y_wall_right_x_pos, y_wall_right_y_pos, y_wall_right_z_pos), y_wall_right_LV, "y_wall_right_PV", WorldLV, false, 0, fCheckOverlaps);
    y_wall_right_LV->SetVisAttributes(yellowTVA);
    
    G4double room_x_wall_adj_door_length = 54.*inch - room_x_right_wall_thickness;
    G4Box* room_x_wall_adj_door_box = new G4Box("x_wall_adj_door", room_x_wall_adj_door_length/2, room_x_right_wall_thickness/2, (room_inner_z-room_z_wall_thickness)/2);
    x_wall_adj_door_LV = new G4LogicalVolume(room_x_wall_adj_door_box, Concrete, "x_wall_adj_door_LV");
    G4double x_wall_adj_door_x_pos = room_inner_x_short + (room_x_left_wall_thickness -room_inner_x + room_x_right_wall_thickness + room_x_wall_adj_door_length)/2;
    G4double x_wall_adj_door_y_pos = (room_y_front_wall_thickness + room_inner_y + room_x_right_wall_thickness - room_y_back_wall_thickness)/2 - room_inner_y_short;
    G4double x_wall_adj_door_z_pos = 0;
    x_wall_adj_door_PV = new G4PVPlacement(0, G4ThreeVector(x_wall_adj_door_x_pos, x_wall_adj_door_y_pos, x_wall_adj_door_z_pos), x_wall_adj_door_LV, "x_wall_adj_door_PV", WorldLV, false, 0, fCheckOverlaps);
    x_wall_adj_door_LV->SetVisAttributes(yellowTVA);
    
    mate = G4Material::GetMaterial("wood");
    G4double cupboard_x = 27.0*inch;
    G4double cupboard_y = 59.5*inch;
    G4double cupboard_z = 36.0*inch;
    G4double cupboard_thi = 1.*inch;
    G4Box* cupboard_OV = new G4Box("cupboard_OV", cupboard_x/2, cupboard_y/2, cupboard_z/2);
    G4Box* cupboard_IV = new G4Box("cupboard_IV", (cupboard_x-2* cupboard_thi)/2, (cupboard_y-2* cupboard_thi)/2, (cupboard_z-2* cupboard_thi)/2);
    G4SubtractionSolid* cupboard = new G4SubtractionSolid("cupboard", cupboard_OV, cupboard_IV, 0, G4ThreeVector(0,0,0));
    cupboard_LV = new G4LogicalVolume(cupboard, mate, "cupboard_LV");
    G4double cupboard_x_pos = room_inner_x_short + (room_x_left_wall_thickness - room_inner_x - room_x_right_wall_thickness - cupboard_x) / 2;
    G4double cupboard_y_pos = (room_y_front_wall_thickness + room_inner_y - room_y_back_wall_thickness - cupboard_y) / 2;
    G4double cupboard_z_pos = (cupboard_z + room_z_wall_thickness - room_inner_z) / 2;
    cupboard_PV = new G4PVPlacement(0, G4ThreeVector(cupboard_x_pos, cupboard_y_pos, cupboard_z_pos), cupboard_LV, "cupboard_PV", WorldLV, false, 0, fCheckOverlaps);
    cupboard_LV->SetVisAttributes(redTVA);
    
    //The pump cabinet (room). Modelled as wooden box
    G4double pump_room_x = 51.5*inch;
    G4double pump_room_y = 102*inch;
    G4double pump_room_z = (room_inner_z-room_z_wall_thickness);
    G4double pump_room_thi = 2.*inch;
    G4Box* pump_room_OV = new G4Box("pump_room_OV", pump_room_x/2, pump_room_y/2, pump_room_z/2);
    G4Box* pump_room_IV = new G4Box("pump_room_IV", (pump_room_x-2* pump_room_thi)/2, (pump_room_y-2* pump_room_thi)/2, pump_room_z/2);
    G4SubtractionSolid* pump_room = new G4SubtractionSolid("pump_room", pump_room_OV, pump_room_IV, 0, G4ThreeVector(0,0,0));
    pump_room_LV = new G4LogicalVolume(pump_room, mate,"pump_room_LV");
    G4double pump_room_x_pos = (room_x_left_wall_thickness + pump_room_x - room_inner_x - room_x_right_wall_thickness) / 2;
    G4double pump_room_y_pos = (room_y_front_wall_thickness + pump_room_y - room_inner_y - room_y_back_wall_thickness) / 2;
    G4double pump_room_z_pos = 0;
    pump_room_PV = new G4PVPlacement(0, G4ThreeVector(pump_room_x_pos, pump_room_y_pos, pump_room_z_pos), pump_room_LV, "pump_room_PV", WorldLV, false, 0, fCheckOverlaps);
    pump_room_LV->SetVisAttributes(redTVA);
    
    //Platform pillar
    mate = G4Material::GetMaterial("Al6061");
    G4double pillar_radius = 5.0*inch;
    G4double pillar_height = 81.0*inch;
    G4Tubs* platform_pillar = new G4Tubs("platform_pillar", 0, pillar_radius, pillar_height/2, 0, 360*degree);
    platform_pillar_LV = new G4LogicalVolume(platform_pillar, mate, "platform_pillar_LV ");
    G4double platform_pillar_x_pos = 81.*inch + (room_x_left_wall_thickness - room_inner_x - room_x_right_wall_thickness) / 2;
    G4double platform_pillar_y_pos = (room_y_front_wall_thickness + room_inner_y - room_y_back_wall_thickness) / 2 - (9.*inch + 49.5*inch);
    G4double platform_pillar_z_pos = (pillar_height + room_z_wall_thickness - room_inner_z) /2;
    platform_pillar_PV =  new G4PVPlacement(0, G4ThreeVector(platform_pillar_x_pos, platform_pillar_y_pos, platform_pillar_z_pos), platform_pillar_LV, "platform_pillar_PV", WorldLV, false, 0, fCheckOverlaps);
    platform_pillar_LV->SetVisAttributes(greenTVA);
    
    //Platform
    std::vector<G4TwoVector> points;
    G4double platform_thi = 7.*inch;
    points.push_back(G4TwoVector(0.0, 0.0));
    points.push_back(G4TwoVector(-81*inch, 49.5*inch));
    points.push_back(G4TwoVector(-81*inch, -49.5*inch));
    G4ExtrudedSolid* platform_tri_pri = new G4ExtrudedSolid("platform_tri_pri", points, platform_thi, G4TwoVector(0,0), 1.0, G4TwoVector(0,0), 1.0);
    G4double hole_radius = 12.5*inch;
    G4Tubs* platform_hole = new G4Tubs("platform_hole", 0, hole_radius, platform_thi/2, 0, 360*degree);
    G4SubtractionSolid* platform = new G4SubtractionSolid("platform", platform_tri_pri, platform_hole, 0, G4ThreeVector(-53.*inch,0,0));
    platform_LV = new G4LogicalVolume(platform, mate, "platform_LV ");
    G4double platform_z_pos = pillar_height + platform_thi + room_z_wall_thickness/2 - room_inner_z /2;
    platform_PV =  new G4PVPlacement(0, G4ThreeVector(platform_pillar_x_pos, platform_pillar_y_pos, platform_z_pos), platform_LV, "platform_PV", WorldLV, false, 0, fCheckOverlaps);
    platform_LV->SetVisAttributes(greenTVA);
    
    mate = G4Material::GetMaterial("Soil");
    G4double building_space_x = room_x_left_wall_thickness + room_inner_x + room_x_right_wall_thickness + spare_distance;
    G4double building_space_y = spare_distance + room_y_front_wall_thickness + room_inner_y + room_y_back_wall_thickness;
    G4double building_space_z = room_z_wall_thickness + room_inner_z + room_z_wall_thickness + spare_distance;
    G4Box* building_space = new G4Box("building_space", building_space_x/2, building_space_y/2, building_space_z/2) ; 
    G4SubtractionSolid* soil_space = new G4SubtractionSolid ("soil_space", world_box, building_space, 0, G4ThreeVector((spare_distance/2),-(spare_distance/2),(spare_distance/2)));
    soil_space_LV = new G4LogicalVolume(soil_space, mate, "soil_space_LV");
    soil_space_PV = new G4PVPlacement(0, G4ThreeVector(0,0,0), soil_space_LV, "soil_space_PV", WorldLV, false, 0, fCheckOverlaps);
    soil_space_LV->SetVisAttributes(greyTVA);

    //You can treat the neutron source as a point source. I just want to see its position
/*    G4double dose_box_xyz = 250.*mm;
    G4Box* dose_box = new G4Box("dose_box", dose_box_xyz/2, dose_box_xyz/2, dose_box_xyz/2);
    G4Material* water = mat_man -> FindOrBuildMaterial("G4_WATER");
    dose_box_LV = new G4LogicalVolume(dose_box, water, "dose_box_LV");
    G4double dose_box_x_pos = 200*inch + (room_x_left_wall_thickness - room_inner_x - room_x_right_wall_thickness) / 2; 
    G4double dose_box_y_pos = (room_y_front_wall_thickness + room_inner_y - room_y_back_wall_thickness) / 2 - 240*inch;
    G4double dose_box_z_pos = 60*inch - room_inner_z/2;
    dose_box_PV = new G4PVPlacement(0, G4ThreeVector(dose_box_x_pos,dose_box_y_pos,dose_box_z_pos), dose_box_LV, "dose_box_PV", WorldLV, false, 0);
    dose_box_LV->SetVisAttributes(blueTVA);*/

    dose_box_LV = G4tgbVolumeMgr::GetInstance()->FindG4LogVol("dose_box", 1);
    dose_box_PV = G4tgbVolumeMgr::GetInstance()->FindG4PhysVol("dose_box", 1);

    return WorldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BirgeDDDetectorConstruction::ConstructSDandField()
{
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue = G4ThreeVector();
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
