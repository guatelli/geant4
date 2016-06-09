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
// $Id: g4rwPrimaryGeneratorAction.cc,v 1.3 2004/12/07 09:45:15 gcosmo Exp $
// GEANT4 tag $Name: geant4-07-01 $
//

#include "g4rwPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4UImanager.hh"
#include "globals.hh"

gogdmlPrimaryGeneratorAction::gogdmlPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/gun/particle geantino");
  UI->ApplyCommand("/gun/position 0.0 0.0 0.0 cm");
}

gogdmlPrimaryGeneratorAction::~gogdmlPrimaryGeneratorAction()
{
  delete particleGun;
}

void gogdmlPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4UImanager* UI = G4UImanager::GetUIpointer();
  G4int i = anEvent->GetEventID() % 3;
  switch(i)
  {
    case 0:
      UI->ApplyCommand("/gun/direction 0.2 0.0 1.0");
      break;
    case 1:
      UI->ApplyCommand("/gun/direction 0.0 0.3 1.0");
      break;
    case 2:
      UI->ApplyCommand("/gun/direction 0.1 0.0 1.0");
      break;
  }

  particleGun->GeneratePrimaryVertex(anEvent);
}


