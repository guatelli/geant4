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
// * authors in the GEANT4 collaboration.                             *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4PreCompoundNeutron.hh,v 1.9 2002/01/15 12:45:46 vlara Exp $
// GEANT4 tag $Name: geant4-04-00-patch-02 $
//
// by V. Lara


#ifndef G4PreCompoundNeutron_h
#define G4PreCompoundNeutron_h 1

#include "G4VPreCompoundNucleon.hh"
#include "G4ReactionProduct.hh"
#include "G4Neutron.hh"
#include "G4PreCompoundParameters.hh"
#include "Randomize.hh"

#include "G4NeutronCoulombBarrier.hh"


class G4PreCompoundNeutron : public G4VPreCompoundNucleon
{
public:
  // default constructor
  G4PreCompoundNeutron() : G4VPreCompoundNucleon(1,0,&theNeutronCoulomBarrier,"Neutron") {}

  // copy constructor
  G4PreCompoundNeutron(const G4PreCompoundNeutron &right): G4VPreCompoundNucleon(right) {}

  // destructor
  ~G4PreCompoundNeutron() {}

  // operators  
  const G4PreCompoundNeutron & operator=(const G4PreCompoundNeutron &right) {
    if (&right != this) this->G4VPreCompoundNucleon::operator=(right);
    return *this;
  }

  G4bool operator==(const G4PreCompoundNeutron &right) const
  { return G4VPreCompoundNucleon::operator==(right);}
  
  G4bool operator!=(const G4PreCompoundNeutron &right) const
  { return G4VPreCompoundNucleon::operator!=(right);}


    G4ReactionProduct * GetReactionProduct() const
	{
	    G4ReactionProduct * theReactionProduct = 
		new G4ReactionProduct(G4Neutron::NeutronDefinition());
	    theReactionProduct->SetMomentum(GetMomentum().vect());
	    theReactionProduct->SetTotalEnergy(GetMomentum().e());
#ifdef pctest
	    theReactionProduct->SetCreatorModel("G4PrecompoundModel");
#endif
	    return theReactionProduct;
	}



public:
  G4double ProbabilityDistributionFunction(const G4double & eKin, const G4Fragment & aFragment);


private:

  G4NeutronCoulombBarrier theNeutronCoulomBarrier;

};

#endif
 
