// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: Em1PrimaryGeneratorAction.hh,v 1.2 1999/12/15 14:48:56 gunter Exp $
// GEANT4 tag $Name: geant4-03-01 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef Em1PrimaryGeneratorAction_h
#define Em1PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class Em1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    Em1PrimaryGeneratorAction();    
   ~Em1PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);

  private:
    G4ParticleGun*  particleGun;	//pointer a to G4 service class
};

#endif

