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
// $Id: G4NeutronHPTCFissionFS.hh,v 1.9 2005/06/04 13:44:43 jwellisc Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
#ifndef G4NeutronHPTCFissionFS_h
#define G4NeutronHPTCFissionFS_h 1

#include "globals.hh"
#include "G4HadProjectile.hh"
#include "G4DynamicParticleVector.hh"
#include "G4NeutronHPFissionBaseFS.hh"

class G4NeutronHPTCFissionFS : public G4NeutronHPFissionBaseFS
{
  public:
  
  G4NeutronHPTCFissionFS(){ hasXsec = false; }
  ~G4NeutronHPTCFissionFS(){}
  void Init (G4double A, G4double Z, G4String & dirName, G4String & aFSType);
  G4DynamicParticleVector * ApplyYourself(G4int NNeutrons);
  G4NeutronHPFinalState * New() 
  {
   G4NeutronHPTCFissionFS * theNew = new G4NeutronHPTCFissionFS;
   return theNew;
  }
  
  private:
  G4HadFinalState * ApplyYourself(const G4HadProjectile & ) { return NULL; }
    
};
#endif
