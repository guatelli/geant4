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
// $Id: FCALTBEventAction.cc,v 1.11 2004/11/29 18:03:07 ribon Exp $
// GEANT4 tag $Name: geant4-07-01 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "FCALTBEventAction.hh"

#include "FCALTBEventActionMessenger.hh"

#include "FCALRunAction.hh"

#include "FCALCalorHit.hh"

#include <vector>

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include "FCALSteppingAction.hh"

#include "FCALAnalysisManager.hh"

#include "G4ios.hh"
#include "iostream.h"
#include "fstream.h"

#ifdef G4ANALYSIS_USE
  #include <AIDA/AIDA.h>
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

FCALTBEventAction::FCALTBEventAction(FCALSteppingAction* SA)
  :calorimeterCollID(-1),drawFlag("all"),printModulo(10), StepAction(SA), eventMessenger(0)
{
  eventMessenger = new FCALTBEventActionMessenger(this);
  runManager = new FCALRunAction();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

FCALTBEventAction::~FCALTBEventAction()
{
  delete eventMessenger;
  eventMessenger = 0;
  delete  runManager;
  runManager = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void FCALTBEventAction::BeginOfEventAction(const G4Event* evt)
{  
  G4int evtNb = evt->GetEventID();
    if (evtNb%printModulo == 0)
    { 
      G4cout << "\n---> Begin of event: " << evtNb+1 << G4endl;
//      HepRandom::showEngineStatus();
    }
    
  NTracksOutOfWorld = 0;
  NSecondaries = 0;
 
  StepAction->initialize(evtNb+1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void FCALTBEventAction::EndOfEventAction(const G4Event*)
{
#ifdef G4ANALYSIS_USE
    FCALAnalysisManager* analysis = FCALAnalysisManager::getInstance();
#endif

  G4int i,j;
  NTracksOutOfWorld = StepAction->GetOutOfWorldTracks(0, 0); 
  G4cout << "N Tracks out of world " << NTracksOutOfWorld << G4endl;

  // Write Leaving Particles in File
  //--------------------------------
  G4String FileName1 = "OutTracks_802_1mm.dat";
  std::ios::openmode iostemp1;
  if(Init1 == 0) {
    iostemp1 = std::ios::out;
    Init1++;
  } else {
    iostemp1 = std::ios::out|std::ios::app; // std::ios::app;  
  };
  ofstream OutTracks(FileName1, iostemp1);

  OutTracks << NTracksOutOfWorld << G4endl;

  G4double OutOfWorld;
  for(i=1; i<= NTracksOutOfWorld ; i++){
    for(j=1; j<11 ; j++) {
      //      G4double OutOfWorld = StepAction->GetOutOfWorldTracks(i,j);
      OutOfWorld = StepAction->GetOutOfWorldTracks(i,j);
      OutTracks << OutOfWorld << " " ; 
    }
    OutTracks << std::endl;
    // G4double OutOfWorld2 = StepAction->GetOutOfWorldTracks(i,j);
  } 
  OutTracks.close();

#ifdef G4ANALYSIS_USE
    analysis->getfhisto_1()->fill(NTracksOutOfWorld);
#endif

  NSecondaries = StepAction->GetSecondaries(0,0);
  G4cout << "N Scondaries " << NSecondaries << G4endl;   
  
  // Write Secondary Particles in File
  //----------------------------------
  G4String FileName2 = "SecndTracks_802_1mm.dat";
  std::ios::openmode iostemp2;
  if(Init2 == 0) {
    iostemp2 = std::ios::out;
    Init2++;
  } else {
    iostemp2 = std::ios::out|std::ios::app; // std::ios::app;  
  };
  
  ofstream SecndTracks(FileName2, iostemp2);
  
  SecndTracks << NSecondaries << std::endl;

  G4double Secondary;  
  for(i=1; i<= NSecondaries ; i++){
    for(j=1; j<11 ; j++) {
      Secondary = StepAction->GetSecondaries(i,j);
      SecndTracks << Secondary  << " " ; 
    }
    SecndTracks << std::endl;
    // G4double Secondary2 = StepAction->GetSecondaries(i,j);
  }
  SecndTracks.close();
  
#ifdef G4ANALYSIS_USE
    analysis->getfhisto_2()->fill(NSecondaries);
#endif

  // Write Edep in FCAL1 and FCAL2 
  G4String FileName3 = "EdepFCAL_802_1mm.dat";
  std::ios::openmode iostemp3;
  if(Init3 == 0) {
    iostemp3 = std::ios::out;
    Init3++;
  } else {
    iostemp3 = std::ios::out|std::ios::app; // std::ios::app;  
  };
  
  ofstream EdepFCAL(FileName3, iostemp3);
  
  G4double EmEdep  = StepAction->GetEdepFCAL("FCALEm");
  G4double HadEdep = StepAction->GetEdepFCAL("FCALHad");

  EdepFCAL << EmEdep << " ";
  EdepFCAL << HadEdep; 
  EdepFCAL << std::endl;
  EdepFCAL.close();

#ifdef G4ANALYSIS_USE
  analysis->getfhisto_3()->fill(EmEdep);
  analysis->getfhisto_4()->fill(HadEdep);
#endif

  G4cout<<"EmEdep is="<<EmEdep<<G4endl;
  G4cout<<"HadEdep is="<<HadEdep<<G4endl;

  G4cout << "Edep in FCAL1 FCAl2 : " << StepAction->GetEdepFCAL("FCALEm") << " ";
  G4cout << StepAction->GetEdepFCAL("FCALHad") << G4endl;
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
