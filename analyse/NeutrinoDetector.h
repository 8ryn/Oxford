#include "NeutrinoUtils.h"

class NeutrinoDetector
{
 public:
  static void SaveInfo(const Int_t target, const Int_t nu_truereac, const Int_t nu_parentpdg, const Int_t nu_pdg, const Int_t ntpctracks, const Int_t topology,   const Int_t selp_pid, const Int_t selcharge, const Int_t selpid, const Int_t muonrectype=-999, const Int_t eventtypesim=-999,  const Int_t simotherpdg=-999, const Int_t necaltracks=-999, const Int_t ecalpdgsim=-999);

  static void SetNeutrinoSim(const Float_t nu_truedir[], const Float_t nu_trueE);
  static void SetNeutrinoRec(const TVector3 & nudir);
  static void SetNeutrinoGuess(const Float_t nu_truedir[]);
  static void SetMuonGuess();

  //== independent of NeutrinoUtils
  static TChain * IniIO(const TString flist, const TString tn);
  static Int_t SetMother(const TLorentzVector * nuref, NeutrinoParticle * ftrueptr,  const TLorentzVector * daughter1, const TLorentzVector * daughter2);
  static Int_t SetParticleSim(const TLorentzVector * nusim, NeutrinoParticle * ftrueptr, const Double_t truemass, const Float_t true_truedir[], const Float_t true_truemom, const Int_t pdg, const Float_t true_charge=-999);
  static Int_t SetParticleRec(const TLorentzVector * nurec, NeutrinoParticle * selptr, const Double_t selmass, const Float_t sel_dir[], const Float_t sel_mom, const Float_t *vertex_pos=0x0, const Float_t sel_charge=-999, const Float_t *sel_endpos=0x0, const Float_t sel_Chi2=-999, const Float_t sel_NDOF=-999, const Int_t tmpnq=0, const Double_t *tmpqs=0x0, const Int_t sel_ntpcs=-999, const Int_t *sel_tpc_nhits=0x0, const Float_t pullele=-999, const Float_t pullmu=-999, const Float_t pullpi=-999, const Float_t pullproton=-999);
  static Int_t SetProtonToy(const Bool_t kstaticN, NeutrinoParticle * neutronToy, const TLorentzVector * nuSim, const TLorentzVector * muonSim, NeutrinoParticle * protonToy, const Int_t murecpdg );

 private:
  
  static void SetNeutronToy(NeutrinoParticle *ntoy, const Bool_t kstatic);
  static TLorentzVector *GetFakeProton(const TLorentzVector * neutrinosim,  const TLorentzVector * ntoy, const TLorentzVector * muonsim);
};


void NeutrinoDetector::SetNeutrinoSim(const Float_t nu_truedir[], const Float_t nu_trueE)
{
  delete NeutrinoUtils::fNeutrinoSim;
  NeutrinoUtils::fNeutrinoSim = 0x0;

  TVector3 nup3(nu_truedir[0],nu_truedir[1],nu_truedir[2]);

  if(nu_trueE > EPSILON && nup3.Mag() > EPSILON){
    nup3 *= nu_trueE * 1e-3 / nup3.Mag(); //in GeV/c
    
    const Double_t nuE = nup3.Mag();
    NeutrinoUtils::fNeutrinoSim = new TLorentzVector(nup3, nuE);
  }
}

void NeutrinoDetector::SetNeutrinoRec(const TVector3 & nudir)
{
  delete NeutrinoUtils::fNeutrinoRec;
  NeutrinoUtils::fNeutrinoRec = new TLorentzVector(nudir,1);
}

void NeutrinoDetector::SetNeutrinoGuess(const Float_t nu_truedir[])
{
  delete NeutrinoUtils::fNeutrinoGuess;
  NeutrinoUtils::fNeutrinoGuess = 0x0;

  //
  //  NeutrinoUtils::fNeutrinoGuess = new TVector3(0,0,1);

  //fast access to true, but not really needed
  TVector3 nup3(nu_truedir[0],nu_truedir[1],nu_truedir[2]);
  
  if(nup3.Mag()>EPSILON){
    //use true beam direciton for Guess so that the pt resolution with true beam dir can be got from pt guess
    //can happen that fNeutrinoSim is bad because at this stage SetNeutrinoSim is not called!!
    NeutrinoUtils::fNeutrinoGuess = new TLorentzVector(nup3.Unit(),1);
  }
}

void NeutrinoDetector::SetMuonGuess()
{
  NeutrinoUtils::fMuonGuess->Reset();

  if(NeutrinoUtils::GetMuonNRec()>0){
    //should call SetParticleRec first!
    NeutrinoUtils::fMuonGuess->fLorentzVec = new TLorentzVector(*(NeutrinoUtils::fMuonRec->fLorentzVec));
    
    //should call SetNeutrinoGuess first
    NeutrinoUtils::fMuonGuess->SetNeutrino(NeutrinoUtils::fNeutrinoGuess);
    
    NeutrinoUtils::fMuonGuess->SetKinematics();
  }
}

void NeutrinoDetector::SaveInfo(const Int_t target, const Int_t nu_truereac, const Int_t nu_parentpdg, const Int_t nu_pdg, const Int_t ntpctracks, const Int_t topology, const Int_t selp_pid, const Int_t selcharge, const Int_t selpid, const Int_t muonrectype, const Int_t eventtypesim, const Int_t simotherpdg, const Int_t necaltracks, const Int_t ecalpdgsim)
{
  NeutrinoUtils::fTarget = target;
  NeutrinoUtils::fNeutMode = nu_truereac;
  NeutrinoUtils::fNeutrinoParentPDG = nu_parentpdg;
  NeutrinoUtils::fNeutrinoParentType = NeutrinoTools::PDGToType(NeutrinoUtils::fNeutrinoParentPDG);
  NeutrinoUtils::fNeutrinoType = nu_pdg;
  NeutrinoUtils::fkOsciMuSurvive = 1;

  //use TPC for multiplicity; has to be confirmed; test; 
  NeutrinoUtils::SetMultiplicity(ntpctracks);

  NeutrinoUtils::fSelp_PID = selp_pid;
  NeutrinoUtils::fSelX_Charge = selcharge;
  NeutrinoUtils::fTopology = topology;
  NeutrinoUtils::fSelX_PID = selpid;

  NeutrinoUtils::fMuonRecType = muonrectype;

  NeutrinoUtils::fEventTypeSim = eventtypesim;
  NeutrinoUtils::fSimOtherPDG = simotherpdg;
  NeutrinoUtils::fNECalTracks = necaltracks;
  NeutrinoUtils::fECalPDGSim = ecalpdgsim;
}



//================================================================================================
//independent of NeutrinoUtils
//================================================================================================
TChain * NeutrinoDetector::IniIO(const TString flist, const TString tn)
{
  printf("NeutrinoDetector::IniIO flist %s %s\n", flist.Data(), tn.Data());

  return NeutrinoTools::InputFiles(flist, tn);
}

Int_t NeutrinoDetector::SetMother(const TLorentzVector * nuref, NeutrinoParticle * ftrueptr,  const TLorentzVector * daughter1, const TLorentzVector * daughter2)
{
  ftrueptr->Reset();

  Int_t nmother = 0;

  if(daughter1 && daughter2){
    ftrueptr->fLorentzVec = new TLorentzVector( *(daughter1) + *(daughter2) );
    
    ftrueptr->SetNeutrino(nuref);
    
    ftrueptr->SetKinematics();

    //ftrueptr->fPDG = pdg;
    //ftrueptr->fType =  NeutrinoTools::PDGToType(pdg);
    
    //ftrueptr->fCharge = charge;

    nmother = 1;
  }
  else{
    nmother = 0;
  }

  return nmother;
}

Int_t NeutrinoDetector::SetParticleSim(const TLorentzVector * nusim, NeutrinoParticle * ftrueptr, const Double_t truemass, const Float_t true_truedir[], const Float_t true_truemom, const Int_t pdg, const Float_t true_charge)
{
  ftrueptr->Reset();

  Int_t nfound = 0;
  //negative mom is -999 due to NC
  TVector3 parp3(true_truedir[0], true_truedir[1], true_truedir[2]);
  if(truemass > 0 && true_truemom>EPSILON && parp3.Mag() > EPSILON){
    parp3 *= true_truemom * 1e-3 / parp3.Mag();
    
    const Double_t parE = TMath::Sqrt(truemass*truemass+parp3.Mag2());
    //checked by ploting ->M(), confirmed to be 0.1057
    ftrueptr->fLorentzVec = new TLorentzVector(parp3, parE);

    //should SetNeitrinoSim first!!
    ftrueptr->SetNeutrino(nusim);

    ftrueptr->SetKinematics();

    ftrueptr->fPDG = pdg;
    ftrueptr->fType =  NeutrinoTools::PDGToType(pdg);

    ftrueptr->fCharge = (Int_t) true_charge;

    nfound = 1;
  }
  return nfound;
}

Int_t NeutrinoDetector::SetParticleRec(const TLorentzVector * nurec, NeutrinoParticle * selptr, const Double_t selmass, const Float_t sel_dir[], const Float_t sel_mom, const Float_t * vertex_pos, const Float_t sel_charge, const Float_t *sel_endpos, const Float_t sel_Chi2, const Float_t sel_NDOF, const Int_t tmpnq, const Double_t *tmpqs, const Int_t sel_ntpcs, const Int_t *sel_tpc_nhits, const Float_t pullele, const Float_t pullmu, const Float_t pullpi, const Float_t pullproton)
{
  selptr->Reset();

  TVector3 parp3(sel_dir[0],sel_dir[1],sel_dir[2]);
  const Double_t momvar = sel_mom;

  Int_t nrec = 0;

  if(selmass > 0 && momvar > EPSILON && parp3.Mag()>EPSILON){
    parp3 *= momvar * 1e-3 / parp3.Mag();

    const Double_t parE = TMath::Sqrt(selmass*selmass+parp3.Mag2());
    selptr->fLorentzVec = new TLorentzVector(parp3, parE); 

    //should call SetNeutrinoRec first!!
    selptr->SetNeutrino(nurec);

    selptr->SetKinematics();

    if(vertex_pos){
      const TVector3 tmpvertex(vertex_pos);
      selptr->fVertex = new TVector3(tmpvertex * 0.001); //default in mm
    }

    if(sel_endpos){
      const TVector3 tmpendpos(sel_endpos);
      selptr->fEndPos = new TVector3(tmpendpos * 0.001); //default in mm
      
      if(vertex_pos){  
        selptr->fFlightPath = new TVector3( (*(selptr->fEndPos)) - (*(selptr->fVertex))); //default mm
      }
    }
    
    selptr->fCharge = (Int_t)sel_charge;

    selptr->fChi2 = sel_Chi2;
    selptr->fNDOF = sel_NDOF;

    //nhits = sel_tpc_nnodes
    //safe for muon, not for proton due to unknown accmu_level
    if(sel_ntpcs==0){
      printf("NeutrinoDetector::SetParticleRec bad sel_ntpcs %d\n", sel_ntpcs); exit(1);
    }
    
    selptr->fNdets[0] = sel_ntpcs;
    
    if(sel_tpc_nhits){
      for(Int_t itpc=0; itpc<sel_ntpcs; itpc++){
        selptr->fNhits[itpc] = sel_tpc_nhits[itpc];
      }
    }

    //set pull
    selptr->fPullele = pullele;
    selptr->fPullmu  = pullmu;
    selptr->fPullpi  = pullpi;
    selptr->fPullproton   = pullproton;

    if(tmpqs){
      selptr->fNE = tmpnq;
      selptr->fE0 = tmpqs[0];
      selptr->fE1 = tmpqs[1];
      selptr->fE2 = tmpqs[2];
      selptr->fE3 = tmpqs[3];
      selptr->fE4 = tmpqs[4];
      selptr->fE5 = tmpqs[5];
    }

    nrec = 1;
  }

  return nrec;
}


void NeutrinoDetector::SetNeutronToy(NeutrinoParticle *ntoy, const Bool_t kstatic)
{
  ntoy->Reset();

  if(!kstatic){
    TVector3 fermiP;
    NeutrinoTools::SampleUnityIsotropicVector(&fermiP);
    fermiP *= NeutrinoTools::SampleFermiMomentum();
    
    const Double_t nE = TMath::Sqrt(fermiP.Mag2()+NeutrinoTools::NeutronMass()*NeutrinoTools::NeutronMass());
    ntoy->fLorentzVec = new TLorentzVector(fermiP, nE);
  }
  else{
    ntoy->fLorentzVec = new TLorentzVector(0,0,0, NeutrinoTools::NeutronMass());
  }
}

TLorentzVector *NeutrinoDetector::GetFakeProton(const TLorentzVector * neutrinosim,  const TLorentzVector * ntoy, const TLorentzVector * muonsim)
{
  TLorentzVector * fakep = 0x0;
  if(neutrinosim && muonsim){
    fakep = new TLorentzVector((*neutrinosim)+(*ntoy)-(*muonsim));
  }
  return fakep;
}

Int_t NeutrinoDetector::SetProtonToy(const Bool_t kstaticN, NeutrinoParticle * neutronToy, const TLorentzVector * nuSim, const TLorentzVector * muonSim, NeutrinoParticle * protonToy, const Int_t murecpdg )
{
  protonToy->Reset();
  Int_t ntoy = 0;

  //kstaticN
  //kTRUE:  test with static Neutron to validate the codes
  //kFALSE: fermi motion of neutron
  /*
  //to test
  tree->Draw("fNeutronToy->M()","fMuonNSim>0")
  //all M: ~0-RMS
  
  tree->Draw("fNeutronToy->P()","fMuonNSim>0")
  tree->Draw("fNeutronToy->Theta()","fMuonNSim>0")
  tree->Draw("fNeutronToy->Phi()","fMuonNSim>0")
  
  //static: P, theta, phi: 0
  //non static: P: fermi momentum GEANT4 max~0.17, theta: sin(theta), phi: flat
  
  tree->Draw("fDeltaToyPt->Mag()","fMuonNSim>0")
  tree->Draw("fDeltaToyPt->Theta()","fMuonNSim>0")
  tree->Draw("fDeltaToyPt->Phi()","fMuonNSim>0")
  
  //static: delta pt: ~0, theta(=alpha): not defined (unless for FSIfactor!=1), phi: 0
  */

  SetNeutronToy(neutronToy, kstaticN);

  TLorentzVector * fakeP1 = GetFakeProton(nuSim, neutronToy->fLorentzVec, muonSim);

  if(fakeP1){

    //static void RutherfordTransport(TLorentzVector * v0, const Int_t nstep, const Double_t regtheta, const Double_t regde);
    //NeutrinoTools::RutherfordTransport(fakeP1, 1, 0, 0, 0);//no move
    //NeutrinoTools::RutherfordTransport(fakeP1, 1, 0, 0, 1e-1);//only de active. dpT small away from 0, dalpha small away from pi, dphi 0.
    //NeutrinoTools::RutherfordTransport(fakeP1, 1, 1, 0, 0);//only phi active. dpT nearly 0, dalpha undefined (corresponding to 0 dpT), dphiT 0 --> good. When no polar angle change, azimuth should not change
    //NeutrinoTools::RutherfordTransport(fakeP1, 1, 1, 1E-6, 0);//only phi, theta active (phi has to be active!! otherwise only scatter in theta). regtheta=1 too big, dpt mean 0.311 GeV/c. regtheta 1E-6, dpt mean 0.0016 : dpT small away from 0, dalpha big range between 0-pi and mild bump at pi/2, deflection makes the pT projection bigger! dphi small away from 0.
    //NeutrinoTools::RutherfordTransport(fakeP1, 1, 1, 1E-6, 1E-1);//all active, one step. dpT small away from 0, dalpha sharp peak at pi, long tail to 0, dip at pi/2! dphi small away from 0.
    //NeutrinoTools::RutherfordTransport(fakeP1, 10, 1, 1E-6, 1E-1);//all active, 10 steps. dpt landau, dalpha all pulled to pi (dedx too large), dphi small away from 0.
    //NeutrinoTools::RutherfordTransport(fakeP1, 10, 1, 1E-6, 1E-3);//all active, 10 steps. dpt narrow landau, dalpha partial pull and no peak at 0, dphi small away from 0.
    
    //conclusion: not to transport at the moment since too many parameters and no clear way to handle. 
    
    Float_t fakeV[]={fakeP1->X(), fakeP1->Y(), fakeP1->Z()};
    //FSIfactor > 1, accelerated, alpha=0
    //FSIfactor < 1, decelearted, alpha=pi
    const Double_t FSIfactor = 1; //0.1;//2;

    //momentum should be in MeV
    SetParticleSim(nuSim, protonToy, NeutrinoTools::ProtonMass(), fakeV,   fakeP1->P()*1e3*FSIfactor,   murecpdg);

    ntoy = 1;
  }

  return ntoy;
}
