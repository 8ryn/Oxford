#include "NeutrinoTools.h"

#include "TLorentzVector.h"
#include "TVector3.h"
#include "TTree.h"

class NeutrinoParticle
{
 public:
  NeutrinoParticle();

  void SetKinematics(){
    SetPt(); 
    SetAlpha(); 
    SetQ2();
  }

  void SetTransverseKinematics(const NeutrinoParticle * refpar, const Bool_t kprint=kFALSE);
  void SetImbalance(const TLorentzVector * ininucleon, const TLorentzVector * lepton);
  
  void SetNeutrino(const TLorentzVector * neu)
  {
    if(!neu){
      printf("NeutrinoParticle::SetNeutrino bad input!\n");
    }
    fNeutrino = neu;
    fNuDir = new TVector3(fNeutrino->Vect());
  }

  void Reset();

  void SetTree(TString tag, TTree * tout, const Int_t spl);
  //-----------

  const TLorentzVector * fLorentzVec; 
  const TVector3 * fPt;
  Int_t fCharge;
  Double_t fPtMag;
  Double_t fAlpha;
  Double_t fQ2;//only make sense for muon in sim
  Double_t fFullDeltaE;
  Double_t fVisiDeltaE;
  TVector3 *fFullDeltaP;
  TVector3 *fDeltaPt;
  Double_t fKt;

  TVector3 * fVertex;
  TVector3 * fEndPos;
  TVector3 * fFlightPath;

  Double_t fChi2;
  Int_t    fNDOF;
  Int_t fNdets[2];
  Int_t fNhits[3];
  Int_t fTPCCharge[3];

  Double_t fPullele;
  Double_t fPullmu;
  Double_t fPullpi;
  Double_t fPullproton;

  Int_t fNE;
  Double_t fE0;
  Double_t fE1;
  Double_t fE2;
  Double_t fE3;
  Double_t fE4;
  Double_t fE5;

  Int_t fID;

  //sim
  Int_t fPDG;
  Int_t fType;

  const TVector3 * fNuDir;

 private:
  const TLorentzVector * fNeutrino;

  void SetPt();
  void SetAlpha();
  void SetQ2();
};

NeutrinoParticle::NeutrinoParticle():
   fLorentzVec(0x0)
  ,fPt(0x0)
  ,fFullDeltaP(0x0)
  ,fDeltaPt(0x0)
  ,fVertex(0x0)
  ,fEndPos(0x0)
  ,fFlightPath(0x0)
  ,fNuDir(0x0)
  ,fNeutrino(0x0)
{
  //printf("NeutrinoParticle::NeutrinoParticle default constructor called!!\n");
  Reset();
}

void NeutrinoParticle::Reset()
{
  delete fLorentzVec; fLorentzVec=0x0;
  delete fPt; fPt=0x0;
  fCharge = NeutrinoTools::kIniValue;
  fPtMag = NeutrinoTools::kIniValue;
  fAlpha=NeutrinoTools::kIniValue;
  fQ2=NeutrinoTools::kIniValue;
  fFullDeltaE = NeutrinoTools::kIniValue;
  fVisiDeltaE = NeutrinoTools::kIniValue;
  delete fFullDeltaP; fFullDeltaP=new TVector3;
  delete fDeltaPt; fDeltaPt=new TVector3;
  fKt=NeutrinoTools::kIniValue;

  delete fVertex; fVertex=0x0;
  delete fEndPos; fEndPos=0x0;
  delete fFlightPath; fFlightPath=0x0;
  
  fChi2=NeutrinoTools::kIniValue;
  fNDOF=NeutrinoTools::kIniValue;

  fNdets[0]=fNdets[1]=NeutrinoTools::kIniValue;
  fNhits[0]=fNhits[1]=fNhits[2]=NeutrinoTools::kIniValue;
  fTPCCharge[0]=fTPCCharge[1]=fTPCCharge[2]=NeutrinoTools::kIniValue;
  fPullele=fPullmu=fPullpi=fPullproton=NeutrinoTools::kIniValue;

  fNE=0;
  fE0=-999;
  fE1=-999;
  fE2=-999;
  fE3=-999;
  fE4=-999;
  fE5=-999;

  fID=NeutrinoTools::kIniValue;
 
  fPDG=NeutrinoTools::kIniValue;
  fType=NeutrinoTools::kIniValue;

  delete fNuDir; fNuDir = 0x0;

  //external, should not delete
  fNeutrino=0x0;
}

void NeutrinoParticle::SetQ2()
{
  if(fQ2!=NeutrinoTools::kIniValue){
    printf("NeutrinoParticle::SetQ2 fQ2 exist! %f\n", fQ2); exit(1);
  }

  if(!fNeutrino || !fLorentzVec){
    fQ2 = NeutrinoTools::kNullPointer;
  }
  else{
    const TLorentzVector dq = (*fLorentzVec) - (*fNeutrino);
    fQ2 = -dq.Mag2();

    //allow <0 for rec where neutrino energy set to 1
//    if(fQ2<0){
//      printf("NeutrinoParticle::SetQ2 fQ2<0 %e\n", fQ2);
//      exit(1);
//    }
  }
}


void NeutrinoParticle::SetAlpha()
{
  if(fAlpha!=NeutrinoTools::kIniValue){
    printf("NeutrinoParticle::SetAlpha fAlpha exist! %f\n", fAlpha); exit(1);
  }

  if(!fNeutrino || !fLorentzVec){
    fAlpha = NeutrinoTools::kNullPointer;
  }
  else{
    fAlpha = NeutrinoTools::CalcAlpha(fNeutrino, fLorentzVec);
  }
}

void NeutrinoParticle::SetImbalance(const TLorentzVector * ininucleon, const TLorentzVector * lepton)
{
  //fFullDeltaP already exists
  if(fNeutrino && fLorentzVec && ininucleon && lepton){
    fVisiDeltaE = -(fNeutrino->E()+ininucleon->M()-lepton->E()-fLorentzVec->E());

    const TLorentzVector tmp = (*fNeutrino) + (*ininucleon) - (*lepton) - (*fLorentzVec);
    (*fFullDeltaP) = tmp.Vect();
    fFullDeltaE = tmp.E();
  }
}

void NeutrinoParticle::SetPt()
{
  if(fPt){
    printf("NeutrinoParticle::SetPt fPt exists!\n"); exit(1);
  }
  
  if(fNeutrino && fLorentzVec){
    fPt = NeutrinoTools::GetVecT(fNeutrino, fLorentzVec->Px(), fLorentzVec->Py(), fLorentzVec->Pz() );
    fPtMag = fPt->Mag();
  }

//      //pass 1e-10
//      //test->
//      const Double_t fastpt = fLorentzVec->Pt(*fNeutrinoRec);
//      if( fabs((fPtRec->Mag()/fastpt)-1)>1E-10 ){
//        printf("NeutrinoParticle::SetMuonPtRec fast %f slow %f ratio %f\n", fastpt, fPtRec->Mag(), fPtRec->Mag()/fastpt);
//      }
//      //test <-
  
}

void NeutrinoParticle::SetTransverseKinematics(const NeutrinoParticle * refpar, const Bool_t kprint)
{
  if(fPt && refpar->fPt){
    NeutrinoTools::SetDeltaPt(fDeltaPt, refpar->fPt, fPt);

//    //test z001->
//    TVector3 badmuon = fMuonRec->fLorentzVec->Vect();
//    badmuon.SetZ(0.);
//    TVector3 badproton = fProtonRec->fLorentzVec->Vect();
//    badproton.SetZ(0.);
//    NeutrinoTools::SetDeltaPt(fDeltaRecPt, &badmuon, &badproton);
//    //<-
  }

  if(fLorentzVec && fNeutrino && refpar->fLorentzVec){
    //fKt = NeutrinoTools::GetKT(fPt, refpt);

    //Double_t NeutrinoTools::GetPTT(const TVector3 & parMom, const TVector3 & nuDir, const TVector3 & muonDir)
    fKt = NeutrinoTools::GetPTT(fLorentzVec->Vect(), fNeutrino->Vect(), refpar->fLorentzVec->Vect(), kprint);
  }
}

void NeutrinoParticle::SetTree(TString tag, TTree * tout, const Int_t spl)
{
  tout->Branch(tag,"TLorentzVector", &(fLorentzVec), 128000, spl);
  tout->Branch(tag+"Pt", "TVector3", &(fPt), 128000, spl);
  tout->Branch(tag+"Alpha", &(fAlpha), tag+"Alpha/D");
  tout->Branch(tag+"PtMag", &(fPtMag), tag+"PtMag/D");
  tout->Branch(tag+"FullDeltaE", &(fFullDeltaE), tag+"FullDeltaE/D");
  tout->Branch(tag+"VisiDeltaE", &(fVisiDeltaE), tag+"VisiDeltaE/D");
  tout->Branch(tag+"DeltaPt", "TVector3", &(fDeltaPt), 128000, spl);
  tout->Branch(tag+"FullDeltaP", "TVector3", &(fFullDeltaP), 128000, spl);

  tout->Branch(tag+"PDG",&(fPDG),tag+"PDG/I");

  //tout->Branch(tag+"Charge", &(fCharge), tag+"Charge/I");
  //tout->Branch(tag+"Q2", &(fQ2), tag+"Q2/D");
  //tout->Branch(tag+"Kt", &(fKt), tag+"Kt/D");

  tout->Branch(tag+"Vertex", "TVector3", &(fVertex), 128000, spl);
  tout->Branch(tag+"EndPos", "TVector3", &(fEndPos), 128000, spl);
  tout->Branch(tag+"FlightPath", "TVector3", &(fFlightPath), 128000, spl);

  tout->Branch(tag+"Chi2", &(fChi2), tag+"Chi2/D");
  tout->Branch(tag+"NDOF", &(fNDOF), tag+"NDOF/I");

  //tout->Branch(tag+"Ndets",&(fNdets),tag+"Ndets[2]/I");
  //tout->Branch(tag+"Nhits",&(fNhits),tag+"Nhits[3]/I");
  //tout->Branch(tag+"TPCCharge",&(fTPCCharge),tag+"TPCCharge[3]/I");

  //tout->Branch(tag+"Pullele",&(fPullele),tag+"Pullele/D");
  //tout->Branch(tag+"Pullmu",&(fPullmu),tag+"Pullmu/D");
  //tout->Branch(tag+"Pullpi",&(fPullpi),tag+"Pullpi/D");
  //tout->Branch(tag+"Pullproton",&(fPullproton),tag+"Pullproton/D");

  tout->Branch(tag+"NE",&(fNE),tag+"NE/I");
  tout->Branch(tag+"E0",&(fE0),tag+"E0/D");
  tout->Branch(tag+"E1",&(fE1),tag+"E1/D");
  tout->Branch(tag+"E2",&(fE2),tag+"E2/D");
  tout->Branch(tag+"E3",&(fE3),tag+"E3/D");
  tout->Branch(tag+"E4",&(fE4),tag+"E4/D");
  tout->Branch(tag+"E5",&(fE5),tag+"E5/D");

  //tout->Branch(tag+"ID",&(fID),tag+"ID/I");

  //tout->Branch(tag+"Type",&(fType),tag+"Type/I");
}
