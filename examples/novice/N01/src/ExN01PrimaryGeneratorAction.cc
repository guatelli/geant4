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
// $Id: ExN01PrimaryGeneratorAction.cc,v 1.4 2002/01/09 17:23:48 ranjard Exp $
// GEANT4 tag $Name: geant4-04-00-patch-02 $
//

#include "ExN01PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4UImanager.hh"
#include "globals.hh"

ExN01PrimaryGeneratorAction::ExN01PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/gun/particle geantino");
  UI->ApplyCommand("/gun/energy 1.0 GeV");
  UI->ApplyCommand("/gun/position -2.0 0.0 0.0 m");
}

ExN01PrimaryGeneratorAction::~ExN01PrimaryGeneratorAction()
{
  delete particleGun;
}

void ExN01PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4UImanager* UI = G4UImanager::GetUIpointer();
  G4int i = anEvent->GetEventID() % 3;
  switch(i)
  {
    case 0:
      UI->ApplyCommand("/gun/direction 1.0 0.0 0.0");
      break;
    case 1:
      UI->ApplyCommand("/gun/direction 1.0 0.1 0.0");
      break;
    case 2:
      UI->ApplyCommand("/gun/direction 1.0 0.0 0.1");
      break;
  }

  particleGun->GeneratePrimaryVertex(anEvent);
}


