/*
 * AppLPMTest.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include <iostream>
#include "../LBM.h"

using namespace std;

int main() {
  cout << "LPM test..." << endl;

  int nx = 3;
  int ny = 512;
  int tMax = 5000;
  double l0 = 1e-5 / (ny - 1);
  double V0 = -200e-3;

  CollisionD2Q9LPMWang1to1 *cm = new CollisionD2Q9LPMWang1to1();
  UnitHandlerLPM *uh = new UnitHandlerLPM();
  StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
  LatticeModel *lm = new Lattice2D(nx, ny);

  cm->setW(0.5);
  cm->setC(1.0);
  cm->setUnitHandler(uh);
  uh->setCharLength(l0);
  uh->setCharVoltage(V0);
  uh->setTimeStep(1.0);

  LBM *lbm = new LBM(lm, cm, sm);

  /* Boundaries */
  DirichletLPMNodes<CollisionD2Q9LPMWang1to1> *bds = new DirichletLPMNodes<
      CollisionD2Q9LPMWang1to1>();
  bds->setCollisionModel(cm);
  for (int i = 0; i < nx; i++) {
    bds->addNode(i, 0, 1.0);
    bds->addNode(i, ny - 1, 1.0);
  }
  lbm->addBoundaryNodes(bds);

  /* Initialize solver */
  lbm->init();

  /* Main loop */
  for (int t = 0; t < tMax; t++) {
    cout << t << endl;
    lbm->collideAndStream();
    //lbm->handleBoundaries();
  }

  //lbm->calcMacroscopicVars();
  cm->dataToFile();
  cout << "done LPM." << endl;

  return 0;
}
