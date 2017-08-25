#include "NeutrinoTools.h"

class NeutrinoRES
{
 public:
 NeutrinoRES(const TString name, const Int_t beam, const Int_t mode, const Int_t lepton, const Int_t pion): fName(name), fBeam(beam), fMode(mode), fLepton(lepton), fPion(pion){}

 NeutrinoRES(NeutrinoRES & ref): fName(ref.fName), fBeam(ref.fBeam), fMode(ref.fMode), fLepton(ref.fLepton), fPion(ref.fPion){}

  TString Name() const {return fName;}
  Int_t Beam() const {return fBeam;}
  Int_t Mode() const {return fMode;}
  Int_t Lepton() const {return fLepton;}
  Int_t Pion() const {return fPion;}
  Double_t TargetMass() const {return NeutrinoTools::ProtonMass();}
  Int_t Target() const {return NeutrinoTools::PDGProton(); }

  void Dump() const;
  static const NeutrinoRES * Instance(const Int_t beam);

 private:
  const TString fName;
  const Int_t fBeam;
  const Int_t fMode;
  const Int_t fLepton;
  const Int_t fPion;
};

//http://genie.hepforge.org/doxygen/html/namespacegenie_1_1utils_1_1ghep.html#a51cb53894fa9d5325749bbad6eea1151
//GENIE:  if (is_nubar && is_cc && is_p && np==1 && nn==0 && npip==0 && npim==1 && npi0==0 && neKL==0) evtype = -13;
//in NuWro all modes are positive, and seems to have the same definition as nu, so change -13 to 11

NeutrinoRES _RESNuMu(    "_RESNuMu",   NeutrinoTools::PDGNuMu(),   11, NeutrinoTools::PDGMuonMinus(), NeutrinoTools::PDGPionPlus());
NeutrinoRES _RESNuE(     "_RESNuE",    NeutrinoTools::PDGNuE(),    11, NeutrinoTools::PDGElectron(),  NeutrinoTools::PDGPionPlus());
NeutrinoRES _RESAntiMu(  "_RESAntiMu", NeutrinoTools::PDGAntiMu(), 11, NeutrinoTools::PDGMuonPlus(),  NeutrinoTools::PDGPionMinus());
NeutrinoRES _RESAntiE(   "_RESAntiE",  NeutrinoTools::PDGAntiE(),  11, NeutrinoTools::PDGPositron(),  NeutrinoTools::PDGPionMinus());

void NeutrinoRES::Dump() const
{
  printf("NeutrinoRES::Dump Name %20s Beam %3d Mode %3d Lepton %3d Pion %4d TargetMass %10.6f\n", Name().Data(), Beam(), Mode(), Lepton(), Pion(), TargetMass());
}

const NeutrinoRES * NeutrinoRES::Instance(const Int_t beam)
{
  const NeutrinoRES * res = 0x0;

  if(beam==NeutrinoTools::PDGNuMu()){
    res = &_RESNuMu;
  }
  else if(beam==NeutrinoTools::PDGAntiMu()){
    res = &_RESAntiMu;
  }
  else if(beam==NeutrinoTools::PDGNuE()){
    res = &_RESNuE;
  }
  else if(beam==NeutrinoTools::PDGAntiE()){
    res = &_RESAntiE;
  }
  else{
    printf("NeutrinoRES::Instance wrong beam %d\n", beam); exit(1);
  }
  return res;
}
