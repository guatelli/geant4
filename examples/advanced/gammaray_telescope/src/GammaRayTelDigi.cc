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
// $Id: GammaRayTelDigi.cc,v 1.3 2003/05/30 15:09:00 flongo Exp $
// GEANT4 tag $Name: geant4-07-01 $
// ------------------------------------------------------------
//      GEANT 4 class implementation file
//      CERN Geneva Switzerland
//
//
//      ------------ GammaRayTelDigi  ------
//           by F.Longo, R.Giannitrapani & G.Santin (21 oct 2001)
//
// ************************************************************

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
#include "GammaRayTelDigi.hh"

G4Allocator<GammaRayTelDigi> GammaRayTelDigiAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GammaRayTelDigi::GammaRayTelDigi()
{
  PlaneType = 0; 
  PlaneNumber = 0;
  StripNumber=0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GammaRayTelDigi::~GammaRayTelDigi()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GammaRayTelDigi::GammaRayTelDigi(const GammaRayTelDigi& right)
  :G4VDigi()
{
  PlaneType = right.PlaneType; 
  PlaneNumber = right.PlaneNumber;
  StripNumber = right.StripNumber;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

const GammaRayTelDigi& GammaRayTelDigi::operator=(const GammaRayTelDigi& right)
{
  PlaneType = right.PlaneType; 
  PlaneNumber = right.PlaneNumber;
  StripNumber = right.StripNumber;
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

int GammaRayTelDigi::operator==(const GammaRayTelDigi& right) const
{ 
 return ((PlaneType==right.PlaneType)&&(PlaneNumber==right.PlaneNumber)&&(StripNumber==right.StripNumber)); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelDigi::Draw()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelDigi::Print()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....











