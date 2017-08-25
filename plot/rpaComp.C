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

void rpaComp(Int_t opt, Int_t energy, Double_t protCut = 0.0){

  TString file1;
  TString file2;
  TString outtag;
  TString plottag;
  TString tempTitle; //Title to avoid confusion while comparing eWro and NuWro
  Double_t deltaPCut;
  const Double_t Eb = 0.032;
  TString fsi;
  TString nofsi;
  TString basecut;

  if(opt==1){//NuWro

    file1 = Form("/home/robertsb/summerInvestigation/analyse/outdata/NuWroB/Output_tagNuWroRFG_b_NuMu%d.root",energy);
    file2 = Form("/home/robertsb/summerInvestigation/analyse/outdata/NuWroB/Output_tagNuWroRFG_b_NuMu%drpa1.root",energy);
    outtag = protCut == 0 ? Form("outplot/rpaCompNuWro/%d/",energy) :  Form("outplot/rpaCompNuWro/%dcut%d/",energy,(Int_t)(protCut*1000));
    deltaPCut = 0.01;
    plottag = protCut == 0 ? Form("NuWro%d", energy) :  Form("NuWro%dCut%d", energy, (Int_t)(protCut*1000));
    tempTitle = "NuWro";
  }

  else if(opt==2){//eWro

    file1 = Form("/home/robertsb/summerInvestigation/analyse/outdata/eWro/Output_tageWroRFG_a_El%d.root",energy);
    file2 = Form("/home/robertsb/summerInvestigation/analyse/outdata/eWro/Output_tageWroRFG_a_El%drpa1.root",energy);
    outtag = protCut == 0 ? Form("outplot/rpaCompeWro/%d/",energy) :  Form("outplot/rpaCompeWro/%dcut%d/",energy,(Int_t)(protCut*1000));
    deltaPCut = 0.05;
    plottag = protCut == 0 ? Form("eWro%d", energy) :  Form("eWro%dCut%d", energy, (Int_t)(protCut*1000));
    tempTitle = "eWro";
  }
  else exit(1);

  if(protCut==0){  
    fsi = Form("fFullDeltaP>%f",deltaPCut); 
    nofsi = Form("fFullDeltaP<%f",deltaPCut);
    basecut = "";
  }
  else {
    fsi = Form("fFullDeltaP>%f && fFinProtP>%f",deltaPCut, protCut);
    nofsi = Form("fFullDeltaP<%f && fFinProtP>%f ",deltaPCut, protCut); 
    basecut = Form("fFinProtP>%f", protCut);
  }

  //Removes tempTitle, comment out of needed
  tempTitle = "";

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

  TCanvas * c1 = new TCanvas("c1","",990,660);
  c1->SetRightMargin(0.03);
  c1->SetTopMargin(0.08);         
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.15);


  //deltaP<.6 /////////////////////////

  lg = new TLegend(0.75, 0.20, 0.9, 0.35);
  reset(lg);

  h1 = new TH1D("rpa0",";#DeltaP (GeV/c);p.d.f",100,0,0.6);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFullDeltaP",h1->GetName());
  cut= fsi;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,0.6);
  var=Form("(%s)>>%s","fFullDeltaP",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaP<06"+plottag+".png");
  c1->Print(outtag+"deltaP<06"+plottag+".root");

  delete h1;
  delete h2;

  //deltaP ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#DeltaP (GeV/c);p.d.f",100,0,energy/1000 +0.5);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFullDeltaP",h1->GetName());
  cut= fsi;;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,energy/1000 +0.5);
  var=Form("(%s)>>%s","fFullDeltaP",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaP"+plottag+".png");
  c1->Print(outtag+"deltaP"+plottag+".root");

  Int_t intentriesrpa0 = h1->GetEntries();
  Int_t intentriesrpa1 = h2->GetEntries();

  delete h1;
  delete h2;

  //deltaP full ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#Deltap (GeV/c);p.d.f",100,0,energy/1000 +0.5);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFullDeltaP",h1->GetName());
  cut = basecut;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,energy/1000 +0.5);
  var=Form("(%s)>>%s","fFullDeltaP",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaPFull"+plottag+".png");
  c1->Print(outtag+"deltaPFull"+plottag+".root");

  const Double_t taurpa0 = intentriesrpa0/h1->GetEntries();
  const Double_t taurpa1 = intentriesrpa1/h2->GetEntries();

  delete h1;
  delete h2;

  //DeltaP transverse component ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#Deltap_{T} (GeV/c);p.d.f",100,0,energy/1000 +0.5);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFullDeltaPt",h1->GetName());
  cut= fsi;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,energy/1000 +0.5);
  var=Form("(%s)>>%s","fFullDeltaPt",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"DeltaPFullT"+plottag+".png");
  c1->Print(outtag+"DeltaPFullT"+plottag+".root");

  delete h1;
  delete h2;

  //DeltaP longitudinal component ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#Deltap_{L} (GeV/c);p.d.f",100,0,energy/1000 +0.5);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFullDeltaPl",h1->GetName());
  cut= fsi;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,energy/1000 +0.5);
  var=Form("(%s)>>%s","fFullDeltaPl",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"DeltaPFullL"+plottag+".png");
  c1->Print(outtag+"DeltaPFullL"+plottag+".root");

  delete h1;
  delete h2;

//deltaE full ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  if(opt==1) h1 = new TH1D("rpa0",";#DeltaE  /GeV;p.d.f",100,0,0.6);
  else h1 = new TH1D("rpa0",";#DeltaE  /GeV;p.d.f",100,0,0.2);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s-%f","fFullDeltaE",h1->GetName(),Eb);
  cut= basecut;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  if(opt==1) h2 = new TH1D("rpa1","",100,0, 0.6);
  else  h2 = new TH1D("rpa1","",100,0, 0.2);
  var=Form("(%s)>>%s-%f","fFullDeltaE",h2->GetName(),Eb);
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaEFull"+plottag+".png");
  c1->Print(outtag+"deltaEFull"+plottag+".root");

  delete h1;
  delete h2;

  //deltaE only FSI ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  if(opt==1) h1 = new TH1D("rpa0",";#DeltaE only FSI  /GeV;p.d.f",100,0,0.8);
  else h1 = new TH1D("rpa0",";#DeltaE  /GeV;p.d.f",100,0,0.3);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s-%f","fFullDeltaE",h1->GetName(),Eb);
  cut= fsi;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  if(opt==1) h2 = new TH1D("rpa1","",100,0, 0.6);
  else  h2 = new TH1D("rpa1","",100,0, 0.2);
  var=Form("(%s)>>%s-%f","fFullDeltaE",h2->GetName(),Eb);
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaEonlyFSI"+plottag+".png");
  c1->Print(outtag+"deltaEonlyFSI"+plottag+".root");

  delete h1;
  delete h2;

  //deltaPt<0.6 ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#deltaP_{T} (GeV/c);p.d.f",100,0,0.6);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fDeltaPt",h1->GetName());
  cut = basecut;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,0.6);
  var=Form("(%s)>>%s","fDeltaPt",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaPt<06"+plottag+".png");
  c1->Print(outtag+"deltaPt<06"+plottag+".root");

  delete h1;
  delete h2;

  //deltaPt<0.3 ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#deltaP_{T} (GeV/c);p.d.f",100,0,0.3);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fDeltaPt",h1->GetName());
  cut = basecut;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,0.3);
  var=Form("(%s)>>%s","fDeltaPt",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaPt<03"+plottag+".png");
  c1->Print(outtag+"deltaPt<03"+plottag+".root");

  delete h1;
  delete h2;

  //deltaPt ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#deltaP_{T} (GeV/c);p.d.f",100,0,1.6);
  var=Form("(%s)>>%s","fDeltaPt",h1->GetName());
  cut = basecut;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,1.6);
  var=Form("(%s)>>%s","fDeltaPt",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaPt"+plottag+".png");
  c1->Print(outtag+"deltaPt"+plottag+".root");

  delete h1;
  delete h2;

  //deltaPt no FSI ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#deltaP_{T} no FSI (GeV/c);p.d.f",100,0,0.6);
  var=Form("(%s)>>%s","fDeltaPt",h1->GetName());
  cut= nofsi;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,0.6);
  var=Form("(%s)>>%s","fDeltaPt",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaPtnoFSI"+plottag+".png");
  c1->Print(outtag+"deltaPtnoFSI"+plottag+".root");

  delete h1;
  delete h2;

 //deltaPt only FSI ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#deltaP_{T} only FSI (GeV/c);p.d.f",100,0,1);
  var=Form("(%s)>>%s","fDeltaPt",h1->GetName());
  cut= fsi;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,1);
  var=Form("(%s)>>%s","fDeltaPt",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"deltaPtonlyFSI"+plottag+".png");
  c1->Print(outtag+"deltaPtonlyFSI"+plottag+".root");

  delete h1;
  delete h2;

  //alphat ///////////////////////////
 
  lg = new TLegend(0.75, 0.3, 0.9, 0.43);
  reset(lg);

  h1 = new TH1D("rpa0",";#delta#alpha_{T} /rads;p.d.f",100,0,TMath::Pi());
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fAlphat",h1->GetName());
  cut = basecut;
  tree1->Draw(var, cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetMinimum(0);
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,TMath::Pi());
  var=Form("(%s)>>%s","fAlphat",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetMinimum(0);
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"Alphat"+plottag+".png");
  c1->Print(outtag+"Alphat"+plottag+".root");

  delete h1;
  delete h2;

  //alphat no FSI///////////////////////////
 
  lg = new TLegend(0.75, 0.3, 0.9, 0.43);
  reset(lg);

  h1 = new TH1D("rpa0",";#delta#alpha_{T} no FSI /rads;p.d.f",100,0,TMath::Pi());
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fAlphat",h1->GetName());
  cut=nofsi; 
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetMinimum(0);
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1",";#delta#alpha_{T} no FSI /rads;p.d.f",100,0,TMath::Pi());
  var=Form("(%s)>>%s","fAlphat",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetMinimum(0);
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h2->Draw("hist");
  h1->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"AlphatnoFSI"+plottag+".png");
  c1->Print(outtag+"AlphatnoFSI"+plottag+".root");

  delete h1;
  delete h2;

  //alphat only FSI///////////////////////////
 
  lg = new TLegend(0.2, 0.75, 0.4, 0.88);
  reset(lg);

  h1 = new TH1D("rpa0",";#delta#alpha_{T} only FSI /rads;p.d.f",100,0,TMath::Pi());
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fAlphat",h1->GetName());
  cut=fsi; 
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetMinimum(0);
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,TMath::Pi());
  var=Form("(%s)>>%s","fAlphat",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetMinimum(0);
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"AlphatonlyFSI"+plottag+".png");
  c1->Print(outtag+"AlphatonlyFSI"+plottag+".root");

  delete h1;
  delete h2;

  //phit ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#delta#phi_{T} /rads;p.d.f",100,0,2.5);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fPhit",h1->GetName());
  cut = basecut;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1",";#delta#phi_{T} /rads;p.d.f",100,0,2.5);
  var=Form("(%s)>>%s","fPhit",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h2->Draw("hist");
  h1->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"Phit"+plottag+".png");
  c1->Print(outtag+"Phit"+plottag+".root");

  delete h1;
  delete h2;

  //phit <2 ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#delta#phi_{T} /rads;p.d.f",100,0,2);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fPhit",h1->GetName());
  cut = basecut;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1",";#delta#phi_{T} /rads;p.d.f",100,0,2);
  var=Form("(%s)>>%s","fPhit",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h2->Draw("hist");
  h1->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"Phit<2"+plottag+".png");
  c1->Print(outtag+"Phit<2"+plottag+".root");

  delete h1;
  delete h2;

  //phit no FSI ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#delta#phi_{T} no FSI /rads;p.d.f",100,0,2.0);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fPhit",h1->GetName());
  cut=nofsi; 
  tree1->Draw(var, cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1",";#delta#phi_{T} no FSI /rads;p.d.f",100,0,2.0);
  var=Form("(%s)>>%s","fPhit",h2->GetName());
  tree2->Draw(var, cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h2->Draw("hist");
  h1->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"PhitnoFSI"+plottag+".png");
  c1->Print(outtag+"PhitnoFSI"+plottag+".root");

  delete h1;
  delete h2;

  //phit only FSI ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";#delta#phi_{T} only FSI /rads;p.d.f",100,0,2.0);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fPhit",h1->GetName());
  cut=fsi; 
  tree1->Draw(var, cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1",";#delta#phi_{T} only FSI /rads;p.d.f",100,0,2.0);
  var=Form("(%s)>>%s","fPhit",h2->GetName());
  tree2->Draw(var, cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  h2->SetMinimum(0);
  lg->AddEntry(h2, "rpa1", "l");


  h2->Draw("hist");
  h1->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"PhitonlyFSI"+plottag+".png");
  c1->Print(outtag+"PhitonlyFSI"+plottag+".root");

  delete h1;
  delete h2;

  //Q2 ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";Q^{2} (GeV/c)^{2} ;p.d.f",100,0,1.6);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fQ2",h1->GetName());
  cut = basecut;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1",";Q^{2} (GeV/c)^{2};p.d.f",100,0,1.6);
  var=Form("(%s)>>%s","fQ2",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  h2->SetMinimum(0);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"Q2"+plottag+".png");
  c1->Print(outtag+"Q2"+plottag+".root");

  delete h1;
  delete h2;

  //initial nucleon momentum ///////////////////////////
 
  lg = new TLegend(0.65, 0.75, 0.8, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";p^{N} (GeV/c);p.d.f",100,0,0.24);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fIniNucP",h1->GetName());
  cut = basecut;
  tree1->Draw(var, cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,0,0.24);
  var=Form("(%s)>>%s","fIniNucP",h2->GetName());
  tree2->Draw(var, cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"IniNucP"+plottag+".png");
  c1->Print(outtag+"IniNucP"+plottag+".root");

  delete h1;
  delete h2;

  //final proton momentum ///////////////////////////
 
  lg = new TLegend(0.65, 0.75, 0.8, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";p^{P} (GeV/c);p.d.f",100,protCut,energy/1000 +0.5);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFinProtP",h1->GetName());
  cut = basecut;
  tree1->Draw(var, cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1","",100,protCut,energy/1000+0.5);
  var=Form("(%s)>>%s","fFinProtP",h2->GetName());
  tree2->Draw(var, cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"FinProtP"+plottag+".png");
  c1->Print(outtag+"FinProtP"+plottag+".root");

  delete h1;
  delete h2;

  //final proton transverse momentum ///////////////////////////
 
  lg = new TLegend(0.75, 0.75, 0.9, 0.9);
  reset(lg);

  h1 = new TH1D("rpa0",";p_{T}^{P} (GeV/c);p.d.f",100,0,energy/1000);
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFinProtPt",h1->GetName());
  cut = basecut;
  tree1->Draw(var, cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  h2 = new TH1D("rpa1",";p_{T}^{P} (GeV/c);p.d.f",100,0,energy/1000);
  var=Form("(%s)>>%s","fFinProtPt",h2->GetName());
  tree2->Draw(var, cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h2->Draw("hist");
  h1->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"FinProtPt"+plottag+".png");
  c1->Print(outtag+"FinProtPt"+plottag+".root");

  delete h1;
  delete h2;

  //final lepton momentum ///////////////////////////
 
  lg = new TLegend(0.20, 0.75, 0.40, 0.9);
  reset(lg);

  if(opt==1) h1 = new TH1D("rpa0",";p^{#mu} (GeV/c);p.d.f",100,0,energy/1000);
  else if(opt==2){
    if(energy==1000){
      h1 = new TH1D("rpa0",";p^{e} (GeV/c);p.d.f",100,0.7,1.0);
    }
    else {
      h1 = new TH1D("rpa0",";p^{e} (GeV/c);p.d.f",100,1.6,2.5);
    }
  }
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFinLeptP",h1->GetName());
  cut = basecut;
  tree1->Draw(var,cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  if(opt==1) h2 = new TH1D("rpa1","",100,0,energy/1000);
  else if(opt==2){ 
    if(energy==1000){
      h2 = new TH1D("rpa1","",100, 0.7,1.0);
    }
    else{
      h2 = new TH1D("rpa1","",100, 1.6,2.5);
    }
  }
  var=Form("(%s)>>%s","fFinLeptP",h2->GetName());
  tree2->Draw(var,cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"FinLeptP"+plottag+".png");
  c1->Print(outtag+"FinLeptP"+plottag+".root");

  delete h1;
  delete h2;

//final lepton transverse momentum ///////////////////////////
 
  lg = new TLegend(0.20, 0.75, 0.40, 0.9);
  reset(lg);

  if(opt==1) h1 = new TH1D("rpa0",";p_{T}^{#mu} (GeV/c);p.d.f",100,0,0.7*energy/1000);
  else if(opt==2){
    if(energy==1000){
      h1 = new TH1D("rpa0",";p_{T}^{e} (GeV/c);p.d.f",100,0.7,1.0);
    }
    else {
      h1 = new TH1D("rpa0",";p_{T}^{e} (GeV/c);p.d.f",100,1.6,2.5);
    }
  }
  h1->SetTitle(tempTitle);
  var=Form("(%s)>>%s","fFinLeptPt",h1->GetName());
  cut = basecut;
  tree1->Draw(var, cut);
  h1->Scale(1./h1->Integral(0,h1->GetNbinsX()+1)/h1->GetBinWidth(1));
  h1->SetLineColor(1);
  lg->AddEntry(h1, "rpa0", "l");

  if(opt==1) h2 = new TH1D("rpa1","",100,0,0.7*energy/1000);
  else if(opt==2){ 
    if(energy==1000){
      h2 = new TH1D("rpa1","",100, 0.7,1.0);
    }
    else{
      h2 = new TH1D("rpa1","",100, 1.6,2.5);
    }
  }
  var=Form("(%s)>>%s","fFinLeptPt",h2->GetName());
  tree2->Draw(var, cut);
  h2->Scale(1./h2->Integral(0,h2->GetNbinsX()+1)/h2->GetBinWidth(1));
  h2->SetLineColor(2);
  lg->AddEntry(h2, "rpa1", "l");


  h1->Draw("hist");
  h2->Draw("same hist");
  lg->Draw();

  c1->Print(outtag+"FinLeptPt"+plottag+".png");
  c1->Print(outtag+"FinLeptPt"+plottag+".root");

  delete h1;
  delete h2;

  delete c1;

  Int_t tree1entries = tree1->GetEntries();
  Int_t tree2entries = tree2->GetEntries();

  //Print number of entries in each file
  printf("rpa1 entries = %d \n", tree1entries);
  printf("rpa2 entries = %d \n", tree2entries);

  //Print tau values
  printf("rpa0 tau = %f \n", taurpa0);
  printf("rpa1 tau= %f \n", taurpa1);
}
