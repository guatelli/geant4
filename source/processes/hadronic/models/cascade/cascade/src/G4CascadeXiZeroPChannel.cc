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

#include "G4CascadeXiZeroPChannel.hh"


G4CascadeXiZeroPChannel::G4CascadeXiZeroPChannel()
  :G4CascadeChannel()
{
  G4int i, k, m;
  G4int start, stop;

  // Initialize multiplicity array

  for (m = 0; m < 6; m++) {
    start = x0pindex[m][0];
    stop = x0pindex[m][1];
    for (k = 0; k < 31; k++) {
      x0pMultiplicities[m][k] = 0.0;
      for (i = start; i < stop; i++) x0pMultiplicities[m][k] += x0pCrossSections[i][k];
    }
  }

  // Initialize total cross section array

  for (k = 0; k < 31; k++) {
    x0ptot[k] = 0.0;
    for (m = 0; m < 6; m++) x0ptot[k] += x0pMultiplicities[m][k];
  }

}

 
G4CascadeXiZeroPChannel::~G4CascadeXiZeroPChannel()
{;}


G4double G4CascadeXiZeroPChannel::getCrossSection(G4double ke) const
{
  std::pair<G4int, G4double> epair = interpolateEnergy(ke);
  G4int k = epair.first;
  G4double fraction = epair.second;

  return x0ptot[k] + fraction*(x0ptot[k+1] - x0ptot[k]);
}


G4int G4CascadeXiZeroPChannel::getMultiplicity(G4double ke) const
{
  G4double multint(0.);
  std::vector<G4double> sigma;

  std::pair<G4int, G4double> epair = interpolateEnergy(ke);
  G4int k = epair.first;
  G4double fraction = epair.second;

  for(G4int m = 0; m < 6; m++) {
    multint = x0pMultiplicities[m][k] 
         + fraction*(x0pMultiplicities[m][k+1] - x0pMultiplicities[m][k]);
      sigma.push_back(multint);
  }

  return sampleFlat(sigma);
}


std::vector<G4int> 
G4CascadeXiZeroPChannel::getOutgoingParticleTypes(G4int mult, G4double ke) const
{
  G4int i;
  G4double sigint(0.);
  std::vector<G4double> sigma;

  std::pair<G4int, G4double> epair = interpolateEnergy(ke);
  G4int k = epair.first;
  G4double fraction = epair.second;

  G4int start = x0pindex[mult-2][0];
  G4int stop = x0pindex[mult-2][1];
 
  for(i = start; i < stop; i++) {
      sigint = x0pCrossSections[i][k] 
          + fraction*(x0pCrossSections[i][k+1] - x0pCrossSections[i][k]);
      sigma.push_back(sigint);
  }
 
  G4int channel = sampleFlat(sigma);

  std::vector<G4int> kinds;

  if (mult == 2) {
    for(i = 0; i < mult; i++) kinds.push_back(x0p2bfs[channel][i]);
  } else if (mult == 3) {
    for(i = 0; i < mult; i++) kinds.push_back(x0p3bfs[channel][i]);
  } else if (mult == 4) {
    for(i = 0; i < mult; i++) kinds.push_back(x0p4bfs[channel][i]);
  } else if (mult == 5) {
    for(i = 0; i < mult; i++) kinds.push_back(x0p5bfs[channel][i]);
  } else if (mult == 6) {
    for(i = 0; i < mult; i++) kinds.push_back(x0p6bfs[channel][i]);
  } else if (mult == 7) {
    for(i = 0; i < mult; i++) kinds.push_back(x0p7bfs[channel][i]);
  } else {
    G4cout << " Illegal multiplicity " << G4endl;
  }

  return kinds;
}

// Total cross section as a function of kinetic energy
G4double G4CascadeXiZeroPChannel::x0ptot[31];

// Multiplicities as a function of kinetic energy
G4double G4CascadeXiZeroPChannel::x0pMultiplicities[6][31];


const G4int G4CascadeXiZeroPChannel::x0pindex[6][2] = 
   {{0, 3}, {3, 21}, {21,74}, {74,76}, {76,78}, {78,80}};

// Outgoing particle types of a given multiplicity

const G4int G4CascadeXiZeroPChannel::x0p2bfs[3][2] =
  {{1, 29}, {21,23}, {23,25}};

const G4int G4CascadeXiZeroPChannel::x0p3bfs[18][3] =
  {{1,17,21}, {3,21,21}, {1,13,23}, {2,17,23}, {7,21,23}, {5,23,23},
   {7,23,25}, {3,23,27}, {1,17,25}, {3,21,25}, {3,25,25}, {1,7,29},
   {2,3,29},  {11,21,29},{11,25,29},{15,23,29},{1,3,31},  {11,23,31}};  

const G4int G4CascadeXiZeroPChannel::x0p4bfs[53][4] =
  {{1,1,13,17},  {1,2,17,17},  {1,7,17,21},  {1,3,13,21},  {1,7,17,25},  
   {1,3,13,25},  {1,7,13,23},  {1,5,17,23},  {1,3,17,27},  {1,7,7,29},
   {1,3,5,29},   {1,11,13,29}, {1,15,17,29}, {1,3,7,31},   {1,11,17,31},
   {2,3,17,21},  {2,3,17,25},  {2,7,17,23},  {2,3,13,23},  {2,3,7,29},
   {2,11,17,29}, {2,3,3,31},   {3,7,21,21},  {11,17,21,21},{3,7,21,25},  
   {11,17,21,25},{7,7,21,23},  {3,5,21,23},  {11,13,21,23},{15,17,21,23},
   {3,3,21,27},  {7,11,21,29}, {3,15,21,29}, {3,11,21,31}, {7,7,23,25},  
   {3,5,23,25},  {11,13,23,25},{15,17,23,25},{3,7,25,25},  {11,17,25,25},
   {3,3,25,27},  {3,15,25,29}, {7,11,25,29}, {3,11,25,31}, {3,7,23,27},
   {11,17,23,27},{5,7,23,23},  {13,15,23,23},{7,15,23,29}, {5,11,23,29}, 
   {3,15,23,31}, {7,11,23,31}, {3,11,27,29}};

const G4int G4CascadeXiZeroPChannel::x0p5bfs[2][5] =
  {{1,7,7,7,29},  {1,3,5,7,29}};

const G4int G4CascadeXiZeroPChannel::x0p6bfs[2][6] =
  {{1,7,7,7,7,29},  {1,3,5,7,7,29}};

const G4int G4CascadeXiZeroPChannel::x0p7bfs[2][7] =
  {{1,7,7,7,7,7,29},  {1,3,5,7,7,7,29}};

// Cross sections for X0 p -> 2-7 body final states
// 
// first index:    0-2: channels for mult = 2
//                3-20: channels for mult = 3 
//               21-73: channels for mult = 4
//               74-75: channels for mult = 5
//               76-77: channels for mult = 6
//               78-79: channels for mult = 7
//
// second index: kinetic energy
// 
const G4float G4CascadeXiZeroPChannel::x0pCrossSections[80][31] = {
 //
 // multiplicity 2 (3 channels)
 //
 // X0 p
 {16.00, 9.60, 7.00, 6.80, 6.60, 6.40, 6.20, 6.00, 5.82, 5.64,
   5.45, 4.80, 4.58, 4.20, 3.80, 3.50, 3.20, 3.10, 2.95, 2.80,
   2.65, 2.55, 2.45, 2.35, 2.25, 2.15, 2.10, 2.05, 2.04, 2.03, 1.95},

 // L S+ 
 { 0.0,  0.0,  0.0,  1.80, 3.60, 5.40, 7.20, 9.00, 9.82,10.64,
  11.45,14.40,12.97,11.31, 8.38, 5.45, 2.50, 2.10, 1.90, 1.70,
   1.50, 1.40, 1.30, 1.20, 1.10, 1.05, 1.00, 0.95, 0.94, 0.93, 0.85},

 // S0 S+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.55, 1.09,
   1.64, 3.60, 4.32, 3.77, 2.80, 2.00, 1.50, 1.40, 1.30, 1.20,
   1.10, 1.00, 0.95, 0.90, 0.85, 0.80, 0.75, 0.70, 0.69, 0.68, 0.60},

 //
 //  multiplicity 3 (18 channels)
 //
 // L p K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.09, 0.18, 
   0.27, 0.60, 0.71, 0.90, 1.10, 1.00, 0.90, 0.80, 0.68, 0.56,
   0.40, 0.30, 0.20, 0.10, 0.07, 0.05, 0.03, 0.01, 0.01, 0.01, 0.0},

 // L L pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.46, 0.91,
   1.36, 3.00, 1.93, 1.80, 1.70, 1.50, 1.30, 1.10, 1.00, 0.90,
   0.75, 0.60, 0.50, 0.40, 0.30, 0.25, 0.20, 0.15, 0.14, 0.13, 0.10},

 // S+ p K-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.01, 0.05, 0.10, 0.15, 0.17, 0.17, 0.15, 0.13, 
   0.10, 0.08, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01, 0.0},

 // S+ n K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.01, 0.05, 0.10, 0.15, 0.17, 0.17, 0.15, 0.13,
   0.10, 0.08, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01, 0.0},

 // S+ L pi0  
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.55, 1.09,
   1.64, 3.60, 3.36, 3.10, 3.00, 2.80, 2.60, 2.30, 2.00, 1.80,
   1.60, 1.50, 1.40, 1.30, 1.20, 1.15, 1.10, 1.05, 1.04, 1.03, 0.90},

 // S+ S+ pi-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.10, 0.15, 0.20, 0.22, 0.23, 0.20, 0.17, 0.15,
   0.12, 0.10, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // S+ S0 pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.10, 0.15, 0.20, 0.22, 0.23, 0.20, 0.17, 0.15,
   0.12, 0.10, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // S+ S- pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.10, 0.15, 0.20, 0.22, 0.23, 0.20, 0.17, 0.15,
   0.12, 0.10, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // S0 p K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.01, 0.05, 0.10, 0.15, 0.17, 0.17, 0.15, 0.13,
   0.10, 0.08, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01, 0.0},

 // S0 L pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.10, 0.15, 0.20, 0.22, 0.23, 0.20, 0.17, 0.15,
   0.12, 0.10, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // S0 S0 pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.10, 0.15, 0.20, 0.22, 0.23, 0.20, 0.17, 0.15,
   0.12, 0.10, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // X0 p pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.14, 0.27,
   0.41, 0.90, 1.02, 1.50, 1.40, 1.10, 1.00, 0.90, 0.80, 0.65,
   0.50, 0.40, 0.30, 0.25, 0.20, 0.15, 0.12, 0.10, 0.09, 0.09, 0.05},

 // X0 n pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.14, 0.27,
   0.41, 0.90, 1.02, 1.50, 1.40, 1.10, 1.00, 0.90, 0.80, 0.65,
   0.50, 0.40, 0.30, 0.25, 0.20, 0.15, 0.12, 0.10, 0.09, 0.09, 0.05},

 // X0 L K+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03,
   0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01},

 // X0 S0 K+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03,
   0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01},

 // X0 S+ K0 
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03,
   0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01},

 // X- p pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.46, 0.91,
   1.36, 3.00, 3.56, 3.32, 3.10, 3.10, 3.00, 2.80, 2.60, 2.40,
   2.20, 2.00, 1.90, 1.80, 1.70, 1.65, 1.60, 1.55, 1.54, 1.53, 1.40},

 // X- S+ K+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02, 0.03,
   0.03, 0.03, 0.03, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01},

 //
 //  multiplicity 4 (53 channels)
 //
 // p p K0bar K-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.11, 0.14, 0.13, 0.12, 0.11,
   0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // p n K0bar K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.11, 0.14, 0.13, 0.12, 0.11,
   0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // p L K0bar pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.11, 0.14, 0.13, 0.12, 0.11,
   0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // p L K- pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.11, 0.14, 0.13, 0.12, 0.11,
   0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // p S0 K0bar pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.11, 0.14, 0.13, 0.12, 0.11,
   0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // p S0 K- pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.11, 0.14, 0.13, 0.12, 0.11,
   0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // p S+ K- pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.11, 0.14, 0.13, 0.12, 0.11,
   0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // p S+ K0bar pi-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.11, 0.14, 0.13, 0.12, 0.11,
   0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // p S- K0bar pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.11, 0.14, 0.13, 0.12, 0.11,
   0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // p X0 2pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.04, 0.09, 0.14, 0.20, 0.25, 0.20, 0.17,
   0.15, 0.12, 0.10, 0.07, 0.05, 0.04, 0.03, 0.02, 0.02, 0.02, 0.01},

 // p X0 pi+ pi-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.06, 0.23, 0.40, 0.57, 0.75, 0.70, 0.60,
   0.50, 0.40, 0.30, 0.25, 0.20, 0.15, 0.10, 0.08, 0.07, 0.07, 0.04},

 // p X0 K+ K-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // p X0 K0bar K0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // p X- pi+ pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // p X- K+ K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // n L K0bar pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // n S0 K0bar pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // n S+ K0bar pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // n S+ K- pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // n X0 pi+ pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.11, 0.14, 0.15, 0.14, 0.13,
   0.12, 0.11, 0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.05, 0.04, 0.03},

 // n X0 K+ K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // n X- 2pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.13, 0.12, 0.11,
   0.10, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.03, 0.03, 0.01},

 // L L pi+ pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.02, 0.01, 0.01},

 // L L K+ K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.02, 0.01, 0.01},

 // L S0 pi+ pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.02, 0.01, 0.01},

 // L S0 K+ K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.02, 0.01, 0.01},

 // L S+ 2pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.07, 0.34, 0.60, 0.87, 1.14, 1.50, 1.40,
   1.30, 1.20, 1.10, 1.00, 0.85, 0.75, 0.60, 0.50, 0.48, 0.46, 0.30},

 // L S+ pi+ pi-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.12, 0.56, 1.00, 1.45, 1.90, 2.50, 2.40,
   2.30, 2.10, 1.95, 1.80, 1.65, 1.50, 1.35, 1.20, 1.18, 1.16, 0.90},

 // L S+ K+ K-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.02, 0.01, 0.01},

 // L S+ K0bar K0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.05, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.02, 0.01, 0.01},

 // L S- 2pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.12, 0.56, 1.00, 1.45, 1.90, 2.50, 2.20,
   2.05, 1.90, 1.75, 1.60, 1.45, 1.30, 1.10, 1.00, 0.88, 0.86, 0.70},

 // L X0 K+ pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // L X0 K0 pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // L X- K+ pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // S0 S+ 2pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.04, 0.12, 0.20, 0.28, 0.36, 0.24, 0.20,
   0.17, 0.10, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S0 S+ pi+ pi-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.06, 0.19, 0.33, 0.46, 0.60, 0.40, 0.25,
   0.15, 0.10, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S0 S+ K+ K-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S0 S+ K0 K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S0 S0 pi+ pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S0 S0 K+ K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S0 S- 2pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.06, 0.19, 0.33, 0.46, 0.60, 0.40, 0.25,
   0.15, 0.10, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S0 X0 K0 pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // S0 X0 K+ pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // S0 X- K+ pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // S+ S- pi+ pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S+ S- K+ K0bar
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S+ S+ pi- pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S+ S+ K- K0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.04, 0.10, 0.13, 0.12, 0.11, 0.10,
   0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01, 0.01, 0.01},

 // S+ X0 K0 pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // S+ X0 K+ pi-
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // S+ X- K0 pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // S+ X- K+ pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 // S- X0 K+ pi+
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},

 //
 //  multiplicity 5 (2 channels)
 // 
 // p X0 3pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
   0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

 // p X0 pi+ pi- pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
   0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

 //
 //  multiplicity 6 (2 channels)
 // 
 // p X0 4pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01,
   0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

 // p X0 pi+ pi- 2pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01,
   0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

 //
 //  multiplicity 7 (2 channels)
 // 
 // p X0 5pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
   0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

 // p X0 pi+ pi- 3pi0
 { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
   0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
   0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01} };
