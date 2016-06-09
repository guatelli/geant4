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
// $Id: B03ImportanceDetectorConstruction.hh,v 1.2 2003/06/16 16:47:22 gunter Exp $
// GEANT4 tag $Name: geant4-07-01 $
//

#ifndef B03ImportanceDetectorConstruction_hh 
#define B03ImportanceDetectorConstruction_hh  B03ImportanceDetectorConstruction_hh 

#include "globals.hh"
#include <map>
#include "B03PVolumeStore.hh"
class G4VPhysicalVolume;



class B03ImportanceDetectorConstruction
{
public:
  B03ImportanceDetectorConstruction();
  ~B03ImportanceDetectorConstruction();

  const G4VPhysicalVolume &GetPhysicalVolumeByName(const G4String& name) const;
  G4VPhysicalVolume &GetWorldVolume() const;
  G4String ListPhysNamesAsG4String();
  G4String GetCellName(G4int i);
  G4GeometryCell GetGeometryCell(G4int i);

private:
  void Construct();
  B03PVolumeStore fPVolumeStore;;
  G4VPhysicalVolume *fWorldVolume;
};

#endif
