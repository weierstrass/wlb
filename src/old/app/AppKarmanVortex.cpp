/*
 * AppPoiseuilleForce.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include <iostream>
#include "../LBM.h"
#include <math.h>

using namespace std;

int main() {

  omp_set_num_threads(1);

  int nx = 500, ny = 150, tMax = 50000, tMod = 100;
  double w = 1.89;
  double c = 1.0;

  double **fx = allocate2DArray(ny, nx);
  double **fy = allocate2DArray(ny, nx);

  cout << "Karman vortex street..." << endl;
  LatticeModel *lm = new Lattice2D(nx, ny);
  //StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
  StreamD2Q9 *sm = new StreamD2Q9();
  CollisionD2Q9BGKNSF *cm = new CollisionD2Q9BGKNSF();

  cm->setW(w);
  cm->setC(c);

  LBM *lbm = new LBM(lm, cm, sm);

  /* Set boundary conditions*/
  BounceBackNodes<CollisionD2Q9BGKNSF> *bbns = new BounceBackNodes<
      CollisionD2Q9BGKNSF>();
  bbns->setCollisionModel(cm);
  for (int i = 0; i < nx; i++) {
    bbns->addNode(i, 0, 0);
    bbns->addNode(i, ny - 1, 0);
  }

  // add cylindrical obstacle
  int xc = nx / 4, yc = ny / 2;
  double r = ny / 15.0;
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      if (sqrt((double) ((i - xc) * (i - xc) + (j - yc) * (j - yc))) < r) {
        bbns->addNode(i, j, 0);
      }
    }
  }

  lbm->addBoundaryNodes(bbns);

  /* Set force */
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      fx[j][i] = 0.000005;
      fy[j][i] = 0.0;
    }
  }
  cm->setForce(fx, fy);

  /* Initialize solver */
  lbm->init();

  stringstream ss;
  string base = "vis_scripts/bench_karman_vortex/";

  /* Main loop */
  for (int t = 0; t < tMax; t++) {
    cout << t << endl;
    lbm->collideAndStream();

    // write result to file
    if (t % tMod == 0) {
      ss.str("");
      ss << base << "KV";
      ss << t / tMod << "/";
      createDirectory(ss.str());
      cm->dataToFile(ss.str());
    }

//		if(t == 3500){
//			for(int i = 0; i < nx; i++){
//				for(int j = 0; j < ny; j++){
//				    fx[j][i] = 0.0;
//				    fy[j][i] = 0.0;
//				}
//			}
//
//		}
  }

  //cm->dataToFile("vis_scripts/bench_karman_vortex/");
  cout << "done cyl." << endl;

  return 0;
}
