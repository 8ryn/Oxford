#include "TTree.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include <iostream>

class AnaTaskCompare{
public:
  TTree *fChain;

  TLorentzVector * fProtonSim;

  TBranch *b_fProtonSim;

  virtual void Init(TTree *tree);
  void Test();
};

void AnaTaskCompare::Init(TTree *tree){
  if (!tree) return;
  fChain = tree;
  fChain->SetMakeClass(0);

  fChain->SetBranchAddress("fProtonSim",&fProtonSim, &b_fProtonSim);
}


void AnaTaskCompare::Test(){
TString filelist = "/home/robertsb/summerInvestigation/analyse/outdata/NuWro/PureMCoutput_tagNuWroRFG_b_NuMuB3000_beam14_isExpMode0_protonMeVthres-999_otherMeVthres-999_dpttwidth-999_myEntries_1000000_PX_-999_0_0_qe_-999_694698_685400_EStatus0_EHepN0_EMEC0_EMom0.root";

  TFile * fin = new TFile(filelist);
  TTree * tree = (TTree*) fin->Get("tree");

  AnaTaskCompare::Init(tree);
  
  const Int_t nentries = fChain->GetEntries();

  for(Int_t jentry=0; jentry<nentries; jentry++){
    if(!fChain->GetEntry(jentry)){
      printf("readeWro::DoAnalysis GetEntry ends at jentry %d\n", jentry);
      break;
     }
    printf("Final Proton Momentum = %f \n", fProtonSim->Vect().Mag());
    printf("\n Type \"q\" to quit, or anything else to move to next entry\n");
    TString resp;
    std::cin >> resp;
    if(resp =="q") return;
  }
}

