#include "TestUtils.h"
#include <iostream>

using namespace std;

void IssueCheck(){

  TestUtils::fNum = 346;
  cout << "fNum = " << TestUtils::fNum << endl;

  TestUtils::SetParticlePDG(54,123);
  cout<< "PDG = " << TestUtils::GetParticlePDG(54) << endl;
}
