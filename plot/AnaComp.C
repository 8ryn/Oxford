#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TH1D.h" 
#include "TStyle.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TLegend.h"

void reset(TLegend * lg){
  lg->SetTextSize(0.05);
  lg->SetFillStyle(-1);
  lg->SetBorderSize(-1);
}

void AnaComp(){

  const TString file1 = "/home/robertsb/summerInvestigation/analyse/outdata/NuWro/PureMCoutput_tagNuWroRFG_b_NuMuB3000_beam14_isExpMode0_protonMeVthres-999_otherMeVthres-999_dpttwidth-999_myEntries_1000000_PX_-999_0_0_qe_-999_694698_685400_EStatus0_EHepN0_EMEC0_EMom0.root";
  const TString file2 = "/home/robertsb/summerInvestigation/analyse/outdata/NuWroB/Output_tagNuWroRFG_b_NuMu3000.root";
  const TString outtag = "outplot/anaComp/";

  TFile * fin1 = new TFile(file1);
  TTree * tree1 = (TTree*) fin1->Get("tree");

  TFile * fin2 = new TFile(file2);
  TTree * tree2 = (TTree*) fin2->Get("tree");

  TH1D * h1 = 0x0;
  TH1D * h2 = 0x0;

  TLegend * lg = 0x0;

  TString var;
  TString cut;

  gStyle->SetOptStat(0);

  TCanvas * c1 = new TCanvas("c1","",600,400);
  c1->SetRightMargin(0.03);
  c1->SetTopMargin(0.08);         
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.15);


  //deltaP<.6 /////////////////////////

  lg = new TLegend(0.75, 0.20, 0.9, 0.35);
  reset(lg);

  h1 = new TH1D("orig",";#DeltaP (GeV/c);p.d.f",100,0,0.6);
  var=Form("(%s)>>%s","fProtonSimFullDeltaP->Mag()",h1->GetName());
  cut= "fProtonSimFullDeltaP->Mag()>0.01";
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(2);
  lg->AddEntry(h1, "Original", "l");

  h2 = new TH1D("new1","",100,0,0.6);
  var=Form("(%s)>>%s","fFullDeltaP",h2->GetName());
  cut= "fFullDeltaP>0.01";
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(1);
  lg->AddEntry(h2, "Mine", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaP<06.png");
  c1->Print(outtag+"deltaP<06.root");

  delete h1;
  delete h2;

  //deltaP ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("orig",";#DeltaP (GeV/c);p.d.f",100,0,3);
  var=Form("(%s)>>%s","fProtonSimFullDeltaP->Mag()",h1->GetName());
  cut= "fProtonSimFullDeltaP->Mag()>0.01";
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(2);
  lg->AddEntry(h1, "Original", "l");

  h2 = new TH1D("new1","",100,0,3);
  var=Form("(%s)>>%s","fFullDeltaP",h2->GetName());
  cut= "fFullDeltaP>0.01";
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(1);
  lg->AddEntry(h2, "Mine", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaP.png");
  c1->Print(outtag+"deltaP.root");

  delete h1;
  delete h2;

}
