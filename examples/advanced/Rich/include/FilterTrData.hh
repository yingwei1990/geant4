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
// Rich advanced example for Geant4
// FilterTrData.chh for Rich of LHCb
// History:
// Created: Sajan Easo (Sajan.Easo@cern.ch)
// Revision and changes: Patricia Mendez (Patricia.Mendez@cern.ch)
/////////////////////////////////////////////////////////////////////////////
#ifndef FilterTrData_h
#define FilterTrData_h 1
#include "G4ios.hh" 
#include "globals.hh"
#include <vector>
#include "FilterTypeSpec.hh"

class FilterTrData {

public: 
  FilterTrData(G4int , G4String );
  virtual ~FilterTrData();

  G4double GetCurrentFilTrans(G4double);
  G4double GetTotFilTrans(G4double);

  void ReadFilterTrans();
  G4int GetNumberofBins() {return NumberOfTrBins; }
  G4double GetCurTransWL(G4int BinNumw ) {return TransWaveL[BinNumw]; }
  G4double GetCurTransValue(G4int BinNumv ) {return TransValue[BinNumv];}
  G4double GetCurTransTotValue(G4int BinNumv ) {return TransTotValue[BinNumv];}
  
  G4double GetCurFilterThickness() {return FilterThickness; }
  std::vector<G4double> GetTransWL() { return TransWaveL ; }
  std::vector<G4double> GetTransValue() {return TransValue ; }
  std::vector<G4double> GetTransTotValue() {return TransTotValue ; }
  FilterType GetFilterTypeIndex() {return FilterTypeIndex ; }

private:

  FilterType FilterTypeIndex;
  G4int FilterTypeNumber;
  G4int NumberOfTrBins;
  G4double FilterThickness;
  G4double FilterRefIndexNominal;
  std::vector<G4double>TransWaveL ;
  std::vector<G4double>TransValue ;
  std::vector<G4double>TransTotValue;
  G4double CurNeighbourRefIndexNominal;
  G4String FilterTransDataFileName;

};

#endif 