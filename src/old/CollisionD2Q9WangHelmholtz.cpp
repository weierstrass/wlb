/*
 * CollisionD2Q9WangHelmholtz.cpp
 * Andreas B�lling, 2012
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9WangHelmholtz.h"

CollisionD2Q9WangHelmholtz::CollisionD2Q9WangHelmholtz() {
  // TODO Auto-generated constructor stub

}

CollisionD2Q9WangHelmholtz::~CollisionD2Q9WangHelmholtz() {
  // TODO Auto-generated destructor stub
}

double CollisionD2Q9WangHelmholtz::g_rhs(int i, int j) {
  //cout<<"YESSSssssssssssssssssS"<<endl;
  UnitHandlerLPM *uh = dynamic_cast<UnitHandlerLPM*>(unitHandler);
  return -lambda * lambda * psi[j][i] * uh->getTimeStep();
}

