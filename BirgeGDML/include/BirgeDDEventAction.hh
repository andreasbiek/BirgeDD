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
// $Id: BirgeDDEventAction.hh $
// 
/// \file BirgeDDEventAction.hh
/// \brief Definition of the BirgeDDEventAction class

#ifndef BirgeDDEventAction_h
#define BirgeDDEventAction_h 1

#include "G4UserEventAction.hh"
#include "BirgeDDRunAction.hh"
#include "globals.hh"

/// Event action class
///
/// In EndOfEventAction(), it prints the accumulated quantities of the energy 
/// deposit and track lengths of charged particles in Absober and Gap layers 
/// stored in the hits collections.

class BirgeDDEventAction : public G4UserEventAction
{
  public:
    BirgeDDEventAction(BirgeDDRunAction* runAction);
    virtual ~BirgeDDEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);

    void AddDose(G4double de);
    
  private:
    // methods
    void PrintEventStatistics(G4double Edep) const;
  
    // data members
    BirgeDDRunAction* fRunAction;               
    G4double fEnergyDep;
};

// inline functions

inline void BirgeDDEventAction::AddDose(G4double de) {
  fEnergyDep += de; 
}
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
