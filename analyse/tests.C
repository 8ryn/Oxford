
void tests(){
  TString filelist = "/home/robertsb/summerInvestigation/analyse/genData/RFG_a/mergedRFG_a_out_TestParams1.root";

  TFile * fin = new TFile(filelist);
  TTree * tree = (TTree*) fin->Get("nRooTracker");

  tree->Draw("-StdHepP4[1][0]*StdHepP4[1][0]-StdHepP4[1][1]*StdHepP4[1][1]-StdHepP4[1][2]*StdHepP4[1][2]+StdHepP4[1][3]*StdHepP4[1][3]");
 
  
}

