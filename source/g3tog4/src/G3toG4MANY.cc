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
// $Id: G3toG4MANY.cc,v 1.1 2001/11/08 16:08:01 gcosmo Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
// By I. Hrivnacova, 22.10.01 

//#define G3G4DEBUG 1

#include "globals.hh"
#include "G3toG4MANY.hh"
#include "G3Pos.hh"
#include "G3RotTable.hh"
#include "G4SubtractionSolid.hh"

void G3toG4MANY(G3VolTableEntry* curVTE)
{
  if (curVTE->GetNoOverlaps() > 0) {
  
    // check consistency 
    if (!curVTE->HasMANY()) { 
      G4String text = "G3toG4MANY: volume ";
      text = text + curVTE->GetName() + " has specified overlaps \n";
      text = text + " but is not defined as MANY.";
      G4Exception(text);
    }  

    // only MANY volumes with one position are supported
    if (curVTE->NPCopies() != 1) {
      G4String text = "G3toG4MANY: volume ";
      text = text + curVTE->GetName() + " which has MANY has not just one position.";
      G4Exception(text);
    }  

    #ifdef G3G4DEBUG
    G4cout << "G3toG4MANY  " << curVTE->GetName() << " boolean" << G4endl;
    #endif

    G4Transform3D transform = GetTransform3D(curVTE->GetG3PosCopy(0)); 
    
    MakeBooleanSolids(curVTE, curVTE->GetOverlaps(), transform.inverse());
  }

  // process daughters
  for (G4int i=0; i<curVTE->GetNoDaughters(); i++)
    G3toG4MANY(curVTE->GetDaughter(i));
}

void MakeBooleanSolids(G3VolTableEntry* curVTE, G3VolTableEntryVector* overlaps,
		       const G4Transform3D& transform)
{			     
  // loop over overlap VTEs
  for (size_t i=0; i<overlaps->size(); i++){
   
    G3VolTableEntry* overlapVTE = (*overlaps)[i]; 

     // loop over clone VTEs
    for (G4int ij=0; ij<overlapVTE->GetMasterClone()->GetNoClones(); ij++){
    
      G3VolTableEntry* cloneVTE = overlapVTE->GetMasterClone()->GetClone(ij);   
   
      // loop over clone positions
      for (G4int j=0; j<cloneVTE->NPCopies(); j++){

        #ifdef G3G4DEBUG
        G4cout << "From '" << curVTE->GetName() << "' "
	       << "cut '" << cloneVTE->GetName() << "' :"
	       << i  << "th overlap (from " << overlaps->size() << ") "
	       << ij << "th clone (from " << overlapVTE->GetMasterClone()->GetNoClones() << ") "
	       << j  << "th copy (from " << cloneVTE->NPCopies() << ")  "
	       << G4endl;
        #endif

        SubstractSolids(curVTE, cloneVTE, j, transform); 
      }
    }    
  }				  
}			

void SubstractSolids(G3VolTableEntry* vte1, G3VolTableEntry* vte2,
	             G4int copy, const G4Transform3D& transform)
{			     
  // vte2 transformation
  G4Transform3D transform2 = GetTransform3D(vte2->GetG3PosCopy(copy));
   
  // compose new name 
  G4String newName = vte1->GetSolid()->GetName();
  newName = newName + "-" + vte2->GetSolid()->GetName();   

  #ifdef G3G4DEBUG
  G4cout << "   " << newName << G4endl; 
  #endif

  G4VSolid* newSolid 
    = new G4SubtractionSolid(newName, vte1->GetSolid(), vte2->GetSolid(),
                             transform*transform2);
				 
  // update vte1
  vte1->SetSolid(newSolid);

  // process daughters
  for (G4int k=0; k<vte1->GetNoDaughters(); k++){
         	
    G3VolTableEntry* dVTE = vte1->GetDaughter(k);				
	 
    if (dVTE->NPCopies() != 1) {
      G4String text = "G3toG4MANY: volume ";
      text = text + dVTE->GetName() + " which has MANY has not just one position.";
      G4Exception(text);
    }
	  
    G4Transform3D dt = GetTransform3D(dVTE->GetG3PosCopy(0)); 
    SubstractSolids(dVTE, vte2, copy, dt.inverse()*transform);
  }	
}			

G4Transform3D GetTransform3D(G3Pos* g3pos)
{
  G4int irot = g3pos->GetIrot();
  G4RotationMatrix* theMatrix = 0;
  if (irot>0) theMatrix = G3Rot.Get(irot);
  
  G4Rotate3D rotation;
  if (theMatrix) {            
     rotation = G4Rotate3D(*theMatrix);
  }

  G4Translate3D translation(*(g3pos->GetPos()));
  G4Transform3D transform3D = translation * (rotation.inverse());
  
  return transform3D;
}


