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
// $Id: G4ForceCondition.hh,v 1.4 2002/10/31 23:41:52 tsasaki Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
//
//---------------------------------------------------------------
//
// G4ForceCondition  
//
// Class Description:
//   This enumaration specifies possible conditions the three
//   types of DoIt can be assinged by physics processes.
//
// Contact:
//   Questions and comments to this code should be sent to
//     Katsuya Amako  (e-mail: Katsuya.Amako@kek.jp)
//     Takashi Sasaki (e-mail: Takashi.Sasaki@kek.jp)
//
//---------------------------------------------------------------

#ifndef G4ForceCondition_h
#define G4ForceCondition_h 1

/////////////////////
enum G4ForceCondition  
/////////////////////
{
  InActivated,       
  // This PostStepDoit is inactivated by a user
  Forced,            
    // This PostStepDoIt is forced to invoke if particle is not a state of StopAndKill.              
  NotForced,         
    // This PostStepDoIt is not forced to invoke.
  Conditionally,     
    // This PostStepDoIt is forced to invoke only when corresponding
    // AlongStepDoIt limits the Step.
  ExclusivelyForced, 
    // Only this PostStepDoIt (or AtRestDoIt) is exclusively forced 
    // to invoke - all other DoIt including AlongStepDoIts are ignored.
  StronglyForced
   // This PostStepDoIt is really forced to invoke, anyway.
};

#endif


