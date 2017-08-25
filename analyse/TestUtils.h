#include "TTree.h"
#include "ElectronTools.h"
#include "TMath.h"

class TestUtils{

 public:
  static Int_t fNum;
  static Int_t fParticlePDG[100];
  static Double_t fParticleP4[100][4];
  static Int_t fFinalNucleons;
  static Int_t fFinalProtons;
  static Int_t fFinalNeutrons;
  static Double_t fIniNucP;
  static Double_t fIniElecP;
  static Double_t fFinProtP;
  static Double_t fFinLeptP;
  static Double_t fFinLeptPt;
  static Double_t fFinProtPt;
  static Double_t fFullDeltaP;
  static Double_t fFullDeltaPt;  //Transverse component
  static Double_t fFullDeltaPl;  //Longitudinal component
  static Double_t fFullDeltaE;
  static Double_t fVisiDeltaE;
  static Double_t fDeltaPt;
  static Double_t fTestDeltaPt; //Calculated differently in order to investigate strange results
  static Double_t fAlphat;
  static Double_t fPhit;
  static Double_t fQ2;
  static Double_t fNucleonMass;

  // static const TLorentzVector * fProtonVec;

  static void SetParticlePDG( const Int_t parN, const Int_t var){
    fParticlePDG[parN] = var;
  }
  static int GetParticlePDG(const Int_t parN){ return fParticlePDG[parN];}
  static void SetParticleP4(const Int_t parN, Double_t p4[4]){
    for(Int_t i=0; i<4; i++){
      fParticleP4[parN][i] = p4[i];
    }
  }

  //static void SetProtonVec(const TLorentzVector &lproton);
  static void SetFullDelta( const TLorentzVector &lIniElec, const TLorentzVector &lIniNuc, const TLorentzVector &lFinElec, const TLorentzVector &lProton);
  static void SetDeltaPt(const TLorentzVector &lIniElec, const TLorentzVector &lIniNuc, const TLorentzVector &lFinElec, const TLorentzVector &lProton);

  static TTree * GetTree(){

    TTree * tout = new TTree("tree", "tree");

    // const Int_t spl =1;

    tout->Branch("fNum", &fNum, "fNum/I");
    tout->Branch("fParticlePDG", fParticlePDG, "fParticlePDG[fNum]/I");
    tout->Branch("fParticleP4",  fParticleP4, "fParticleP4[fNum][4]/D");
    tout->Branch("fFinalNucleons", &fFinalNucleons, "fFinalNucleons/I");
    tout->Branch("fFinalProtons", &fFinalProtons, "fFinalProtons/I");
    tout->Branch("fIniNucP", &fIniNucP, "fIniNucP/D");
    tout->Branch("fIniElecP", &fIniElecP, "fIniElecP/D");
    tout->Branch("fFinProtP", &fFinProtP, "fFinProtP/D");
    tout->Branch("fFinLeptP", &fFinLeptP, "fFinLeptP/D");
    tout->Branch("fFinLeptPt", &fFinLeptPt, "fFinLeptPt/D");
    tout->Branch("fFinProtPt", &fFinProtPt, "fFinProtPt/D");
    tout->Branch("fFinalNeutrons", &fFinalNeutrons, "fFinalNeutrons/I");
    tout->Branch("fFullDeltaP", &fFullDeltaP, "fFullDeltaP/D");
    tout->Branch("fFullDeltaPt", &fFullDeltaPt, "fFullDeltaPt/D");
    tout->Branch("fFullDeltaPl", &fFullDeltaPl, "fFullDeltaPl/D");
    tout->Branch("fTestDeltaPt", &fTestDeltaPt, "fTestDeltaPt/D");
    tout->Branch("fFullDeltaE", &fFullDeltaE, "fFullDeltaE/D");
    tout->Branch("fVisiDeltaE", &fVisiDeltaE, "fVisiDeltaE/D");
    tout->Branch("fDeltaPt", &fDeltaPt, "fDeltaPt/D");
    tout->Branch("fAlphat", &fAlphat, "fAlphat/D");
    tout->Branch("fPhit", &fPhit, "fPhit/D");
    tout->Branch("fQ2", &fQ2, "fQ2/D");
    tout->Branch("fNucleonMass", &fNucleonMass, "fNucleonMass/D");

    // tout->Branch("fProtonVec", "TLorentzVector", &fProtonVec, 128000, spl);

    return tout;
  }
};

//Initialises the static variables
Int_t TestUtils::fNum = -999;
Int_t TestUtils::fFinalNucleons = -999;
Int_t TestUtils::fFinalProtons = -999;
Int_t TestUtils::fFinalNeutrons = -999;
Double_t TestUtils::fIniElecP = -999;
Double_t TestUtils::fIniNucP = -999;
Double_t TestUtils::fFinProtP = -999;
Double_t TestUtils::fFinLeptP = -999;
Double_t TestUtils::fFinProtPt = -999;
Double_t TestUtils::fFinLeptPt= -999;
Double_t TestUtils::fFullDeltaP = -999;
Double_t TestUtils::fFullDeltaPt = -999;
Double_t TestUtils::fFullDeltaPl =-999;
Double_t TestUtils::fFullDeltaE = -999;
Double_t TestUtils::fVisiDeltaE = -999;
Double_t TestUtils::fDeltaPt = -999;
Double_t TestUtils::fTestDeltaPt= -999;
Double_t TestUtils::fAlphat = -999;
Double_t TestUtils::fPhit = -999;
Double_t TestUtils::fQ2 = -999;
Double_t TestUtils::fNucleonMass = -999;

Int_t TestUtils::fParticlePDG[100] = {};
Double_t TestUtils::fParticleP4[100][4]= {};

//const TLorentzVector * TestUtils::fProtonVec = 0x0;


//void TestUtils::SetProtonVec(const TLorentzVector &lproton){
  
//  delete TestUtils::fProtonVec;
//  TestUtils::fProtonVec = 0x0;

//  TestUtils::fProtonVec = new TLorentzVector(lproton);
//}

void TestUtils::SetFullDelta( const TLorentzVector &lIniLept, const TLorentzVector &lIniNuc, const TLorentzVector &lFinLept, const TLorentzVector &lProton){
  TLorentzVector lFullDeltaP = (lIniLept + lIniNuc) - (lFinLept + lProton);
  TVector3 vFullDeltaP = lFullDeltaP.Vect();
  TestUtils::fFullDeltaP = vFullDeltaP.Mag();
  TestUtils::fFullDeltaE = lFullDeltaP.E();

  TestUtils::fQ2 = (lIniLept - lFinLept).Mag2()*-1;

  
  const TVector3 * ptDeltaP = ElectronTools::GetVecT(&lIniLept, &lFullDeltaP);
  TestUtils::fFullDeltaPt = ptDeltaP->Mag();
  TestUtils::fFullDeltaPl = (vFullDeltaP- *ptDeltaP).Mag();
 
  //Consitency check
  const TVector3 * ptIniNuc = ElectronTools::GetVecT(&lIniLept, &lIniNuc);
  TVector3 testDeltaPt = *ptIniNuc - *ptDeltaP;
  TestUtils::fTestDeltaPt = testDeltaPt.Mag();
}

void TestUtils::SetDeltaPt(const TLorentzVector &lIniLept, const TLorentzVector &lIniNuc, const TLorentzVector &lFinLept, const TLorentzVector &lProton){
  const TVector3 * ptElectron = ElectronTools::GetVecT(&lIniLept, &lFinLept);
  const TVector3 * ptProton = ElectronTools::GetVecT(&lIniLept, &lProton);
  TestUtils::fFinLeptPt = ptElectron->Mag();
  TestUtils::fFinProtPt = ptProton->Mag();
  TVector3 deltaPt = *ptElectron + *ptProton;
  TestUtils::fDeltaPt = deltaPt.Mag();

  TestUtils::fAlphat = TMath::ACos(deltaPt.Dot(*ptElectron)*(-1)/deltaPt.Mag()/ptElectron->Mag());
  TestUtils::fPhit = TMath::ACos(ptElectron->Dot(*ptProton)*(-1)/ptElectron->Mag()/ptProton->Mag());
  TestUtils::fVisiDeltaE = lIniLept.E() + lIniNuc.M() - (lFinLept.E() + lProton.E());
}
