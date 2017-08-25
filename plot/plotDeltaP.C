#include "TString.h"
#include "TH2D.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLine.h"
#include "TGaxis.h"

#include "TPaveStats.h"

#include "TLegend.h"
#include "style.h"


void Plot(){
  TString filelist = "/home/robertsb/summerInvestigation/analyse/outdata/Ana/Output_tageWroRFG_a_El3000.root";

  TFile * fin = new TFile(filelist);
  TTree * tree = (TTree*) fin->Get("tree");

  // style::SetGlobalStyle();

  TCanvas * c1 = new TCanvas("c1","",1200,800);
  // style::fgkYTitleOffset = 1.1;

  // style::PadSetup(c1);
  TGaxis::SetMaxDigits(3);
  //c1->SetRightMargin(0.03);
  c1->SetTopMargin(0.08);                                                                                                      
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.15);

  TH1D *h0=0x0;

  gStyle->SetOptStat(0);

  h0 = new TH1D("htest",";#Deltap (MeV/c);p.d.f",80,0.0,2000);

  tree->Draw(Form("(fFullDeltaP*1e3)>>%s", h0->GetName()));
  h0->Scale(1./h0->Integral(0,h0->GetNbinsX()+1)/h0->GetBinWidth(1));
  c1->Print("outdata/test/DeltaP.eps");
  c1->Print("outdata/test/DeltaP.png");

  tree->Draw(Form("(fFullDeltaP*1e3)>>%s", h0->GetName()), "fFullDeltaP>0.1");
  h0->Scale(1./h0->Integral(0,h0->GetNbinsX()+1)/h0->GetBinWidth(1));
  c1->Print("outdata/test/DeltaP>100.eps");
  c1->Print("outdata/test/DeltaP>100.png");

  TH1D *h1 = new TH1D("htest1",";#Deltap (MeV/c);p.d.f",56,0.0,560);
  tree->Draw(Form("(fFullDeltaP*1e3)>>%s", h1->GetName()), "fFullDeltaP>0.1");
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  c1->Print("outdata/test/100<DeltaP<560.eps");
  c1->Print("outdata/test/100<DeltaP<560.png");

  h1 = new TH1D("htest",";#Deltap (MeV/c);p.d.f",50,0.0,100);
  tree->Draw(Form("(fFullDeltaP*1e3)>>%s", h1->GetName()), "fFullDeltaP<0.1");
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  c1->Print("outdata/test/DeltaP<100.eps");
  c1->Print("outdata/test/DeltaP<100.png");


}
