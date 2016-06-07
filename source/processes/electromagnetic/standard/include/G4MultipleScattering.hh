// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4MultipleScattering.hh,v 2.9 1998/12/09 09:17:31 urban Exp $
// GEANT4 tag $Name: geant4-00 $
//
// $Id:
// --------------------------------------------------------------
//    GEANT 4 class header file
//  
//    For information related to this code contact:
//    CERN, IT Division, ASD Group
//    History: based on object model of
//    2nd December 1995, G.Cosmo
//    --------- G4MultipleScattering physics process --------
//               by Laszlo Urban, October 1997
// **************************************************************
//      UNIVERSAL: for arbitrary single charged particle
//  09/12/98:      charge can be != +- 1 !!!!   L.Urban
// --------------------------------------------------------------
// 22/10/98: cleanup , L.Urban

#ifndef G4MultipleScattering_h
#define G4MultipleScattering_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "Randomize.hh"
#include "G4EnergyLossTables.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonPlus.hh"
#include "G4Proton.hh"
#include "G4PhysicsLogVector.hh"
#include "G4GPILSelection.hh"
#include "G4VContinuousDiscreteProcess.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Material.hh"
#include "G4ParticleChangeForMSC.hh"
#include "G4UnitsTable.hh"

class G4MultipleScattering : public G4VContinuousDiscreteProcess

{
 public:

   G4MultipleScattering(const G4String& processName="msc") ;

   ~G4MultipleScattering() ;
          
   G4bool IsApplicable ( const G4ParticleDefinition& ) ;

   void SetPhysicsTableBining(G4double lowE,G4double highE,G4int nBins);

   void BuildPhysicsTable(const G4ParticleDefinition& aParticleType) ;

   void PrintInfoDefinition();

   G4double GetContinuousStepLimit(const G4Track& aTrack,
                                   G4double previousStepSize,
                                   G4double currentMinimumStep,
                                   G4double& currentSafety) ; 

   G4double GetMeanFreePath(const G4Track& aTrack,
                            G4double previousStepSize,
                            G4ForceCondition* condition) ;

   G4VParticleChange* AlongStepDoIt(const G4Track& aTrack,const G4Step& aStep);

   G4VParticleChange* PostStepDoIt(const G4Track& aTrack,const G4Step& aStep) ;

   G4double GetLambda(G4double KineticEnergy,G4Material* material);

 protected:

   G4double ComputeTransportCrossSection(
                             const G4ParticleDefinition& aParticleType,
                                   G4double KineticEnergy,
                                   G4double AtomicNumber) ;

   G4double TrueToGeomTransformation(const G4DynamicParticle* aParticle,
                                     G4Material* aMaterial,
                                     G4double truePathLength) ;

 private:

 //  hide assignment operator as  private
   G4MultipleScattering & operator = (const G4MultipleScattering &right) ;
   G4MultipleScattering ( const G4MultipleScattering &) ;


 // data members ...................................................
 private:

   G4PhysicsTable* theTransportMeanFreePathTable ;

   G4double fTransportMeanFreePath ;

   G4double fMeanLateralDisplacement ;

   G4double LowestKineticEnergy ;
   G4double HighestKineticEnergy ;
   G4int TotBin ;

   const G4Electron* theElectron ;
   const G4Positron* thePositron ;
   
   G4Material* lastMaterial;
   G4double lastKineticEnergy;

   G4double tLast ;
   G4double zLast ;

   G4double tuning;

   //New ParticleChange
   G4ParticleChangeForMSC fParticleChange ;
   
};

#include "G4MultipleScattering.icc"

#endif
 

 