/*
 * CollisionD2Q9BGKNS.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9BGKNS.h"

CollisionD2Q9BGKNS::CollisionD2Q9BGKNS() {
  cout << "allocating u memory" << endl;
  u = new double[2];
  double c2inv = 1.0 / c * c;
  c1 = 3.0 * c2inv;
  c2 = 4.5 * (c2inv * c2inv);
  c3 = -1.5 * c2inv;
}

CollisionD2Q9BGKNS::~CollisionD2Q9BGKNS() {
  delete[] u;
}

void CollisionD2Q9BGKNS::fEq(int i, int j, double *eq) {
  double rho = get0moment(i, j);
  get1moment(i, j, u);
  fEq(rho, u, eq);
}

void CollisionD2Q9BGKNS::getU(double **ux, double **uy) {
  double rho;
  for (int j = 0; j < lm->n.y; j++) {
    for (int i = 0; i < lm->n.x; i++) {
      get1moment(i, j, u);
      rho = get0moment(i, j);
      ux[j][i] = u[X] / rho;
      uy[j][i] = u[Y] / rho;
    }
  }
}

void CollisionD2Q9BGKNS::init(double **rhoI, double **uxI, double **uyI) {
  double *uTemp = new double[2];
  double *eq = new double[lm->UDIRS];

  for (int j = 0; j < lm->n.y; j++) {
    for (int i = 0; i < lm->n.x; i++) {

      uTemp[X] = uxI[j][i];
      uTemp[Y] = uyI[j][i];
      fEq(rhoI[j][i], uTemp, eq);

      for (int d = 0; d < lm->UDIRS; d++) {
        f[0][j][i][d] = eq[d];
      }
    }
  }

  //clean up
  delete[] uTemp;
  delete[] eq;
}

void CollisionD2Q9BGKNS::fEq(double rho, double *u, double *eq) {
  double rho_inv = 1 / rho;
  u[X] *= rho_inv;
  u[Y] *= rho_inv;

  double c2inv = 1.0 / c * c;
  double u2 = u[X] * u[X] + u[Y] * u[Y];

  for (int d = 0; d < lm->UDIRS; d++) {
    double cu = lm->e[0][d] * u[X] + lm->e[1][d] * u[Y];

    // eq[d] = W[d]*rho*(1 + 3.0*c2inv*(cu) \
                + 4.5*(c2inv*c2inv)*(cu*cu) \
                - 1.5*c2inv*u2);
    // cout<<eq[d] <<" == ";
    eq[d] = rho * W[d] * (1 + c1 * cu + c2 * cu * cu + c3 * u2);
    //cout<<eq[d]<<"?"<<endl;
  }
}
