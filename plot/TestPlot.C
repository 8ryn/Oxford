void TestPlot(){
  TString filelist = "/home/robertsb/summerInvestigation/analyse/outdata/Ana/Output_tageWroRFG_a_El3000.root";

  TFile * fin = new TFile(filelist);
  TTree * tree = (TTree*) fin->Get("tree");

  tree->Draw("fFullDeltaP", "fFullDeltaP<0.1");
 
  
}

