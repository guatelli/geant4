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
// $Id: G4VRML1FileViewer.hh,v 1.7 2001/09/18 07:53:08 stanaka Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
// G4VRML1FileViewer.hh
// Satoshi Tanaka and Yasuhide Sawada

#ifndef G4VRML1FILE_VIEWER_HH
#define G4VRML1FILE_VIEWER_HH

#include "G4VViewer.hh"
#include "globals.hh"

class G4VRML1FileSceneHandler;

class G4VRML1FileViewer: public G4VViewer {
public:
	G4VRML1FileViewer(G4VRML1FileSceneHandler& scene, const G4String& name = "");
	virtual ~G4VRML1FileViewer();
	void ClearView();
	void DrawView();
	void ShowView();
	void FinishView();
private:
	void SetView();

private:
	G4VRML1FileSceneHandler& fSceneHandler; // Reference to Graphics Scene for this view.
};

#endif //G4VRML1File_VIEW_HH
