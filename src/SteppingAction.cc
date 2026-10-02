#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include <map>
#include <fstream>

namespace B1
{

static std::map<G4String,int> gSayim;

SteppingAction::SteppingAction(EventAction* eventAction)
: fEventAction(eventAction)
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const auto detConstruction = static_cast<const DetectorConstruction*>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detConstruction->GetScoringVolume();
  }

  // --- Fantoma GIREN parcaciklari say ---
  const G4StepPoint* pre  = step->GetPreStepPoint();
  const G4StepPoint* post = step->GetPostStepPoint();

  if (post->GetStepStatus() == fGeomBoundary) {
    if (post->GetPhysicalVolume() &&
        post->GetPhysicalVolume()->GetName() == "Phantom" &&
        pre->GetPhysicalVolume() &&
        pre->GetPhysicalVolume()->GetName() != "Phantom") {
      G4String ad = step->GetTrack()->GetDefinition()->GetParticleName();
      gSayim[ad]++;
    }
  }

  // --- Doz toplama (eskisi gibi) ---
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  if (volume != fScoringVolume) return;

  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);
}

void SteppingAction::SayimYaz()
{
  std::ofstream f("parcacik_sayimi.txt");
  for (const auto& p : gSayim) f << p.first << " " << p.second << "\n";
  f.close();
  gSayim.clear();
}

}
