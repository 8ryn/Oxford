#include "TTree.h"
#include "TFile.h"
#include <iostream>

class DeltaPCheck{
public:
  TTree *fChain;

  Double_t fParticleP4[100][4];
  Double_t fFullDeltaP;
  Int_t fNum;
  Int_t fParticlePDG[100];
  Double_t fFinProtP;

  TBranch *b_fParticleP4;
  TBranch *b_fFullDeltaP;
  TBranch *b_fNum;
  TBranch *b_fParticlePDG;
  TBranch *b_fFinProtP;

  virtual void Init(TTree *tree);
  void Test();
};

void DeltaPCheck::Init(TTree *tree){
  if (!tree) return;
  fChain = tree;
  fChain->SetMakeClass(0);

  fChain->SetBranchAddress("fParticleP4", fParticleP4, &b_fParticleP4);
  fChain->SetBranchAddress("fFullDeltaP", &fFullDeltaP, &b_fFullDeltaP);
  fChain->SetBranchAddress("fNum", &fNum, &b_fNum);
  fChain->SetBranchAddress("fParticlePDG", fParticlePDG, &b_fParticlePDG);
  fChain->SetBranchAddress("fFinProtP", &fFinProtP, &b_fFinProtP);
}


void DeltaPCheck::Test(){
  TString filelist = "/home/robertsb/summerInvestigation/analyse/outdata/NuWroB/Output_tagNuWroRFG_b_NuMu3000.root";

  TFile * fin = new TFile(filelist);
  TTree * tree = (TTree*) fin->Get("tree");

  DeltaPCheck::Init(tree);
  
  const Int_t nentries = fChain->GetEntries();

  for(Int_t jentry=0; jentry<nentries; jentry++){
    if(!fChain->GetEntry(jentry)){
      printf("readNuWro::DoAnalysis GetEntry ends at jentry %d\n", jentry);
      break;
     }
    for (Int_t i=0; i<fNum; i++){
      printf("Particle %d:\n" ,i+1);
      printf("PDG = %d \n", fParticlePDG[i]);
      printf("P[0] = %f, P[1] = %f, P[2] = %f, P[3] = %f\n", fParticleP4[i][0], fParticleP4[i][1], fParticleP4[i][2], fParticleP4[i][3]);
    }
    printf("Calculated DeltaP = %f \n", fFullDeltaP);
    printf("Final proton momentum = %f \n", fFinProtP);
    printf("\n Type \"q\" to quit, or anything else to move to next entry\n");
    TString resp;
    std::cin >> resp;
    if(resp =="q") return;
  }
}

