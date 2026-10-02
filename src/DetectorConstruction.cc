#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

namespace B1
{

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();

  G4Material* melanin = new G4Material("Melanin", 1.5*g/cm3, 4);
  melanin->AddElement(nist->FindOrBuildElement("C"), 0.5245);
  melanin->AddElement(nist->FindOrBuildElement("H"), 0.0340);
  melanin->AddElement(nist->FindOrBuildElement("N"), 0.0788);
  melanin->AddElement(nist->FindOrBuildElement("O"), 0.3627);

  G4Material* aluminium = nist->FindOrBuildMaterial("G4_Al");
  G4Material* polyeth   = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* vacuum    = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* water     = nist->FindOrBuildMaterial("G4_WATER");

  // ===== HER KOSUDA SADECE BU SATIRI DEGISTIR =====
  G4Material* shieldMat = polyeth;   // melanin / aluminium / polyeth
  // ================================================

  G4double arealDensity = 20.0*g/cm2;
  G4double shieldThick  = arealDensity / shieldMat->GetDensity();

  G4double shieldSide   = 40*cm;
  G4double phantomSide  = 30*cm;
  G4double phantomThick = 30*cm;
  G4double worldSize    = 100*cm;

  G4cout << "=== KALKAN: " << shieldMat->GetName()
         << " | yogunluk " << shieldMat->GetDensity()/(g/cm3) << " g/cm3"
         << " | kalinlik " << shieldThick/cm << " cm"
         << " | alansal " << arealDensity/(g/cm2) << " g/cm2"
         << " ===" << G4endl;

  G4Box* solidWorld = new G4Box("World", 0.5*worldSize, 0.5*worldSize, 0.5*worldSize);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, vacuum, "World");
  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World",
                      nullptr, false, 0, true);

  G4Box* solidShield = new G4Box("Shield", 0.5*shieldSide, 0.5*shieldSide, 0.5*shieldThick);
  G4LogicalVolume* logicShield = new G4LogicalVolume(solidShield, shieldMat, "Shield");
  new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicShield, "Shield",
                    logicWorld, false, 0, true);

  G4double phantomZ = 0.5*shieldThick + 0.5*phantomThick;
  G4Box* solidPhantom = new G4Box("Phantom", 0.5*phantomSide, 0.5*phantomSide, 0.5*phantomThick);
  G4LogicalVolume* logicPhantom = new G4LogicalVolume(solidPhantom, water, "Phantom");
  new G4PVPlacement(nullptr, G4ThreeVector(0,0,phantomZ), logicPhantom, "Phantom",
                    logicWorld, false, 0, true);

  fScoringVolume = logicPhantom;

  return physWorld;
}

}
