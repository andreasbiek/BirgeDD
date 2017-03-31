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
// $Id: BirgeDD.cc $
//
/// \file BirgeDD.cc
/// \brief Main program of the BirgeDD example

//#include "BirgeDDDetectorConstruction.hh"
#include "GDMLDetectorConstruction.hh"
#include "BirgeDDActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "QGSP_BIC_HP.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "G4GDMLParser.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " BirgeDD [-m macro ] [-u UIsession] [-t nThreads]" << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode."
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
   G4cout << G4endl;
   G4cout << "Usage: gdml_det <intput_gdml_file:mandatory>"
          << G4endl;
   G4cout << G4endl;

   if (argc<2)
   {
      G4cout << "Error! Mandatory input file is not specified!" << G4endl;
      G4cout << G4endl;
      return -1;
   }

   // Detect interactive mode (if only one argument) and define UI session
   //
   G4UIExecutive* ui = 0;
   if ( argc == 2 ) {
     ui = new G4UIExecutive(argc, argv);
   }

   G4GDMLParser parser;
   parser.Read(argv[1]);

  // Choose the Random engine
  //
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager * runManager = new G4MTRunManager;
  if ( nThreads > 0 ) { 
    runManager->SetNumberOfThreads(nThreads);
  }  
#else
  G4RunManager * runManager = new G4RunManager;
#endif

/*  // Read detector construction from GDML file
  G4GDMLParser parser;
  parser.Read("g4test2.gdml",false);*/

  // Set mandatory initialization classes
  //
  GDMLDetectorConstruction* detConstruction = new GDMLDetectorConstruction(parser.GetWorldVolume());
  runManager->SetUserInitialization(detConstruction);

  G4VModularPhysicsList* physicsList = new QGSP_BIC_HP;
  runManager->SetUserInitialization(physicsList);
    
  BirgeDDActionInitialization* actionInitialization
     = new BirgeDDActionInitialization(detConstruction);
  runManager->SetUserInitialization(actionInitialization);
  
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
if ( ! ui )   // batch mode  
   {
     G4String command = "/control/execute ";
     G4String fileName = argv[2];
     UImanager->ApplyCommand(command+fileName);
   }
   else           // interactive mode
   {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    if (ui->IsGUI()) {
      UImanager->ApplyCommand("/control/execute gui.mac");
    }
    ui->SessionStart();
     delete ui;
   }

/*  // Write geometry to GDML file
  G4VPhysicalVolume* pWorld = G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking()->GetWorldVolume();

  G4GDMLParser parser;
  parser.Write("g4test.gdml", pWorld);*/

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !

  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
