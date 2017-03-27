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
// $Id: BirgeDDRunAction.cc $
//
/// \file BirgeDDRunAction.cc
/// \brief Implementation of the BirgeDDRunAction class

#include "BirgeDDRunAction.hh"
#include "BirgeDDAnalysis.hh"
#include "BirgeDDDetectorConstruction.hh"
#include "BirgeDDPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BirgeDDRunAction::BirgeDDRunAction()
 : G4UserRunAction(),
 fEdep(0.),
 fEdep2(0.),
 nDeposits(0)
{ 
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in BirgeDDAnalysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Default Settings
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("BirgeDD");

  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);

  // Creating ntuple
  //
  analysisManager->CreateNtuple("BirgeDD", "Edep");
  analysisManager->CreateNtupleDColumn("Eabs");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BirgeDDRunAction::~BirgeDDRunAction()
{
  delete G4AnalysisManager::Instance();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BirgeDDRunAction::BeginOfRunAction(const G4Run*)
{
  
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BirgeDDRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  G4double rms = fEdep2 - fEdep*fEdep/nofEvents;
  if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;  

  const BirgeDDDetectorConstruction* detectorConstruction
   = static_cast<const BirgeDDDetectorConstruction*>
     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  G4double mass = detectorConstruction->GetMeterLV()->GetMass();
  G4double dose = fEdep/mass;
  G4double rmsDose = rms/mass;

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const BirgeDDPrimaryGeneratorAction* generatorAction
   = static_cast<const BirgeDDPrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  if (generatorAction)
  {
    const G4GeneralParticleSource* particleSource = generatorAction->GetParticleSource();
    runCondition += particleSource->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleSource->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
  }

  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "<< runCondition
     << G4endl
     << " Cumulated dose per run, in scoring volume : " 
     << G4BestUnit(dose,"Dose") << " rms = " << G4BestUnit(rmsDose,"Dose")
     << G4endl
     << " There were " << nDeposits << " events depositing energy in the sensitive volume"
     << G4endl
     << "------------------------------------------------------------"
     << G4endl
     << G4endl;

  // print histogram statistics
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  /*if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl; 
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl; 
    }
    
    G4cout << " EAbs : mean = " 
       << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy") 
       << " rms = " 
       << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Energy") << G4endl;
    
    G4cout << " Esci : mean = " 
       << G4BestUnit(analysisManager->GetH1(2)->mean(), "Energy") 
       << " rms = " 
       << G4BestUnit(analysisManager->GetH1(2)->rms(),  "Energy") << G4endl;
    
    G4cout << " LAbs : mean = " 
      << G4BestUnit(analysisManager->GetH1(2)->mean(), "Length") 
      << " rms = " 
      << G4BestUnit(analysisManager->GetH1(2)->rms(),  "Length") << G4endl;

    G4cout << " Lsci : mean = " 
      << G4BestUnit(analysisManager->GetH1(4)->mean(), "Length") 
      << " rms = " 
      << G4BestUnit(analysisManager->GetH1(4)->rms(),  "Length") << G4endl;
  }*/

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BirgeDDRunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
  if ( edep > 0 ) 
  {
    nDeposits += 1;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
