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
// $Id: G4PrimaryTransformer.hh,v 1.10 2005/04/27 01:32:46 asaim Exp $
// GEANT4 tag $Name: geant4-07-01 $
//

#ifndef G4PromaryTransformer_h 
#define G4PromaryTransformer_h 1

#include "G4TrackVector.hh"
#include "G4ParticleTable.hh"
#include "globals.hh"
class G4Event;
class G4PrimaryVertex;
#include "G4PrimaryParticle.hh"

// class description:
//
//  This class is exclusively used by G4EventManager for the conversion
// from G4PrimaryVertex/G4PrimaryParticle to G4DynamicParticle/G4Track.
//

class G4PrimaryTransformer
{
  public:
    G4PrimaryTransformer();
    virtual ~G4PrimaryTransformer();
    
    G4TrackVector* GimmePrimaries(G4Event* anEvent, G4int trackIDCounter=0);
    void CheckUnknown();

  protected:
    G4TrackVector TV;
    G4ParticleTable* particleTable;
    G4int verboseLevel;
    G4int trackID;

    G4ParticleDefinition* unknown;
    G4bool unknownParticleDefined;

  public:
    inline void SetVerboseLevel(G4int vl)
    { verboseLevel = vl; };

  public: //with description
    void SetUnknnownParticleDefined(G4bool vl);
    // By invoking this Set method, the user can alter the treatment of unknown
    // particle. The ideal place to invoke this method is in the BeginOfRunAction.

    inline G4bool GetUnknownParticleDefined() const
    { return unknownParticleDefined; }

  protected:
    void GenerateTracks(G4PrimaryVertex* primaryVertex);
    void GenerateSingleTrack(G4PrimaryParticle* primaryParticle,
              G4double x0,G4double y0,G4double z0,G4double t0,G4double wv);
    void SetDecayProducts(G4PrimaryParticle* mother,
                            G4DynamicParticle* motherDP);
    G4bool CheckDynamicParticle(G4DynamicParticle*DP);

  protected: //with description
  // Following two virtual methods are provided to customize the use of PrimaryTransformer
  // for particle types exotic to Geant4.

    virtual G4ParticleDefinition* GetDefinition(G4PrimaryParticle*pp);
    // Return appropriate G4ParticleDefinition w.r.t. the primary particle. 
    // If NULL is returned, the particle will not be treated as a track, but its daughters
    // will be examined in case it has "pre-assigned decay products".

    virtual G4bool IsGoodForTrack(G4ParticleDefinition*pd);
    // Return true if a primary particle should be converted into a track.
    // By default, all particles of non-shortlived and shortlived with valid decay
    // tables are converted.
};

#endif


