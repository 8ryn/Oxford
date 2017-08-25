class ND280Utils
{
 public:

 private:
  static const TVector3 * GetNuDirSim(const Float_t nu_NuParentDecPoint[], const Float_t vertex_truepos[], const Float_t nu_truedir[]);

  //== independent of NeutrinoUtils
  static void SetNeutrinoParentDecPointRec(TVector3 *vec){ vec->SetXYZ(-0.1388, -1.729, 34.55); }

  static const TVector3 * CalcNuDir(const TVector3 * nup0Global, const TVector3 * nup1Local);
  
  static const TVector3 * GetNuDirRec(const Float_t vertex_pos[]);
};


const TVector3 * ND280Utils::GetNuDirSim(const Float_t nu_NuParentDecPoint[], const Float_t vertex_truepos[], const Float_t nu_truedir[])
{
  //-------- nup0 
  //in m
  TVector3 nup0Global(nu_NuParentDecPoint);
  nup0Global *= 0.01; //default cm
  
  //shows a distribution with mean in m: ( -0.1388, -1.729, 34.55 )
  NeutrinoUtils::fNeutrinoParentDecPointSim = new TVector3(nup0Global);

  //------ nup1
  //in m
  TVector3 nup1Local(vertex_truepos);
  nup1Local *= 0.001; //default mm

  const TVector3 * dirsim = CalcNuDir(&nup0Global, &nup1Local);

  //test ->
  TVector3 nuDirTrue(nu_truedir);
  nuDirTrue *= 1./nuDirTrue.Mag();
  
  const Double_t ddir=1-dirsim->Dot(nuDirTrue);
  //pass 1e-14, fail at 1E-15
  if(ddir>1e-14){
    printf("test bad!! %e\n", ddir);
    dirsim->Print();
    nuDirTrue.Print();
    exit(1);
  }
  //test <-
  
  return dirsim;
}

const TVector3 * ND280Utils::CalcNuDir(const TVector3 * nup0Global, const TVector3 * nup1Local)
{
  if( nup0Global->Mag()<EPSILON || nup1Local->Mag()<EPSILON ){
    printf("ND280Utils::CalcNuDir bad input %f %f\n", nup0Global->Mag(), nup1Local->Mag()); exit(1);
    return 0x0;
  }

  //in m
  const Double_t nd280x= -3.221999;
  const Double_t nd280y= -8.14599;
  const Double_t nd280z= 280.10;
  const TVector3 nd280Global(nd280x, nd280y, nd280z);

  //in m 
  const TVector3 nup0Local = (*nup0Global) - nd280Global;

  TVector3 *nuDirCalc = new TVector3( (*nup1Local) - nup0Local );
  (*nuDirCalc) *= 1./nuDirCalc->Mag();

  return nuDirCalc;

  /*
//testing code
r NeutWaterAir_PXr3872_O01.root 

default->SetAlias("Dx","nu_NuParentDecPoint[0]*0.01")
default->SetAlias("Dy","nu_NuParentDecPoint[1]*0.01")
default->SetAlias("Dz","nu_NuParentDecPoint[2]*0.01")

default->SetAlias("Vx","vertex_pos[0]*0.001")
default->SetAlias("Vy","vertex_pos[1]*0.001")
default->SetAlias("Vz","vertex_pos[2]*0.001")

default->SetAlias("Px","nu_truedir[0]")
default->SetAlias("Py","nu_truedir[1]")
default->SetAlias("Pz","nu_truedir[2]")

default->SetAlias("Gx","-3.221999")
default->SetAlias("Gy","-8.14599")
default->SetAlias("Gz","+280.10")

default->Scan("Vx-(Dx-Gx):Vy-(Dy-Gy):Px:Py")
default->Scan("Vz-(Dz-Gz):Vy-(Dy-Gy):Pz:Py")
default->Draw("((Vx-(Dx-Gx))/(Vy-(Dy-Gy)))/(Px/Py)>>hxy(10001,0,2)")
default->Draw("((Vz-(Dz-Gz))/(Vy-(Dy-Gy)))/(Pz/Py)>>hzy(10001,0,2)")
default->Draw("((Vz-(Dz-Gz))/(Vx-(Dx-Gx)))/(Pz/Px)>>hzx(10001,0,2)")
   */
}


const TVector3 * ND280Utils::GetNuDirRec(const Float_t vertex_pos[])
{
  //=======================================
  //dirRaw001;
  //return (new TVector3(0,0,1));

  //======================================
  //dirSim
  //return GetNuDirSim(nu_NuParentDecPoint, vertex_truepos);

  //========================================
  //dir_p0Sim_p1Rec
  //TVector3 nup0Global(nu_NuParentDecPoint);
  //nup0Global *= 0.01;

  //========================================
  //dir_p0Rec_p1Rec

  //-------- nup0 
  //in m, mean of the distribution, 6B neutrino flux
  TVector3 nup0Global;
  SetNeutrinoParentDecPointRec(&nup0Global);
  
  //------ nup1
  //in m
  TVector3 nup1Local(vertex_pos);
  nup1Local *= 0.001; //default mm

  return CalcNuDir(&nup0Global, &nup1Local);
}

