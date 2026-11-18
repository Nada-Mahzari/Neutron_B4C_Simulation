
#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

DetectorConstruction::DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Get NIST material manager
    G4NistManager* nist = G4NistManager::Instance();

    // Define air
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

    // Define elements
    G4Element* boron = nist->FindOrBuildElement("B");
    G4Element* carbon = nist->FindOrBuildElement("C");

    // Define Boron Carbide (B4C)
    G4Material* B4C = new G4Material(
        "B4C",
        2.52 * g/cm3,
        2
    );

    B4C->AddElement(boron, 4);
    B4C->AddElement(carbon, 1);

    // Define World volume: 20 x 20 x 20 cm3
    G4Box* solidWorld = new G4Box(
        "World",
        10.0 * cm,
        10.0 * cm,
        10.0 * cm
    );

    G4LogicalVolume* logicWorld = new G4LogicalVolume(
        solidWorld,
        air,
        "World"
    );

    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        nullptr,
        G4ThreeVector(),
        logicWorld,
        "World",
        nullptr,
        false,
        0,
        true
    );

    // Define B4C block: 5 x 5 x 5 cm3
    G4Box* solidB4C = new G4Box(
        "B4C_Block",
        2.5 * cm,
        2.5 * cm,
        2.5 * cm
    );

    G4LogicalVolume* logicB4C = new G4LogicalVolume(
        solidB4C,
        B4C,
        "B4C_Logical"
    );

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, 0),
        logicB4C,
        "B4C_Physical",
        logicWorld,
        false,
        0,
        true
    );

    return physWorld;
}
