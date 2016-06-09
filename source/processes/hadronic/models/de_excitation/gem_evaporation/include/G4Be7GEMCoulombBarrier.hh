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
//
// $Id: G4Be7GEMCoulombBarrier.hh,v 1.3 2006/06/29 20:14:41 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Dec 1999)

#ifndef G4Be7GEMCoulombBarrier_h
#define G4Be7GEMCoulombBarrier_h 1

#include "G4GEMCoulombBarrierHE.hh"
#include "globals.hh"

class G4Be7GEMCoulombBarrier : public G4GEMCoulombBarrierHE
{
public:
  G4Be7GEMCoulombBarrier() : G4GEMCoulombBarrierHE(7,4) {};
  ~G4Be7GEMCoulombBarrier() {};

private:
  G4Be7GEMCoulombBarrier(const G4Be7GEMCoulombBarrier & right);

  const G4Be7GEMCoulombBarrier & operator=(const G4Be7GEMCoulombBarrier & right);
  G4bool operator==(const G4Be7GEMCoulombBarrier & right) const;
  G4bool operator!=(const G4Be7GEMCoulombBarrier & right) const;
  

};

#endif