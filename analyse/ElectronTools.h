#include "TLorentzVector.h"
#include "TVector3.h"

class ElectronTools{

 public:
  //Finds the vector component perpendicular to refdir
  static const TVector3 * GetVecT(const TLorentzVector * refdir, const TLorentzVector * vec){

    TVector3 vRotated(vec->Vect());
    vRotated.Rotate(TMath::Pi(), refdir->Vect());

    const TVector3 *vt = new TVector3( (vec->Vect() - vRotated)*0.5 );

    return vt;
  }
};
