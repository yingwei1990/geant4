// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4VGraphicsSystem.hh,v 2.1 1998/11/06 13:43:02 allison Exp $
// GEANT4 tag $Name: geant4-00 $
//
// 
// John Allison  27th March 1996
// Abstract interface class for graphics systems.

#ifndef G4VGRAPHICSSYSTEM_HH
#define G4VGRAPHICSSYSTEM_HH

#include "globals.hh"

class G4VScene;
class G4VView;

class G4VGraphicsSystem {

public:

  enum Functionality {
    noFunctionality,
    twoD,               // Simple 2D, e.g., X (no stored structures).
    twoDStore,          // 2D with stored structures.
    threeD,             // Passive 3D (with stored structures).
    threeDInteractive,  // 3D with "pick" functionality.
    virtualReality      // Virtual Reality functionality.
  };

  G4VGraphicsSystem (const G4String& name,
		     Functionality f);

  G4VGraphicsSystem (const G4String& name,
		     const G4String& nickname,
		     Functionality f);

  G4VGraphicsSystem (const G4String& name,
		     const G4String& nickname,
		     const G4String& description,
		     Functionality f);

  virtual ~G4VGraphicsSystem ();

  // For RWTPtrOrderedVector...
  G4bool operator == (const G4VGraphicsSystem& system) const;

  virtual G4VScene* CreateScene (const G4String& name)            = 0;
  virtual G4VView*  CreateView  (G4VScene&, const G4String& name) = 0;

  // Access functions.
  const G4String& GetName          () const;
  const G4String& GetNickname      () const;
  const G4String& GetDescription   () const;
  Functionality   GetFunctionality () const;

protected:
  const G4String fName;
  const G4String fNickname;
  const G4String fDescription;
  Functionality  fFunctionality;
};

ostream& operator << (ostream& os, const G4VGraphicsSystem& gs);

#include "G4VGraphicsSystem.icc"

#endif