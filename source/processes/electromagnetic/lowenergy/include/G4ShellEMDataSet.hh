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
// $Id: G4ShellEMDataSet.hh,v 1.12 2008/03/17 13:45:25 pia Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// Author: Maria Grazia Pia (Maria.Grazia.Pia@cern.ch)
//
// History:
// -----------
// 31 Jul 2001   MGP        Created
//  9 Mar 2008   MGP        Cleaned up unreadable code modified by former developer
//                          (Further clean-up needed) 
//
// -------------------------------------------------------------------

// Class description:
// Low Energy Electromagnetic Physics
// Data set for an electromagnetic physics process
// A strategy pattern is used to encapsulate algorithms for data interpolation
// Further documentation available from http://www.ge.infn.it/geant4/lowE

// -------------------------------------------------------------------

#ifndef  G4SHELLEMDATASET_HH
#define  G4SHELLEMDATASET_HH 1

#include "globals.hh"
#include "G4VEMDataSet.hh"
#include <vector>

class G4VDataSetAlgorithm;

class G4ShellEMDataSet : public G4VEMDataSet 
{ 
public:
  G4ShellEMDataSet(G4int Z, 
		   G4VDataSetAlgorithm* algo, 
		   G4double eUnit=MeV, 
		   G4double dataUnit=barn);

  virtual ~G4ShellEMDataSet();
 
  virtual G4double FindValue(G4double energy, G4int componentId=0) const;
  
  virtual void PrintData(void) const;

  virtual const G4VEMDataSet*  GetComponent(G4int componentId) const { return components[componentId]; }
  virtual void AddComponent(G4VEMDataSet* dataSet) { components.push_back(dataSet); }
  virtual size_t NumberOfComponents(void) const { return components.size(); }

  virtual const G4DataVector& GetEnergies(G4int componentId) const { return GetComponent(componentId)->GetEnergies(0); }
  virtual const G4DataVector& GetData(G4int componentId) const { return GetComponent(componentId)->GetData(0); }
  virtual void SetEnergiesData(G4DataVector* energies, G4DataVector* data, G4int componentId);

  virtual G4bool LoadData(const G4String& fileName);
  virtual G4bool SaveData(const G4String& fileName) const;

  virtual G4double RandomSelect(G4int /*componentId = 0*/) const { return -1.; };
   
protected:

  G4double GetUnitEnergies() const { return unitEnergies; }
  G4double GetUnitData() const { return unitData; }
  const G4VDataSetAlgorithm* GetAlgorithm() const { return algorithm; }
   
  void CleanUpComponents(void);

private:

  G4String FullFileName(const G4String& fileName) const;
  
  // Hide copy constructor and assignment operator 
  G4ShellEMDataSet();
  G4ShellEMDataSet(const G4ShellEMDataSet& copy);
  G4ShellEMDataSet& operator=(const G4ShellEMDataSet& right);

  std::vector<G4VEMDataSet*> components;          // Owned pointers

  G4int z;

  G4VDataSetAlgorithm* algorithm;           // Owned pointer 
  
  G4double unitEnergies;
  G4double unitData;
};
#endif /* G4SHELLEMDATASET_HH */