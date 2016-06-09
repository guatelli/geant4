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
// $Id: G4ExcitedDeltaConstructor.hh,v 1.5 2001/07/11 10:02:05 gunter Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
// 
// --------------------------------------------------------------
//	GEANT 4 class implementation file 
//
//      History: first implementation, based on object model of
//      10 oct 1998  H.Kurashige
// ---------------------------------------------------------------
#ifndef G4ExcitedDeltaConstructor_h
#define G4ExcitedDeltaConstructor_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4ExcitedBaryonConstructor.hh"

class G4ExcitedDeltaConstructor: public G4ExcitedBaryonConstructor
{
  //This class is a utility class for construction 
  //short lived particles

  public:
    G4ExcitedDeltaConstructor();
    virtual  ~G4ExcitedDeltaConstructor();

  protected:
    virtual  G4int    GetEncoding(G4int iIsoSpin3, G4int idxState);

  protected:  
    virtual  G4bool   Exist( G4int ){return true;}

    virtual  G4int    GetQuarkContents(G4int, G4int);
    virtual  G4String GetName(G4int iIso3, G4int iState);
    virtual  G4String GetMultipletName(G4int iState);

    virtual  G4double GetMass(G4int iState);
    virtual  G4double GetWidth(G4int iState);
    virtual  G4int    GetiSpin(G4int iState);
    virtual  G4int    GetiParity(G4int iState);
    virtual  G4int    GetEncodingOffset(G4int iState);

    virtual  G4DecayTable* CreateDecayTable(const G4String& name,
					    G4int iIso3, G4int iState,
					    G4bool fAnti = false);
  private:
    G4DecayTable* AddNGammaMode( G4DecayTable* table, const G4String& name,
				    G4double br, G4int iIso3, G4bool fAnti);
    G4DecayTable* AddNPiMode( G4DecayTable* table, const G4String& name,
				     G4double br, G4int iIso3, G4bool fAnti);
    G4DecayTable* AddNRhoMode( G4DecayTable* table, const G4String& name,
				     G4double br, G4int iIso3, G4bool fAnti);
    G4DecayTable* AddDeltaPiMode( G4DecayTable* table, const G4String& name,
				     G4double br, G4int iIso3, G4bool fAnti);
    G4DecayTable* AddNStarPiMode( G4DecayTable* table, const G4String& name,
				     G4double br, G4int iIso3, G4bool fAnti);

  public:
    enum     { NStates = 9  };
  private:
    enum     { DeltaIsoSpin = 3 };

  private:
    static const char* name[ NStates ];
    static const G4double mass[ NStates ];
    static const G4double width[ NStates ];
    static const G4int    iSpin[ NStates ];
    static const G4int    iParity[ NStates ];
    static const G4int    encodingOffset[ NStates ];

  public:
    enum     { NumberOfDecayModes = 5};
  private:
    enum     { NGamma=0, NPi=1, NRho=2, DeltaPi=3, NStarPi=4 };
  private:
    static const G4double bRatio[ NStates ][ NumberOfDecayModes];
};

inline
 G4double G4ExcitedDeltaConstructor::GetMass(G4int iState)
{ 
  return mass[iState]; 
}

inline
 G4double G4ExcitedDeltaConstructor::GetWidth(G4int iState)
{
  return width[iState];
}

inline
 G4int    G4ExcitedDeltaConstructor::GetiSpin(G4int iState)
{
  return iSpin[iState];
}

inline
 G4int    G4ExcitedDeltaConstructor::GetiParity(G4int iState)
{
  return iParity[iState];
}

inline
 G4int    G4ExcitedDeltaConstructor::GetEncodingOffset(G4int iState)
{
  return encodingOffset[iState];
}

inline
 G4int  G4ExcitedDeltaConstructor::GetQuarkContents(G4int iQ, G4int iIso3)
{
  // Quark contents
  //    iIso3 = +3 : uuu
  //    iIso3 = +1 : uud
  //    iIso3 = -1 : udd
  //    iIso3 = -3 : ddd
  G4int quark=0;
  if ( iQ == 0 ){
    if ( iIso3 == -3 ){
    // d-quark
      quark = 1;
    } else {
    // u-quark
      quark = 2;
    }
  } else if ( iQ == 2 ){
    if ( iIso3 == +3 ){
    // u-quark
      quark = 2;
    } else {
    // d-quark
      quark = 1;
    }
  } else {
    if (( iIso3 == -1 )||( iIso3 == -3 )) {
    // d-quark
      quark = 1;
    } else {
    // u-quark
      quark = 2;
    }
  }
  return quark;
}

inline 
 G4String G4ExcitedDeltaConstructor::GetMultipletName(G4int iState)
{
  return name[iState];
}

inline 
 G4String G4ExcitedDeltaConstructor::GetName(G4int iIso3, G4int iState)
{
  G4String particle = name[iState];
  if ( iIso3 == -3 ){
    particle += "-";
  } else if ( iIso3 == -1 ){
    particle += "0";
  } else if ( iIso3 == +1 ){
    particle += "+";
  } else {
    particle += "++";
  }
  return particle;
}
#endif










