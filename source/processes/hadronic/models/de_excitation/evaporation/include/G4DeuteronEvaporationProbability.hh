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
//J.M. Quesada (August2008). Based on:
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Oct 1998)
//

#ifndef G4DeuteronEvaporationProbability_h
#define G4DeuteronEvaporationProbability_h 1


#include "G4EvaporationProbability.hh"
#include "G4DeuteronCoulombBarrier.hh"

class G4DeuteronEvaporationProbability : public G4EvaporationProbability
{
public:
  // Only available constructor
  G4DeuteronEvaporationProbability();

  ~G4DeuteronEvaporationProbability() {}
private:  
  // Copy constructor
  G4DeuteronEvaporationProbability(const G4DeuteronEvaporationProbability &right);

  const G4DeuteronEvaporationProbability & operator=(const G4DeuteronEvaporationProbability &right);
  G4bool operator==(const G4DeuteronEvaporationProbability &right) const;
  G4bool operator!=(const G4DeuteronEvaporationProbability &right) const;


private:

  virtual G4double CrossSection(const  G4Fragment & fragment, const  G4double K);

  G4double GetOpt0(const G4double K);
  G4double GetOpt12(const G4double K);
  G4double GetOpt34(const G4double K);

  
 virtual G4double CalcAlphaParam(const G4Fragment & fragment) ;
 
 virtual G4double CalcBetaParam(const G4Fragment & fragment) ;
 
  G4double CCoeficient(const G4double aZ) ;
  
//data members

      G4DeuteronCoulombBarrier theCoulombBarrier; 

      G4double ResidualA;
      G4double ResidualZ; 
      G4double theA;
      G4double theZ;
      G4double ResidualAthrd;
      G4double FragmentA;
      G4double FragmentAthrd;


};


#endif


