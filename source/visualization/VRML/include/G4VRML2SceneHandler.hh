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
// $Id: G4VRML2SceneHandler.hh,v 1.12 2005/06/02 17:43:47 allison Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
// G4VRML2SceneHandler.hh
// Satoshi Tanaka & Yasuhide Sawada

#ifndef WIN32

#ifdef  G4VIS_BUILD_VRML_DRIVER

#ifndef G4VRML2_SCENE_HANDLER_HH
#define G4VRML2_SCENE_HANDLER_HH

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4VSceneHandler.hh"

#include "G4FRClient.hh"

class G4VRML2;
class G4VisAttributes;

class G4VRML2SceneHandler: public G4VSceneHandler {

	enum { MAX_CONNECTION_TRIAL = 10 } ;

// methods (public) 
public:
	G4VRML2SceneHandler(G4VRML2& system, const G4String& name = "");
	virtual ~G4VRML2SceneHandler();
	void AddSolid(const G4Box&);
	void AddSolid(const G4Cons&);
	void AddSolid(const G4Tubs&);
	void AddSolid(const G4Trd&);
	void AddSolid(const G4Trap&);
	void AddSolid(const G4Sphere&);
	void AddSolid(const G4Para&);
	void AddSolid(const G4Torus&);
        void AddSolid ( const G4Polycone& polycone ) {
          G4VSceneHandler::AddSolid (polycone);
        }
        void AddSolid ( const G4Polyhedra& polyhedra) {
          G4VSceneHandler::AddSolid (polyhedra);
        }
	void AddSolid(const G4VSolid&);
        void AddCompound ( const G4VTrajectory& traj) {
          G4VSceneHandler::AddCompound(traj);
        }
        void AddCompound ( const G4VHit& hit) {
          G4VSceneHandler::AddCompound(hit);
        }

	void BeginPrimitives(const G4Transform3D& objectTransformation);
	void EndPrimitives();

	void AddPrimitive(const G4Polyline&);
	void AddPrimitive(const G4Polyhedron&);
	void AddPrimitive(const G4NURBS&); 
	void AddPrimitive(const G4Text&); 
	void AddPrimitive(const G4Circle&);
	void AddPrimitive(const G4Square&);
	void AddPrimitive (const G4Polymarker& polymarker)
		{ G4VSceneHandler::AddPrimitive (polymarker); }
        void AddPrimitive (const G4Scale& scale) 
                { G4VSceneHandler::AddPrimitive (scale); }

	void ClearTransientStore();  // Used for triggering detector re-drawing.

	void BeginModeling();
	void EndModeling();

	void VRMLBeginModeling();
	void VRMLEndModeling();

	void connectPort(int max_trial = MAX_CONNECTION_TRIAL );
	void closePort();

// methods (private) 
private:
	void      SendMaterialNode        ( const G4VisAttributes*  pAV ); 
	void      SendMaterialNode        ();

	void      SendLineColor           ( const G4VisAttributes*  pAV ); 
	void      SendMarkerColor         ( const G4VMarker&  mark ) ;
	void      SendMarkerWorldPosition ( const G4VMarker&  mark ) ;

	G4double  GetMarkerHalfSize       ( const G4VMarker&  mark ) ;
	void      GetMarkerWorldPosition  (	const G4VMarker&  mark , 
						double* pX             ,
						double* pY             ,
						double* pZ              ) ;

	G4bool    IsPVPickable     ()                { return fPVPickable   ;}  
	void      SetPVPickability  ( G4bool on_off ) { fPVPickable = on_off ;}  
	G4double  SetPVTransparency ()  ; 
	G4double  GetPVTransparency () { return fPVTransparency ; } 

// data 
private:

	G4VRML2& fSystem;	// Graphics system for this scene.

	G4bool   fPVPickable     ;
	G4double fPVTransparency ;

	static G4int fSceneIdCount;

public: 
	G4FRClient fDest ;

};

#endif //G4VRML2_SCENE_HH
#endif //G4VIS_BUILD_VRML_DRIVER
#endif //WIN32
