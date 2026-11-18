#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"

SteppingAction::SteppingAction()
{
    outputFile.open("neutron_results.csv");
    outputFile << "Initial_Energy,Final_Energy,Energy_Loss,Hadronic_Interaction\n";
}

SteppingAction::~SteppingAction()
{
    if (outputFile.is_open())
        outputFile.close();
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4Track* track = step->GetTrack();

    if (track->GetDefinition()->GetParticleName() != "neutron")
        return;

    if (track->GetParentID() != 0)
        return;

    auto* preVolume =
        step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

    auto* postVolume =
        step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();

    if (!preVolume)
        return;

    G4bool enteringB4C =
        preVolume->GetLogicalVolume()->GetName() != "B4C_Logical" &&
        postVolume &&
        postVolume->GetLogicalVolume()->GetName() == "B4C_Logical";

    G4bool leavingB4C =
        preVolume->GetLogicalVolume()->GetName() == "B4C_Logical" &&
        (!postVolume ||
         postVolume->GetLogicalVolume()->GetName() != "B4C_Logical");

    if (enteringB4C)
    {
        initialEnergy = step->GetPostStepPoint()->GetKineticEnergy();
        hasCollided = false;
        recorded = false;
    }

    if (preVolume->GetLogicalVolume()->GetName() == "B4C_Logical")
    {
        auto* process = step->GetPostStepPoint()->GetProcessDefinedStep();

        if (process && process->GetProcessType() == fHadronic)
            hasCollided = true;
    }

    if (leavingB4C && !recorded)
    {
        G4double finalEnergy =
            step->GetPostStepPoint()->GetKineticEnergy();

        G4double energyLoss = initialEnergy - finalEnergy;

        outputFile
            << initialEnergy / MeV << ","
            << finalEnergy / MeV << ","
            << energyLoss / MeV << ","
            << (hasCollided ? "Yes" : "No")
            << "\n";

        recorded = true;
        track->SetTrackStatus(fStopAndKill);
    }
}
