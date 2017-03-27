#include "G4Material.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "OxCryoMaterials.hh"

OxCryoMaterials* OxCryoMaterials::fInstance = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OxCryoMaterials::OxCryoMaterials()
{
    fNistMan = G4NistManager::Instance();
    CreateMaterials();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OxCryoMaterials::~OxCryoMaterials()
{
    delete Shap_powder;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OxCryoMaterials* OxCryoMaterials::GetInstance()
{
    if (fInstance == 0)
    {
        fInstance = new OxCryoMaterials();
    }
    return fInstance;
}

G4Material* OxCryoMaterials::GetMaterial(const G4String material)
{
    G4Material* mat =  fNistMan->FindOrBuildMaterial(material);
    
    if (!mat) mat = G4Material::GetMaterial(material);
    if (!mat) {
        std::ostringstream o;
        o << "Material " << material << " not found!";
        G4Exception("WLSMaterials::GetMaterial","",
                    FatalException,o.str().c_str());
    }
    
    return mat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OxCryoMaterials::CreateMaterials()
{
    
    G4double density;
    std::vector<G4int> natoms;
    std::vector<G4double> fractionMass;
    std::vector<G4String> elements;

    // vacuum
    G4Material* Vacuum = fNistMan->FindOrBuildMaterial("G4_Galactic");
    Vacuum->SetName("Vacuum");
    
    // air
    G4Material* Air = fNistMan->FindOrBuildMaterial("G4_AIR");
    Air->SetName("Air");
    
    //lead for shielding
    G4Material* lead = fNistMan->FindOrBuildMaterial("G4_Pb");
    lead->SetName("Lead");

    //copper for shielding and OxCryo holder
    G4Material* copper = fNistMan->FindOrBuildMaterial("G4_Cu");
    copper->SetName("Copper");

    //Germanium for crystal and dead layer
    G4Material* germanium = fNistMan->FindOrBuildMaterial("G4_Ge");
    germanium->SetName("Germanium");
    
    //Aluminium for cap
    G4Material* aluminium = fNistMan->FindOrBuildMaterial("G4_Al");
    aluminium->SetName("Aluminium");

    // glass
    G4Material* glass = fNistMan->FindOrBuildMaterial("G4_GLASS_PLATE");
    glass->SetName("Glass");
    
    //polyethylene
    G4Material* poly = fNistMan->FindOrBuildMaterial("G4_POLYETHYLENE");
    poly->SetName("Polyethylene");
    
    //plexiglass
    G4Material* plex = fNistMan->FindOrBuildMaterial("G4_PLEXIGLASS");
    plex->SetName("Plexiglass");
    
    //titanium
    G4Material* titanium = fNistMan->FindOrBuildMaterial("G4_Ti");
    titanium->SetName("Titanium");

    //PVC
    G4Material* pvc = fNistMan->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
    pvc->SetName("PVC");

    // quartz
    G4Material* quartz = fNistMan->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    quartz->SetName("Quartz");
    
    //teflon
    G4Material* teflon = fNistMan->FindOrBuildMaterial("G4_TEFLON");
    teflon->SetName("Teflon");
    
    //brass
    G4Material* brass = fNistMan->FindOrBuildMaterial("G4_BRASS");
    brass->SetName("Brass");

    //stainless
    G4Material* stainless = fNistMan->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    stainless->SetName("Stainless");

    //viton
    G4Material* viton = fNistMan->FindOrBuildMaterial("G4_VITON");
    viton->SetName("Viton");
    
    //kapton
    G4Material* kapton = fNistMan->FindOrBuildMaterial("G4_KAPTON");
    kapton->SetName("Kapton");
    
    //CaWo4 - Calcium Tungstate
    G4Material* CaWo4 = fNistMan->FindOrBuildMaterial("G4_CALCIUM_TUNGSTATE");
    CaWo4->SetName("CaWO4");

    //Al203 - Aluminium Oxide
    G4Material* Al2O3 = fNistMan->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
    Al2O3->SetName("Al2O3");
    
    //Nylon
    G4Material* nylon = fNistMan->FindOrBuildMaterial("G4_NYLON-8062");
    nylon->SetName("Nylon");

    //Silicon
    G4Material* Si = fNistMan->FindOrBuildMaterial("G4_Si");
    Si->SetName("Silicon");

    //kovar - FerNiCo I
    elements.push_back("Fe");     fractionMass.push_back(0.55);
    elements.push_back("Ni");     fractionMass.push_back(0.29);
    elements.push_back("Co");     fractionMass.push_back(0.16);
    density = 8.0*g/cm3;
    kovar = fNistMan->ConstructNewMaterial("Kovar", elements, fractionMass, density);
    elements.clear();
    fractionMass.clear();
    
    //Stainless Steel 304
    elements.push_back("Fe");     fractionMass.push_back(0.718);
    elements.push_back("C");      fractionMass.push_back(0.001);
    elements.push_back("Si");     fractionMass.push_back(0.005);
    elements.push_back("Mn");     fractionMass.push_back(0.007);
    elements.push_back("Ni");     fractionMass.push_back(0.086);
    elements.push_back("Cr");     fractionMass.push_back(0.183);
    density = 8.0*g/cm3;
    stainless_steel_304 = fNistMan->ConstructNewMaterial("Stainless_steel_304", elements, fractionMass, density);
    elements.clear();
    fractionMass.clear();
    
    //Borosilicate galss
     elements.push_back("B");     fractionMass.push_back(0.040064);
    elements.push_back("O");      fractionMass.push_back(0.53956);
    elements.push_back("Na");     fractionMass.push_back(0.028191);
    elements.push_back("Al");     fractionMass.push_back(0.011644);
    elements.push_back("Si");     fractionMass.push_back(0.377220);
    elements.push_back("K");     fractionMass.push_back(0.003321);
    density = 2.23*g/cm3;
    borosilicate_glass = fNistMan->ConstructNewMaterial("Borosilicate_glass", elements, fractionMass, density);
    elements.clear();
    fractionMass.clear();
    
    //calcium molybdate - CaMoO4
    elements.push_back("Ca");     fractionMass.push_back(0.2004);
    elements.push_back("Mo");     fractionMass.push_back(0.4797);
    elements.push_back("O");      fractionMass.push_back(0.3200);
    density = 4.26*g/cm3;
    CaMoO4 = fNistMan->ConstructNewMaterial("CaMoO4",elements,fractionMass,density);
    elements.clear();
    fractionMass.clear();

    //Carbon Fibre for endcap
    elements.push_back("C");     natoms.push_back(1);
    density = 1.42*g/cm3;
    Cf = fNistMan->ConstructNewMaterial("CarbonFibre", elements, natoms, density);
    elements.clear();
    natoms.clear();
    
    elements.push_back("Si");     natoms.push_back(1);
    elements.push_back("O");     natoms.push_back(2);
    density = 2.2*g/cm3;
    synthetic_silica = fNistMan->ConstructNewMaterial("Synthetic_silica", elements, natoms, density);
    elements.clear();
    natoms.clear();
    
    //soil
    elements.push_back("H");     fractionMass.push_back(0.021);
    elements.push_back("C");     fractionMass.push_back(0.016);
    elements.push_back("O");     fractionMass.push_back(0.577);
    elements.push_back("Al");     fractionMass.push_back(0.050);
    elements.push_back("Si");     fractionMass.push_back(0.271);
    elements.push_back("K");     fractionMass.push_back(0.013);
    elements.push_back("Ca");     fractionMass.push_back(0.041);
    elements.push_back("Fe");     fractionMass.push_back(0.011);
    density = 1.50*g/cm3;
    soil = fNistMan->ConstructNewMaterial("Soil", elements, fractionMass, density);
    elements.clear();
    fractionMass.clear();
    
    //Aluminium alloy 6061-T6
    elements.push_back("Al");     fractionMass.push_back(0.980);
    elements.push_back("Mg");     fractionMass.push_back(0.010);
    elements.push_back("Si");     fractionMass.push_back(0.006);
    elements.push_back("Fe");     fractionMass.push_back(0.004);
    density = 2.70*g/cm3;
    al6061 = fNistMan->ConstructNewMaterial("Al6061", elements, fractionMass, density);
    elements.clear();
    fractionMass.clear();
    
    
    //wood
    elements.push_back("H");     natoms.push_back(4);
    elements.push_back("O");     natoms.push_back(1);
    elements.push_back("C");     natoms.push_back(2);
    density = 0.9*g/cm3;
    wood = fNistMan->ConstructNewMaterial("wood", elements, natoms, density);
    elements.clear();
    natoms.clear();
    
    
    //IAEA-385 powder
   /* elements.push_back("Si");     natoms.push_back(1);
    elements.push_back("O");     natoms.push_back(2);
    density = 1.5*g/cm3;
    IAEA_powder = fNistMan->ConstructNewMaterial("IAEA_Powder", elements, natoms, density);
    elements.clear();
    natoms.clear();
    
    //Shap powder
  elements.push_back("Si");     natoms.push_back(1);
    elements.push_back("O");     natoms.push_back(2);
    density = 0.64*g/cm3;
    Shap_powder = fNistMan->ConstructNewMaterial("Shap_Powder", elements, natoms, density);
    elements.clear();
    natoms.clear();
    
    //Pb210 powder
    elements.push_back("Si");     natoms.push_back(1);
    elements.push_back("O");     natoms.push_back(2);
    density = 0.97*g/cm3;
    Pb210_powder = fNistMan->ConstructNewMaterial("Pb210_Powder", elements, natoms, density);
    elements.clear();
    natoms.clear();
    
    //Pb210 powder
    elements.push_back("Si");     natoms.push_back(1);
    elements.push_back("O");     natoms.push_back(2);
    density = 0.97*g/cm3;
    MGS4_powder = fNistMan->ConstructNewMaterial("MGS4_Powder", elements, natoms, density);
    elements.clear();
    natoms.clear();*/
    
    //sand
    elements.push_back("Si");     natoms.push_back(1);
    elements.push_back("O");     natoms.push_back(2);
    density = 1.5 *g/cm3;
    sand = fNistMan->ConstructNewMaterial("Sand", elements, natoms, density);
    elements.clear();
    natoms.clear();
    
    //Ceramic
    elements.push_back("Al");     natoms.push_back(2);
    elements.push_back("O");     natoms.push_back(3);
    density = 2.88 *g/cm3;
    ceramic = fNistMan->ConstructNewMaterial("Ceramic", elements, natoms, density);
    elements.clear();
    natoms.clear();
    
    //Epoxy
    elements.push_back("H");     natoms.push_back(2);
    elements.push_back("C");     natoms.push_back(2);
    density = 1.2*g/cm3;
    epoxy = fNistMan->ConstructNewMaterial("Epoxy" , elements, natoms, density);
    
    //Dirt
//    elements.push_back("H");        fractionMass.push_back(0.004);
    elements.push_back("C");        natoms.push_back(2);
    elements.push_back("O");        natoms.push_back(50);
    elements.push_back("Na");       natoms.push_back(1);
    elements.push_back("Mg");       natoms.push_back(2);
    elements.push_back("Al");       natoms.push_back(7);
    elements.push_back("Si");       natoms.push_back(27);
    elements.push_back("K");        natoms.push_back(2);
    elements.push_back("Ca");       natoms.push_back(4);
//    elements.push_back("Ti");       fractionMass.push_back(0.004);
    elements.push_back("Fe");       natoms.push_back(4);

    density = 1.5*g/cm3;
    dirt = fNistMan->ConstructNewMaterial("Dirt",elements,natoms,density);
    elements.clear();
    natoms.clear();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
