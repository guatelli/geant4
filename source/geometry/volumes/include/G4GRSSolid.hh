//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4GRSSolid.hh,v 1.7 2003/11/02 16:06:04 gcosmo Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
// 
// class G4GRSSolid
//
// Class description:
//
// Object representing a touchable solid - maintains the association
// between a solid and its net resultant local->global transform.
//
// NOTE: The (optional) rotation matrix is copied

// History:
// - Created. Paul Kent, August 1996
// ----------------------------------------------------------------------
#ifndef G4GRSSOLID_HH
#define G4GRSSOLID_HH

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4VTouchable.hh"

class G4VSolid;

class G4GRSSolid : public G4VTouchable
{
  public:  // with description

    G4GRSSolid(G4VSolid *pSolid,
         const G4RotationMatrix *pRot,
         const G4ThreeVector &tlate);
    G4GRSSolid(G4VSolid *pSolid,
         const G4RotationMatrix &rot,
         const G4ThreeVector &tlate);
    ~G4GRSSolid();

    inline G4VSolid* GetSolid(G4int depth=0) const;
    inline const G4ThreeVector& GetTranslation(G4int depth=0) const;
    inline const G4RotationMatrix*  GetRotation(G4int depth=0) const;

  private:

    G4GRSSolid(const G4GRSSolid&);
    G4GRSSolid& operator=(const G4GRSSolid&);
      // Copy constructor and assignment operator NOT public

  private:
  
    G4VSolid *fsolid;
    G4RotationMatrix *frot;
    G4ThreeVector ftlate;
};

#include "G4GRSSolid.icc"

#endif
