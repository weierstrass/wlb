/*
 * PeriodicTest.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include <iostream>
#include "../LBM.h"

int main() {
  cout << "Poiseuille flow..." << endl;
  int nx = 4;
  int ny = 4;

  double ****f = allocate4DArray(1, ny, nx, 9);

  int a = 0;
  for (int j = 0; j < ny; j++) {
    for (int i = 0; i < nx; i++) {
      for (int d = 0; d < 9; d++) {
        f[0][j][i][d] = a;
      }
      a++;
    }
  }

  StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
  Lattice2D *lm = new Lattice2D(ny, nx);

  sm->registerF(f);
  sm->registerN(lm->n);

  sm->init();
  print2DArray(f[0], ny, nx, 8);

  sm->stream();

  print2DArray(f[0], ny, nx, 8);

  return 0;
}
