#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"

int main(int argc, char** argv)
{
    auto* ui = new G4UIExecutive(argc, argv);

    auto* runManager = new G4RunManager();

    runManager->SetUserInitialization(
        new DetectorConstruction()
    );

    G4PhysListFactory factory;
    auto* physics = factory.GetReferencePhysList("FTFP_BERT_HP");

    runManager->SetUserInitialization(physics);

    runManager->SetUserAction(
        new PrimaryGeneratorAction()
    );

    runManager->SetUserAction(
        new SteppingAction()
    );

    runManager->Initialize();

    auto* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager::GetUIpointer()->ApplyCommand(
        "/control/execute vis.mac"
    );

    ui->SessionStart();

    delete visManager;
    delete runManager;
    delete ui;

    return 0;
}
