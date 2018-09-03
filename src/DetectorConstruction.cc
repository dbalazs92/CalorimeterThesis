/**
 * @file /EMCal_MT/src/DetectorConstruction.cc
 * @author Balázs Demeter <balazsdemeter92@gmail.com>
 * @date 2017/09/15 <creation>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of EMcal's Detector construction source code to define materials and geometry. 
 * Latest updates of project can be found in README file.
 **/

#include "DetectorConstruction.hh"
#include "G4SubtractionSolid.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"


/// @brief Constructor of Detector construction

DetectorConstruction::DetectorConstruction(G4int fiber)
: G4VUserDetectorConstruction(), fFiber(fiber)
{}

/// @brief Destructor of Detector construction

DetectorConstruction::~DetectorConstruction()
{ }

/**
 * @brief Construct function to built objects and frame of reference
 * 
 * @return	Placement of world
 * 
 **/

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4double a, z, density_pmma, density_ps, pos=18, r = (0.47/2)*mm; /// Useable constants and variables (radius, density and etc.)
  G4int nelements;

  G4double tank_sizeXY = 0.87*mm, tank_sizeZ = 12.6*cm; /// Size of Tank

  G4NistManager* nist = G4NistManager::Instance(); /// Get nist material manager

  G4bool checkOverlaps = false; /// Option to switch on/off checking of volumes overlaps

  G4Element* C = new G4Element("Carbon", "C", z=6 , a=12.01*g/mole); /// definition of elements for materials
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

/**
  * ... Frame of reference ...
  *
  * @param world_sizeXY		Size of world in meter (x,y axis)
  * @param world_sizeZ		Size of world in meter (z axis)
  * @param world_mat		Saterial of world
  * @param solidWorld		Geometry of world
  * @param logicWorld		Logical volume of world
  * @param physWorld		Placement of world
  *
  **/

  G4double world_sizeXY = 1.2*m, world_sizeZ  = 1.2*m;
  G4Box* solidWorld = new G4Box("World", world_sizeXY, world_sizeXY, world_sizeZ);

  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);

/**
  * ... Tank ...
  *
  * @param tank_sizeX		Size of tank in meter (x axis)
  * @param tank_sizeY		Size of tank in meter (y axis)
  * @param tank_sizeZ		Size of tank in meter (z axis)
  * @param posTank			Position of tank in world
  * @param tank_mat			Material of tank
  * @param solidTank		Geometry of tank (full)
  * @param subTank			Geometry of tank (after subtraction)
  * @param logicTank		Logical volume of tank
  * @param tankColour		Color of tank
  * @param tankVisAtt		Visual attributes of tank
  *
  **/

    G4ThreeVector posTank = G4ThreeVector(0, 0*cm, pos*cm);

    G4Box* solidTank = new G4Box("Tank", (fFiber)*(tank_sizeXY/2), (fFiber)*(tank_sizeXY/2), tank_sizeZ);
    //G4Tubs* solidTank = new G4Tubs("Tank", 0*cm, 18*cm, tank_sizeZ, 0*deg, 360*deg);

    G4Material* tank_mat = nist->FindOrBuildMaterial("G4_W");

    G4LogicalVolume* logicTank = new G4LogicalVolume(solidTank, tank_mat, "Tank");

    G4Colour tankColour( 0.0, 1.0, 0.0, 0.4 );
    G4VisAttributes* tankVisAtt = new G4VisAttributes( tankColour );
    logicTank->SetVisAttributes(tankVisAtt);



/**
  *
  * ... Fiber ...
  *
  * @param r 				 Radius of fiber in milimeter
  * @param posFiber 		 Position of fiber in world
  * @param fiberInterior 	 Geometry of fiber's interior
  * @param fiberCover 		 Geometry of fiber's cover
  * @param fiberFull		 Geometry of complete fiber (for subtraction)
  * @param pmma				 PMMA (Material of fiber's cover)
  * @param ps				 Polystyrene (Material of fiber's interior)
  * @param fiberInteriorLog	 Logical volume of fiber's interior
  * @param fiberCoverLog	 Logical volume of fiber's cover
  * @param fiberColour		 Color of fiber
  * @param fiberVisAtt		 Visual attributes of tank
  * @param interiorPhysVol   Physical volume of fiber's interior
  *
  **/

  G4ThreeVector posFiber = posTank;
  G4Tubs* fiberInterior  = new G4Tubs("fInterior", 0*cm, (r-(r*0.02)), tank_sizeZ, 0*deg, 360*deg);
  G4Tubs* fiberCover 	 = new G4Tubs("fCover", (r-(r*0.02)), r, tank_sizeZ, 0*deg, 360*deg);


  G4Material* pmma = new G4Material("PMMA", density_pmma = 1.190*g/cm3, nelements=3);
  pmma->AddElement(C, 33.34*perCent);
  pmma->AddElement(H, 53.33*perCent);
  pmma->AddElement(O, 13.33*perCent);

  G4Material* polyStyrene = nist->FindOrBuildMaterial("G4_POLYSTYRENE");

  G4LogicalVolume* fiberInteriorLog = new G4LogicalVolume(fiberInterior, polyStyrene, "fiberInterior");
  G4LogicalVolume* fiberCoverLog = new G4LogicalVolume(fiberCover, pmma, "fiberCover");

  G4Colour fiberColour( 1.0, 0.0, 0.0, 1.0 );
  G4VisAttributes* fiberVisAtt = new G4VisAttributes( fiberColour );
  fiberInteriorLog->SetVisAttributes(fiberVisAtt);
  fiberCoverLog->SetVisAttributes(fiberVisAtt);
  
  G4VPhysicalVolume* fiberCover_phys;
  G4VPhysicalVolume* fiberInterior_phys;
  G4VPhysicalVolume* Tank_phys;
  Tank_phys=new G4PVPlacement(0, posTank, logicTank, "Tank", logicWorld, false, 0, checkOverlaps);
   for(int i=0;i<fFiber;i++)
    {
        for(int j=0;j<fFiber;j++)
        {
			
        fiberCover_phys=new G4PVPlacement(0,
                          G4ThreeVector((i*tank_sizeXY)-((fFiber-1)*(tank_sizeXY/2)), (j*tank_sizeXY)-((fFiber-1)*(tank_sizeXY/2)), 0*cm),
                          fiberCoverLog, "fiberCover", logicTank,
                          false, 0, checkOverlaps);
        fiberInterior_phys=new G4PVPlacement(0,
                          G4ThreeVector((i*tank_sizeXY)-((fFiber-1)*(tank_sizeXY/2)), (j*tank_sizeXY)-((fFiber-1)*(tank_sizeXY/2)), 0*cm), // fent is lent is pos*cm
                          fiberInteriorLog, "fiberInterior",
                          logicTank, false, 0, checkOverlaps);
        
        }
    }
/**
  * ... Detector ...
  *
  * @param detec_sizeZ		Size of detector in meter (z axis)
  * @param posDetec			Position of detector in world
  * @param detec_mat		Material of detector
  * @param solidDetec		Geometry of detector (full)
  * @param subDetec			Geometry of detector (after subtraction)
  * @param logicDetec		Logical volume of detector
  * @param detecColour		Color of detector
  * @param detecVisAtt		Visual attributes of detector
  *
  **/
  
  G4double detec_sizeZ = 1*mm;
  G4Box* solidDetec = new G4Box("Detector", (fFiber)*(tank_sizeXY/2), (fFiber)*(tank_sizeXY/2), detec_sizeZ);
  G4ThreeVector posDetec =G4ThreeVector(0, 0*cm, ((pos*cm)+(tank_sizeZ)+(detec_sizeZ))); ///zpos+(fTank_z)+(mirror_z)

  G4Material* detec_mat = nist->FindOrBuildMaterial("G4_Pyrex_Glass");

  G4LogicalVolume* logicDetec = new G4LogicalVolume(solidDetec, detec_mat, "Detector");

  G4Colour detColour( 1.0, 1.0, 1.0, 1.0 );
  G4VisAttributes* detVisAtt = new G4VisAttributes(detColour);
  logicDetec->SetVisAttributes(detVisAtt);

  G4VPhysicalVolume* Detector_phys = new G4PVPlacement(0,posDetec, logicDetec, "Detector", logicWorld, false, 0, checkOverlaps);
  
  /// optical database
  
  G4double photonEnergy[] = { 2.00*eV, 2.44*eV, 2.88*eV, 3.31*eV, 3.75*eV, 4.19*eV, 4.63*eV, 5.06*eV };

  const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);
  
  G4double rIps[] = { 1.59, 1.60, 1.61, 1.62, 1.63, 1.64, 1.65, 1.66};
  G4double refFiberInterior[] = {0.05, 0.55, 0.06, 0.65, 0.07, 0.08, 0.09, 0.1};
  G4double absPS[]={2.*cm, 2.05*cm, 2.1*cm, 2.15*cm, 2.2*cm, 2.25*cm, 2.3*cm, 2.35*cm};
  G4double scFastPS[]={0.00, 0.10, 0.14, 0.18, 0.92, 0.98, 1.00, 1.00};
  G4double effPS[]={1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};

  G4MaterialPropertiesTable* mptPS = new G4MaterialPropertiesTable();
  mptPS->AddProperty("RINDEX", photonEnergy, rIps, nEntries);
  mptPS->AddProperty("REFLECTIVITY", photonEnergy, refFiberInterior, nEntries);
  mptPS->AddProperty("EFFICIENCY",photonEnergy,effPS,nEntries);
  mptPS->AddProperty("ABSLENGTH",photonEnergy,absPS, nEntries);
  mptPS->AddProperty("FASTCOMPONENT",photonEnergy, scFastPS, nEntries);
  mptPS->AddConstProperty("SCINTILLATIONYIELD",10./keV);
  mptPS->AddConstProperty("RESOLUTIONSCALE",1.0);
  mptPS->AddConstProperty("FASTTIMECONSTANT", 10.*ns);
  mptPS->AddConstProperty("YIELDRATIO",1.0);

  G4cout << "Polystyrene G4MaterialPropertiesTable" << G4endl;
  mptPS->DumpTable();

  polyStyrene->SetMaterialPropertiesTable(mptPS);
  polyStyrene->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
  
  G4double rIpmma[] = { 1.49, 1.495, 1.50, 1.505, 1.51, 1.515, 1.52, 1.525};
  G4double refFiberCover[] = {0.04, 0.45, 0.05, 0.55, 0.06, 0.07, 0.08, 0.09};

  G4MaterialPropertiesTable* mptPMMA = new G4MaterialPropertiesTable();
  mptPMMA->AddProperty("RINDEX", photonEnergy, rIpmma, nEntries);
  mptPMMA->AddProperty("REFLECTIVITY", photonEnergy, refFiberCover, nEntries);

  G4cout << "PMMA G4MaterialPropertiesTable" << G4endl;
  mptPMMA->DumpTable();

  pmma->SetMaterialPropertiesTable(mptPMMA);
  
  G4double rImirror[] = { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};
  G4double refMirror[] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};

  G4MaterialPropertiesTable* mptmirror = new G4MaterialPropertiesTable();
  mptmirror->AddProperty("RINDEX", photonEnergy, rImirror, nEntries);
  mptmirror->AddProperty("REFLECTIVITY", photonEnergy, refMirror, nEntries);

  G4cout << "mirror G4MaterialPropertiesTable" << G4endl;
  mptmirror->DumpTable();

  detec_mat->SetMaterialPropertiesTable(mptmirror);
  
  ///Surfaces
  
  G4OpticalSurface*  fiberInteriorSurface = new G4OpticalSurface("fiberInteriorOpticalSurface");
  fiberInteriorSurface->SetType(dielectric_dielectric);
  fiberInteriorSurface->SetFinish(polished);
  fiberInteriorSurface->SetModel(glisur);
  new G4LogicalSkinSurface("fiberInteriorSurface", fiberInteriorLog, fiberInteriorSurface);

  G4OpticalSurface*  fiberCoverSurface = new G4OpticalSurface("fiberCoverOpticalSurface");
  fiberCoverSurface->SetType(dielectric_dielectric);
  fiberCoverSurface->SetFinish(polishedbackpainted);
  fiberCoverSurface->SetModel(unified);
  new G4LogicalSkinSurface("fiberCoverSurface", fiberCoverLog, fiberCoverSurface);

  G4OpticalSurface*  TankSurface = new G4OpticalSurface("TankOpticalSurface");
  TankSurface->SetType(dielectric_metal);
  TankSurface->SetFinish(ground);
  TankSurface->SetModel(unified);
  new G4LogicalSkinSurface("TankSurface", logicTank, TankSurface);

  G4OpticalSurface*  MirrorSurface = new G4OpticalSurface("MirrorSurface");
  MirrorSurface->SetType(dielectric_metal);
  MirrorSurface->SetFinish(ground);
  MirrorSurface->SetModel(unified);
  new G4LogicalSkinSurface("MirrorSurface", logicDetec, MirrorSurface);

  return physWorld;

}

/// End of file
