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
// $Id: G4PhysicsVector.hh,v 1.13 2005/03/15 19:11:35 gcosmo Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
// 
//---------------------------------------------------------------
//      GEANT 4 class header file
//
//  G4PhysicsVector.hh
//
//  Class description:
//
//    A physics vector which has values of energy-loss, cross-section, 
//    and other physics values of a particle in matter in a given 
//    range of the energy, momentum, etc.
//    This class serves as the base class for a vector having various 
//    energy scale, for example like 'log', 'linear', 'free', etc.

//  History:
//    02 Dec. 1995, G.Cosmo : Structure created based on object model
//    03 Mar. 1996, K.Amako : Implemented the 1st version
//    27 Apr. 1996, K.Amako : Cache mechanism added
//    01 Jul. 1996, K.Amako : Now GetValue not virtual
//    21 Sep. 1996, K.Amako : Added [] and () operators
//    11 Nov. 2000, H.Kurashige : use STL vector for dataVector and binVector
//    18 Jan. 2001, H.Kurashige : removed ptrNextTable
//    09 Mar. 2001, H.Kurashige : added G4PhysicsVectorType & Store/Retrieve()
//
//---------------------------------------------------------------

#ifndef G4PhysicsVector_h
#define G4PhysicsVector_h 1

#include <vector>
#include "globals.hh"
#include "G4ios.hh"
#include <iostream>
#include <fstream>

#include  "G4PhysicsVectorType.hh"

class G4PhysicsVector 
{
  public:  

    G4PhysicsVector();
         // constructor  
         // This class is an abstract class with pure virtual method of
         // virtual size_t FindBinLocation(G4double theEnergy) const
         // So, default constructor is not supposed to be invoked explicitly

    G4PhysicsVector(const G4PhysicsVector&);
    G4PhysicsVector& operator=(const G4PhysicsVector&);
         // Copy constructor and assignment operator.

  public:  // with description

    virtual ~G4PhysicsVector();
         // destructor

    inline G4double GetValue(G4double theEnergy, G4bool& isOutRange);
         // Get the cross-section/energy-loss value corresponding to the
         // given energy. An appropriate interpolation is used to calculate
         // the value. 
         // [Note] isOutRange is not used anymore. This argument is kept
         //        for the compatibility reason.

    G4int operator==(const G4PhysicsVector &right) const ;
    G4int operator!=(const G4PhysicsVector &right) const ;
    inline G4double operator[](const size_t binNumber) const ;
         // Returns simply the value in the bin specified by 'binNumber'
         // of the dataVector. The boundary check will be Done. If you
         // don't want this check, use the operator ().
    inline G4double operator()(const size_t binNumber) const ;
         // Returns simply the value in the bin specified by 'binNumber'
         // of the dataVector. The boundary check will not be Done. If 
         // you want this check, use the operator [].

    inline void PutValue(size_t binNumber, G4double theValue);
         // Put 'theValue' into the bin specified by 'binNumber'.
         // Take note that the 'binNumber' starts from '0'.
         // To fill the vector, you have beforehand to Construct a vector
         // by the constructor with Emin, Emax, Nbin. 'theValue' should
         // be the crosssection/energyloss value corresponding to the low 
         // edge energy of the bin specified by 'binNumber'. You can get
         // the low edge energy value of a bin by GetLowEdgeEnergy().
    virtual G4double GetLowEdgeEnergy(size_t binNumber) const;
         // Get the energy value at the low edge of the specified bin.
         // Take note that the 'binNumber' starts from '0'.
         // This value is defined when a physics vector is constructed
         // by a constructor of a derived class. Use this function
         // when you fill physis vector by PutValue().
    inline size_t GetVectorLength() const;
         // Get the toal length (bin number) of the vector. 
    inline G4bool IsFilledVectorExist() const;
         // Is non-empty physics vector already exist?

    inline void PutComment(const G4String& theComment);
         // Put a comment to the G4PhysicsVector. This may help to check
         // whether your are accessing to the one you want. 
    inline const G4String& GetComment() const;
         // Retrieve the comment of the G4PhysicsVector.

    inline G4PhysicsVectorType GetType() const;
         // Get physics vector type

    virtual G4bool Store(std::ofstream& fOut, G4bool ascii=false);
    virtual G4bool Retrieve(std::ifstream& fIn, G4bool ascii=false);
         // To store/retrieve persistent data to/from file streams.

    friend std::ostream& operator<<(std::ostream&, const G4PhysicsVector&);

  protected:

    inline G4double LinearInterpolation(G4double theEnergy, size_t theLocBin);
         // Linear interpolation function

    virtual size_t FindBinLocation(G4double theEnergy) const=0;
         // Find the bin# in which theEnergy belongs - pure virtual function

    typedef std::vector<G4double> G4PVDataVector;

    G4PhysicsVectorType type;   // The type of PhysicsVector (enumerator)

    G4double edgeMin;           // Lower edge value of the lowest bin
    G4double edgeMax;           // Lower edge value of the highest bin
    size_t numberOfBin;

    G4double lastEnergy;        // Cache the last input value
    G4double lastValue;         // Cache the last output value   
    size_t lastBin;             // Cache the last bin location

    G4PVDataVector dataVector;    // Vector to keep the crossection/energyloss
    G4PVDataVector binVector;     // Vector to keep the low edge value of bin

  private:

    G4String comment;
};

#include "G4PhysicsVector.icc"

#endif
