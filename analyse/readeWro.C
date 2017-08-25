#define readeWro_cxx
#include "readeWro.h"
#include "TestUtils.h"

#include <iostream>

void readeWro::DumpEvent()
{
  for(Int_t ii=0; ii<StdHepN; ii++){
    printf("EvtNum %d EvtCode %s ii %d StdHepPdg %d StdHepStatus %d StdHepP4 %f %f %f %f\n", EvtNum, EvtCode->String().Data(), ii, StdHepPdg[ii], StdHepStatus[ii], StdHepP4[ii][0], StdHepP4[ii][1], StdHepP4[ii][2], StdHepP4[ii][3]);
  }
}

//Sets Lorentzvector lv to take the value of particle ii
void readeWro::SetLv(TLorentzVector & lv, const Int_t ii)
{
  //double	StdHepP4[350][4]		4-p (px,py,pz,E) of particle in LAB frame (GeV)
  lv.SetXYZT(StdHepP4[ii][0],StdHepP4[ii][1],StdHepP4[ii][2],StdHepP4[ii][3]);
}

void readeWro::DoAnalysis(const TString filelist, const TString tag, const TString outdir){

  std::cout << "Starting analysis of " << filelist << endl;

  //Opens file where data is stored, creates appropriate tree to access data and set Branch addresses/pointers
  TFile * fin = new TFile(filelist);
  TTree * tmptree = (TTree*) fin->Get("nRooTracker");
  Init(tmptree);  //Defined within readeWro.h

  //Opens output file
  const TString oldfilename = Form("%sOutput_tag%s.root", outdir.Data(), tag.Data());
  TFile *fout = new TFile(oldfilename, "recreate");

  TTree *tout = TestUtils::GetTree();

  const Int_t nentries = fChain->GetEntries();

  for(Int_t jentry=0; jentry<nentries; jentry++){
    
    // Stops loop if no more entries, but more importantly updates values of variables to that of the next entry
    if(!fChain->GetEntry(jentry)){
      printf("readeWro::DoAnalysis GetEntry ends at jentry %d\n", jentry);
      break;
    }

    //Less than 3 particles should be impossible so exit
    if(StdHepN<3){
      printf("readeWro ::DoAnalysis StdHepN < 3: %d, impossible, exit\n", StdHepN);
      DumpEvent();
      exit(1);
    }
    
   //Sets the output variables for the current entry

    //Reset the count (may be worth creating a TestUtils function to do this for all variables)
    Int_t nProton = 0;
    Int_t nNeutron = 0;
    TLorentzVector lProton;
    Double_t protonmaxe = -1e10;

    for( Int_t partN=3; partN < StdHepN; partN++){
   
      //Counts the nucleons and finds max energy proton
      if(StdHepPdg[partN]== 2212){
	nProton += 1;
	if(StdHepP4[partN][3]>protonmaxe){
	  protonmaxe = StdHepP4[partN][3];
	  SetLv(lProton,partN);
	}
      }
      else if(StdHepPdg[partN]== 2112) nNeutron += 1;

    }
    if(nProton==0) continue; //Can't work with events with no proton so filter these events out
    
    //Not needed assuming the method below to assign nucmass works
    //Double_t nucmass = TMath::Sqrt(StdHepP4[1][3]*StdHepP4[1][3]-StdHepP4[1][0]*StdHepP4[1][0]-StdHepP4[1][1]*StdHepP4[1][1]-StdHepP4[1][2]*StdHepP4[1][2]);

    //Sets LorentzVectors of important particles
    TLorentzVector lIniElec;
    TLorentzVector lIniNuc;
    TLorentzVector lFinElec;
    SetLv(lIniElec,0);
    SetLv(lIniNuc, 1);
    SetLv(lFinElec,2);

    Double_t nucmass = lIniNuc.M();
    if(nucmass > 0.9392) continue;  //This filters out events where the initial nucleon is a neutron, makes minimal difference but may be worth considering whether this is a good idea

    TestUtils::SetFullDelta(lIniElec, lIniNuc, lFinElec, lProton);
    TestUtils::SetDeltaPt(lIniElec, lIniNuc, lFinElec, lProton);
    
    TestUtils::fIniElecP = lIniElec.P();
    TestUtils::fIniNucP = lIniNuc.P();
    TestUtils::fFinProtP = lProton.P();
    TestUtils::fFinLeptP = lFinElec.P();
    
    TestUtils::fFinalProtons = nProton;
    TestUtils::fFinalNeutrons = nNeutron;
    TestUtils::fFinalNucleons = nProton + nNeutron;
    // TestUtils::SetProtonVec(lProton);

    TestUtils::fNum = StdHepN;
    TestUtils::fNucleonMass = nucmass;
    
    for( Int_t partN=0; partN < StdHepN; partN++){
      TestUtils::SetParticlePDG(partN, StdHepPdg[partN]);
      TestUtils::SetParticleP4(partN, StdHepP4[partN]);

    }

    tout->Fill();
  }

  tout->Write();
  fout->Save();
  fout->Close();
  delete fout;

  std::cout << "Analysis of " << filelist << " complete." << endl;

}
