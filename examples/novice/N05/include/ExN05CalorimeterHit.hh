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
// $Id: ExN05CalorimeterHit.hh,v 1.7 2003/11/10 14:41:33 gcosmo Exp $
// GEANT4 tag $Name: geant4-07-01 $
//

#ifndef ExN05CalorimeterHit_h
#define ExN05CalorimeterHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class ExN05CalorimeterHit : public G4VHit
{
  public:

      ExN05CalorimeterHit();
      ExN05CalorimeterHit(G4LogicalVolume* logVol);
      ~ExN05CalorimeterHit();
      ExN05CalorimeterHit(const ExN05CalorimeterHit &right);
      const ExN05CalorimeterHit& operator=(const ExN05CalorimeterHit &right);
      G4int operator==(const ExN05CalorimeterHit &right) const;


      inline void *operator new(size_t);
      inline void operator delete(void *aHit);
      void *operator new(size_t,void*p){return p;}
#ifndef G4NOT_ISO_DELETES
      void operator delete(void *,void*){}
#endif

      void Draw();
      void Print();

  private:
      G4double edep;
      G4ThreeVector pos;
      G4RotationMatrix rot;
      const G4LogicalVolume* pLogV;

  public:
      inline void SetEdep(G4double de)
      { edep = de; };
      inline void AddEdep(G4double de)
      { edep += de; };
      inline G4double GetEdep()
      { return edep; };
      inline void SetPos(G4ThreeVector xyz)
      { pos = xyz; };
      inline G4ThreeVector GetPos()
      { return pos; };
      inline void SetRot(G4RotationMatrix rmat)
      { rot = rmat; };
      inline G4RotationMatrix GetRot()
      { return rot; };
      inline const G4LogicalVolume * GetLogV()
      { return pLogV; };

};

typedef G4THitsCollection<ExN05CalorimeterHit> ExN05CalorimeterHitsCollection;

extern G4Allocator<ExN05CalorimeterHit> ExN05CalorimeterHitAllocator;

inline void* ExN05CalorimeterHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) ExN05CalorimeterHitAllocator.MallocSingle();
  return aHit;
}

inline void ExN05CalorimeterHit::operator delete(void *aHit)
{
  ExN05CalorimeterHitAllocator.FreeSingle((ExN05CalorimeterHit*) aHit);
}

#endif
