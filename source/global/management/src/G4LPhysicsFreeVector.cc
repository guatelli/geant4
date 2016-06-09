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
// $Id: G4LPhysicsFreeVector.cc,v 1.9 2005/03/15 19:11:35 gcosmo Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
// 
// --------------------------------------------------------------------
// Class G4LPhysicsFreeVector
// Derived from base class G4PhysicsVector
// This is a free vector for Low Energy Physics cross section data
//
// F.W. Jones, TRIUMF, 04-JUN-96
//
// 27-MAR-97 FWJ: first version for Alpha release
// 11-NOV-00 H.Kurashige : use STL vector for dataVector and binVector
//

#include "G4LPhysicsFreeVector.hh"

#include <stdio.h>

G4LPhysicsFreeVector::G4LPhysicsFreeVector()
   : verboseLevel(0)
{
   type = T_G4LPhysicsFreeVector;

   edgeMin = 0.0;
   edgeMax = 0.0;
   numberOfBin = 0;
}

G4LPhysicsFreeVector::G4LPhysicsFreeVector(size_t nbin,
                                           G4double binmin,
                                           G4double binmax)
   : verboseLevel(0)
{
   type = T_G4LPhysicsFreeVector;

   edgeMin = binmin;
   edgeMax = binmax;
   numberOfBin = nbin;
   lastEnergy = 0.;
   lastValue = 0.;
   lastBin = 0;
   binVector.reserve(nbin);
   dataVector.reserve(nbin);
   for (size_t i=0; i<numberOfBin; i++)
   {
     binVector.push_back(0.0);
     dataVector.push_back(0.0);
   }
}  

G4LPhysicsFreeVector::~G4LPhysicsFreeVector()
{
}

void G4LPhysicsFreeVector::DumpValues()
{
   for (size_t i = 0; i < numberOfBin; i++)
   {
      printf(" %12.4f   %7.1f\n", binVector[i], dataVector[i]/millibarn);
   }
}
