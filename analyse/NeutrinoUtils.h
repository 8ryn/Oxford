#include "NeutrinoParticle.h"

class NeutrinoUtils
{
 public:
  enum NeutrinoParent{
    kNull = -999,
    kBad = -2,
    kLost = -1,
    kOther=0,
    kPion,
    kKaon,
    kMuon
  };
  
  static void IniCC();
  static void IniCCQE();

  //--- Reconstruction related
  static const TLorentzVector * fNeutrinoSim;
  static const TLorentzVector * fNeutrinoRec;
  static const TLorentzVector * fIninucleonSim;
  static NeutrinoParticle * fMuonSim;
  static NeutrinoParticle * fMuonRec; 
  static NeutrinoParticle * fProtonSim;
  static NeutrinoParticle * fProtonRec;
  static NeutrinoParticle * fXSim;
  static NeutrinoParticle * fXRec;
  static NeutrinoParticle * fResonanceSim;
  static NeutrinoParticle * fResonanceRec;
  static Double_t fMuonDeltaPTTSim;
  static Double_t fMuonDeltaPTTRec;
  static Double_t fProtonDeltaPTTSim;
  static Double_t fProtonDeltaPTTRec;
  static Double_t fXDeltaPTTSim;
  static Double_t fXDeltaPTTRec;
  static Double_t fMuonDeltaPTLSim;
  static Double_t fMuonDeltaPTLRec;
  static Double_t fSumPtSim;
  static Double_t fSumPtRec;
  static Double_t fEnuSim;
  static Double_t fEnuRec;
  static Double_t fLongiEnergySim;
  static Double_t fLongiEnergyRec;
  static Double_t fQuasiAccuSumEnergySim;
  static Double_t fQuasiAccuSumEnergyRec;
  static Double_t fCCQEProtonMomAppSim;
  static Double_t fCCQEProtonMomAppRec; 
  static Double_t fEnuAppSim;
  static Double_t fEnuAppRec;
  static Double_t fOmegaSim;
  static Double_t fPdotQSim; 
  static Double_t fQ2Truth;
  static Double_t fqinvSim;
  static Double_t fqinvRec;
  static Double_t fttTruth;
  static Double_t fttSim;
  static Double_t fttRec;
  static Double_t fQ2Sim;
  static Double_t fQ2Rec;
  static Double_t fWSQ2Sim;
  static Double_t fWSQ2Rec;
  static Double_t fWSim;
  static Double_t fWRec;
  static Double_t fWSWSim;
  static Double_t fWSWRec;

  static NeutrinoParticle * fNeutronToy;
  static NeutrinoParticle * fProtonToy;
  static NeutrinoParticle * fProtonDet;
  static Double_t fMuonToyKt;

  //---

  static const TLorentzVector * fNeutrinoGuess;
  static NeutrinoParticle * fMuonGuess;

  static const TVector3 * fNeutrinoParentDecPointSim;
  
  static Double_t fOsciMuMuProb;
  static Int_t fkOsciMuSurvive;
  static Int_t fNeutrinoParentPDG;
  static Int_t fNeutrinoParentType;
  static Int_t fNeutrinoType;
  static Int_t fTarget;
  static Int_t fkNuclearEmission;
  static Int_t fNNeutrals;
  static Int_t fNeutMode;
  static Int_t fTopology;
  static Int_t fSelp_PID;
  static Int_t fSelX_Charge;
  static Int_t fSelX_PID;
  static Int_t fMuonRecType;
  static Int_t fEventTypeSim;
  static Int_t fSimOtherPDG;
  static Int_t fNECalTracks;
  static Int_t fECalPDGSim;

  static void SetMuonNRec(const Int_t var){ fMuonNRec = var; }
  static Int_t GetMuonNRec(){return fMuonNRec;}
  static void SetMuonNSim(const Int_t var){ fMuonNSim = var; }
  static Int_t GetMuonNSim(){return fMuonNSim;}
  
  static void SetProtonNRec(const Int_t var){ fProtonNRec = var; }
  static Int_t GetProtonNRec(){return fProtonNRec;}
  static void SetProtonNSim(const Int_t var){ fProtonNSim = var; }
  static Int_t GetProtonNSim(){return fProtonNSim;}

  static void SetXNRec(const Int_t var){ fXNRec = var; }
  static Int_t GetXNRec(){return fXNRec;}
  static void SetXNSim(const Int_t var){ fXNSim = var; }
  static Int_t GetXNSim(){return fXNSim;}

  static void SetMultiplicity(const Int_t mul){fMultiplicity = mul;}
  static Int_t GetMultiplicity(){return fMultiplicity;}
  
  //only rec. meaningful; phi angle in the transver plane w.r.t. beam direction, -180 ~ 180, by definition muon at (-)180.
  static Double_t fBetaRec[10];  
  static Double_t fGammaRec[10];
  
  //-------- Calculations ---------
  //--- Reconstruction related
  Double_t CalcBetaRec(const Double_t dir0, const Double_t dir1, const Double_t dir2);
  Double_t CalcGammaRec(const Double_t dir0, const Double_t dir1, const Double_t dir2);
 
  static void SetRecGuessKinematics(const Bool_t kdummy=kFALSE);

  //---Simulation related
  static void MuonNSimSanityCheck();

  static void SetSimKinematics();
  static void SetTransverseKinematics();
  static void SetNuclearEmission(const Int_t kNuclearEmission);
  static void SetNNeutrals(const Int_t nNeutrals);

  //-------- IO ---------
  static TTree * GetTree();
  static TList * GetHistList();

  static Int_t FillCount(TList *lin, const Int_t var){ return NeutrinoTools::FillTH1I(lin, kcount, var);}

 private:
  //==========================================================
  //Variables and setters
  //==========================================================
  static void SetEventKinematics(Double_t & qinv, Double_t &wrongsW, Double_t &wrongsq2, Double_t & ttransfer, Double_t & ccqeprotonmomapp, Double_t & enuapp, Double_t & sumEnu, Double_t & sumLongiEnergy, Double_t & QuasiAccuSumEnergy, Double_t & sumQ2, Double_t & sumPt, Double_t & muondeltaptt, Double_t & protondeltaptt, Double_t & xdeltaptt, Double_t & muondeltaptL, Double_t & resmass, const TLorentzVector * lnu, const NeutrinoParticle * tmuon, const NeutrinoParticle * tproton, const NeutrinoParticle * tX);

  //--- Reconstruction related
  static Double_t fdNeutrinoGuessNeutrinoSim;
  static Double_t fdNeutrinoGuessMuonRec;
  static const Int_t fCutNR;
  static Double_t fGuessCorrection;
  static void SetdNeutrinoGuessNeutrinoSim(); 
  static void SetdNeutrinoGuessMuonRec();

  static Int_t fMuonNRec;
  static Int_t fProtonNRec;
  static Int_t fXNRec;
  
  static Int_t fMultiplicity; 
  static Double_t fMeanBetaRec; 
  static void SetMeanBetaRec(const Bool_t kdummy = kFALSE);
  static Double_t fMeanGammaRec;//use Mean instead of sum to get rid of multiplicity
  static void SetMeanGammaRec(const Bool_t kdummy = kFALSE);

  ///---Simulation related
  static Bool_t IsCC(){ return TMath::Abs(fNeutMode)<30;}

  static Int_t fMuonNSim;
  static Int_t fProtonNSim;
  static Int_t fXNSim;
 
  enum histID{
    kcount,
    kDUMMY
  };

};

//__________________________________________________________

const TLorentzVector * NeutrinoUtils::fNeutrinoRec = 0x0;
NeutrinoParticle *NeutrinoUtils::fMuonRec=0x0; 
NeutrinoParticle *NeutrinoUtils::fProtonRec=0x0; 
NeutrinoParticle *NeutrinoUtils::fResonanceRec=0x0; 
NeutrinoParticle *NeutrinoUtils::fXRec=0x0; 
Double_t NeutrinoUtils::fMuonDeltaPTTSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fMuonDeltaPTTRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fProtonDeltaPTTSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fProtonDeltaPTTRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fXDeltaPTTSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fXDeltaPTTRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fMuonDeltaPTLSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fMuonDeltaPTLRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fSumPtSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fSumPtRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fEnuSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fEnuRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fLongiEnergySim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fLongiEnergyRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fQuasiAccuSumEnergySim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fQuasiAccuSumEnergyRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fCCQEProtonMomAppSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fCCQEProtonMomAppRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fEnuAppSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fEnuAppRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fOmegaSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fPdotQSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fQ2Truth = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fqinvSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fqinvRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fttTruth = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fttSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fttRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fQ2Sim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fQ2Rec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fWSQ2Sim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fWSQ2Rec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fMuonToyKt = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fWSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fWRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fWSWSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fWSWRec = NeutrinoTools::kIniValue;
const TLorentzVector * NeutrinoUtils::fNeutrinoGuess = 0x0;
NeutrinoParticle *NeutrinoUtils::fMuonGuess=0x0; 
const TLorentzVector * NeutrinoUtils::fNeutrinoSim = 0x0;
const TLorentzVector * NeutrinoUtils::fIninucleonSim = 0x0;
NeutrinoParticle *NeutrinoUtils::fMuonSim=0x0; 
NeutrinoParticle *NeutrinoUtils::fProtonSim=0x0; 
NeutrinoParticle *NeutrinoUtils::fResonanceSim=0x0; 
NeutrinoParticle *NeutrinoUtils::fXSim=0x0; 
NeutrinoParticle *NeutrinoUtils::fNeutronToy=0x0; 
NeutrinoParticle *NeutrinoUtils::fProtonToy=0x0; 
NeutrinoParticle *NeutrinoUtils::fProtonDet=0x0; 

const TVector3 * NeutrinoUtils::fNeutrinoParentDecPointSim = 0x0;

Double_t NeutrinoUtils::fOsciMuMuProb = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fkOsciMuSurvive = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fNeutrinoParentPDG = NeutrinoUtils::kNull;
Int_t NeutrinoUtils::fNeutrinoParentType = NeutrinoUtils::kNull;
Int_t NeutrinoUtils::fNeutrinoType = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fTarget = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fkNuclearEmission = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fNNeutrals = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fNeutMode = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fTopology = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fSelp_PID = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fSelX_Charge = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fSelX_PID = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fMuonRecType = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fEventTypeSim = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fSimOtherPDG = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fNECalTracks = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fECalPDGSim = NeutrinoTools::kIniValue;

Int_t NeutrinoUtils::fMuonNRec = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fMuonNSim = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fProtonNRec = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fProtonNSim = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fXNRec = NeutrinoTools::kIniValue;
Int_t NeutrinoUtils::fXNSim = NeutrinoTools::kIniValue;

Int_t NeutrinoUtils::fMultiplicity = NeutrinoTools::kIniValue;

Double_t NeutrinoUtils::fBetaRec[10]={NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue,NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue,NeutrinoTools::kIniValue};
Double_t NeutrinoUtils::fMeanBetaRec = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fGammaRec[10]={NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue,NeutrinoTools::kIniValue, NeutrinoTools::kIniValue, NeutrinoTools::kIniValue,NeutrinoTools::kIniValue};
Double_t NeutrinoUtils::fMeanGammaRec = NeutrinoTools::kIniValue;

Double_t NeutrinoUtils::fdNeutrinoGuessNeutrinoSim = NeutrinoTools::kIniValue;
Double_t NeutrinoUtils::fdNeutrinoGuessMuonRec = NeutrinoTools::kIniValue;

Double_t NeutrinoUtils::fGuessCorrection = 1;
const Int_t NeutrinoUtils::fCutNR = 1;

//_______________________________________________________________________________________________
//_______________________________________________________________________________________________
void NeutrinoUtils::IniCC()
{
  delete fMuonSim; fMuonSim= new NeutrinoParticle;
  delete fMuonRec; fMuonRec= new NeutrinoParticle;
  delete fMuonGuess; fMuonGuess= new NeutrinoParticle;

  fMuonNRec = 0;
  fMuonNSim = 0;
}

void NeutrinoUtils::IniCCQE()
{
  IniCC();
  delete fProtonSim; fProtonSim= new NeutrinoParticle;
  delete fResonanceSim; fResonanceSim= new NeutrinoParticle;
  delete fXSim;    fXSim= new NeutrinoParticle;
  delete fNeutronToy; fNeutronToy= new NeutrinoParticle;
  delete fProtonToy; fProtonToy= new NeutrinoParticle;
  delete fProtonDet; fProtonDet= new NeutrinoParticle;
  delete fProtonRec; fProtonRec= new NeutrinoParticle;
  delete fResonanceRec; fResonanceRec= new NeutrinoParticle;
  delete fXRec;   fXRec= new NeutrinoParticle;
  fMuonDeltaPTTSim = NeutrinoTools::kIniValue;
  fMuonDeltaPTTRec = NeutrinoTools::kIniValue;
  fProtonDeltaPTTSim = NeutrinoTools::kIniValue;
  fProtonDeltaPTTRec = NeutrinoTools::kIniValue;
  fXDeltaPTTSim = NeutrinoTools::kIniValue;
  fXDeltaPTTRec = NeutrinoTools::kIniValue;
  fMuonDeltaPTLSim = NeutrinoTools::kIniValue;
  fMuonDeltaPTLRec = NeutrinoTools::kIniValue;
  fSumPtSim = NeutrinoTools::kIniValue;
  fSumPtRec = NeutrinoTools::kIniValue;
  fEnuSim = NeutrinoTools::kIniValue;
  fEnuRec = NeutrinoTools::kIniValue;
  fLongiEnergySim = NeutrinoTools::kIniValue;
  fLongiEnergyRec = NeutrinoTools::kIniValue;
  fQuasiAccuSumEnergySim = NeutrinoTools::kIniValue;
  fQuasiAccuSumEnergyRec = NeutrinoTools::kIniValue;
  fCCQEProtonMomAppSim = NeutrinoTools::kIniValue;
  fCCQEProtonMomAppRec = NeutrinoTools::kIniValue;
  fEnuAppSim = NeutrinoTools::kIniValue;
  fEnuAppRec = NeutrinoTools::kIniValue;
  fOmegaSim = NeutrinoTools::kIniValue;
  fPdotQSim = NeutrinoTools::kIniValue;
  fQ2Truth = NeutrinoTools::kIniValue;
  fqinvSim = NeutrinoTools::kIniValue;
  fqinvRec = NeutrinoTools::kIniValue;
  fttTruth = NeutrinoTools::kIniValue;
  fttSim = NeutrinoTools::kIniValue;
  fttRec = NeutrinoTools::kIniValue;
  fQ2Sim = NeutrinoTools::kIniValue;
  fQ2Rec = NeutrinoTools::kIniValue;
  fWSQ2Sim = NeutrinoTools::kIniValue;
  fWSQ2Rec = NeutrinoTools::kIniValue;
  fMuonToyKt = NeutrinoTools::kIniValue;
  fWSim = NeutrinoTools::kIniValue;
  fWRec = NeutrinoTools::kIniValue;
  fWSWSim = NeutrinoTools::kIniValue;
  fWSWRec = NeutrinoTools::kIniValue;
  fProtonNRec = 0;
  fProtonNSim = 0;
  fXNRec = 0;
  fXNSim = 0;
}

void NeutrinoUtils::SetRecGuessKinematics(const Bool_t kdummy)
{ 
  SetdNeutrinoGuessMuonRec();
  SetMeanBetaRec(kdummy);
  SetMeanGammaRec(kdummy);
}

void NeutrinoUtils::SetSimKinematics()
{ 
  SetdNeutrinoGuessNeutrinoSim();
}

void NeutrinoUtils::SetEventKinematics(Double_t & qinv, Double_t &wrongsW, Double_t &wrongsq2, Double_t & ttransfer, Double_t & ccqeprotonmomapp, Double_t & enuapp, Double_t & sumEnu, Double_t & sumLongiEnergy, Double_t & QuasiAccuSumEnergy, Double_t & sumQ2, Double_t & sumPt, Double_t & muondeltaptt, Double_t & protondeltaptt, Double_t & xdeltaptt, Double_t & muondeltaptL, Double_t & resmass, const TLorentzVector * lnu, const NeutrinoParticle * tmuon, const NeutrinoParticle * tproton, const NeutrinoParticle * tX)
{
  qinv = NeutrinoTools::kIniValue;
  wrongsW = NeutrinoTools::kIniValue;
  wrongsq2 = NeutrinoTools::kIniValue;
  ttransfer = NeutrinoTools::kIniValue;
  ccqeprotonmomapp = NeutrinoTools::kIniValue;
  enuapp = NeutrinoTools::kIniValue;
    
  sumEnu   = NeutrinoTools::kIniValue;
  sumLongiEnergy   = NeutrinoTools::kIniValue;
  sumQ2   = NeutrinoTools::kIniValue;
  sumPt    = NeutrinoTools::kIniValue;
  muondeltaptt = NeutrinoTools::kIniValue;
  protondeltaptt = NeutrinoTools::kIniValue;
  xdeltaptt = NeutrinoTools::kIniValue;
  muondeltaptL = NeutrinoTools::kIniValue;
  resmass  = NeutrinoTools::kIniValue;

  TLorentzVector restp;
  restp.SetXYZM(0,0,0, NeutrinoTools::ProtonMass());

  TLorentzVector sumLvNeutrino;
  TVector3 sumV3FinalState;

  if(tmuon->fPt && tproton->fPt){
    sumLvNeutrino += *(tmuon->fLorentzVec) + *(tproton->fLorentzVec) - restp;
    sumV3FinalState += *(tmuon->fPt)         + *(tproton->fPt); 

    if(tX->fPt){
      sumLvNeutrino += *(tX->fLorentzVec);
      sumV3FinalState += *(tX->fPt);

      muondeltaptt = NeutrinoTools::GetDeltaPTT(tproton->fLorentzVec->Vect(), tX->fLorentzVec->Vect(), lnu->Vect(), tmuon->fLorentzVec->Vect());
      protondeltaptt = NeutrinoTools::GetDeltaPTT(tX->fLorentzVec->Vect(), tmuon->fLorentzVec->Vect(), lnu->Vect(), tproton->fLorentzVec->Vect());
      xdeltaptt = NeutrinoTools::GetDeltaPTT(tmuon->fLorentzVec->Vect(), tproton->fLorentzVec->Vect(), lnu->Vect(), tX->fLorentzVec->Vect());
      muondeltaptL = NeutrinoTools::GetDeltaPTL(*(tproton->fPt), *(tX->fPt), lnu->Vect(), *(tmuon->fPt));

      resmass  = NeutrinoTools::GetMass(tproton->fLorentzVec, tX->fLorentzVec);

      //wrong signed q2
      wrongsq2 = -((sumLvNeutrino - *(tX->fLorentzVec)).Mag2());

      //
      const Double_t qi2 = -(*(tproton->fLorentzVec) - *(tX->fLorentzVec)).Mag2();
      if(qi2>EPSILON){
        qinv = TMath::Sqrt(qi2);
      }        
    }

    sumEnu = sumLvNeutrino.E();
    sumLongiEnergy = (sumLvNeutrino.Vect()-sumV3FinalState).Mag();

    sumQ2 = -((sumLvNeutrino - *(tmuon->fLorentzVec)).Mag2());

    sumPt  = sumV3FinalState.Mag();

    //wrong signed W
    wrongsW =  NeutrinoTools::GetMass(tproton->fLorentzVec, tmuon->fLorentzVec);

    //only valid if selp_PID == 2, namely , exclusive mu/pi final states where proton is in fact a pion
    TVector3 tTsum = (*tmuon->fPt) + (*tproton->fPt);
    TVector3 tLmuon = tmuon->fLorentzVec->Vect()-(*tmuon->fPt);
    TVector3 tLproton =  tproton->fLorentzVec->Vect()-(*tproton->fPt);
    ttransfer = TMath::Power(tmuon->fLorentzVec->E()-tLmuon.Mag() + tproton->fLorentzVec->E()-tLproton.Mag() ,2) +  + tTsum.Mag2();
  }

  ccqeprotonmomapp =  NeutrinoTools::kIniValue;
  enuapp =  NeutrinoTools::kIniValue;
  QuasiAccuSumEnergy   = NeutrinoTools::kIniValue;

  //static Double_t GetEnuApp(const TVector3 v3Nu, const Double_t mN, const TLorentzVector lvL, const Double_t mX);
  if(tmuon->fPt){
    //Double_t tmpN = NeutrinoTools::kIniValue;
    //Double_t tmpX = NeutrinoTools::kIniValue;

    if(tX->fPt){
      ccqeprotonmomapp = -1e10;

      //tmpN = NeutrinoTools::ProtonMass();
      //tmpX = NeutrinoTools::DeltaPPMass();
      enuapp = -1e10;
    }
    else{
      ccqeprotonmomapp = NeutrinoTools::GetCCQEProtonMomApp(lnu->Vect(), tmuon->fLorentzVec);

      const Double_t tmpN = NeutrinoTools::NeutronMass() - NeutrinoTools::BindingEnergyCarbon();
      const Double_t tmpX = NeutrinoTools::ProtonMass();
      enuapp = NeutrinoTools::GetEnuApp(lnu->Vect(), tmpN, tmuon->fLorentzVec, tmpX);

      if(tproton->fPt){
        // static Double_t GetQuasiAccuSumEnergy(const Double_t mN, const TLorentzVector *lvF, const TVector3 * ptF);
        const TLorentzVector lvF = *(tmuon->fLorentzVec)+*(tproton->fLorentzVec);
        const TVector3 ptF = *(tmuon->fPt)+*(tproton->fPt);
        QuasiAccuSumEnergy = NeutrinoTools::GetQuasiAccuSumEnergy(tmpN, &lvF, &ptF);
      }
    }
  }
}

void NeutrinoUtils::SetTransverseKinematics()
{
  fMuonSim->SetTransverseKinematics(fProtonSim);
  fProtonSim->SetTransverseKinematics(fMuonSim);
  fProtonSim->SetImbalance(fIninucleonSim, fMuonSim->fLorentzVec);
  fResonanceSim->SetTransverseKinematics(fMuonSim);
  fResonanceSim->SetImbalance(fIninucleonSim, fMuonSim->fLorentzVec);
  fXSim->SetTransverseKinematics(fMuonSim);

  fMuonRec->SetTransverseKinematics(fProtonRec);
  fProtonRec->SetTransverseKinematics(fMuonRec);
  fResonanceRec->SetTransverseKinematics(fMuonRec);
  fXRec->SetTransverseKinematics(fMuonRec);

  fProtonToy->SetTransverseKinematics(fMuonSim);
  fProtonDet->SetTransverseKinematics(fMuonSim);

  //============

  SetEventKinematics(fqinvSim, fWSWSim, fWSQ2Sim, fttSim, fCCQEProtonMomAppSim, fEnuAppSim, fEnuSim, fLongiEnergySim, fQuasiAccuSumEnergySim, fQ2Sim, fSumPtSim, fMuonDeltaPTTSim, fProtonDeltaPTTSim, fXDeltaPTTSim, fMuonDeltaPTLSim, fWSim, fNeutrinoSim, fMuonSim, fProtonSim, fXSim);
  SetEventKinematics(fqinvRec, fWSWRec, fWSQ2Rec, fttRec, fCCQEProtonMomAppRec, fEnuAppRec, fEnuRec, fLongiEnergyRec, fQuasiAccuSumEnergyRec, fQ2Rec, fSumPtRec, fMuonDeltaPTTRec, fProtonDeltaPTTRec, fXDeltaPTTRec, fMuonDeltaPTLRec, fWRec, fNeutrinoRec, fMuonRec, fProtonRec, fXRec);
  //============

  fQ2Truth = NeutrinoTools::kIniValue;
  if(fMuonSim->fLorentzVec){
    const TLorentzVector p4tran = *(fNeutrinoSim) - *(fMuonSim->fLorentzVec);
    fQ2Truth = -( p4tran.Mag2() );

    fOmegaSim = p4tran.E();
    fPdotQSim = (fIninucleonSim->Vect()).Dot(p4tran.Vect());
  } 
  //============

  //only valid in case selp_PID == 2, exclusive mu/pi final states  where proton is in fact a pion
  fttTruth = NeutrinoTools::kIniValue;
  if(fMuonSim->fLorentzVec && fProtonSim->fLorentzVec){
    const TLorentzVector tmptt = *fNeutrinoSim - *(fMuonSim->fLorentzVec) - *(fProtonSim->fLorentzVec);
    fttTruth = -tmptt.M2();
  }
  //============
  
  fMuonToyKt = NeutrinoTools::kIniValue;
  if(fMuonSim->fLorentzVec && fProtonToy->fLorentzVec){
    fMuonToyKt = NeutrinoTools::GetPTT(fMuonSim->fLorentzVec->Vect(), fNeutrinoSim->Vect(), fProtonToy->fLorentzVec->Vect());
  }
}

void NeutrinoUtils::SetdNeutrinoGuessNeutrinoSim()
{
  //flat in cos, not tha angle
  //tested with = fNeutrinoRec; should be 0; confirmed
  if(!fNeutrinoGuess){
    fdNeutrinoGuessNeutrinoSim = NeutrinoTools::kNullPointer;
  }
  else{
    const Double_t tmpcos= NeutrinoTools::GetCos(fNeutrinoGuess, fNeutrinoSim, "NeutrinoUtils::SetdNeutrinoGuessNeutrinoSimGetCos");
    if(tmpcos== NeutrinoTools::kZeroDivider){
      fdNeutrinoGuessNeutrinoSim = NeutrinoTools::kZeroDivider;
    }
    else{
      fdNeutrinoGuessNeutrinoSim =  tmpcos - 1;
    }
  }
}

void NeutrinoUtils::SetNuclearEmission(const Int_t kNuclearEmission)
{
  fkNuclearEmission = kNuclearEmission;
}

void NeutrinoUtils::SetNNeutrals(const Int_t nNeutrals)
{
  fNNeutrals = nNeutrals;
}

void NeutrinoUtils::SetdNeutrinoGuessMuonRec()
{
  //flat in cos, not tha angle

  //calculation confirmed by
  //tree->Draw("fdNeutrinoGuessMuonRec","fMultiplicity==1") //should = 1
  
  //tested with = &(fMuonRec->Vect())// should be 0; confirmed
  if(!fMuonRec->fLorentzVec || !fNeutrinoGuess){
    fdNeutrinoGuessMuonRec = NeutrinoTools::kNullPointer;
  }
  else{
    const Double_t tmpcos = NeutrinoTools::GetCos(fNeutrinoGuess, fMuonRec->fLorentzVec, "NeutrinoUtils::SetdNeutrinoGuessMuonRecGetCos");
    if(tmpcos== NeutrinoTools::kZeroDivider){
      fdNeutrinoGuessMuonRec = NeutrinoTools::kZeroDivider;
    }
    else{
      fdNeutrinoGuessMuonRec = tmpcos - 1;
    }
  }
}

void NeutrinoUtils::SetMeanBetaRec(const Bool_t kdummy)
{
  if(kdummy){
    fMeanBetaRec = NeutrinoTools::kIniValue;
    return;
  }

  fMeanBetaRec = 0;
  for(Int_t ipar=0; ipar<fMultiplicity; ipar++){
    //remove muon contribution
    if(ipar == fMuonRec->fID){
      continue;
    }

    fMeanBetaRec += fBetaRec[ipar];
  }

  if(fMultiplicity==1){
    fMeanBetaRec=NeutrinoTools::kZeroDivider;
  }
  else{//multiplicity >= 2
    fMeanBetaRec /= (fMultiplicity-1);
  }
}

void NeutrinoUtils::SetMeanGammaRec(const Bool_t kdummy)
{
  if(kdummy){
    fMeanGammaRec = NeutrinoTools::kIniValue;
    return;
  }

  fMeanGammaRec = 0;
  for(Int_t ipar=0; ipar<fMultiplicity; ipar++){
    //remove muon contribution
    if(ipar == fMuonRec->fID){
      continue;
    }
    fMeanGammaRec += fGammaRec[ipar];
  }

  if(fMultiplicity==1){
    fMeanGammaRec = NeutrinoTools::kZeroDivider;
  }
  else{
    fMeanGammaRec /= (fMultiplicity-1);
  }
}

void NeutrinoUtils::MuonNSimSanityCheck()
{
  //sanity check -1
  if(fMuonNSim==0 && IsCC()){
    printf("MuonNSimSanityCheck wrong fMuonNSim CC %d %d\n", fMuonNSim, fNeutMode); exit(1);
  }
  //sanity check -2
  if(fMuonNSim>0 && !IsCC()){
    printf("MuonNSimSanityCheck wrong fMuonNSim NC %d %d\n", fMuonNSim, fNeutMode); exit(1);
  }
}

Double_t NeutrinoUtils::CalcBetaRec(const Double_t dir0, const Double_t dir1, const Double_t dir2)
{
  //
  //magnitude does not magger
  //w.r.t. beam direction (z-axis) and muon opposite direction  (x-axis)
  //-180 ~ 180
  //
  if(!fMuonRec->fPt){
    return NeutrinoTools::kNullPointer;
  }

  const TVector3 *vt = NeutrinoTools::GetVecT(fNeutrinoRec, dir0, dir1, dir2);

  //muon pt direction := -180 deg, i.e. -x axis
  const TVector3 xaxis = (*fMuonRec->fPt)*(-1);

  //0 ~ 180

  
  Double_t beta = NeutrinoTools::GetAngle(&xaxis, vt, "NeutrinoUtils::CalcBetaRec");

  if( (fNeutrinoRec->Vect()).Dot(xaxis.Cross(*vt)) < 0 )
    beta *= -1;

  if(beta<-180 + 1e-3){
    beta+= 360;
  }

  delete vt;
  return beta;
}

Double_t NeutrinoUtils::CalcGammaRec(const Double_t dir0, const Double_t dir1, const Double_t dir2)
{
  const TVector3 vec(dir0, dir1, dir2);

  const TVector3 refdir=fNeutrinoRec->Vect();
  return NeutrinoTools::GetAngle(&vec, &refdir, "NeutrinoUtils::CalcGammaRec");
}

//___________________________________________________________________________________

//___________________________________________________________________________________________________

TTree * NeutrinoUtils::GetTree()
{
  TTree * tout = new TTree("tree","tree");

  const Int_t spl = 1;

  fMuonRec->SetTree("fMuonRec",tout,spl);
  fMuonSim->SetTree("fMuonSim",tout,spl);

  if(fProtonRec && fProtonSim){
    fProtonRec->SetTree("fProtonRec",tout,spl);
    fProtonSim->SetTree("fProtonSim",tout,spl);
  }

  if(fResonanceRec && fResonanceSim){
    fResonanceRec->SetTree("fResonanceRec",tout,spl);
    fResonanceSim->SetTree("fResonanceSim",tout,spl);
  }

  if(fXRec && fXSim){
    fXRec->SetTree("fXRec",tout,spl);
    fXSim->SetTree("fXSim",tout,spl);
  }

  tout->Branch("fNeutrinoSim","TLorentzVector", &fNeutrinoSim, 128000, spl);
  tout->Branch("fNeutrinoRec", "TVector3", &(fMuonRec->fNuDir), 128000, spl);
  tout->Branch("fIninucleonSim","TLorentzVector", &fIninucleonSim, 128000, spl);

  tout->Branch("fMuonNSim",&fMuonNSim,"fMuonNSim/I");
  tout->Branch("fMuonNRec",&fMuonNRec,"fMuonNRec/I");
  tout->Branch("fProtonNSim",&fProtonNSim,"fProtonNSim/I");
  tout->Branch("fProtonNRec",&fProtonNRec,"fProtonNRec/I");
  tout->Branch("fXNSim",&fXNSim,"fXNSim/I");
  tout->Branch("fXNRec",&fXNRec,"fXNRec/I");

  tout->Branch("fNeutrinoType",&fNeutrinoType,"fNeutrinoType/I");
  tout->Branch("fTarget",&fTarget,"fTarget/I");
  tout->Branch("fkNuclearEmission",&fkNuclearEmission,"fkNuclearEmission/I");
  tout->Branch("fNNeutrals",&fNNeutrals,"fNNeutrals/I");
  tout->Branch("fNeutMode",&fNeutMode,"fNeutMode/I");
  tout->Branch("fTopology",&fTopology,"fTopology/I");
  tout->Branch("fSelp_PID",&fSelp_PID,"fSelp_PID/I");
  tout->Branch("fSelX_Charge",&fSelX_Charge,"fSelX_Charge/I");
  tout->Branch("fSelX_PID",&fSelX_PID,"fSelX_PID/I");

  tout->Branch("fMuonRecType",&fMuonRecType,"fMuonRecType/I");

  tout->Branch("fMuonDeltaPTTSim",&fMuonDeltaPTTSim,"fMuonDeltaPTTSim/D");
  tout->Branch("fMuonDeltaPTTRec",&fMuonDeltaPTTRec,"fMuonDeltaPTTRec/D");

  tout->Branch("fEnuSim",&fEnuSim,"fEnuSim/D");
  tout->Branch("fEnuRec",&fEnuRec,"fEnuRec/D");
  tout->Branch("fQuasiAccuSumEnergySim",&fQuasiAccuSumEnergySim,"fQuasiAccuSumEnergySim/D");
  tout->Branch("fQuasiAccuSumEnergyRec",&fQuasiAccuSumEnergyRec,"fQuasiAccuSumEnergyRec/D");
  tout->Branch("fCCQEProtonMomAppSim",&fCCQEProtonMomAppSim,"fCCQEProtonMomAppSim/D");
  tout->Branch("fCCQEProtonMomAppRec",&fCCQEProtonMomAppRec,"fCCQEProtonMomAppRec/D");
  tout->Branch("fEnuAppSim",&fEnuAppSim,"fEnuAppSim/D");
  tout->Branch("fEnuAppRec",&fEnuAppRec,"fEnuAppRec/D");
  tout->Branch("fOmegaSim",&fOmegaSim,"fOmegaSim/D");  
  tout->Branch("fPdotQSim",&fPdotQSim,"fPdotQSim/D");  
  tout->Branch("fWSim",&fWSim,"fWSim/D");
  tout->Branch("fWRec",&fWRec,"fWRec/D");

  tout->Branch("fNeutrinoParentDecPointSim", "TVector3", &fNeutrinoParentDecPointSim, 128000, spl);

//  if(fProtonToy){
//    fNeutronToy->SetTree("fNeutronToy",tout,spl);
//    fProtonToy->SetTree("fProtonToy",tout,spl);
//  }
//
//  if(fProtonDet){
//    fProtonDet->SetTree("fProtonDet",tout,spl);
//  }
//
//  tout->Branch("fProtonDeltaPTTSim",&fProtonDeltaPTTSim,"fProtonDeltaPTTSim/D");
//  tout->Branch("fProtonDeltaPTTRec",&fProtonDeltaPTTRec,"fProtonDeltaPTTRec/D");
//  tout->Branch("fXDeltaPTTSim",&fXDeltaPTTSim,"fXDeltaPTTSim/D");
//  tout->Branch("fXDeltaPTTRec",&fXDeltaPTTRec,"fXDeltaPTTRec/D");
//  tout->Branch("fMuonDeltaPTLSim",&fMuonDeltaPTLSim,"fMuonDeltaPTLSim/D");
//  tout->Branch("fMuonDeltaPTLRec",&fMuonDeltaPTLRec,"fMuonDeltaPTLRec/D");
//  tout->Branch("fSumPtSim",&fSumPtSim,"fSumPtSim/D");
//  tout->Branch("fSumPtRec",&fSumPtRec,"fSumPtRec/D");
//  tout->Branch("fLongiEnergySim",&fLongiEnergySim,"fLongiEnergySim/D");
//  tout->Branch("fLongiEnergyRec",&fLongiEnergyRec,"fLongiEnergyRec/D");
//  tout->Branch("fQ2Truth",&fQ2Truth,"fQ2Truth/D");  
//  tout->Branch("fqinvSim",&fqinvSim,"fqinvSim/D");
//  tout->Branch("fqinvRec",&fqinvRec,"fqinvRec/D");
//  tout->Branch("fttTruth",&fttTruth,"fttTruth/D");
//  tout->Branch("fttSim",&fttSim,"fttSim/D");
//  tout->Branch("fttRec",&fttRec,"fttRec/D");  
//  tout->Branch("fQ2Sim",&fQ2Sim,"fQ2Sim/D");  
//  tout->Branch("fQ2Rec",&fQ2Rec,"fQ2Rec/D");
//  tout->Branch("fWSQ2Sim",&fWSQ2Sim,"fWSQ2Sim/D");
//  tout->Branch("fWSQ2Rec",&fWSQ2Rec,"fWSQ2Rec/D");
//  tout->Branch("fMuonToyKt",&fMuonToyKt,"fMuonToyKt/D");
//  tout->Branch("fWSWSim",&fWSWSim,"fWSWSim/D");
//  tout->Branch("fWSWRec",&fWSWRec,"fWSWRec/D");
  
//  tout->Branch("fNeutrinoGuess", "TVector3", &(fMuonGuess->fNuDir), 128000, spl);
  
//  tout->Branch("fdNeutrinoGuessNeutrinoSim", &fdNeutrinoGuessNeutrinoSim, "fdNeutrinoGuessNeutrinoSim/D");
//  tout->Branch("fdNeutrinoGuessMuonRec", &fdNeutrinoGuessMuonRec, "fdNeutrinoGuessMuonRec/D");

//  tout->Branch("fGuessCorrection", &fGuessCorrection, "fGuessCorrection/D");
//  tout->Branch("fMuonPtGuess", &(fMuonGuess->fPtMag), "fMuonPtGuess/D");

//  tout->Branch("fOsciMuMuProb",&fOsciMuMuProb,"fOsciMuMuProb/D");
//  tout->Branch("fkOsciMuSurvive",&fkOsciMuSurvive,"fkOsciMuSurvive/I");
//  tout->Branch("fNeutrinoParentPDG",&fNeutrinoParentPDG,"fNeutrinoParentPDG/I");
//  tout->Branch("fNeutrinoParentType",&fNeutrinoParentType,"fNeutrinoParentType/I");
//  tout->Branch("fEventTypeSim",&fEventTypeSim,"fEventTypeSim/I");
//  tout->Branch("fSimOtherPDG",&fSimOtherPDG,"fSimOtherPDG/I");
//  tout->Branch("fNECalTracks",&fNECalTracks,"fNECalTracks/I");
//  tout->Branch("fECalPDGSim",&fECalPDGSim,"fECalPDGSim/I"); 

//  tout->Branch("fMultiplicity",&fMultiplicity,"fMultiplicity/I");

//  tout->Branch("fMeanBetaRec", &fMeanBetaRec, "fMeanBetaRec/D");
//  tout->Branch("fMeanGammaRec", &fMeanGammaRec, "fMeanGammaRec/D");

  return tout;
}

TList * NeutrinoUtils::GetHistList()
{
  TList *lout=new TList;
  lout->SetName("lout");
  
  TH1D * hcount = new TH1D("count","",30, -0.5, 29.5); lout->AddAt(hcount,kcount);  
  return lout;
}
