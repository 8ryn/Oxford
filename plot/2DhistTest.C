#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TH1D.h" 
#include "TH2D.h"
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

//Normalizes a 2D hist (taken from Sujay who modified Xianguo's)
TH2D* normalHist(TH2D* hraw){
  TH2D* hh = (TH2D*)hraw->Clone(Form("%snor",hraw->GetName())); //Makes clone of input histo
  hh->Scale(0); //Clears clone
    
  //Finds bounds
  const Int_t x0 = hh->GetXaxis()->GetFirst();
  const Int_t x1 = hh->GetXaxis()->GetLast();
  const Int_t y0 = hh->GetYaxis()->GetFirst();
  const Int_t y1 = hh->GetYaxis()->GetLast();

  Double_t hmax = -1e10;
  Double_t hmin = 1e10;
  Double_t nent = 0;

  //Loops through slices and projects to Y 
  for(Int_t ix=x0; ix<=x1; ix++)
    {
      TH1D * sliceh = hraw->ProjectionY(Form("tmpnormalhist%sx%d",hh->GetName(), ix),ix,ix);
      const Double_t tot = sliceh->GetEntries();

      TH1D * pdfh=0x0;

      //Gets bin content of each bin along slice and finds max bin
      nent += tot;
      Double_t imax = -999;
      imax = sliceh->GetBinContent(sliceh->GetMaximumBin());
      
      //Rescales slice according to max bin content
      for(Int_t iy=y0; iy<=y1; iy++){
	  const Double_t cont = sliceh->GetBinContent(iy)/imax;
	  if(cont>0){
	      hh->SetBinContent(ix,iy,cont);
	      if(cont>hmax) hmax = cont;
	      if(cont<hmin) hmin = cont;
	    }
	}
        

      delete pdfh;
      delete sliceh;
    }

  hh->SetEntries(nent);
  hh->SetMinimum(0.99*hmin);
  hh->SetMaximum(1.1*hmax);

  return hh;
}

void rpaComp2(Int_t opt, Int_t energy){

  TString file1;
  TString file2;
  TString outtag;
  TString plottag;
  TString tempTitle; //Title to avoid confusion while comparing eWro and NuWro
  Double_t deltaPCut;

  if(opt==1){//NuWro

    file1 = Form("/home/robertsb/summerInvestigation/analyse/outdata/NuWroB/Output_tagNuWroRFG_b_NuMu%d.root",energy);
    file2 = Form("/home/robertsb/summerInvestigation/analyse/outdata/NuWroB/Output_tagNuWroRFG_b_NuMu%drpa1.root",energy);
    outtag = Form("outplot/rpaCompNuWro/%d/",energy);
    deltaPCut = 0.01;
    plottag = Form("NuWro%d", energy);
    tempTitle = "NuWro";
  }

  else if(opt==2){//eWro

    file1 = Form("/home/robertsb/summerInvestigation/analyse/outdata/eWro/Output_tageWroRFG_a_El%d.root",energy);
    file2 = Form("/home/robertsb/summerInvestigation/analyse/outdata/eWro/Output_tageWroRFG_a_El%drpa1.root",energy);
    outtag = Form("outplot/rpaCompeWro/%d/",energy);
    deltaPCut = 0.05;
    plottag = Form("eWro%d", energy);
    tempTitle = "eWro";
  }
  else exit(1);

  //Removes tempTitle, comment out of needed
  tempTitle = "";

  TFile * fin1 = new TFile(file1);
  TTree * tree1 = (TTree*) fin1->Get("tree");

  TFile * fin2 = new TFile(file2);
  TTree * tree2 = (TTree*) fin2->Get("tree");

  TH1D * h1 = 0x0;
  TH1D * h2 = 0x0;
  TH2D * h3 = 0x0;

  TLegend * lg = 0x0;

  TString var;
  TString cut;

  gStyle->SetOptStat(0);
  gStyle->SetPalette(56);

  TCanvas * c1 = new TCanvas("c1","",990,660);
  c1->SetRightMargin(0.03);
  c1->SetTopMargin(0.08);         
  c1->SetLeftMargin(0.12);
  c1->SetBottomMargin(0.15);

  //Alphat, muonPt 2D hist ////////////////////

  //rpa=0
  h3 = new TH2D("alphPt","RPA=0;p^{#mu}_{T} (GeV/c);#delta#alpha_{T} /rads",80,0,0.65,50,0,TMath::Pi());
  var=Form("%s>>%s", "fAlphat:fFinLeptPt", h3->GetName());
  cut=Form("fFullDeltaP<%f", deltaPCut);
  tree1->Draw(var,cut);
  h3 = normalHist(h3);
  h3->Draw("colz");

  c1->Print(outtag+"alphavPtrpa0"+plottag+".png");
  c1->Print(outtag+"alphavPtrpa0"+plottag+".root");

  delete h3;
  
  //rpa=1
  h3 = new TH2D("alphPt","RPA=1;p^{#mu}_{T} (GeV/c);#delta#alpha_{T} /rads",80,0,0.65,50,0,TMath::Pi());
  var=Form("%s>>%s", "fAlphat:fFinLeptPt", h3->GetName());
  cut=Form("fFullDeltaP<%f", deltaPCut);
  tree2->Draw(var,cut);
  h3 = normalHist(h3);
  h3->Draw("colz");

  c1->Print(outtag+"alphavPtrpa1"+plottag+".png");
  c1->Print(outtag+"alphavPtrpa1"+plottag+".root");

  delete h3;
  
  delete c1;
}
