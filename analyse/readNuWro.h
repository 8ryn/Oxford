//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 16 01:03:27 2015 by ROOT version 5.34/14
// from TTree gRooTracker/GENIE event tree rootracker format
// found on file: gntp.0.gtrac.root
//////////////////////////////////////////////////////////

#ifndef readNuWro_h
#define readNuWro_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TBits.h>
#include <TObjString.h>
#include <TLorentzVector.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

#define _ARRAYSIZE_ 100

class readNuWro {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //TBits           *EvtFlags;
   UInt_t          fNbits;
   UInt_t          fNbytes;
   UChar_t         fAllBits[1];   //[fNbytes]
   TObjString      *EvtCode;
   //TString         EvtCode_fString;
   Int_t           EvtNum;
   Int_t           StruckNucleonPDG;
   Double_t        EvtXSec;
   Double_t        EvtDXSec;
   Double_t        EvtWght;
   Double_t        EvtProb;
   Double_t        EvtVtx[4];
   Int_t           StdHepN;
   Int_t           StdHepPdg[_ARRAYSIZE_];   //[StdHepN]
   Int_t           StdHepStatus[_ARRAYSIZE_];   //[StdHepN]
   Double_t        StdHepX4[_ARRAYSIZE_][4];   //[StdHepN]
   Double_t        StdHepP4[_ARRAYSIZE_][4];   //[StdHepN]
   Double_t        StdHepPolz[_ARRAYSIZE_][3];   //[StdHepN]
   Int_t           StdHepFd[_ARRAYSIZE_];   //[StdHepN]
   Int_t           StdHepLd[_ARRAYSIZE_];   //[StdHepN]
   Int_t           StdHepFm[_ARRAYSIZE_];   //[StdHepN]
   Int_t           StdHepLm[_ARRAYSIZE_];   //[StdHepN]

   // List of branches
   TBranch        *b_EvtFlags_fNbits;   //!
   TBranch        *b_EvtFlags_fNbytes;   //!
   TBranch        *b_fAllBits;   //!
   //TBranch        *b_EvtCode_fString;   //!
   TBranch        *b_EvtCode;   //!
   TBranch        *b_EvtNum;   //!
   TBranch        *b_StruckNucleonPDG;
   TBranch        *b_EvtXSec;   //!
   TBranch        *b_EvtDXSec;   //!
   TBranch        *b_EvtWght;   //!
   TBranch        *b_EvtProb;   //!
   TBranch        *b_EvtVtx;   //!
   TBranch        *b_StdHepN;   //!
   TBranch        *b_StdHepPdg;   //!
   TBranch        *b_StdHepStatus;   //!
   TBranch        *b_StdHepX4;   //!
   TBranch        *b_StdHepP4;   //!
   TBranch        *b_StdHepPolz;   //!
   TBranch        *b_StdHepFd;   //!
   TBranch        *b_StdHepLd;   //!
   TBranch        *b_StdHepFm;   //!
   TBranch        *b_StdHepLm;   //!

   //=====
   void DumpEvent();
   Int_t GetTrueReacWithRESModification();
   void SetLv(TLorentzVector & lv, const Int_t ii);
   void GetParticles(const Int_t numode, Int_t & selp_pid, Int_t & selX_charge, Int_t & selX_pid, Int_t &kNuclearEmission, const Double_t protonMeVthres, const Double_t otherMeVthres, Int_t & nNeutrals);

 readNuWro():fChain(0){}
   virtual ~readNuWro();
   virtual void     Init(TTree *tree);
   virtual void     DoAnalysis(const TString filelist, const Int_t nQEtoread, const Int_t nREStoread, const TString tag, const TString outdir, const Bool_t isExpMode, const Double_t protonMeVthres=-999, const Double_t otherMeVthres=-999, const Double_t dpttwidth= -999);
};

#endif

#ifdef readNuWro_cxx

readNuWro::~readNuWro()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}


void readNuWro::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   
   //only 0 works!!
   fChain->SetMakeClass(0);
   EvtCode = new TObjString;

   fChain->SetBranchAddress("fNbits", &fNbits, &b_EvtFlags_fNbits);
   fChain->SetBranchAddress("fNbytes", &fNbytes, &b_EvtFlags_fNbytes);
   fChain->SetBranchAddress("fAllBits", &fAllBits, &b_fAllBits);
   fChain->SetBranchAddress("EvtCode", &EvtCode, &b_EvtCode);
   fChain->SetBranchAddress("EvtNum", &EvtNum, &b_EvtNum);
   fChain->SetBranchAddress("StruckNucleonPDG", &StruckNucleonPDG, &b_StruckNucleonPDG);
   fChain->SetBranchAddress("EvtXSec", &EvtXSec, &b_EvtXSec);
   fChain->SetBranchAddress("EvtDXSec", &EvtDXSec, &b_EvtDXSec);
   fChain->SetBranchAddress("EvtWght", &EvtWght, &b_EvtWght);
   fChain->SetBranchAddress("EvtProb", &EvtProb, &b_EvtProb);
   fChain->SetBranchAddress("EvtVtx", EvtVtx, &b_EvtVtx);
   fChain->SetBranchAddress("StdHepN", &StdHepN, &b_StdHepN);
   fChain->SetBranchAddress("StdHepPdg", StdHepPdg, &b_StdHepPdg);
   fChain->SetBranchAddress("StdHepStatus", StdHepStatus, &b_StdHepStatus);
   fChain->SetBranchAddress("StdHepX4", StdHepX4, &b_StdHepX4);
   fChain->SetBranchAddress("StdHepP4", StdHepP4, &b_StdHepP4);
   fChain->SetBranchAddress("StdHepPolz", StdHepPolz, &b_StdHepPolz);
   fChain->SetBranchAddress("StdHepFd", StdHepFd, &b_StdHepFd);
   fChain->SetBranchAddress("StdHepLd", StdHepLd, &b_StdHepLd);
   fChain->SetBranchAddress("StdHepFm", StdHepFm, &b_StdHepFm);
   fChain->SetBranchAddress("StdHepLm", StdHepLm, &b_StdHepLm);
}

#endif // #ifdef readNuWro_cxx
