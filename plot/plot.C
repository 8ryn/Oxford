#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TH1D.h" 
#include "TStyle.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"

void reset(TLegend * lg){
  lg->SetTextSize(0.05);
  lg->SetFillStyle(-1);
  lg->SetBorderSize(-1);
}

void plot(Int_t opt, Int_t energy){

  TString file1;
  TString outtag;
  TString plottag;
  TString tempTitle; //Title to avoid confusion while comparing eWro and NuWro
  Double_t deltaPCut;

  if(opt==1){//NuWro

    file1 = Form("/home/robertsb/summerInvestigation/analyse/outdata/NuWroB/Output_tagNuWroRFG_b_NuMu%d.root",energy);
    outtag = Form("outplot/NuWro/%d/",energy);
    deltaPCut = 0.01;
    plottag = Form("NuWro%d", energy);
    tempTitle = "NuWro";
  }

  else if(opt==2){//eWro

    file1 = Form("/home/robertsb/summerInvestigation/analyse/outdata/eWro/Output_tageWroRFG_a_El%d.root",energy);
    outtag = Form("outplot/eWro/%d/",energy);
    deltaPCut = 0.05;
    if(energy<=1000) deltaPCut = 0.15; //Because it's all a bit dodgy
    plottag = Form("eWro%d", energy);
    tempTitle = "eWro";
  }
  else exit(1);

  //Removes tempTitle, comment out of needed
  // tempTitle = "";

  TFile * fin1 = new TFile(file1);
  TTree * tree1 = (TTree*) fin1->Get("tree");

  TH1D * h1 = 0x0;

  TString var;
  TString cut;

  gStyle->SetOptStat(0);

  TCanvas * c1 = new TCanvas("c1","",990,660);
  c1->SetRightMargin(0.03);
  c1->SetTopMargin(0.08);         
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.15);


  //deltaP<.6 /////////////////////////

  h1 = new TH1D("rpa0",";#DeltaP (GeV/c);p.d.f",100,0,0.6);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFullDeltaP",h1->GetName());
  cut= Form("fFullDeltaP>%f",deltaPCut);
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"deltaP<06"+plottag+".png");
  c1->Print(outtag+"deltaP<06"+plottag+".root");

  delete h1;


  //deltaPFull<.5 /////////////////////////

  h1 = new TH1D("rpa0",";#DeltaP (GeV/c);p.d.f",100,0,0.5);
  h1->SetTitle(Form("E = %.1f GeV",(Double_t)energy/1000));
  var=Form("(%s)>>%s","fFullDeltaP",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"deltaPFull<05"+plottag+".png");
  c1->Print(outtag+"deltaPFull<05"+plottag+".root");

  delete h1;

  //deltaP ///////////////////////////

  h1 = new TH1D("rpa0",";#DeltaP (GeV/c);p.d.f",100,0,energy/1000);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFullDeltaP",h1->GetName());
  cut= Form("fFullDeltaP>%f",deltaPCut);;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"deltaP"+plottag+".png");
  c1->Print(outtag+"deltaP"+plottag+".root");

  Int_t intentries = h1->GetEntries();

  delete h1;

  //deltaP full ///////////////////////////

  h1 = new TH1D("rpa0",";#DeltaP (GeV/c);p.d.f",100,0,energy/1000);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFullDeltaP",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"deltaPFull"+plottag+".png");
  c1->Print(outtag+"deltaPFull"+plottag+".root");

  Double_t tau = intentries/h1->GetEntries();

  delete h1;

  //deltaE full ///////////////////////////

  if (opt==1) h1 = new TH1D("rpa0",";#DeltaE /GeV);p.d.f",100,0,0.6);
  else h1 = new TH1D("rpa0",";#DeltaE /GeV);p.d.f",100,0,0.2);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFullDeltaE-0.032",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"deltaEFull"+plottag+".png");
  c1->Print(outtag+"deltaEFull"+plottag+".root");


  delete h1;

  //deltaPt<0.6 ///////////////////////////

  h1 = new TH1D("rpa0",";#deltaP_{T} (GeV/c);p.d.f",100,0,0.6);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fDeltaPt",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"deltaPt<06"+plottag+".png");
  c1->Print(outtag+"deltaPt<06"+plottag+".root");

  delete h1;

  //deltaPt ///////////////////////////

  h1 = new TH1D("rpa0",";#deltaP_{T} (GeV/c);p.d.f",100,0,1.6);
  var=Form("(%s)>>%s","fDeltaPt",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"deltaPt"+plottag+".png");
  c1->Print(outtag+"deltaPt"+plottag+".root");

  delete h1;

  //alphat ///////////////////////////

  h1 = new TH1D("rpa0",";#delta#alpha_{T} /rads;p.d.f",100,0,TMath::Pi());
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fAlphat",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetMinimum(0);
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"Alphat"+plottag+".png");
  c1->Print(outtag+"Alphat"+plottag+".root");

  delete h1;

  //alphat no FSI///////////////////////////

  h1 = new TH1D("rpa0",";#delta#alpha_{T} no FSI /rads;p.d.f",100,0,TMath::Pi());
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fAlphat",h1->GetName());
  cut=Form("fFullDeltaP<%f", deltaPCut); 
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetMinimum(0);
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"AlphatnoFSI"+plottag+".png");
  c1->Print(outtag+"AlphatnoFSI"+plottag+".root");

  delete h1;

  //alphat only FSI///////////////////////////

  h1 = new TH1D("rpa0",";#delta#alpha_{T} only FSI /rads;p.d.f",100,0,TMath::Pi());
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fAlphat",h1->GetName());
  cut=Form("fFullDeltaP>%f", deltaPCut); 
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetMinimum(0);
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"AlphatonlyFSI"+plottag+".png");
  c1->Print(outtag+"AlphatonlyFSI"+plottag+".root");

  delete h1;

  //phit ///////////////////////////

  h1 = new TH1D("rpa0",";#delta#phi_{T} /rads;p.d.f",100,0,2.5);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fPhit",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"Phit"+plottag+".png");
  c1->Print(outtag+"Phit"+plottag+".root");

  delete h1;

  //phit <1 ///////////////////////////

  h1 = new TH1D("rpa0",";#delta#phi_{T} /rads;p.d.f",100,0,1);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fPhit",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"Phit<1"+plottag+".png");
  c1->Print(outtag+"Phit<1"+plottag+".root");

  delete h1;

  //phit no FSI ///////////////////////////
 
  h1 = new TH1D("rpa0",";#delta#phi_{T} no FSI /rads;p.d.f",100,0,2.0);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fPhit",h1->GetName());
  cut=Form("fFullDeltaP<%f", deltaPCut); 
  tree1->Draw(var, cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"PhitnoFSI"+plottag+".png");
  c1->Print(outtag+"PhitnoFSI"+plottag+".root");

  delete h1;

  //phit only FSI ///////////////////////////
 
  h1 = new TH1D("rpa0",";#delta#phi_{T} only FSI /rads;p.d.f",100,0,2.0);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fPhit",h1->GetName());
  cut=Form("fFullDeltaP>%f", deltaPCut); 
  tree1->Draw(var, cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"PhitonlyFSI"+plottag+".png");
  c1->Print(outtag+"PhitonlyFSI"+plottag+".root");

  delete h1; 

 //Q2 ///////////////////////////

  if(opt==1) h1 = new TH1D("rpa0",";Q^{2} (GeV/c)^{2} ;p.d.f",100,-1.6,0);
  else if(opt==2)  h1 = new TH1D("rpa0",";Q^{2} (GeV/c)^{2} ;p.d.f",100,-0.3,-0.15);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fQ2",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"Q2"+plottag+".png");
  c1->Print(outtag+"Q2"+plottag+".root");

  delete h1;

  //initial nucleon momentum ///////////////////////////
 
  h1 = new TH1D("rpa0",";p^{N} (GeV/c);p.d.f",100,0,0.24);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fIniNucP",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"IniNucP"+plottag+".png");
  c1->Print(outtag+"IniNucP"+plottag+".root");

  delete h1;

  //final proton momentum ///////////////////////////
 
  if(opt==1) h1 = new TH1D("rpa0",";p^{P} (GeV/c);p.d.f",100,0,energy/1000 +0.5);
  else if(opt==2) h1 = new TH1D("rpa0",";p^{P} (GeV/c);p.d.f",100,0,0.8*energy/1000 );
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFinProtP",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"FinProtP"+plottag+".png");
  c1->Print(outtag+"FinProtP"+plottag+".root");

  delete h1;

  //final lepton momentum ///////////////////////////

  if(opt==1) h1 = new TH1D("rpa0",";p^{#mu} (GeV/c);p.d.f",100,0,energy/1000);
  else if(opt==2){
    if(energy==1000){
      h1 = new TH1D("rpa0",";p^{e} (GeV/c);p.d.f",100,0.7,1.0);
    }
    else {
      h1 = new TH1D("rpa0",";p^{e} (GeV/c);p.d.f",100,1.6,2.5);
    }
  }
  else if(opt==2) h1 = new TH1D("rpa0",";p^{e} (GeV/c);p.d.f",100,1.6,2.5);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFinLeptP",h1->GetName());
  tree1->Draw(var);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);

  h1->Draw("hist");

  c1->Print(outtag+"FinLeptP"+plottag+".png");
  c1->Print(outtag+"FinLeptP"+plottag+".root");

  delete h1;

  delete c1;

  Int_t nEntries = tree1->GetEntries();
  printf("Number of entries = %d \n", nEntries); 

  //Print tau values
  printf("tau = %f \n", tau);
}
