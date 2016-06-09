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
#include "G4LorentzConvertor.hh"
#include "G4HadronicException.hh"

G4LorentzConvertor::G4LorentzConvertor() 
  : verboseLevel(2), degenerated(false) {

  if (verboseLevel > 3) {
    G4cout << " >>> G4LorentzConvertor::G4LorentzConvertor" << G4endl;
  }
}

void G4LorentzConvertor::toTheCenterOfMass() {
   
  if (verboseLevel > 3) {
    G4cout << " >>> G4LorentzConvertor::toTheCenterOfMass" << G4endl;
  }

  const G4double small = 1.0e-10;

  v2 = 0.0;

  G4double pv = 0.0;

   G4double e_sum = target_mom[0] + bullet_mom[0];

  velocity.resize(4);
  G4int i(0);
  for(i = 1; i < 4; i++) {
    velocity[i] = (target_mom[i] + bullet_mom[i]) / e_sum;
    v2 += velocity[i] * velocity[i];
    pv += target_mom[i] * velocity[i];
  };
   
  gamma = 1.0 / std::sqrt(std::fabs(1.0 - v2));
  ecm_tot = e_sum / gamma;

  G4double pa = 0.0;

  G4double pb = 0.0;

  G4double xx = pv * (gamma - 1.0) / v2 - target_mom[0] * gamma;

  for(i = 1; i < 4; i++) {
    scm_momentum[i] = -target_mom[i] - velocity[i] * xx;

    if (verboseLevel > 3) {
      G4cout << " i " << i << " pscm(i) " << scm_momentum[i] << G4endl;
    }

    pa += scm_momentum[i] * scm_momentum[i];
    pb += scm_momentum[i] * velocity[i];
  };
  ga = v2 - pb * pb / pa;
  if(ga < small) {
    ga = small;
    degenerated = true;

    if (verboseLevel > 3) {
      G4cout << " degenerated case " << G4endl; 
    }

  } else {
    ga = std::sqrt(ga);
  }; 

  if (verboseLevel > 3) {
    G4cout << " ga " << ga << " v2 " << v2 << " pb " << pb << 
      " pb * pb / pa " << pb * pb / pa << " pv " << pv << G4endl;
  }

  pscm = std::sqrt(pa);
  gb = pb / pscm;
  gbpp = gb / pscm;
  gapp = ga * pscm;
}

G4CascadeMomentum G4LorentzConvertor::rotate(const G4CascadeMomentum& mom) const {

  if (verboseLevel > 3) {
    G4cout << " >>> G4LorentzConvertor::rotate(G4CascadeMomentum)" << G4endl;
  }

  G4CascadeMomentum mom_rot;

  if (verboseLevel > 3) {
    G4cout << " ga " << ga << " gbpp " << gbpp << " gapp " << gapp << G4endl;  
    G4cout << " gegenerated " << degenerated << G4endl;
    G4cout << " before rotation: px " << mom[1] << " py " << mom[2] <<
      " pz " << mom[3] << G4endl;
  }

  if(degenerated) {
    mom_rot = mom; 
  } else {
    mom_rot[1] = mom[1] * (velocity[1] - gbpp * scm_momentum[1]) / ga + 
      mom[2] * (scm_momentum[2] * velocity[3] - scm_momentum[3] * velocity[2]) / gapp +
      mom[3] * scm_momentum[1] / pscm;
    mom_rot[2] = mom[1] * (velocity[2] - gbpp * scm_momentum[2]) / ga + 
      mom[2] * (scm_momentum[3] * velocity[1] - scm_momentum[1] * velocity[3]) / gapp +
      mom[3] * scm_momentum[2] / pscm;
    mom_rot[3] = mom[1] * (velocity[3] - gbpp * scm_momentum[3]) / ga + 
      mom[2] * (scm_momentum[1] * velocity[2] - scm_momentum[2] * velocity[1]) / gapp +
      mom[3] * scm_momentum[3] / pscm;
  };

  if (verboseLevel > 3) {
    G4cout << " after rotation: px " << mom_rot[1] << " py " << mom_rot[2] <<
      " pz " << mom_rot[3] << G4endl;
  }

  return mom_rot;
}

G4CascadeMomentum G4LorentzConvertor::rotate(const G4CascadeMomentum& mom1, 
					    const G4CascadeMomentum& mom) const {

  if (verboseLevel > 3) {
    G4cout << " >>> G4LorentzConvertor::rotate(G4CascadeMomentum,G4CascadeMomentum)" << G4endl;
  }

  const G4double small = 1.0e-10;

  G4CascadeMomentum mom_rot;

  G4double pp = 0.0;

  G4double pv = 0.0;

  for(G4int i = 0; i < 4; i++) {
    pp += mom1[i] * mom1[i];
    pv += mom1[i] * velocity[i];
  };

  G4double ga1 = v2 - pv * pv / pp;

  if(ga1 < small) {
    mom_rot = mom;
  } else {  
    ga1 = std::sqrt(ga1);

    G4double gb1 = pv / pp;

    pp = std::sqrt(pp);

    G4double ga1pp = ga1 * pp;

    mom_rot[1] = mom[1] * (velocity[1] - gb1 * mom1[1]) / ga1 + 
      mom[2] * (mom1[2] * velocity[3] - mom1[3] * velocity[2]) / ga1pp +
      mom[3] * mom1[1] / pp;
    mom_rot[2] = mom[1] * (velocity[2] - gb1 * mom1[2]) / ga1 + 
      mom[2] * (mom1[3] * velocity[1] - mom1[1] * velocity[3]) / ga1pp +
      mom[3] * mom1[2] / pp;
    mom_rot[3] = mom[1] * (velocity[3] - gb1 * mom1[3]) / ga1 + 
      mom[2] * (mom1[1] * velocity[2] - mom1[2] * velocity[1]) / ga1pp +
      mom[3] * mom1[3] / pp;
  };

  return mom_rot;
}

void G4LorentzConvertor::toTheTargetRestFrame() {
   
  if (verboseLevel > 3) {
    G4cout << " >>> G4LorentzConvertor::toTheTargetRestFrame" << G4endl;
  }

  const G4double small = 1.0e-10;

  gamma = target_mom[0] / target_mass;
  v2 = 0.0;

  G4double pv = 0.0;

  //  G4double e_sum = target_mom[0] + bullet_mom[0];

  velocity.resize(4);
  G4int i(0);
  for(i = 1; i < 4; i++) {
    velocity[i] = target_mom[i] / target_mom[0];
    v2 += velocity[i] * velocity[i];
    pv += bullet_mom[i] * velocity[i];
  };

  G4double pa = 0.0;

  G4double pb = 0.0;

  G4double xx = 0.0;

  if(v2 > small) xx = pv * (gamma - 1.0) / v2 - bullet_mom[0] * gamma;
  for(i = 1; i < 4; i++) {
    scm_momentum[i] = bullet_mom[i] + velocity[i] * xx;

    if (verboseLevel > 3) {
      G4cout << " rf: i " << i << " pscm(i) " << scm_momentum[i] << G4endl;
    }
    pa += scm_momentum[i] * scm_momentum[i];
    pb += scm_momentum[i] * velocity[i];
  };

  ga = v2 - pb * pb / pa;
  if(ga < small) {
    ga = small;
    degenerated = true;
  } else {
    ga = std::sqrt(ga);
  };  
  pscm = std::sqrt(pa);
  plab = pscm;
  gb = pb / pscm;
  gbpp = gb / pscm;
  gapp = ga * pscm;   
}

G4CascadeMomentum G4LorentzConvertor::backToTheLab(const G4CascadeMomentum& mom) const {

  if (verboseLevel > 3) {
    G4cout << " >>> G4LorentzConvertor::backToTheLab" << G4endl;
  }

  const G4double small = 1.0e-10;

  if (verboseLevel > 3) {
    G4cout << " at rest: px " << mom[1] << " py " << mom[2] << " pz " << mom[3] << 
      " e " << mom[0] << G4endl;
    G4cout << " v2 " << v2 << G4endl;   
  }

  G4CascadeMomentum mom1;

  if(v2 < small) {
    mom1 = mom;
  } else { 
    G4double pv = 0.0;

    G4int i(0);
    for(i = 1; i < 4; i++) pv += mom[i] * velocity[i];

    G4double xx = pv * (gamma - 1.0) / v2 + mom[0] * gamma;

    for(i = 1; i < 4; i++) mom1[i] = mom[i] + velocity[i] * xx;
  };

  if (verboseLevel > 3) {
    G4cout << " at lab: px " << mom1[1] << " py " << mom1[2] << " pz " << mom1[3] << G4endl;
  }

  return mom1;
}

G4bool G4LorentzConvertor::reflectionNeeded() const {

  if (verboseLevel > 3) {
    G4cout << " >>> G4LorentzConvertor::reflectionNeeded" << G4endl;
  }

  const G4double small = 1.0e-10;

  if(v2 < small) {
    return false;
  }  else {   
    if(degenerated) return (scm_momentum[3] < 0.0);
    else 
    {
      throw G4HadronicException(__FILE__, __LINE__, "G4LorentzConvertor::reflectionNeeded - return value undefined");
      return false;
    }
  };
}






