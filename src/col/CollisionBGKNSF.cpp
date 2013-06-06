/*
 * CollisionBGKNSF.cpp - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#include "CollisionBGKNSF.h"

CollisionBGKNSF::CollisionBGKNSF() {
  force = NULL;
}

CollisionBGKNSF::~CollisionBGKNSF() {
  // TODO Auto-generated destructor stub
}

void CollisionBGKNSF::fEq(int k, int j, int i, double *eq) {
  rho = get0moment(k, j, i);
  get1momentEq(k, j, i, u);
  CollisionBGKNS::fEq(eq);
}

void CollisionBGKNSF::get1moment(int k, int j, int i, double *ret) {
  CollisionBGK::get1moment(k, j, i, ret);
  for (int l = 0; l < lm->DIM; l++) {
    ret[l] += force[l][k][j][i] * 0.5;
  }
}

void CollisionBGKNSF::get1momentEq(int k, int j, int i, double *ret) {
  CollisionBGK::get1moment(k, j, i, ret);
  for (int l = 0; l < lm->DIM; l++) {
    ret[l] += force[l][k][j][i] * wInv;
  }
}
