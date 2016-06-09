//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// ====================================================================
//
//   G4HepMCInterface.cc
//   $Id: G4HepMCInterface.cc,v 1.2 2006/06/29 17:13:38 gunter Exp $
//
// ====================================================================

#ifndef WIN32         // Temporarly disabled on Windows, until CLHEP
                      // will support the HepMC module

#include "G4HepMCInterface.hh"

#include "globals.hh"
#include "G4LorentzVector.hh"
#include "G4Event.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"

////////////////////////////////////
G4HepMCInterface::G4HepMCInterface()
  : hepmcEvent(0)
////////////////////////////////////
{
}

/////////////////////////////////////
G4HepMCInterface::~G4HepMCInterface()
/////////////////////////////////////
{
  delete hepmcEvent;
}

////////////////////////////////////////////////////////////////
void G4HepMCInterface::HepMC2G4(const HepMC::GenEvent* hepmcevt, 
				G4Event* g4event)
////////////////////////////////////////////////////////////////
{
  for(HepMC::GenEvent::vertex_const_iterator vitr= hepmcevt->vertices_begin();
      vitr != hepmcevt->vertices_end(); ++vitr ) { // loop for vertex ...

    // real vertex?
    G4bool qvtx=false;
    for (HepMC::GenVertex::particle_iterator 
	   pitr= (*vitr)->particles_begin(HepMC::children);
	 pitr != (*vitr)->particles_end(HepMC::children); ++pitr) {

      if (!(*pitr)->end_vertex() && (*pitr)->status()==1) {
	qvtx=true;
	break;
      }
    }
    if (!qvtx) continue;

    // check world boundary
    G4LorentzVector xvtx= (*vitr)-> position();
    if (! CheckVertexInsideWorld(xvtx.vect()*mm)) continue;

    // create G4PrimaryVertex and associated G4PrimaryParticles
    G4PrimaryVertex* g4vtx= 
      new G4PrimaryVertex(xvtx.x()*mm, xvtx.y()*mm, xvtx.z()*mm, 
			  xvtx.t()*mm/c_light);

    for (HepMC::GenVertex::particle_iterator 
	   vpitr= (*vitr)->particles_begin(HepMC::children);
	 vpitr != (*vitr)->particles_end(HepMC::children); ++vpitr) {

      if( (*vpitr)->status() != 1 ) continue;

      G4int pdgcode= (*vpitr)-> pdg_id();
      G4LorentzVector p= (*vpitr)-> momentum();
      G4PrimaryParticle* g4prim= 
	new G4PrimaryParticle(pdgcode, p.x()*GeV, p.y()*GeV, p.z()*GeV);

      g4vtx-> SetPrimary(g4prim);
    }
    g4event-> AddPrimaryVertex(g4vtx);
  } 
} 


///////////////////////////////////////////////////////
HepMC::GenEvent* G4HepMCInterface::GenerateHepMCEvent()
///////////////////////////////////////////////////////
{
  HepMC::GenEvent* aevent= new HepMC::GenEvent();
  return aevent;
}

//////////////////////////////////////////////////////////////
void G4HepMCInterface::GeneratePrimaryVertex(G4Event* anEvent)
//////////////////////////////////////////////////////////////
{
  // delete previous event object
  delete hepmcEvent;

  // generate next event
  hepmcEvent= GenerateHepMCEvent();
  if(! hepmcEvent) {
    G4Exception("G4HepMCInterface","GeneratePrimaryVertex",RunMustBeAborted,
              "HepMCInterface: no generated particles. run terminated..." );
    return;
  }
  HepMC2G4(hepmcEvent, anEvent);
}

#endif