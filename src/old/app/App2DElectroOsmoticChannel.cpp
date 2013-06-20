/*
 * App2DElectroOsmoticChannel.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include <iostream>
#include <string.h>
#include "../LBM.h"

using namespace std;

void calcForce(CollisionD2Q9LPMChai1to1 *lpmcm, UnitHandlerLPM *lpmuh,
    UnitHandlerNS *lbmuh, Lattice2D *lm, double **fx, double **fy, double **ux,
    double **uy, double **psi, double lambda, double d, double dPdx);

int main() {
  cout << "electro-viscous effect benchmark." << endl;

  string path = "bench_elo_70/";

  int nx = 3;
  int ny = 101;
  int tMax = 10000;
  double t2Max = 20000;

  double d = 1e-5; //channel height [m]
  double T = 273; //temperature [K]
  double cinf = 1e-4; //ion concentration at inf. [Mol]
  double epsilon = 80 * PHYS_EPS0; //absolute permittivity [F/m]
  double dPdx = 1e6; //magnitude of pressure gradient [Pa/m]
  double lambda = 1.2639e-7; //conductivity [S/m]

  double l0 = d / (ny - 1);
  double V0 = -20e-3;
  double u0 = 5e0;
  double rho0 = 1000;

  CollisionD2Q9LPMChai1to1 *lpmcm = new CollisionD2Q9LPMChai1to1();
  StreamD2Q9Periodic *lpmsm = new StreamD2Q9Periodic();
  LatticeModel *lpmlm = new Lattice2D(nx, ny);
  UnitHandlerLPM *lpmuh = new UnitHandlerLPM();
  UnitHandlerNS *lbmuh = new UnitHandlerNS();

  lpmuh->setCharLength(l0);
  lpmuh->setCharVoltage(V0);

  lbmuh->setCharLength(l0);
  lbmuh->setCharVelocity(u0);
  lbmuh->setcharDensity(rho0);

  lpmcm->setUnitHandler(lpmuh);
  lpmcm->setW(1.0);
  lpmcm->setC(1.0);
  lpmcm->setTemperature(T);
  lpmcm->setInfConcentration(cinf);
  lpmcm->setPermittivity(epsilon);

  LBM *lpm = new LBM(lpmlm, lpmcm, lpmsm);

  /* Boundaries */
  HeZouLPMChaiNodes *bds = new HeZouLPMChaiNodes();
  bds->setCollisionModel(lpmcm);
  for (int i = 0; i < nx; i++) {
    bds->addNode(i, 0, 0, 1.0 / 1.8);
    bds->addNode(i, ny - 1, 0, 1.0 / 1.8);
  }
  lpm->addBoundaryNodes(bds);

  /* Initialize solver */
  lpm->init();
  bds->init();

  /* Main loop */
  for (int t = 0; t < tMax; t++) {
    cout << t << endl;
    lpm->collideAndStream();
  }

  lpmcm->dataToFile();
  cout << "done LPM." << endl;

  /* Use determined potential => charge density
   * to calculate flow */

  CollisionD2Q9BGKShanChenForce *cm = new CollisionD2Q9BGKShanChenForce();
  StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
  Lattice2D *lm = new Lattice2D(nx, ny);

  LBM *lbm = new LBM(lm, cm, sm);

  double w = 0.5; //determines viscosity for flow
  double c = 1.0;

  cm->setC(c);
  cm->setW(w);

  /* Set boundary conditions for flow */
  BounceBackNodes<CollisionD2Q9BGKShanChenForce> *bbns = new BounceBackNodes<
      CollisionD2Q9BGKShanChenForce>();
  bbns->setCollisionModel(cm);
  for (int i = 0; i < nx; i++) {
    bbns->addNode(i, 0, 0);
    bbns->addNode(i, ny - 1, 0);
  }
  lbm->addBoundaryNodes(bbns);

  lbm->init();
  cout << "done init" << endl;

  double **psi = lpmcm->getPotential();
  double **fx = allocate2DArray(ny, nx);
  double **fy = allocate2DArray(ny, nx);
  double ***uu;
  cm->setForce(fx, fy);

  /* Main loop */
  for (int t = 0; t < t2Max; t++) {
    cout << t << endl;

    //calculate force...
    uu = cm->getVelocityField();
    calcForce(lpmcm, lpmuh, lbmuh, lm, fx, fy, uu[X], uu[Y], psi, lambda, d,
        dPdx);

    lbm->collideAndStream();
  }

  cm->dataToFile(path);
  cout << "done." << endl;

  return 0;
}

void calcForce(CollisionD2Q9LPMChai1to1 *lpmcm, UnitHandlerLPM *lpmuh,
    UnitHandlerNS *lbmuh, Lattice2D *lm, double **fx, double **fy, double **ux,
    double **uy, double **psi, double lambda, double d, double dPdx) {
  double eps = lpmcm->getPermittivity();
  double l0 = lpmuh->getCharLength();
  double V0 = lpmuh->getCharVoltage();
  double u0 = lbmuh->getCharVelocity();
  double rho0 = lbmuh->getCharDensity();

  dPdx *= l0 / (rho0 * u0 * u0);
  cout << "dPdx: " << dPdx << endl;
  double f_temp;

  for (int i = 0; i < lm->n.x; i++) {
    f_temp = 0;
    for (int j = 0; j < lm->n.y; j++) {
      f_temp += ux[j][i] * u0 * lpmcm->getSIChargeDensity(psi[j][i]) * l0;
    }

    f_temp *= -1.0 / (lambda * d); //divide by conductivity and channel height
    cout << "SI force: " << f_temp << endl;
    f_temp *= l0 / (rho0 * u0 * u0); //rescale to lattice NS lattice units
    cout << "Fx: " << f_temp << endl;

    //f_temp = 0;

    for (int j = 0; j < lm->n.y; j++) {
      fx[j][i] = f_temp * lpmcm->getSIChargeDensity(psi[j][i]) + dPdx;
      fy[j][i] = 0.0; // in this example only force in x dir.
    }
  }
}
