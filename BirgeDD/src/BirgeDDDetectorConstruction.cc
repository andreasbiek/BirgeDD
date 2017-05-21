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

#include "G4PhysicalConstants.hh"
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

    G4double a;  // mass of a mole;
    G4double z;  // z=mean number of protons;
    G4double density, fractionMass;
    G4String symbol, name;
    G4int nComponents, nAtoms;
    G4double temp;

    G4Element* elH  = new G4Element(name = "Hydrogen"   , symbol = "H"  , z = 1.  , a =  1.008*g/mole);
    G4Element* elC  = new G4Element(name = "Carbon"     , symbol = "C"  , z = 6.  , a = 12.011*g/mole);
    G4Element* elN  = new G4Element(name = "Nitrogen"   , symbol = "N"  , z = 7.  , a = 14.007*g/mole);
    G4Element* elO  = new G4Element(name = "Oxygen"     , symbol = "O"  , z = 8.  , a = 15.999*g/mole);
    G4Element* elSi = new G4Element(name = "Silicon"    , symbol = "Si" , z = 14. , a = 28.086*g/mole);
    G4Element* elP  = new G4Element(name = "Phosphorus" , symbol = "P"  , z = 15. , a = 30.974*g/mole);
    G4Element* elS  = new G4Element(name = "Sulfur"     , symbol = "S"  , z = 16. , a = 32.065*g/mole);
    G4Element* elCr = new G4Element(name = "Chromium"   , symbol = "Cr" , z = 24. , a = 51.996*g/mole);
    G4Element* elMn = new G4Element(name = "Manganese"  , symbol = "Mn" , z = 25. , a = 54.938*g/mole);
    G4Element* elFe = new G4Element(name = "Iron"       , symbol = "Fe" , z = 26. , a = 55.845*g/mole);
    G4Element* elNi = new G4Element(name = "Nickel"     , symbol = "Ni" , z = 28. , a = 58.693*g/mole);
    G4Element* elMo = new G4Element(name = "Molybdenum" , symbol = "Mo" , z = 42. , a = 95.94 *g/mole);

    // Liquid helium material
    // Density from (assuming 3K LHe)
    // https://www.bnl.gov/magnets/staff/gupta/cryogenic-data-handbook/Section2.pdf

    new G4Material("liquid_helium", z=2., a= 4.00*g/mole, density= 0.141*g/cm3, kStateLiquid, temp=3.*kelvin);
    new G4Material("liquid_nitrogen", z=7., a= 14.00*g/mole, density= 0.807*g/cm3, kStateLiquid, temp=77.*kelvin);

    // Vacuum
    G4Material* Galactic  = new G4Material("galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

    //Stainless Steel Type 304
    G4Material* ss_t316 = new G4Material(name = "ss_t316" , density = 8.03*g/cm3 , nComponents = 10);
    ss_t316 -> AddElement(elC  , fractionMass =   0.08*perCent);
    ss_t316 -> AddElement(elMn , fractionMass =   2.00*perCent);
    ss_t316 -> AddElement(elP  , fractionMass =  0.045*perCent);
    ss_t316 -> AddElement(elS  , fractionMass =  0.030*perCent);
    ss_t316 -> AddElement(elSi , fractionMass =   0.75*perCent);
    ss_t316 -> AddElement(elCr , fractionMass =  17.00*perCent);
    ss_t316 -> AddElement(elNi , fractionMass =  12.00*perCent);
    ss_t316 -> AddElement(elMo , fractionMass =   2.50*perCent);
    ss_t316 -> AddElement(elN  , fractionMass =   0.10*perCent);
    ss_t316 -> AddElement(elFe , fractionMass = 65.495*perCent);

    new G4Material(name = "Cu",z = 29., a =  63.546*g/mole, density = 8.96*g/cm3);

    new G4Material(name = "Al",z = 13., a =  26.981538*g/mole, density = 2.70*g/cm3);

    //Naphthalene
    G4Material* Generic_Organic_Scintillator = new G4Material(name = "generic_organic_scintillator" , density = 1.0253*g/cm3 , nComponents = 2);
    Generic_Organic_Scintillator -> AddElement(elH , nAtoms = 8);
    Generic_Organic_Scintillator -> AddElement(elC  , nAtoms = 10);

    G4Material* Synthetic_Silica = new G4Material(name = "synthetic_silica" , density = 2.65*g/cm3 , nComponents = 2);
    Synthetic_Silica -> AddElement(elSi , nAtoms = 1);
    Synthetic_Silica -> AddElement(elO  , nAtoms = 2);

    G4Material* Generic_Acrylic = new G4Material(name = "generic_acrylic", 1.18*g/cm3, nComponents = 3);
    Generic_Acrylic -> AddElement(elH , nAtoms=8);
    Generic_Acrylic -> AddElement(elC , nAtoms=5);
    Generic_Acrylic -> AddElement(elO , nAtoms=2);

    G4Material* Generic_PMT = new G4Material(name = "generic_pmt", 0.1*g/cm3, nComponents = 2);
    Generic_PMT -> AddMaterial(Galactic , fractionMass=80.0*perCent);
    Generic_PMT -> AddMaterial(ss_t316 , fractionMass=20.0*perCent);

    // Print materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* BirgeDDDetectorConstruction::DefineVolumes()
{

    //===============  Materials ===============//

    G4NistManager* mat_man = G4NistManager::Instance(); //material mananger

    // Room

    G4Material* world_material = mat_man -> FindOrBuildMaterial("G4_AIR");
    G4Material* z_wall_material = mat_man -> FindOrBuildMaterial("G4_CONCRETE");
    G4Material* x_wall_short_material = mat_man -> FindOrBuildMaterial("G4_CONCRETE");
    G4Material* x_wall_long_material = mat_man -> FindOrBuildMaterial("G4_CONCRETE");
    G4Material* y_wall_left_material = mat_man -> FindOrBuildMaterial("G4_CONCRETE");
    G4Material* y_wall_right_material = mat_man -> FindOrBuildMaterial("G4_CONCRETE");
    G4Material* x_wall_adj_door_material = mat_man -> FindOrBuildMaterial("G4_CONCRETE");
    G4Material* cupboard_material = G4Material::GetMaterial("wood");
    G4Material* pump_room_material = G4Material::GetMaterial("wood");
    G4Material* platform_pillar_material = G4Material::GetMaterial("Al6061");
    G4Material* platform_material = G4Material::GetMaterial("Al6061");
    G4Material* soil_space_material = G4Material::GetMaterial("Soil");
    G4Material* dose_box_material = mat_man -> FindOrBuildMaterial("G4_WATER");

    // Cryostat

    G4Material* default_material = G4Material::GetMaterial("galactic");
    G4Material* liquid_helium_material = G4Material::GetMaterial("liquid_helium");
    
    G4Material* can_sample_outer_material = G4Material::GetMaterial("ss_t316");
    G4Material* can_4k_outer_material = G4Material::GetMaterial("Cu");
    G4Material* can_77k_outer_material = G4Material::GetMaterial("Cu");
    G4Material* can_vacuum_outer_material = G4Material::GetMaterial("ss_t316");
    G4Material* arm_vacuum_material = G4Material::GetMaterial("ss_t316");
    G4Material* arm_77k_material = G4Material::GetMaterial("Al");
    G4Material* arm_4k_material = G4Material::GetMaterial("Al");
    G4Material* cryo_vacuum_outer_material = G4Material::GetMaterial("ss_t316");
    G4Material* cryo_77k_outer_material = G4Material::GetMaterial("ss_t316");
    G4Material* cryo_nitrogen_material = G4Material::GetMaterial("liquid_nitrogen");
    G4Material* cryo_4k_outer_material = G4Material::GetMaterial("ss_t316");
    
    G4Material* can_sample_inner_material = G4Material::GetMaterial("liquid_helium");
    G4Material* can_4k_inner_material = G4Material::GetMaterial("galactic");
    G4Material* can_77k_inner_material = G4Material::GetMaterial("galactic");
    G4Material* can_vacuum_inner_material = G4Material::GetMaterial("galactic");
    G4Material* cryo_vacuum_inner_material = G4Material::GetMaterial("galactic");
    G4Material* cryo_77k_inner_material = G4Material::GetMaterial("galactic");
    G4Material* cryo_4k_inner_material = G4Material::GetMaterial("liquid_helium");

    // T-slot frame

    G4Material* tslot_material = G4Material::GetMaterial("Al6061");
    
    if ( ! default_material || ! liquid_helium_material ) {
        G4ExceptionDescription msg;
        msg << "Cannot retrieve materials already defined.";
        G4Exception("LHeSDetectorConstruction::DefineVolumes()",
            "MyCode0001", FatalException, msg);
    }
    
    static const G4double inch = 2.54*cm;
       
    // Clean old geometry, if any
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();
 
    //===============  Dimensions ===============//

    //wall thickness of the room
    G4double room_z_wall_thickness = 10.5*inch; //thickness of the slab of the floor on the top of the room, provided by building service. The same thickness is assumed for the bottom
    G4double room_x_left_wall_thickness = 10.5*inch; //thickness of the wall facing the soil. Estimated value
    G4double room_x_right_wall_thickness = 6.*inch; //thickness of the wall to Room 257 (preparation room), provided by building service
    G4double room_y_back_wall_thickness = 10.5*inch; //thickness of the wall facing the soil. Estimated value
    G4double room_y_front_wall_thickness = 5.*inch; //thickness of the wall to Room 245 (xenon room), provided by building service
        
    //inner dimensions of the room
    G4double room_inner_x = 284.*inch; //measured value
    G4double room_inner_y = 261.*inch; //measured value
    G4double room_inner_z = 148.*inch; //measured value
    G4double room_inner_x_short = 230.*inch; //measured value?
    G4double room_inner_y_short = 189.*inch; //measured value?
    G4double room_x_wall_adj_door_length = 54.*inch - room_x_right_wall_thickness; //measured?
        
    G4double spare_distance = 40*inch; //to account for the effect of the soil outside the building, and evaluate the radiation dose in the lab adjacent

    // Room

    G4double world_x = room_inner_x + room_x_left_wall_thickness + room_x_right_wall_thickness + 2 * spare_distance;
    G4double world_y = room_inner_y + room_y_back_wall_thickness + room_y_front_wall_thickness + 2 * spare_distance;
    G4double world_z = room_inner_z + 2 * room_z_wall_thickness + 2 * spare_distance;

    G4double room_z_wall_box_x = room_inner_x + room_x_left_wall_thickness  + room_x_right_wall_thickness +  spare_distance;
    G4double room_z_wall_box_y = room_inner_y + room_y_back_wall_thickness + room_y_front_wall_thickness + spare_distance;
    G4double room_z_wall_box_z = room_z_wall_thickness;

    G4double room_x_wall_short_x = room_inner_x_short + room_x_left_wall_thickness + room_x_right_wall_thickness;
    G4double room_x_wall_short_y = room_y_back_wall_thickness;
    G4double room_x_wall_short_z = room_inner_z;

    G4double room_x_wall_long_x = room_inner_x + room_x_left_wall_thickness + room_x_right_wall_thickness;
    G4double room_x_wall_long_y = room_y_front_wall_thickness;
    G4double room_x_wall_long_z = room_inner_z;

    G4double room_y_wall_left_x = room_x_left_wall_thickness;
    G4double room_y_wall_left_y = room_inner_y;
    G4double room_y_wall_left_z = room_inner_z;

    G4double room_y_wall_right_x = room_x_right_wall_thickness;
    G4double room_y_wall_right_y = room_inner_y_short;
    G4double room_y_wall_right_z = room_inner_z;

    G4double room_x_wall_adj_door_x = room_x_wall_adj_door_length;
    G4double room_x_wall_adj_door_y = room_x_right_wall_thickness;
    G4double room_x_wall_adj_door_z = room_inner_z;

    G4double cupboard_x = 27.0*inch;
    G4double cupboard_y = 59.5*inch;
    G4double cupboard_z = 36.0*inch;
    G4double cupboard_thi = 1.*inch;

    G4double pump_room_x = 51.5*inch;
    G4double pump_room_y = 102*inch;
    G4double pump_room_z = room_inner_z;
    G4double pump_room_thi = 2.*inch;

    G4double pillar_radius = 5.0*inch;
    G4double pillar_height = 81.0*inch;

    std::vector<G4TwoVector> points;
    G4double platform_thi = 7.*inch;
    points.push_back(G4TwoVector(0.0, 0.0));
    points.push_back(G4TwoVector(-81*inch, 49.5*inch));
    points.push_back(G4TwoVector(-81*inch, -49.5*inch));
    G4double hole_radius = 12.5*inch;

    G4double building_space_x = room_x_left_wall_thickness + room_inner_x + room_x_right_wall_thickness + spare_distance;
    G4double building_space_y = spare_distance + room_y_front_wall_thickness + room_inner_y + room_y_back_wall_thickness;
    G4double building_space_z = room_z_wall_thickness + room_inner_z + room_z_wall_thickness + spare_distance;

    // Cryostat

    G4double can_sample_outer_rMin = 0.0*mm;
    G4double can_sample_outer_rMax = 65.0*mm;
    G4double can_sample_outer_Dz = 193.0*mm;
    G4double can_sample_outer_SPhi = 0.0*deg;
    G4double can_sample_outer_DPhi = 360.0*deg;
    
    G4double can_sample_inner_rMin = 0.0*mm;
    G4double can_sample_inner_rMax = can_sample_outer_rMax - 1.0*mm;
    G4double can_sample_inner_Dz = can_sample_outer_Dz - 10.0*mm;
    G4double can_sample_inner_SPhi = 0.0*deg;
    G4double can_sample_inner_DPhi = 360.0*deg;
    
    G4double can_4k_outer_rMin = 0.0*mm;
    G4double can_4k_outer_rMax = 70.5*mm;
    G4double can_4k_outer_Dz = 337.0*mm;
    G4double can_4k_outer_SPhi = 0.0*deg;
    G4double can_4k_outer_DPhi = 360.0*deg;
    
    G4double can_4k_inner_rMin = 0.0*mm;
    G4double can_4k_inner_rMax = can_4k_outer_rMax - 1.6*mm;
    G4double can_4k_inner_Dz = can_4k_outer_Dz - 10.0*mm;
    G4double can_4k_inner_SPhi = 0.0*deg;
    G4double can_4k_inner_DPhi = 360.0*deg;
    
    G4double can_77k_outer_rMin = 0.0*mm;
    G4double can_77k_outer_rMax = 76.2*mm;
    G4double can_77k_outer_Dz = 368.0*mm;
    G4double can_77k_outer_SPhi = 0.0*deg;
    G4double can_77k_outer_DPhi = 360.0*deg;
    
    G4double can_77k_inner_rMin = 0.0*mm;
    G4double can_77k_inner_rMax = can_77k_outer_rMax - 1.2*mm;
    G4double can_77k_inner_Dz = can_77k_outer_Dz - 10.0*mm;
    G4double can_77k_inner_SPhi = 0.0*deg;
    G4double can_77k_inner_DPhi = 360.0*deg;
    
    G4double can_vacuum_outer_rMin = 0.0*mm;
    G4double can_vacuum_outer_rMax = 101.6*mm;
    G4double can_vacuum_outer_Dz = 451.0*mm;
    G4double can_vacuum_outer_SPhi = 0.0*deg;
    G4double can_vacuum_outer_DPhi = 360.0*deg;
    
    G4double can_vacuum_inner_rMin = 0.0*mm;
    G4double can_vacuum_inner_rMax = can_vacuum_outer_rMax-1.3*mm;
    G4double can_vacuum_inner_Dz = can_vacuum_outer_Dz-10.0*mm;
    G4double can_vacuum_inner_SPhi = 0.0*deg;
    G4double can_vacuum_inner_DPhi = 360.0*deg;

    G4double arm_vacuum_rMax = 50.8*mm;
    G4double arm_vacuum_rMin = arm_vacuum_rMax - 5.0*mm;
    G4double arm_vacuum_Dz = 304.8*mm;
    G4double arm_vacuum_SPhi = 0.0*deg;
    G4double arm_vacuum_DPhi = 360.0*deg;
    
    G4double arm_77k_rMax = 44.0*mm;
    G4double arm_77k_rMin = arm_77k_rMax - 5.0*mm;
    G4double arm_77k_Dz = 300.8*mm;
    G4double arm_77k_SPhi = 0.0*deg;
    G4double arm_77k_DPhi = 360.0*deg;

    G4double arm_4k_rMax = 38*mm;
    G4double arm_4k_rMin = arm_4k_rMax - 5.0*mm;
    G4double arm_4k_Dz = 296.8*mm;
    G4double arm_4k_SPhi = 0.0*deg;
    G4double arm_4k_DPhi = 360.0*deg;

    G4double cryo_vacuum_outer_rMin = 0.0*mm;
    G4double cryo_vacuum_outer_rMax = 209.6*mm;
    G4double cryo_vacuum_outer_Dz = 889.0*mm;
    G4double cryo_vacuum_outer_SPhi = 0.0*deg;
    G4double cryo_vacuum_outer_DPhi = 360.0*deg;
    
    G4double cryo_vacuum_inner_rMin = 0.0*mm;
    G4double cryo_vacuum_inner_rMax = cryo_vacuum_outer_rMax - 5.0*mm;
    G4double cryo_vacuum_inner_Dz = cryo_vacuum_outer_Dz - 10.0*mm;
    G4double cryo_vacuum_inner_SPhi = 0.0*deg;
    G4double cryo_vacuum_inner_DPhi = 360.0*deg;

    G4double cryo_77k_outer_rMin = 0.0*mm;
    G4double cryo_77k_outer_rMax = 184.2*mm;
    G4double cryo_77k_outer_Dz = 762.0*mm;
    G4double cryo_77k_outer_SPhi = 0.0*deg;
    G4double cryo_77k_outer_DPhi = 360.0*deg;
    
    G4double cryo_nitrogen_rMin = 152.4*mm;
    G4double cryo_nitrogen_rMax = cryo_77k_outer_rMax - 5.0*mm;
    G4double cryo_nitrogen_Dz = cryo_77k_outer_Dz - 25.4*mm;
    G4double cryo_nitrogen_SPhi = 0.0*deg;
    G4double cryo_nitrogen_DPhi = 360.0*deg;
    
    G4double cryo_77k_inner_rMin = 0.0*mm;
    G4double cryo_77k_inner_rMax = cryo_nitrogen_rMin - 5.0*mm;
    G4double cryo_77k_inner_Dz = cryo_77k_outer_Dz - 10.0*mm;
    G4double cryo_77k_inner_SPhi = 0.0*deg;
    G4double cryo_77k_inner_DPhi = 360.0*deg;

    G4double cryo_4k_outer_rMin = 0.0*mm;
    G4double cryo_4k_outer_rMax = 133.4*mm;
    G4double cryo_4k_outer_Dz = 508.0*mm;
    G4double cryo_4k_outer_SPhi = 0.0*deg;
    G4double cryo_4k_outer_DPhi = 360.0*deg;
    
    G4double cryo_4k_inner_rMin = 0.0*mm;
    G4double cryo_4k_inner_rMax = cryo_4k_outer_rMax - 5.0*mm;
    G4double cryo_4k_inner_Dz = cryo_4k_outer_Dz - 10.0*mm;
    G4double cryo_4k_inner_SPhi = 0.0*deg;
    G4double cryo_4k_inner_DPhi = 360.0*deg;

    // T-slot frame

    G4double tslot_width = 38.1*mm;
    G4double tslot_length_z = 2286.0*mm;
    G4double tslot_length_xy = 1410.0*mm;

    //===============  Positions ===============//

    // Room

    G4double z_wall_x_pos = spare_distance / 2.0;
    G4double z_wall_y_pos = -spare_distance / 2.0;
    G4double z_wall_z_pos_1 = (room_inner_z + room_z_wall_thickness) / 2.0;
    G4double z_wall_z_pos_2 = -(room_inner_z + room_z_wall_thickness) / 2.0;

    G4double x_wall_short_x_pos = (room_inner_x_short - room_inner_x) / 2.0;
    G4double x_wall_short_y_pos = (room_inner_y + room_y_front_wall_thickness) / 2.0;
    G4double x_wall_short_z_pos = 0;

    G4double x_wall_long_x_pos = 0;
    G4double x_wall_long_y_pos = -(room_inner_y + room_y_back_wall_thickness) / 2.0;
    G4double x_wall_long_z_pos = 0;

    G4double y_wall_left_x_pos = -(room_inner_x + room_x_right_wall_thickness) / 2.0;
    G4double y_wall_left_y_pos = (room_y_front_wall_thickness - room_y_back_wall_thickness)/2.0;
    G4double y_wall_left_z_pos = 0;

    G4double y_wall_right_x_pos = room_inner_x_short + (room_x_left_wall_thickness - room_inner_x) / 2.0;
    G4double y_wall_right_y_pos = (room_y_front_wall_thickness - room_y_back_wall_thickness + room_inner_y - room_inner_y_short) / 2.0;
    G4double y_wall_right_z_pos = 0;

    G4double x_wall_adj_door_x_pos = room_inner_x_short + (room_x_left_wall_thickness -room_inner_x + room_x_right_wall_thickness + room_x_wall_adj_door_length)/2.0;
    G4double x_wall_adj_door_y_pos = (room_y_front_wall_thickness + room_inner_y + room_x_right_wall_thickness - room_y_back_wall_thickness)/2.0 - room_inner_y_short;
    G4double x_wall_adj_door_z_pos = 0;

    G4double cupboard_x_pos = room_inner_x_short + (room_x_left_wall_thickness - room_inner_x - room_x_right_wall_thickness - cupboard_x) / 2.0;
    G4double cupboard_y_pos = (room_y_front_wall_thickness + room_inner_y - room_y_back_wall_thickness - cupboard_y) / 2.0;
    G4double cupboard_z_pos = (cupboard_z - room_inner_z) / 2.0;

    G4double pump_room_x_pos = (room_x_left_wall_thickness + pump_room_x - room_inner_x - room_x_right_wall_thickness) / 2.0;
    G4double pump_room_y_pos = (room_y_front_wall_thickness + pump_room_y - room_inner_y - room_y_back_wall_thickness) / 2.0;
    G4double pump_room_z_pos = 0;

    G4double platform_pillar_x_pos = 81.*inch + (room_x_left_wall_thickness - room_inner_x - room_x_right_wall_thickness) / 2;
    G4double platform_pillar_y_pos = (room_y_front_wall_thickness + room_inner_y - room_y_back_wall_thickness) / 2 - (9.*inch + 49.5*inch);
    G4double platform_pillar_z_pos = (pillar_height - room_inner_z) /2;

    G4double platform_z_pos = pillar_height + platform_thi - room_inner_z /2;

    // Cryostat

    G4double can_sample_outer_posX = 0.0*mm;
    G4double can_sample_outer_posY = 0.0*mm;
    G4double can_sample_outer_posZ = (can_4k_outer_Dz - can_sample_outer_Dz)/2.0 - 13.0*mm;
    
    G4double can_sample_inner_posX = 0.0*mm;
    G4double can_sample_inner_posY = 0.0*mm;
    G4double can_sample_inner_posZ = 0.0*mm;
    
    G4double can_4k_outer_posX = 0.0*mm;
    G4double can_4k_outer_posY = 0.0*mm;
    G4double can_4k_outer_posZ = (can_77k_outer_Dz - can_4k_outer_Dz)/2.0 - 13.0*mm;
    
    G4double can_4k_inner_posX = 0.0*mm;
    G4double can_4k_inner_posY = 0.0*mm;
    G4double can_4k_inner_posZ = 0.0*mm;
    
    G4double can_77k_outer_posX = 0.0*mm;
    G4double can_77k_outer_posY = 0.0*mm;
    G4double can_77k_outer_posZ = (can_vacuum_outer_Dz - can_77k_outer_Dz)/2.0 - 13.0*mm;
    
    G4double can_77k_inner_posX = 0.0*mm;
    G4double can_77k_inner_posY = 0.0*mm;
    G4double can_77k_inner_posZ = 0.0*mm;
    
    G4double can_vacuum_outer_posX = 31.75*mm;
    G4double can_vacuum_outer_posY = 970.80*mm;
    G4double can_vacuum_outer_posZ =  (1.0*m + can_vacuum_outer_Dz/2.0) - (room_inner_z/2.0);
    
    G4double can_vacuum_inner_posX = 0.0*mm;
    G4double can_vacuum_inner_posY = 0.0*mm;
    G4double can_vacuum_inner_posZ = 0.0*mm;

    G4double arm_vacuum_posX = can_vacuum_outer_posX;
    G4double arm_vacuum_posY = can_vacuum_outer_posY;
    G4double arm_vacuum_posZ = can_vacuum_outer_posZ + (can_vacuum_outer_Dz/2.0) + (arm_vacuum_Dz/2.0);

    G4double arm_77k_posX = arm_vacuum_posX;
    G4double arm_77k_posY = arm_vacuum_posY;
    G4double arm_77k_posZ = arm_vacuum_posZ;

    G4double arm_4k_posX = arm_vacuum_posX;
    G4double arm_4k_posY = arm_vacuum_posY;
    G4double arm_4k_posZ = arm_vacuum_posZ;

    G4double cryo_vacuum_outer_posX = can_vacuum_outer_posX;
    G4double cryo_vacuum_outer_posY = can_vacuum_outer_posY;
    G4double cryo_vacuum_outer_posZ = arm_vacuum_posZ + (arm_vacuum_Dz/2.0) + (cryo_vacuum_outer_Dz/2.0);
    
    G4double cryo_vacuum_inner_posX = 0.0*mm;
    G4double cryo_vacuum_inner_posY = 0.0*mm;
    G4double cryo_vacuum_inner_posZ = 0.0*mm;

    G4double cryo_77k_outer_posX = 0.0*mm;
    G4double cryo_77k_outer_posY = 0.0*mm;
    G4double cryo_77k_outer_posZ = -38.1*mm;

    G4double cryo_nitrogen_posX = 0.0*mm;
    G4double cryo_nitrogen_posY = 0.0*mm;
    G4double cryo_nitrogen_posZ = 0.0*mm;

    G4double cryo_77k_inner_posX = 0.0*mm;
    G4double cryo_77k_inner_posY = 0.0*mm;
    G4double cryo_77k_inner_posZ = 0.0*mm;

    G4double cryo_4k_outer_posX = 0.0*mm;
    G4double cryo_4k_outer_posY = 0.0*mm;
    G4double cryo_4k_outer_posZ = 25.4*mm;

    G4double cryo_4k_inner_posX = 0.0*mm;
    G4double cryo_4k_inner_posY = 0.0*mm;
    G4double cryo_4k_inner_posZ = 0.0*mm;

    // T-slot frame

    G4double tslot_vert_1_posX = can_vacuum_outer_posX + (tslot_length_xy/2.0);
    G4double tslot_vert_1_posY = can_vacuum_outer_posY + (tslot_length_xy/2.0);
    G4double tslot_vert_1_posZ = (tslot_length_z - room_inner_z)/2.0;

    G4double tslot_vert_2_posX = can_vacuum_outer_posX + (tslot_length_xy/2.0);
    G4double tslot_vert_2_posY = can_vacuum_outer_posY - (tslot_length_xy/2.0);
    G4double tslot_vert_2_posZ = tslot_vert_1_posZ;

    G4double tslot_vert_3_posX = can_vacuum_outer_posX - (tslot_length_xy/2.0);
    G4double tslot_vert_3_posY = can_vacuum_outer_posY + (tslot_length_xy/2.0);
    G4double tslot_vert_3_posZ = tslot_vert_1_posZ;

    G4double tslot_vert_4_posX = can_vacuum_outer_posX - (tslot_length_xy/2.0);
    G4double tslot_vert_4_posY = can_vacuum_outer_posY - (tslot_length_xy/2.0);
    G4double tslot_vert_4_posZ = tslot_vert_1_posZ;

    G4double tslot_hor_1_posX = can_vacuum_outer_posX + (tslot_length_xy/2.0);
    G4double tslot_hor_1_posY = can_vacuum_outer_posY;
    G4double tslot_hor_1_posZ = tslot_vert_1_posZ + tslot_length_z/2.0 + tslot_width/2.0;

    G4double tslot_hor_2_posX = can_vacuum_outer_posX - (tslot_length_xy/2.0);
    G4double tslot_hor_2_posY = can_vacuum_outer_posY;
    G4double tslot_hor_2_posZ = tslot_hor_1_posZ;

    G4double tslot_hor_3_posX = can_vacuum_outer_posX;
    G4double tslot_hor_3_posY = can_vacuum_outer_posY + (tslot_length_xy)/2.0;
    G4double tslot_hor_3_posZ = tslot_hor_1_posZ;

    G4double tslot_hor_4_posX = can_vacuum_outer_posX;
    G4double tslot_hor_4_posY = can_vacuum_outer_posY - (tslot_length_xy)/2.0;
    G4double tslot_hor_4_posZ = tslot_hor_1_posZ;

    G4double tslot_hor_5_posX = can_vacuum_outer_posX + (tslot_width/2.0 + cryo_vacuum_outer_rMax);
    G4double tslot_hor_5_posY = can_vacuum_outer_posY;
    G4double tslot_hor_5_posZ = tslot_vert_1_posZ + tslot_length_z/2.0 + 1.5*tslot_width;

    G4double tslot_hor_6_posX = can_vacuum_outer_posX - (tslot_width/2.0 + cryo_vacuum_outer_rMax);
    G4double tslot_hor_6_posY = can_vacuum_outer_posY;
    G4double tslot_hor_6_posZ = tslot_hor_5_posZ;

    G4double tslot_hor_7_posX = can_vacuum_outer_posX;
    G4double tslot_hor_7_posY = can_vacuum_outer_posY + (tslot_width/2.0 + cryo_vacuum_outer_rMax);
    G4double tslot_hor_7_posZ = tslot_hor_5_posZ;

    G4double tslot_hor_8_posX = can_vacuum_outer_posX;
    G4double tslot_hor_8_posY = can_vacuum_outer_posY - (tslot_width/2.0 + cryo_vacuum_outer_rMax);
    G4double tslot_hor_8_posZ = tslot_hor_5_posZ;

    //===============  Rotations ===============//

    // Room

    G4RotationMatrix* z_wall_1_rm = new G4RotationMatrix;
    G4RotationMatrix* z_wall_2_rm = new G4RotationMatrix;
    G4RotationMatrix* x_wall_short_rm = new G4RotationMatrix;
    G4RotationMatrix* x_wall_long_rm = new G4RotationMatrix;
    G4RotationMatrix* y_wall_left_rm = new G4RotationMatrix;
    G4RotationMatrix* y_wall_right_rm = new G4RotationMatrix;
    G4RotationMatrix* x_wall_adj_door_rm = new G4RotationMatrix;
    G4RotationMatrix* cupboard_rm = new G4RotationMatrix;
    G4RotationMatrix* pump_room_rm = new G4RotationMatrix;
    G4RotationMatrix* platform_pillar_rm = new G4RotationMatrix;
    G4RotationMatrix* platform_rm = new G4RotationMatrix;

    // Cryostat

    G4RotationMatrix* can_sample_outer_rm = new G4RotationMatrix;
    G4RotationMatrix* can_4k_outer_rm = new G4RotationMatrix;
    G4RotationMatrix* can_77k_outer_rm = new G4RotationMatrix;
    G4RotationMatrix* can_vacuum_outer_rm = new G4RotationMatrix;
    G4RotationMatrix* arm_vacuum_rm = new G4RotationMatrix;
    G4RotationMatrix* arm_77k_rm = new G4RotationMatrix;
    G4RotationMatrix* arm_4k_rm = new G4RotationMatrix;
    G4RotationMatrix* cryo_vacuum_outer_rm = new G4RotationMatrix;
    G4RotationMatrix* cryo_77k_outer_rm = new G4RotationMatrix;
    G4RotationMatrix* cryo_nitrogen_rm = new G4RotationMatrix;
    G4RotationMatrix* cryo_4k_outer_rm = new G4RotationMatrix;

    G4RotationMatrix* can_sample_inner_rm = new G4RotationMatrix;
    G4RotationMatrix* can_4k_inner_rm = new G4RotationMatrix;
    G4RotationMatrix* can_77k_inner_rm = new G4RotationMatrix;
    G4RotationMatrix* can_vacuum_inner_rm = new G4RotationMatrix;
    G4RotationMatrix* cryo_vacuum_inner_rm = new G4RotationMatrix;
    G4RotationMatrix* cryo_77k_inner_rm = new G4RotationMatrix;
    G4RotationMatrix* cryo_4k_inner_rm = new G4RotationMatrix;

    // T-slot frame

    G4RotationMatrix* tslot_vert_1_rm = new G4RotationMatrix;
    G4RotationMatrix* tslot_vert_2_rm = new G4RotationMatrix;
    G4RotationMatrix* tslot_vert_3_rm = new G4RotationMatrix;
    G4RotationMatrix* tslot_vert_4_rm = new G4RotationMatrix;

    G4RotationMatrix* tslot_hor_1_rm = new G4RotationMatrix;
    G4RotationMatrix* tslot_hor_2_rm = new G4RotationMatrix;
    G4RotationMatrix* tslot_hor_3_rm = new G4RotationMatrix;
    G4RotationMatrix* tslot_hor_4_rm = new G4RotationMatrix;
    G4RotationMatrix* tslot_hor_5_rm = new G4RotationMatrix;
    G4RotationMatrix* tslot_hor_6_rm = new G4RotationMatrix;
    G4RotationMatrix* tslot_hor_7_rm = new G4RotationMatrix;
    G4RotationMatrix* tslot_hor_8_rm = new G4RotationMatrix;

    can_vacuum_outer_rm->rotateX(180*deg);

    // Commented out is GDML file reading
/*    G4String filename = "test/cube_placement.txt";
    G4tgbVolumeMgr* volmgr = G4tgbVolumeMgr::GetInstance();
    volmgr->AddTextFile(filename);
    WorldPV = volmgr->ReadAndConstructDetector();
    WorldLV = WorldPV->GetLogicalVolume();*/
    
    //===============  Build Geometry ===============//

    G4String name;

    // Room shapes

    name = "world_box";
    G4Box* world_box = new G4Box(name, world_x/2.0, world_y/2.0, world_z/2.0);
    WorldLV = new G4LogicalVolume(world_box, world_material, "WorldLV");
    WorldPV = new G4PVPlacement(0, G4ThreeVector(0,0,0), WorldLV, name, 0, false, 0);
  
    name = "z_wall";
    G4Box* room_z_wall_box = new G4Box(name, room_z_wall_box_x/2.0, room_z_wall_box_y/2.0, room_z_wall_box_z/2.0);
    z_wall_LV = new G4LogicalVolume(room_z_wall_box, z_wall_material, name);
    z_wall_PV_1 = new G4PVPlacement(z_wall_1_rm, G4ThreeVector(z_wall_x_pos, z_wall_y_pos, z_wall_z_pos_1), z_wall_LV, "z_wall_1", WorldLV, true, 0, fCheckOverlaps);    
    z_wall_PV_2 = new G4PVPlacement(z_wall_2_rm, G4ThreeVector(z_wall_x_pos, z_wall_y_pos, z_wall_z_pos_2), z_wall_LV, "z_wall_2", WorldLV, true, 1, fCheckOverlaps);
    
    name = "x_wall_short";
    G4Box* room_x_wall_short_box = new G4Box(name, room_x_wall_short_x/2.0, room_x_wall_short_y/2.0, room_x_wall_short_z/2.0);
    x_wall_short_LV = new G4LogicalVolume(room_x_wall_short_box, x_wall_short_material, name);
    x_wall_short_PV = new G4PVPlacement(x_wall_short_rm, G4ThreeVector(x_wall_short_x_pos, x_wall_short_y_pos, x_wall_short_z_pos), x_wall_short_LV, name, WorldLV, false, 0, fCheckOverlaps);
    
    name = "x_wall_long";
    G4Box* room_x_wall_long_box = new G4Box(name, room_x_wall_long_x/2.0, room_x_wall_long_y/2.0, room_x_wall_long_z/2.0);
    x_wall_long_LV = new G4LogicalVolume(room_x_wall_long_box, x_wall_long_material, name);
    x_wall_long_PV = new G4PVPlacement(x_wall_long_rm, G4ThreeVector(x_wall_long_x_pos, x_wall_long_y_pos, x_wall_long_z_pos), x_wall_long_LV, name, WorldLV, false, 0, fCheckOverlaps);
    
    name = "y_wall_left";
    G4Box* room_y_wall_left_box = new G4Box(name, room_y_wall_left_x/2.0, room_y_wall_left_y/2.0, room_y_wall_left_z/2.0);
    y_wall_left_LV = new G4LogicalVolume(room_y_wall_left_box, y_wall_left_material, name);
    y_wall_left_PV = new G4PVPlacement(y_wall_left_rm, G4ThreeVector(y_wall_left_x_pos, y_wall_left_y_pos, y_wall_left_z_pos), y_wall_left_LV, name, WorldLV, false, 0, fCheckOverlaps);
    
    name = "y_wall_right";
    G4Box* room_y_wall_right_box = new G4Box(name, room_y_wall_right_x/2.0, room_y_wall_right_y/2.0, room_y_wall_right_z/2.0);
    y_wall_right_LV = new G4LogicalVolume(room_y_wall_right_box, y_wall_right_material, name);
    y_wall_right_PV = new G4PVPlacement(y_wall_right_rm, G4ThreeVector(y_wall_right_x_pos, y_wall_right_y_pos, y_wall_right_z_pos), y_wall_right_LV, name, WorldLV, false, 0, fCheckOverlaps);
    
    name = "room_x_wall_adj_door_length";
    G4Box* room_x_wall_adj_door_box = new G4Box(name, room_x_wall_adj_door_x/2.0, room_x_wall_adj_door_y/2.0, room_x_wall_adj_door_z/2.0);
    x_wall_adj_door_LV = new G4LogicalVolume(room_x_wall_adj_door_box, x_wall_adj_door_material, name);
    x_wall_adj_door_PV = new G4PVPlacement(x_wall_adj_door_rm, G4ThreeVector(x_wall_adj_door_x_pos, x_wall_adj_door_y_pos, x_wall_adj_door_z_pos), x_wall_adj_door_LV, name, WorldLV, false, 0, fCheckOverlaps);
    
    name = "cupboard";
    G4Box* cupboard_OV = new G4Box("cupboard_OV", cupboard_x/2.0, cupboard_y/2.0, cupboard_z/2.0);
    G4Box* cupboard_IV = new G4Box("cupboard_IV", (cupboard_x - 2.0 * cupboard_thi)/2.0, (cupboard_y - 2.0 * cupboard_thi)/2.0, (cupboard_z - 2.0 * cupboard_thi)/2.0);
    G4SubtractionSolid* cupboard = new G4SubtractionSolid(name, cupboard_OV, cupboard_IV, 0, G4ThreeVector(0,0,0));
    cupboard_LV = new G4LogicalVolume(cupboard, cupboard_material, name);
    cupboard_PV = new G4PVPlacement(cupboard_rm, G4ThreeVector(cupboard_x_pos, cupboard_y_pos, cupboard_z_pos), cupboard_LV, name, WorldLV, false, 0, fCheckOverlaps);
    
    //The pump cabinet room is modeled as a wooden box
    name = "pump_room";
    G4Box* pump_room_OV = new G4Box("pump_room_OV", pump_room_x/2.0, pump_room_y/2.0, pump_room_z/2.0);
    G4Box* pump_room_IV = new G4Box("pump_room_IV", (pump_room_x - 2.0 * pump_room_thi)/2.0, (pump_room_y - 2.0 * pump_room_thi)/2.0, pump_room_z/2.0);
    G4SubtractionSolid* pump_room = new G4SubtractionSolid(name, pump_room_OV, pump_room_IV, 0, G4ThreeVector(0,0,0));
    pump_room_LV = new G4LogicalVolume(pump_room, pump_room_material, name);
    pump_room_PV = new G4PVPlacement(pump_room_rm, G4ThreeVector(pump_room_x_pos, pump_room_y_pos, pump_room_z_pos), pump_room_LV, name, WorldLV, false, 0, fCheckOverlaps);
    
    name = "platform_pillar";
    G4Tubs* platform_pillar = new G4Tubs(name, 0, pillar_radius, pillar_height/2.0, 0, 360*degree);
    platform_pillar_LV = new G4LogicalVolume(platform_pillar, platform_pillar_material, name);
    platform_pillar_PV =  new G4PVPlacement(platform_pillar_rm, G4ThreeVector(platform_pillar_x_pos, platform_pillar_y_pos, platform_pillar_z_pos), platform_pillar_LV, name, WorldLV, false, 0, fCheckOverlaps);
    
    name = "platform";
    G4ExtrudedSolid* platform_tri_pri = new G4ExtrudedSolid("platform_tri_pri", points, platform_thi, G4TwoVector(0,0), 1.0, G4TwoVector(0,0), 1.0);
    G4Tubs* platform_hole = new G4Tubs("platform_hole", 0, hole_radius, platform_thi/2, 0, 360*degree);
    G4SubtractionSolid* platform = new G4SubtractionSolid(name, platform_tri_pri, platform_hole, 0, G4ThreeVector(-53.*inch,0,0));
    platform_LV = new G4LogicalVolume(platform, platform_material, name);
    platform_PV = new G4PVPlacement(platform_rm, G4ThreeVector(platform_pillar_x_pos, platform_pillar_y_pos, platform_z_pos), platform_LV, name, WorldLV, false, 0, fCheckOverlaps);
    
    name = "soil_space";
    G4Box* building_space = new G4Box("building_space", building_space_x/2, building_space_y/2, building_space_z/2) ; 
    G4SubtractionSolid* soil_space = new G4SubtractionSolid (name, world_box, building_space, 0, G4ThreeVector((spare_distance/2),-(spare_distance/2),(spare_distance/2)));
    soil_space_LV = new G4LogicalVolume(soil_space, soil_space_material, name);
    soil_space_PV = new G4PVPlacement(0, G4ThreeVector(0,0,0), soil_space_LV, name, WorldLV, false, 0, fCheckOverlaps);

    // Cryostat

    name = "can_vacuum_outer";
    G4Tubs* can_vacuum_outer_S = new G4Tubs(name, can_vacuum_outer_rMin, can_vacuum_outer_rMax, can_vacuum_outer_Dz/2.0, can_vacuum_outer_SPhi, can_vacuum_outer_DPhi);
    G4LogicalVolume* can_vacuum_outer_LV = new G4LogicalVolume(can_vacuum_outer_S, can_vacuum_outer_material, name);
    new G4PVPlacement(can_vacuum_outer_rm, G4ThreeVector(can_vacuum_outer_posX,can_vacuum_outer_posY,can_vacuum_outer_posZ), can_vacuum_outer_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "can_vacuum_inner";
    G4Tubs* can_vacuum_inner_S = new G4Tubs(name, can_vacuum_inner_rMin, can_vacuum_inner_rMax, can_vacuum_inner_Dz/2.0, can_vacuum_inner_SPhi, can_vacuum_inner_DPhi);
    G4LogicalVolume* can_vacuum_inner_LV = new G4LogicalVolume(can_vacuum_inner_S, can_vacuum_inner_material, name);
    new G4PVPlacement(can_vacuum_inner_rm, G4ThreeVector(can_vacuum_inner_posX,can_vacuum_inner_posY,can_vacuum_inner_posZ), can_vacuum_inner_LV, name, can_vacuum_outer_LV, false, 0, fCheckOverlaps);

    name = "can_77k_outer";
    G4Tubs* can_77k_outer_S = new G4Tubs(name, can_77k_outer_rMin, can_77k_outer_rMax, can_77k_outer_Dz/2.0, can_77k_outer_SPhi, can_77k_outer_DPhi);
    G4LogicalVolume* can_77k_outer_LV = new G4LogicalVolume(can_77k_outer_S, can_77k_outer_material, name);
    new G4PVPlacement(can_77k_outer_rm, G4ThreeVector(can_77k_outer_posX,can_77k_outer_posY,can_77k_outer_posZ), can_77k_outer_LV, name, can_vacuum_inner_LV, false, 0, fCheckOverlaps);

    name = "can_77k_inner";
    G4Tubs* can_77k_inner_S = new G4Tubs(name, can_77k_inner_rMin, can_77k_inner_rMax, can_77k_inner_Dz/2.0, can_77k_inner_SPhi, can_77k_inner_DPhi);
    G4LogicalVolume* can_77k_inner_LV = new G4LogicalVolume(can_77k_inner_S, can_77k_inner_material, name);
    new G4PVPlacement(can_77k_inner_rm, G4ThreeVector(can_77k_inner_posX,can_77k_inner_posY,can_77k_inner_posZ), can_77k_inner_LV, name, can_77k_outer_LV, false, 0, fCheckOverlaps);

    name = "can_4k_outer";
    G4Tubs* can_4k_outer_S = new G4Tubs(name, can_4k_outer_rMin, can_4k_outer_rMax, can_4k_outer_Dz/2.0, can_4k_outer_SPhi, can_4k_outer_DPhi);
    G4LogicalVolume* can_4k_outer_LV = new G4LogicalVolume(can_4k_outer_S, can_4k_outer_material, name);
    new G4PVPlacement(can_4k_outer_rm, G4ThreeVector(can_4k_outer_posX,can_4k_outer_posY,can_4k_outer_posZ), can_4k_outer_LV, name, can_77k_inner_LV, false, 0, fCheckOverlaps);

    name = "can_4k_inner";
    G4Tubs* can_4k_inner_S = new G4Tubs(name, can_4k_inner_rMin, can_4k_inner_rMax, can_4k_inner_Dz/2.0, can_4k_inner_SPhi, can_4k_inner_DPhi);
    G4LogicalVolume* can_4k_inner_LV = new G4LogicalVolume(can_4k_inner_S, can_4k_inner_material, name);
    new G4PVPlacement(can_4k_inner_rm, G4ThreeVector(can_4k_inner_posX,can_4k_inner_posY,can_4k_inner_posZ), can_4k_inner_LV, name, can_4k_outer_LV, false, 0, fCheckOverlaps);

    name = "can_sample_outer";
    G4Tubs* can_sample_outer_S = new G4Tubs(name, can_sample_outer_rMin, can_sample_outer_rMax, can_sample_outer_Dz/2.0, can_sample_outer_SPhi, can_sample_outer_DPhi);
    G4LogicalVolume* can_sample_outer_LV = new G4LogicalVolume(can_sample_outer_S, can_sample_outer_material, name);
    new G4PVPlacement(can_sample_outer_rm, G4ThreeVector(can_sample_outer_posX,can_sample_outer_posY,can_sample_outer_posZ), can_sample_outer_LV, name, can_4k_inner_LV, false, 0, fCheckOverlaps);

    name = "can_sample_inner";
    G4Tubs* can_sample_inner_S = new G4Tubs(name, can_sample_inner_rMin, can_sample_inner_rMax, can_sample_inner_Dz/2.0, can_sample_inner_SPhi, can_sample_inner_DPhi);
    G4LogicalVolume* can_sample_inner_LV = new G4LogicalVolume(can_sample_inner_S, can_sample_inner_material, name);
    new G4PVPlacement(can_sample_inner_rm, G4ThreeVector(can_sample_inner_posX,can_sample_inner_posY,can_sample_inner_posZ), can_sample_inner_LV, name, can_sample_outer_LV, false, 0, fCheckOverlaps);

    name = "arm_vacuum";
    G4Tubs* arm_vacuum_S = new G4Tubs(name, arm_vacuum_rMin, arm_vacuum_rMax, arm_vacuum_Dz/2.0, arm_vacuum_SPhi, arm_vacuum_DPhi);
    G4LogicalVolume* arm_vacuum_LV = new G4LogicalVolume(arm_vacuum_S, arm_vacuum_material, name);
    new G4PVPlacement(arm_vacuum_rm, G4ThreeVector(arm_vacuum_posX,arm_vacuum_posY,arm_vacuum_posZ), arm_vacuum_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "arm_77k";
    G4Tubs* arm_77k_S = new G4Tubs(name, arm_77k_rMin, arm_77k_rMax, arm_77k_Dz/2.0, arm_77k_SPhi, arm_77k_DPhi);
    G4LogicalVolume* arm_77k_LV = new G4LogicalVolume(arm_77k_S, arm_77k_material, name);
    new G4PVPlacement(arm_77k_rm, G4ThreeVector(arm_77k_posX,arm_77k_posY,arm_77k_posZ), arm_77k_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "arm_4k";
    G4Tubs* arm_4k_S = new G4Tubs(name, arm_4k_rMin, arm_4k_rMax, arm_4k_Dz/2.0, arm_4k_SPhi, arm_4k_DPhi);
    G4LogicalVolume* arm_4k_LV = new G4LogicalVolume(arm_4k_S, arm_4k_material, name);
    new G4PVPlacement(arm_4k_rm, G4ThreeVector(arm_4k_posX,arm_4k_posY,arm_4k_posZ), arm_4k_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "cryo_vacuum_outer";
    G4Tubs* cryo_vacuum_outer_S = new G4Tubs(name, cryo_vacuum_outer_rMin, cryo_vacuum_outer_rMax, cryo_vacuum_outer_Dz/2.0, cryo_vacuum_outer_SPhi, cryo_vacuum_outer_DPhi);
    G4LogicalVolume* cryo_vacuum_outer_LV = new G4LogicalVolume(cryo_vacuum_outer_S, cryo_vacuum_outer_material, name);
    new G4PVPlacement(cryo_vacuum_outer_rm, G4ThreeVector(cryo_vacuum_outer_posX,cryo_vacuum_outer_posY,cryo_vacuum_outer_posZ), cryo_vacuum_outer_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "cryo_vacuum_inner";
    G4Tubs* cryo_vacuum_inner_S = new G4Tubs(name, cryo_vacuum_inner_rMin, cryo_vacuum_inner_rMax, cryo_vacuum_inner_Dz/2.0, cryo_vacuum_inner_SPhi, cryo_vacuum_inner_DPhi);
    G4LogicalVolume* cryo_vacuum_inner_LV = new G4LogicalVolume(cryo_vacuum_inner_S, cryo_vacuum_inner_material, name);
    new G4PVPlacement(cryo_vacuum_inner_rm, G4ThreeVector(cryo_vacuum_inner_posX,cryo_vacuum_inner_posY,cryo_vacuum_inner_posZ), cryo_vacuum_inner_LV, name, cryo_vacuum_outer_LV, false, 0, fCheckOverlaps);

    name = "cryo_77k_outer";
    G4Tubs* cryo_77k_outer_S = new G4Tubs(name, cryo_77k_outer_rMin, cryo_77k_outer_rMax, cryo_77k_outer_Dz/2.0, cryo_77k_outer_SPhi, cryo_77k_outer_DPhi);
    G4LogicalVolume* cryo_77k_outer_LV = new G4LogicalVolume(cryo_77k_outer_S, cryo_77k_outer_material, name);
    new G4PVPlacement(cryo_77k_outer_rm, G4ThreeVector(cryo_77k_outer_posX,cryo_77k_outer_posY,cryo_77k_outer_posZ), cryo_77k_outer_LV, name, cryo_vacuum_inner_LV, false, 0, fCheckOverlaps);

    name = "cryo_nitrogen";
    G4Tubs* cryo_nitrogen_S = new G4Tubs(name, cryo_nitrogen_rMin, cryo_nitrogen_rMax, cryo_nitrogen_Dz/2.0, cryo_nitrogen_SPhi, cryo_nitrogen_DPhi);
    G4LogicalVolume* cryo_nitrogen_LV = new G4LogicalVolume(cryo_nitrogen_S, cryo_nitrogen_material, name);
    new G4PVPlacement(cryo_nitrogen_rm, G4ThreeVector(cryo_nitrogen_posX,cryo_nitrogen_posY,cryo_nitrogen_posZ), cryo_nitrogen_LV, name, cryo_77k_outer_LV, false, 0, fCheckOverlaps);

    name = "cryo_77k_inner";
    G4Tubs* cryo_77k_inner_S = new G4Tubs(name, cryo_77k_inner_rMin, cryo_77k_inner_rMax, cryo_77k_inner_Dz/2.0, cryo_77k_inner_SPhi, cryo_77k_inner_DPhi);
    G4LogicalVolume* cryo_77k_inner_LV = new G4LogicalVolume(cryo_77k_inner_S, cryo_77k_inner_material, name);
    new G4PVPlacement(cryo_77k_inner_rm, G4ThreeVector(cryo_77k_inner_posX,cryo_77k_inner_posY,cryo_77k_inner_posZ), cryo_77k_inner_LV, name, cryo_77k_outer_LV, false, 0, fCheckOverlaps);

    name = "cryo_4k_outer";
    G4Tubs* cryo_4k_outer_S = new G4Tubs(name, cryo_4k_outer_rMin, cryo_4k_outer_rMax, cryo_4k_outer_Dz/2.0, cryo_4k_outer_SPhi, cryo_4k_outer_DPhi);
    G4LogicalVolume* cryo_4k_outer_LV = new G4LogicalVolume(cryo_4k_outer_S, cryo_4k_outer_material, name);
    new G4PVPlacement(cryo_4k_outer_rm, G4ThreeVector(cryo_4k_outer_posX,cryo_4k_outer_posY,cryo_4k_outer_posZ), cryo_4k_outer_LV, name, cryo_77k_inner_LV, false, 0, fCheckOverlaps);

    name = "cryo_4k_inner";
    G4Tubs* cryo_4k_inner_S = new G4Tubs(name, cryo_4k_inner_rMin, cryo_4k_inner_rMax, cryo_4k_inner_Dz/2.0, cryo_4k_inner_SPhi, cryo_4k_inner_DPhi);
    G4LogicalVolume* cryo_4k_inner_LV = new G4LogicalVolume(cryo_4k_inner_S, cryo_4k_inner_material, name);
    new G4PVPlacement(cryo_4k_inner_rm, G4ThreeVector(cryo_4k_inner_posX,cryo_4k_inner_posY,cryo_4k_inner_posZ), cryo_4k_inner_LV, name, cryo_4k_outer_LV, false, 0, fCheckOverlaps);

    // T-slot frame

    name = "tslot_vert_1";
    G4Box* tslot_vert_1 = new G4Box(name, tslot_width/2, tslot_width/2, tslot_length_z/2.0);
    G4LogicalVolume* tslot_vert_1_LV = new G4LogicalVolume(tslot_vert_1, tslot_material, name);
    new G4PVPlacement(tslot_vert_1_rm, G4ThreeVector(tslot_vert_1_posX, tslot_vert_1_posY, tslot_vert_1_posZ), tslot_vert_1_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_vert_2";
    G4Box* tslot_vert_2 = new G4Box(name, tslot_width/2, tslot_width/2, tslot_length_z/2.0);
    G4LogicalVolume* tslot_vert_2_LV = new G4LogicalVolume(tslot_vert_2, tslot_material, name);
    new G4PVPlacement(tslot_vert_2_rm, G4ThreeVector(tslot_vert_2_posX, tslot_vert_2_posY, tslot_vert_2_posZ), tslot_vert_2_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_vert_3";
    G4Box* tslot_vert_3 = new G4Box(name, tslot_width/2, tslot_width/2, tslot_length_z/2.0);
    G4LogicalVolume* tslot_vert_3_LV = new G4LogicalVolume(tslot_vert_3, tslot_material, name);
    new G4PVPlacement(tslot_vert_3_rm, G4ThreeVector(tslot_vert_3_posX, tslot_vert_3_posY, tslot_vert_3_posZ), tslot_vert_3_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_vert_4";
    G4Box* tslot_vert_4 = new G4Box(name, tslot_width/2, tslot_width/2, tslot_length_z/2.0);
    G4LogicalVolume* tslot_vert_4_LV = new G4LogicalVolume(tslot_vert_4, tslot_material, name);
    new G4PVPlacement(tslot_vert_4_rm, G4ThreeVector(tslot_vert_4_posX, tslot_vert_4_posY, tslot_vert_4_posZ), tslot_vert_4_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_hor_1";
    G4Box* tslot_hor_1 = new G4Box(name, tslot_width/2, (tslot_length_xy+tslot_width)/2, tslot_width/2.0);
    G4LogicalVolume* tslot_hor_1_LV = new G4LogicalVolume(tslot_hor_1, tslot_material, name);
    new G4PVPlacement(tslot_hor_1_rm, G4ThreeVector(tslot_hor_1_posX, tslot_hor_1_posY, tslot_hor_1_posZ), tslot_hor_1_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_hor_2";
    G4Box* tslot_hor_2 = new G4Box(name, tslot_width/2, (tslot_length_xy+tslot_width)/2, tslot_width/2.0);
    G4LogicalVolume* tslot_hor_2_LV = new G4LogicalVolume(tslot_hor_2, tslot_material, name);
    new G4PVPlacement(tslot_hor_2_rm, G4ThreeVector(tslot_hor_2_posX, tslot_hor_2_posY, tslot_hor_2_posZ), tslot_hor_2_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_hor_3";
    G4Box* tslot_hor_3 = new G4Box(name, tslot_length_xy/2 - tslot_width/2, tslot_width/2, tslot_width/2.0);
    G4LogicalVolume* tslot_hor_3_LV = new G4LogicalVolume(tslot_hor_3, tslot_material, name);
    new G4PVPlacement(tslot_hor_3_rm, G4ThreeVector(tslot_hor_3_posX, tslot_hor_3_posY, tslot_hor_3_posZ), tslot_hor_3_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_hor_4";
    G4Box* tslot_hor_4 = new G4Box(name, tslot_length_xy/2 - tslot_width/2, tslot_width/2, tslot_width/2.0);
    G4LogicalVolume* tslot_hor_4_LV = new G4LogicalVolume(tslot_hor_4, tslot_material, name);
    new G4PVPlacement(tslot_hor_4_rm, G4ThreeVector(tslot_hor_4_posX, tslot_hor_4_posY, tslot_hor_4_posZ), tslot_hor_4_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_hor_5";
    G4Box* tslot_hor_5 = new G4Box(name, tslot_width/2, (tslot_length_xy+tslot_width)/2, tslot_width/2.0);
    G4LogicalVolume* tslot_hor_5_LV = new G4LogicalVolume(tslot_hor_5, tslot_material, name);
    new G4PVPlacement(tslot_hor_5_rm, G4ThreeVector(tslot_hor_5_posX, tslot_hor_5_posY, tslot_hor_5_posZ), tslot_hor_5_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_hor_6";
    G4Box* tslot_hor_6 = new G4Box(name, tslot_width/2, (tslot_length_xy+tslot_width)/2, tslot_width/2.0);
    G4LogicalVolume* tslot_hor_6_LV = new G4LogicalVolume(tslot_hor_6, tslot_material, name);
    new G4PVPlacement(tslot_hor_6_rm, G4ThreeVector(tslot_hor_6_posX, tslot_hor_6_posY, tslot_hor_6_posZ), tslot_hor_6_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_hor_7";
    G4Box* tslot_hor_7 = new G4Box(name, cryo_vacuum_outer_rMax, tslot_width/2, tslot_width/2.0);
    G4LogicalVolume* tslot_hor_7_LV = new G4LogicalVolume(tslot_hor_7, tslot_material, name);
    new G4PVPlacement(tslot_hor_7_rm, G4ThreeVector(tslot_hor_7_posX, tslot_hor_7_posY, tslot_hor_7_posZ), tslot_hor_7_LV, name, WorldLV, false, 0, fCheckOverlaps);

    name = "tslot_hor_8";
    G4Box* tslot_hor_8 = new G4Box(name, cryo_vacuum_outer_rMax, tslot_width/2, tslot_width/2.0);
    G4LogicalVolume* tslot_hor_8_LV = new G4LogicalVolume(tslot_hor_8, tslot_material, name);
    new G4PVPlacement(tslot_hor_8_rm, G4ThreeVector(tslot_hor_8_posX, tslot_hor_8_posY, tslot_hor_8_posZ), tslot_hor_8_LV, name, WorldLV, false, 0, fCheckOverlaps);

    G4VisAttributes* helium_vis = new G4VisAttributes(G4Colour(0.0,0.0,1.0,0.75));
    G4VisAttributes* nitrogen_vis = new G4VisAttributes(G4Colour(0.0,1.0,1.0,0.75));
    G4VisAttributes* container_vis = new G4VisAttributes(G4Colour(0.5,0.5,0.5,0.75));
    container_vis->SetVisibility(true);

    //===============  Visualization ===============//

    G4VisAttributes* yellowTVA = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.5));
    G4VisAttributes* redTVA = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.5));
    G4VisAttributes* greenTVA = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.5));
    G4VisAttributes* greyTVA = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.25));
    G4VisAttributes* blueTVA = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.5));

    // Room
    WorldLV->SetVisAttributes(G4VisAttributes::Invisible);
    z_wall_LV->SetVisAttributes(yellowTVA);
    x_wall_short_LV->SetVisAttributes(yellowTVA);
    x_wall_long_LV->SetVisAttributes(yellowTVA);
    y_wall_left_LV->SetVisAttributes(yellowTVA);
    y_wall_right_LV->SetVisAttributes(yellowTVA);
    x_wall_adj_door_LV->SetVisAttributes(yellowTVA);
    cupboard_LV->SetVisAttributes(redTVA);
    pump_room_LV->SetVisAttributes(redTVA);
    platform_pillar_LV->SetVisAttributes(greenTVA);
    platform_LV->SetVisAttributes(greenTVA);
    soil_space_LV->SetVisAttributes(greyTVA);

    // Cryostat
    can_sample_inner_LV->SetVisAttributes(helium_vis);
    can_4k_inner_LV->SetVisAttributes(G4VisAttributes::Invisible);
    can_77k_inner_LV->SetVisAttributes(G4VisAttributes::Invisible);
    can_vacuum_inner_LV->SetVisAttributes(G4VisAttributes::Invisible);
    cryo_vacuum_inner_LV->SetVisAttributes(G4VisAttributes::Invisible);
    cryo_77k_inner_LV->SetVisAttributes(G4VisAttributes::Invisible);
    cryo_4k_inner_LV->SetVisAttributes(helium_vis);

    can_sample_outer_LV->SetVisAttributes(container_vis);
    can_4k_outer_LV->SetVisAttributes(container_vis);
    can_77k_outer_LV->SetVisAttributes(container_vis);
    can_vacuum_outer_LV->SetVisAttributes(container_vis);
    arm_vacuum_LV->SetVisAttributes(container_vis);
    arm_77k_LV->SetVisAttributes(container_vis);
    arm_4k_LV->SetVisAttributes(container_vis);
    cryo_vacuum_outer_LV->SetVisAttributes(container_vis);
    cryo_77k_outer_LV->SetVisAttributes(container_vis);
    cryo_nitrogen_LV->SetVisAttributes(nitrogen_vis);
    cryo_4k_outer_LV->SetVisAttributes(container_vis);

    // T-slot frame
    tslot_vert_1_LV->SetVisAttributes(container_vis);
    tslot_vert_2_LV->SetVisAttributes(container_vis);
    tslot_vert_3_LV->SetVisAttributes(container_vis);
    tslot_vert_4_LV->SetVisAttributes(container_vis);

    tslot_hor_1_LV->SetVisAttributes(container_vis);
    tslot_hor_2_LV->SetVisAttributes(container_vis);
    tslot_hor_3_LV->SetVisAttributes(container_vis);
    tslot_hor_4_LV->SetVisAttributes(container_vis);
    tslot_hor_5_LV->SetVisAttributes(container_vis);
    tslot_hor_6_LV->SetVisAttributes(container_vis);
    tslot_hor_7_LV->SetVisAttributes(container_vis);
    tslot_hor_8_LV->SetVisAttributes(container_vis);

    //This is the dose sampling tool
    G4double dose_box_xyz = 250.*mm;
    G4double dose_box_x_pos = 31.75*mm;
    G4double dose_box_y_pos = 1720.80*mm;
    G4double dose_box_z_pos = -745.0*mm;
    G4Box* dose_box = new G4Box("dose_box", dose_box_xyz/2, dose_box_xyz/2, dose_box_xyz/2);
    dose_box_LV = new G4LogicalVolume(dose_box, dose_box_material, "dose_box_LV");
    dose_box_PV = new G4PVPlacement(0, G4ThreeVector(dose_box_x_pos,dose_box_y_pos,dose_box_z_pos), dose_box_LV, "dose_box_PV", WorldLV, false, 0);
    dose_box_LV->SetVisAttributes(blueTVA);

    /*dose_box_LV = G4tgbVolumeMgr::GetInstance()->FindG4LogVol("dose_box", 1);
    dose_box_PV = G4tgbVolumeMgr::GetInstance()->FindG4PhysVol("dose_box", 1);*/

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
