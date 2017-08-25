#define readNuWro_cxx
#include "readNuWro.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TSystem.h>

#include "NeutrinoDetector.h"
#include "ND280Utils.h"

#include "NeutrinoProcess.h"

const NeutrinoRES *fRES = 0x0; //B: NeutrinoRES defined in NeutrinoProcess.h

Int_t gEStatus = 0;
Int_t gEHepN = 0;
Int_t gEMEC = 0;
Int_t gEMom = 0;

//B: Simply prints out the relevant variables
void readNuWro::DumpEvent()
{
  for(Int_t ii=0; ii<StdHepN; ii++){
    printf("EvtNum %d EvtCode %s ii %d StdHepPdg %d StdHepStatus %d StdHepP4 %f %f %f %f\n", EvtNum, EvtCode->String().Data(), ii, StdHepPdg[ii], StdHepStatus[ii], StdHepP4[ii][0], StdHepP4[ii][1], StdHepP4[ii][2], StdHepP4[ii][3]);
  }
}

//B: I suspect this can be removed when dealing with electrons (if not probably needs modification)
Int_t readNuWro::GetTrueReacWithRESModification()
{
  //B: In the case of neutrino interactions EvtCode varies depending on the interaction
  //B: For electrons seems to always take value of 100
  const Int_t rawcode = EvtCode->String().Atoi();

  TLorentzVector tmplv;
  SetLv(tmplv, 1);
  const Double_t tmass=tmplv.M();

  const Int_t wrongmode = 888;

  Int_t modcode = rawcode;
  //B: This certainly isn't currently true for electron interactions
  if(rawcode==fRES->Mode()){
    //NuWro
    if(StruckNucleonPDG==-999){    
      if( TMath::Abs(tmass - fRES->TargetMass() )>1e-4 ){//not on target
        modcode = wrongmode;
        
        if( TMath::Abs(tmass-NeutrinoTools::ProtonMass())>1e-4 && TMath::Abs(tmass-NeutrinoTools::NeutronMass())>1e-4 ){
          printf("readNuWro::GetTrueReacWithRESModification not on nucleon target! NuWro mass %f, %f %f, %f %f\n", tmass, NeutrinoTools::ProtonMass(), NeutrinoTools::NeutronMass(), TMath::Abs(tmass-NeutrinoTools::ProtonMass()), TMath::Abs(tmass-NeutrinoTools::NeutronMass()));
          DumpEvent();
          exit(1);
        }
        
      }
    }
    //Neut or GENIE
    else{
      //mass can be off shell, like in SL, or in GENIE
      //check that the mass has to be (even off-shell) nucleons
      if( tmass > 1.5 ){
        printf("readNuWro::GetTrueReacWithRESModification not on nucleon target! Neut or Genie mass %f\n", tmass);
        DumpEvent();
        exit(1);
      }
      
      if(StruckNucleonPDG!=fRES->Target()){
        modcode = wrongmode;
      }
    }

  }
  /*
//1 is used in both nu and anti-nu QE
  else if(rawcode==1){
    if( TMath::Abs(tmass-NeutrinoTools::NeutronMass())>1e-4 ){
      printf("readNuWro::GetTrueReacWithRESModification QE not on neutron!! %f %f\n",tmass, NeutrinoTools::NeutronMass()); 
      DumpEvent();
      exit(1);
    }
  }
  */
  return modcode;
}

//B: Sets LorentzVector lv to take the value of particle ii
void readNuWro::SetLv(TLorentzVector & lv, const Int_t ii)
{
  //double	StdHepP4[350][4]		4-p (px,py,pz,E) of particle in LAB frame (GeV)
  lv.SetXYZT(StdHepP4[ii][0],StdHepP4[ii][1],StdHepP4[ii][2],StdHepP4[ii][3]);
}

//have to be controled by xmass
void SaveParticles(const Double_t * tmpP4nu, const Double_t * tmpP4ininucleon,  const TLorentzVector llepton, const TLorentzVector lproton, const TLorentzVector lpion, const Double_t xmass)
{
  //E: given that this all relates to a neutrino rather than an electron, editing of some kind is required
  Float_t nu_truedir[]={tmpP4nu[0], tmpP4nu[1], tmpP4nu[2]};
  Float_t nu_trueE = tmpP4nu[3]*1000;//in MeV
  NeutrinoDetector::SetNeutrinoSim(nu_truedir, nu_trueE); //B: Sets NeutrinoUtils::fNeutrinoSim appropriately
        
  delete NeutrinoUtils::fIninucleonSim;
  TLorentzVector tmpininucleon(tmpP4ininucleon);//in GeV
  NeutrinoUtils::fIninucleonSim = new TLorentzVector(tmpininucleon);

  //dummy
  delete NeutrinoUtils::fNeutrinoRec;
  NeutrinoUtils::fNeutrinoRec = new TLorentzVector(*( NeutrinoUtils::fNeutrinoSim));
  //test with angle bias
  //const Double_t dtheta=0*TMath::DegToRad();
  //NeutrinoUtils::fNeutrinoRec = new TLorentzVector(0, sin(dtheta), cos(dtheta), 1);

  Float_t truemu_truedir[]={llepton.X(), llepton.Y(), llepton.Z()};
  Float_t truemu_truemom=llepton.P()*1e3;
  Int_t selmu_pdg = fRES->Lepton();
  const Int_t nmusim = NeutrinoDetector::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fMuonSim,   NeutrinoTools::MuonMass(),   truemu_truedir, truemu_truemom, selmu_pdg);
  NeutrinoUtils::SetMuonNSim(nmusim);
  
  Float_t selp_truedir[]={lproton.X(), lproton.Y(), lproton.Z()};
  Float_t selp_truemom=lproton.P()*1e3;
  Int_t selp_pdg = NeutrinoTools::PDGProton();
  const Int_t npsim  = NeutrinoDetector::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fProtonSim, NeutrinoTools::ProtonMass(), selp_truedir,   selp_truemom,   selp_pdg);
  NeutrinoUtils::SetProtonNSim(npsim);

  Float_t selX_truedir[]={lpion.X(), lpion.Y(), lpion.Z()};
  Float_t selX_truemom = lpion.P()*1e3;
  Int_t selX_pdg = fRES->Pion();
  Int_t selX_charge = (selX_pdg==NeutrinoTools::PDGPionPlus())? 1 : -1;
  const Int_t nxsim = NeutrinoDetector::SetParticleSim(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fXSim, xmass, selX_truedir,   selX_truemom,   selX_pdg, selX_charge);
  NeutrinoUtils::SetXNSim(nxsim);
  
  NeutrinoDetector::SetMother(NeutrinoUtils::fNeutrinoSim, NeutrinoUtils::fResonanceSim, NeutrinoUtils::fProtonSim->fLorentzVec, NeutrinoUtils::fXSim->fLorentzVec);
 
  //-- dummy
  const Int_t nmurec = NeutrinoDetector::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fMuonRec,   NeutrinoTools::MuonMass(),   truemu_truedir, truemu_truemom);
  NeutrinoUtils::SetMuonNRec(nmurec);
  
  const Int_t nprec     = NeutrinoDetector::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fProtonRec, NeutrinoTools::ProtonMass(), selp_truedir,  selp_truemom);
  NeutrinoUtils::SetProtonNRec(nprec);

  const Int_t nxrec = NeutrinoDetector::SetParticleRec(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fXRec,   xmass, selX_truedir,  selX_truemom);
  NeutrinoUtils::SetXNRec(nxrec);

  NeutrinoDetector::SetMother(NeutrinoUtils::fNeutrinoRec, NeutrinoUtils::fResonanceRec, NeutrinoUtils::fProtonRec->fLorentzVec, NeutrinoUtils::fXRec->fLorentzVec);
}

//B: This function should work as intended for electron interactions with no modifications
void IsMeasured(const Int_t pdg, const TLorentzVector tmplv, const Double_t protonMeVthres, const Double_t otherMeVthres, Bool_t & isTrk, Bool_t & isHit, Bool_t & isNtl)
{
  const Double_t Ek = tmplv.E()-tmplv.M();//in GeV  B: Naturally this is kinetic energy (assuming natural units)

  //http://arxiv.org/pdf/1507.08560.pdf
  //Neutrons are assumed to escape detection.
  //The detection thresholds applied in our calculations correspond to the measured kinetic energy of 20 MeV for mesons and 40 MeV for protons.  
  //We assume that produced charged leptons are always detected.

  //T2K type 100/100, Lar type 40/20
  const Double_t protonThres = protonMeVthres/1e3;//in GeV
  const Double_t otherThres = otherMeVthres/1e3;//in GeV
  
  //placeholder!
  const Double_t protonHitThres = 0.1 * protonThres;
  const Double_t otherHitThres = 0.1 * otherThres;


  isTrk = kFALSE;
  isHit = kFALSE;
  isNtl = kFALSE; 
  //all neutral invisible
  if( pdg==NeutrinoTools::PDGNeutron() || pdg==NeutrinoTools::PDGPionZero() || pdg==NeutrinoTools::PDGGamma() ){
    isTrk = kFALSE;
    isHit = kFALSE;

    //only consider detectable neutral, i.e. pi0 and gamma, but they also have to be above threshold (otherThres)
    if( pdg==NeutrinoTools::PDGPionZero() || pdg==NeutrinoTools::PDGGamma() ){
      if(Ek>otherThres){
        isNtl = kTRUE;
      }
    }
  }
  else if(pdg==NeutrinoTools::PDGProton()){
    if(Ek>protonThres){
      isTrk = kTRUE;
      isHit = kFALSE;
    }
    else{
      isTrk = kFALSE;

      if(Ek>protonHitThres){
        isHit = kTRUE;
      }
      else{
        isHit = kFALSE;
      }
    }
  }
  else{
    if(Ek>otherThres){
      isTrk = kTRUE;
      isHit = kFALSE;
    }
    else{
      isTrk = kFALSE;
      
      if(Ek>otherHitThres){
        isHit = kTRUE;
      }
      else{
        isHit = kFALSE;
      }
    }
  }
}

void readNuWro::GetParticles(const Int_t numode, Int_t & selp_pid, Int_t & selX_charge, Int_t & selX_pid, Int_t &kNuclearEmission, const Double_t protonMeVthres, const Double_t otherMeVthres, Int_t & nNeutrals)
{
  selp_pid=-999;
  selX_charge=-999;
  selX_pid=-999;
  kNuclearEmission = -999;
  nNeutrals = 0;

  //__________________________________________________________________________
  //__________________________________________________________________________

  //B: This bit should still work (worth editing text to electron rather than nu)
  //check beam
  if( StdHepPdg[0] != fRES->Beam() ){
    printf("readNuWro::GetParticles wrong position of nu! %d %d\n", StdHepPdg[0], fRES->Beam()); exit(1);
  }

  const Int_t leptonid = 2;
  //select CC
  if( StdHepPdg[leptonid] != fRES->Lepton() ){
    if( StdHepPdg[leptonid] != fRES->Beam() ){
      const Int_t rawcode = EvtCode->String().Atoi();
      if(rawcode>30){
        //printf("readNuWro::GetParticles it is indeed NC!\n");
      }
      else{
        printf("readNuWro::GetParticles wrong lepton, not even NC! %d %d %d\n", StdHepPdg[leptonid], fRES->Lepton(), fRES->Beam()); 
        DumpEvent();
        exit(1);
      }
    }
    return;
  } 

  //B: again this should work but maybe worth changing name of tmpP4nu since its now an electron
  //set beam, initial nucleon and lepton
  const Double_t * tmpP4nu = StdHepP4[0];
  const Double_t * tmpP4ininucleon = StdHepP4[1];
  TLorentzVector llepton;
  SetLv(llepton, leptonid);

  //__________________________________________________________________________
  //__________________________________________________________________________
  //E: This bit is based around particles emitted in neutrino interactions so likely needs rejigging

  Int_t nproton=0;
  Int_t npiRight=0;

  //check for nuclear emission
  Int_t nneutron=0;
  Int_t npiWrong=0;
  Int_t npizero=0;
  Int_t ngamma=0;
  Int_t nother=0;

  TLorentzVector lproton, lpion;
  Double_t protonmaxe=-1e10;
  Double_t pirightmaxe=-1e10;

  
  //in NuWro, mode 11 also has higher mass resonace, exactly like nuclear emission
  //Delta-> pi+ p pi0, or pi+ n pi+
  /*
  if(gkNEUT && gkHydrogen && StdHepN!=5){
    printf("\ntest2 StdHepN %d\n", StdHepN);
    for(Int_t ipar=0; ipar<StdHepN; ipar++){
      printf("test2 %d/%d pdg %d\n", ipar, StdHepN,  StdHepPdg[ipar]);
    }
    return kFALSE;
  }
  */

  //0: beam, checked
  //1: target
  //2: charged lepton, checked
  Int_t totalHit = 0;
  for(Int_t ipar=3; ipar<StdHepN; ipar++){
    //StdHepFd [StdHepN] /< first daughter. First daughter of -1 indicates final state particle (after FSI) --- only applies to Genie     

    if(StdHepStatus[ipar]!=1){
      if(gEStatus==0){
        printf("readNuWro::GetParticles status wrong %d\n", StdHepStatus[ipar]);
        DumpEvent();
        gEStatus=1;
      }
      continue;
      //exit(1);
    }

    //this is for GENIE, including nucleus remnant and also virtual particle
    //EvtNum 30 EvtCode 1 ii 7 StdHepPdg 2000000101 StdHepStatus 1 StdHepP4 -0.056173 -0.153609 0.091082 0.025000
    if(StdHepPdg[ipar]>9999){
      continue;
    }

    TLorentzVector tmplv;
    SetLv(tmplv, ipar);
    //such final state can't be used
    if(tmplv.P()<EPSILON){ //B: EPSILON is defined in NeutrinoTools.h
      if(gEMom==0){
        printf("readNuWro::GetParticles 0 momentum ipar %d pdg %d ", ipar, StdHepPdg[ipar]); tmplv.Print();
        DumpEvent();
        gEMom=1;
      }
      continue;
      //exit(1);
    }

    //B: Probably not needed?
    //check virtual particles in final state with status = 1, accepting gamma, (anti)nu_e, (anti)nu_mu
    if(tmplv.M()<EPSILON && StdHepPdg[ipar]<9999 && (StdHepPdg[ipar]!= 22) && ( TMath::Abs(StdHepPdg[ipar])!= 12 ) && ( TMath::Abs(StdHepPdg[ipar])!= 14 ) ){
      printf("readNuWro::GetParticles 0 mass ipar %d pdg %d ", ipar, StdHepPdg[ipar]); tmplv.Print();
      DumpEvent();
      exit(1);
    }

    Bool_t isTrk = kFALSE;
    Bool_t isHit = kFALSE;
    Bool_t isNtl = kFALSE;
    if(numode!=-999){//true mode  
      isTrk = kTRUE;
      isHit = kFALSE;
      isNtl = kFALSE;
    }
    else{//== -999, experiment mode.  B:What we always use
      //IsMeasured sets the is booleans correctly for the given particle
      IsMeasured(StdHepPdg[ipar], tmplv, protonMeVthres, otherMeVthres, isTrk, isHit, isNtl);
    }

    //B: Seems like majority of the if statements below would work fine. perhaps need to look at the fRES->Pion() bits

    //nNeutral above otherThres
    if(isNtl){
      nNeutrals++;
    }

    if( (!isTrk) && (!isHit) ){
      continue; //B: That is move onto next particle
    }

    //(isTrk, isHit) possible combinations left: (1,0), (0,1)
   
    //always pass for true mode; 
    if(isTrk){
      const Int_t tmppdg = StdHepPdg[ipar];
      const Double_t tmpE = StdHepP4[ipar][3];
      if(tmppdg==NeutrinoTools::PDGProton()){
        nproton++;
        if(tmpE>protonmaxe){
          lproton=tmplv;
          protonmaxe = tmpE;
        }
      }
      else if(tmppdg== fRES->Pion()){
        npiRight++;
        if(tmpE>pirightmaxe){
          lpion=tmplv;
          pirightmaxe = tmpE;
        }
      }
      else if(tmppdg==NeutrinoTools::PDGNeutron()){
        nneutron++;
      }
      else if(TMath::Abs(tmppdg)==TMath::Abs(NeutrinoTools::PDGPionMinus())){//is pion but != fRES->Pion
        npiWrong++;
      }
      else if(tmppdg==NeutrinoTools::PDGPionZero()){
        npizero++;
      }
      else if(tmppdg==NeutrinoTools::PDGGamma()){
        ngamma++;
      }
      else{
        //printf("readNuWro::GetParticles unknown particle %d\n", tmppdg); //exit(1);
        nother++;
      }
    }
    else{
      //only useful for experiment mode to judge nuclear emission; for true mode always 0
      totalHit += isHit;
    }
  }

  //__________________________________________________________________________
  //__________________________________________________________________________

  Bool_t passPX = kFALSE;
  Bool_t passQE = kFALSE;
  const Int_t nhad = (nproton + npiRight + nneutron + npiWrong + npizero + ngamma + nother);
  if(numode!=-999){
    //only check for true mode  
    if( StdHepN-3 - nhad ){
      if(gEHepN==0){
        printf("readNuWro::GetParticles numbers of particle wrong %d, %d %d %d %d %d %d %d\n", StdHepN, nproton, npiRight, nneutron, npiWrong, npizero, ngamma, nother);
        DumpEvent();
        gEHepN=1;
      }
      //exit(1);
    }

    //E: It seems this stuff is probably setup specifically for neutrino nucleus interactions and so may need editing
    //allow more pi+ and also other particles
    passPX = ( (numode==fRES->Mode()) && (nproton>=1) && (npiRight>=1) );
    passQE = ( (numode==1)  && (nproton>=1) );
  }
  else{
    if( nneutron || npizero || ngamma ){
      printf("readNuWro::GetParticles found neutron %d pizero %d gamma %d\n", nneutron, npizero, ngamma); exit(1);
    }

    //track level
    //only allow 1 piright to reduce DIS
    passPX = ( (nproton>=1) && (npiRight==1) && (npiWrong==0) && (nother==0) );
    passQE = ( (nproton>=1) && (npiRight==0) && (npiWrong==0) && (nother==0) );
  }
  //should be exclusive
  if(passPX && passQE){
    printf("readNuWro::GetParticles wrong passPX passQE %d, %d %d, %d %d %d, %d %d\n", numode, nproton, npiRight, nneutron, npiWrong, npizero, ngamma, nother);exit(1);
  }

  if(passPX){
    selp_pid = 1;
    selX_charge = (fRES->Pion()==NeutrinoTools::PDGPionPlus())? 1 : -1;
    selX_pid = 2;

    SaveParticles(tmpP4nu, tmpP4ininucleon, llepton, lproton, lpion, NeutrinoTools::PionMass());

    if(numode!=-999){
      kNuclearEmission = (nhad-2);
    }
    else{
      kNuclearEmission = (totalHit || (nproton>1));
    }
  }
  else if(passQE){
    selp_pid = 1;
    selX_charge = -999;
    selX_pid = -999;

    const TLorentzVector dummy;    
    SaveParticles(tmpP4nu,  tmpP4ininucleon, llepton, lproton, dummy, -999);

    if(numode!=-999){
      kNuclearEmission = (nhad-1);
    }
    else{
      kNuclearEmission = (totalHit || (nproton>1));
    }
  }
  else{//still possible due to nproton = 0
    //printf("************************** readNuWro::GetParticles mode %s %d nproton %d npiRight %d\n", EvtCode->String().Data(), numode, nproton, npiRight); //exit(1);
  }
}

void readNuWro::DoAnalysis(const TString filelist, const Int_t nQEtoread, const Int_t nREStoread, const TString tag, const TString outdir, const Bool_t isExpMode, const Double_t protonMeVthres, const Double_t otherMeVthres, const Double_t dpttwidth)
{
  if(isExpMode==1){
    if(protonMeVthres<0 || otherMeVthres<0){
      printf("readNuWro::DoAnalysis wrong isExpMode %d protonMeVthres %f otherMeVthres %f\n", isExpMode, protonMeVthres, otherMeVthres); exit(1);
    }
  }

  NeutrinoUtils::IniCCQE(); //B: Simply re-initialises the state of NeutrinoUtils
  
  //B: Adds root files from filelist to tmptree TChain 
  TChain *tmptree = NeutrinoDetector::IniIO(filelist, "nRooTracker"); 
  //TChain *tmptree = NeutrinoDetector::IniIO(filelist, "giRooTracker");
  Init(tmptree); //B: Defined within readNuWro.h, intialises fChain and sets the branch addresses and pointers
  
  printf("readNuWro::DoAnalysis nQEtoread %d nREStoread %d\n", nQEtoread, nREStoread);
  
  const TString oldfilename=Form("%sPureMCoutput_tag%s.root", outdir.Data(), tag.Data());
  TFile *fout=new TFile(oldfilename,"recreate");  //B: Creates file for output, recreate is an option which creates a new file and overwrites file if already exists

  //new TTree after new TFile to avoid std::bad_alloc because
  //"This is the expected result as you do not associate the TTree with a file, it must keep in memory all the data until the call to Terminate"
  TTree *tout = NeutrinoUtils::GetTree(); 
  //B: This initialises the tree and it's branches.
  
  //B: fChain is a tree defined within readNuWro.h, so naturally this simply returns the number of entries in the tree
  const Int_t nentries = fChain->GetEntries();//fChain->GetEntriesFast();

  Int_t myEntries = 0;
  Int_t nTotCCPX = 0;
  Int_t nTotccqe = 0;
  Int_t nTotOthers = 0;
  Int_t nSelCCPX = 0;
  Int_t nSelccqe = 0;
  Int_t lastQE = -999;
  Int_t lastPX = -999;
  
  //B: In our code dpttwidth set to -999 as such this bit not relevant 
  //20MeV width
  TF1 * fran = 0x0;
  const Bool_t kSmear = (dpttwidth>0);
  if(kSmear){
    //dptt in MeV, need to change to GeV in formula
    fran = new TF1("fran",Form("TMath::CauchyDist(x,0,%f)", dpttwidth/1e3),-0.5,0.5);
    //fran = new TF1("fran","TMath::Gaus(x,0,0.01)",-0.5,0.5);
  }

  //in case not filled, always -999
  StruckNucleonPDG = -999;

  for(Int_t jentry=0; jentry<nentries;jentry++) {
    //B: Note this part of the code seems to be setup explicitly for 1000000 entries, so may need to change in future,
    //B: although worth noting that it only prints so hardly essential for the code to work
    if(jentry%1000000==0){
      printf("%d/%d myEntries %d nTotCCPX %d nTotccqe %d nTotOthers %d nSelCCPX %d nSelccqe %d\n", jentry, nentries,myEntries, nTotCCPX, nTotccqe, nTotOthers, nSelCCPX, nSelccqe);
    }
    
     //B: Stops loop if no more entries to find, but more importantly updates values of variables to that of the next entry (given the slightly odd way reading from a tree works)
    if(!fChain->GetEntry(jentry)){
      printf("readNuWro::DoAnalysis GetEntry ends at jentry %d\n", jentry);
      break;
    }

    //B: Less than 3 particles should be impossible, so exit
    if(StdHepN<3){ 
      printf("readNuWro::DoAnalysis StdHepN < 4: %d, danger no exit!\n", StdHepN); 
      DumpEvent();
      //continue;
      exit(1);
    }    

    //B: Sets fRES if needed
    //E: This is definitely a section which will need editing to get this code working for an electron beam since the code in NeutrinoRES is designed for neutrinos
    //must go first!
    if(!fRES){
      fRES = NeutrinoRES::Instance(StdHepPdg[0]);
      fRES->Dump();
    }

    //B: I think this entire section is related to interactions we aren't dealing with
    //=============================================================
    const Int_t nu_truereac= GetTrueReacWithRESModification();
    //skipping MEC from the beginning
    if(nu_truereac==2){
      if(gEMEC==0){
        gEMEC=1;
      }
      continue;
    }

    //check counts
    if(nu_truereac==fRES->Mode()){
      nTotCCPX++;
    }
    else if(nu_truereac==1){
      nTotccqe++;
    }
    else{
      nTotOthers++;
    }

    myEntries++;

    //============================================================
    
    //B: This part of code should function fine for electron interactions
    Int_t target = -999;
    if(StdHepPdg[1]==NeutrinoTools::PDGProton()){//Hydrogen
      target = 1;
    }
    else if( (StdHepPdg[1]%1000000000) == 10020 ){//Deuteron
      target = 101;
    }
    else{
      target = (StdHepPdg[1]%1000000000)/10000; //StdHepPdg[1]%1000000000 = 60120 for Carbon
    }

    //=============================================================

    Int_t selp_PID = -999;
    Int_t selX_Charge = -999, selX_PID = -999;
    Int_t kNuclearEmission = -9999;
    Int_t nNeutrals = -999;
    GetParticles(isExpMode? -999 : nu_truereac, selp_PID, selX_Charge, selX_PID, kNuclearEmission, protonMeVthres, otherMeVthres, nNeutrals);
    
    if(selp_PID==1){
      //stop filling when ntoread is reached
      if(
         (selX_PID == -999 && nSelccqe<nQEtoread) ||
         (selX_PID == 2    && nSelCCPX<nREStoread)
         ){
        // static void SaveInfo(const Int_t target, const Int_t nu_truereac, const Int_t nu_parentpdg, const Int_t nu_pdg, const Int_t ntpctracks, const Int_t topology,   const Int_t selp_PID, const Int_t selcharge, const Int_t selpid, const Int_t eventtypesim=-999,  const Int_t simotherpdg=-999, const Int_t necaltracks=-999, const Int_t ecalpdgsim=-999);
        NeutrinoDetector::SaveInfo(target, nu_truereac, -999, fRES->Beam(), -999, -999, selp_PID, selX_Charge, selX_PID);
        
        
        NeutrinoUtils::SetTransverseKinematics();
        NeutrinoUtils::SetNuclearEmission(kNuclearEmission);
        NeutrinoUtils::SetNNeutrals(nNeutrals);

        //smear out dpttrec!
        if(kSmear){
          NeutrinoUtils::fMuonDeltaPTTRec += fran->GetRandom();
        }

        tout->Fill(); //B: I think this is stage where current data is temp. stored

        if(selX_PID == -999){
          nSelccqe++;
        }
        else{
          nSelCCPX++;
        }

        if((selX_PID == -999) && nSelccqe == nQEtoread){
          lastQE = jentry;
        }

        if((selX_PID == 2 )   && nSelCCPX == nREStoread){
          lastPX = jentry;
        }
      }
    }      

    //check end
    //if(ntoread>=0 && jentry>=ntoread-1){
    if(nQEtoread>=0 && nREStoread>=0 && (nSelccqe>=nQEtoread) && (nSelCCPX>=nREStoread) ){
      break;
    }
  }
  
  printf("\n\n");
  if(myEntries-nTotCCPX-nTotccqe-nTotOthers){
    printf("***********************myEntries-nTotCCPX-nTotccqe-nTotOthers !=0, %d %d %d %d\n", myEntries, nTotCCPX, nTotccqe, nTotOthers); exit(1);
  }
  else{
    printf("myEntries %d, nTotCCPX %d, nTotccqe %d, nTotOthers %d good! nSelCCPX %d nSelccqe %d last QE %d RES %d\n",  myEntries, nTotCCPX, nTotccqe, nTotOthers, nSelCCPX, nSelccqe, lastQE, lastPX);
  }

  printf("\n\n");

  tout->Write();
  fout->Save();
  fout->Close();
  delete fout;

  const TString outstr = Form("%s_beam%d_isExpMode%d_protonMeVthres%.0f_otherMeVthres%.0f_dpttwidth%0.f_myEntries_%d_PX_%d_%d_%d_qe_%d_%d_%d_EStatus%d_EHepN%d_EMEC%d_EMom%d", tag.Data(), fRES->Beam(), isExpMode, protonMeVthres, otherMeVthres, dpttwidth, myEntries, lastPX, nTotCCPX, nSelCCPX, lastQE, nTotccqe, nSelccqe, gEStatus, gEHepN, gEMEC, gEMom);
  printf("done %s\n", outstr.Data());
  
  const TString newfilename=Form("%sPureMCoutput_tag%s.root", outdir.Data(), outstr.Data());
  const TString domv=Form("mv %s %s", oldfilename.Data(), newfilename.Data());
  printf("finishing and doing mv...\n%s\n\n", domv.Data());
  gSystem->Exec(domv);
}
