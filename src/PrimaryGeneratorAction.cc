#include "PrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4Neutron.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);

    G4ParticleDefinition* neutron =
        G4Neutron::NeutronDefinition();

    fParticleGun->SetParticleDefinition(neutron);

    // Initial neutron energy: 1 MeV
    fParticleGun->SetParticleEnergy(1.0 * MeV);

    // Starting position: just before the B4C block
    fParticleGun->SetParticlePosition(
        G4ThreeVector(0.0, 0.0, -3.0 * cm)
    );

    // Direction: perpendicular to the B4C surface (+Z)
    fParticleGun->SetParticleMomentumDirection(
        G4ThreeVector(0.0, 0.0, 1.0)
    );
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fParticleGun->GeneratePrimaryVertex(event);
}
