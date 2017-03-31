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
// $Id: BirgeDDActionInitialization.cc $
//
/// \file BirgeDDActionInitialization.cc
/// \brief Implementation of the BirgeDDActionInitialization class

#include "BirgeDDActionInitialization.hh"
#include "BirgeDDPrimaryGeneratorAction.hh"
#include "BirgeDDRunAction.hh"
#include "BirgeDDEventAction.hh"
#include "BirgeDDSteppingAction.hh"
#include "BirgeDDDetectorConstruction.hh"
//#include "GDMLDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BirgeDDActionInitialization::BirgeDDActionInitialization
							(BirgeDDDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
 fDetConstruction(detConstruction)
{}

/*//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BirgeDDActionInitialization::BirgeDDActionInitialization
							(GDMLDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
 fDetConstruction(detConstruction)
{}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BirgeDDActionInitialization::~BirgeDDActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BirgeDDActionInitialization::BuildForMaster() const
{
  SetUserAction(new BirgeDDRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BirgeDDActionInitialization::Build() const
{
  SetUserAction(new BirgeDDPrimaryGeneratorAction);
  
  BirgeDDRunAction* runAction = new BirgeDDRunAction;
  SetUserAction(runAction);
  
  BirgeDDEventAction* eventAction = new BirgeDDEventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new BirgeDDSteppingAction(fDetConstruction, eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
