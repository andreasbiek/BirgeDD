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
// $Id: BirgeDDEventAction.cc 88427 2015-02-19 08:19:38Z gcosmo $
// 
/// \file BirgeDDEventAction.cc
/// \brief Implementation of the BirgeDDEventAction class

#include "BirgeDDEventAction.hh"
#include "BirgeDDRunAction.hh"
#include "BirgeDDAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BirgeDDEventAction::BirgeDDEventAction(BirgeDDRunAction* runAction)
 : G4UserEventAction(),
   fRunAction(runAction),
   fEnergyDep(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BirgeDDEventAction::~BirgeDDEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BirgeDDEventAction::PrintEventStatistics(G4double Edep) const
{
  // print event statistics
  G4cout
     << "    Absorber: total energy: " 
     << std::setw(7) << G4BestUnit(Edep, "Energy")
     /*<< "       total track length: " 
     << std::setw(7) << G4BestUnit(HeTrackLength, "Length")*/
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BirgeDDEventAction::BeginOfEventAction(const G4Event*)
{
  fEnergyDep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BirgeDDEventAction::EndOfEventAction(const G4Event* event)
{  
  // Fill histograms, ntuple
  //

  // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
  /*// fill histograms
  analysisManager->FillH1(1, fEnergyHe);
  analysisManager->FillH1(2, fEnergySci);
  analysisManager->FillH1(3, fTrackLHe);
  analysisManager->FillH1(4, fTrackLSci);*/
  
  // fill ntuple
  analysisManager->FillNtupleDColumn(0, fEnergyDep);
  analysisManager->AddNtupleRow();

  // accumulate energy for doing stats in run action
  fRunAction->AddEdep(fEnergyDep);

  // Print per event (modulo n)
  //
  G4int eventID = event->GetEventID();
  G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) {
    G4cout << "---> End of event: " << eventID << G4endl;     

    PrintEventStatistics(fEnergyDep);
  }  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
