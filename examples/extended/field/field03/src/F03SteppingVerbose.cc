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
// $Id: F03SteppingVerbose.cc,v 1.3 2001/10/15 17:20:52 gcosmo Exp $
// GEANT4 tag $Name: geant4-05-00 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#include "F03SteppingVerbose.hh"

#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

F03SteppingVerbose::F03SteppingVerbose()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

F03SteppingVerbose::~F03SteppingVerbose()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void F03SteppingVerbose::StepInfo()
{
  CopyState();
  
  G4int prec = G4cout.precision(8);

  if( verboseLevel >= 1 ){
    if( verboseLevel >= 4 ) VerboseTrack();
    if( verboseLevel >= 3 ){
      G4cout << G4endl;    
      G4cout << G4std::setw( 5) << "#Step#"     << " "
	     << G4std::setw(10) << "X"          << "    "
	     << G4std::setw(10) << "Y"          << "    "  
	     << G4std::setw(10) << "Z"          << "    "
	     << G4std::setw(10) << "KineE"      << " "
	     << G4std::setw(10) << "dEStep"     << " "  
	     << G4std::setw(10) << "StepLeng"     
	     << G4std::setw(10) << "TrakLeng" 
	     << G4std::setw(10) << "NextVolu" 
	     << G4std::setw(10) << "Process"   
	     << G4std::setw(10) << "Dir_x"        << "    "
	     << G4std::setw(10) << "Dir_y"        << "    "  
	     << G4std::setw(10) << "Dir_z"        << "    "
             << G4endl;	          
    }

    G4cout << G4std::setw( 5) << fTrack->GetCurrentStepNumber() << " "
	   << G4std::setw(10) << G4BestUnit(fTrack->GetPosition().x(),"Length")
	   << G4std::setw(10) << G4BestUnit(fTrack->GetPosition().y(),"Length")
	   << G4std::setw(10) << G4BestUnit(fTrack->GetPosition().z(),"Length")
	   << G4std::setw(10) << G4BestUnit(fTrack->GetKineticEnergy(),"Energy")
	   << G4std::setw(10) << G4BestUnit(fStep->GetTotalEnergyDeposit(),"Energy")
	   << G4std::setw(10) << G4BestUnit(fStep->GetStepLength(),"Length")
	   << G4std::setw(10) << G4BestUnit(fTrack->GetTrackLength(),"Length");

    if( fTrack->GetNextVolume() != 0 ) { 
      G4cout << G4std::setw(10) << fTrack->GetVolume()->GetName();
    } else {
      G4cout << G4std::setw(10) << "OutOfWorld";
    }

    if(fStep->GetPostStepPoint()->GetProcessDefinedStep() != 0){
      G4cout << "  " 
             << G4std::setw(10) << fStep->GetPostStepPoint()->GetProcessDefinedStep()
	                                ->GetProcessName();
    } else {
      G4cout << "   UserLimit";
    }

    G4cout << G4std::setw(12) << G4BestUnit(fTrack->GetMomentumDirection().x(),"Length")
	   << G4std::setw(12) << G4BestUnit(fTrack->GetMomentumDirection().y(),"Length")
	   << G4std::setw(12) << G4BestUnit(fTrack->GetMomentumDirection().z(),"Length");

    G4cout << G4endl;

    if( verboseLevel == 2 ){
      G4int tN2ndariesTot = fN2ndariesAtRestDoIt +
	                    fN2ndariesAlongStepDoIt +
	                    fN2ndariesPostStepDoIt;
      if(tN2ndariesTot>0){
	G4cout << "    :----- List of 2ndaries - "
	       << "#SpawnInStep=" << G4std::setw(3) << tN2ndariesTot 
	       << "(Rest="  << G4std::setw(2) << fN2ndariesAtRestDoIt
	       << ",Along=" << G4std::setw(2) << fN2ndariesAlongStepDoIt
	       << ",Post="  << G4std::setw(2) << fN2ndariesPostStepDoIt
	       << "), "
	       << "#SpawnTotal=" << G4std::setw(3) << (*fSecondary).size()
	       << " ---------------"
	       << G4endl;

	for(size_t lp1=(*fSecondary).size()-tN2ndariesTot; 
                   lp1<(*fSecondary).size(); lp1++){
	  G4cout << "    : "
		 << G4std::setw(6)
		 << G4BestUnit((*fSecondary)[lp1]->GetPosition().x(),"Length")
		 << G4std::setw(6)
		 << G4BestUnit((*fSecondary)[lp1]->GetPosition().y(),"Length")
		 << G4std::setw(6)
		 << G4BestUnit((*fSecondary)[lp1]->GetPosition().z(),"Length")
		 << G4std::setw(6)
		 << G4BestUnit((*fSecondary)[lp1]->GetKineticEnergy(),"Energy")
		 << G4std::setw(10)
		 << (*fSecondary)[lp1]->GetDefinition()->GetParticleName();
	  G4cout << G4endl;
	}
              
	G4cout << "    :-----------------------------"
	       << "----------------------------------"
	       << "-- EndOf2ndaries Info ---------------"
	       << G4endl;
      }
    }
    
  }
  G4cout.precision(prec);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void F03SteppingVerbose::TrackingStarted()
{

  CopyState();
G4int prec = G4cout.precision(3);
  if( verboseLevel > 0 ){

    G4cout << G4std::setw( 5) << "Step#"      << " "
           << G4std::setw( 6) << "X"          << "    "
	   << G4std::setw( 6) << "Y"          << "    "  
	   << G4std::setw( 6) << "Z"          << "    "
	   << G4std::setw( 9) << "KineE"      << " "
	   << G4std::setw( 9) << "dEStep"     << " "  
	   << G4std::setw(10) << "StepLeng"  
	   << G4std::setw(10) << "TrakLeng"
	   << G4std::setw(10) << "Volume"     << "  "
	   << G4std::setw(10) << "Process"    << G4endl;	     

    G4cout << G4std::setw( 5) << fTrack->GetCurrentStepNumber() << " "
	   << G4std::setw( 6) << G4BestUnit(fTrack->GetPosition().x(),"Length")
	   << G4std::setw( 6) << G4BestUnit(fTrack->GetPosition().y(),"Length")
	   << G4std::setw( 6) << G4BestUnit(fTrack->GetPosition().z(),"Length")
	   << G4std::setw( 6) << G4BestUnit(fTrack->GetKineticEnergy(),"Energy")
	   << G4std::setw( 6) << G4BestUnit(fStep->GetTotalEnergyDeposit(),"Energy")
	   << G4std::setw( 6) << G4BestUnit(fStep->GetStepLength(),"Length")
	   << G4std::setw( 6) << G4BestUnit(fTrack->GetTrackLength(),"Length");

    if(fTrack->GetNextVolume()){
      G4cout << G4std::setw(10) << fTrack->GetVolume()->GetName();
    } else {
      G4cout << G4std::setw(10) << "OutOfWorld";
    }
    G4cout  << "    initStep" << G4endl;
  }
  G4cout.precision(prec);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....