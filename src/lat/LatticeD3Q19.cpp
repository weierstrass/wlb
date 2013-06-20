/*
 * LatticeD3Q19.cpp
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "LatticeD3Q19.h"

#define W0 0.33333333333333333
#define W1 0.05555555555555555
#define W2 0.02777777777777777

//int *oppDirs = { 0, 3, 4, 1, 2, 7, 8, 5, 6 };

LatticeD3Q19::LatticeD3Q19(int nx, int ny, int nz) {
  cout << "Creating D3Q19 lattice... ";
  int ex[] = { 0, 1, -1, 0, 0, 0, 0, 1, 1, 1, 1, -1, -1, -1, -1, 0, 0, 0, 0 };
  int ey[] = { 0, 0, 0, 1, -1, 0, 0, 1, -1, 0, 0, 1, -1, 0, 0, 1, 1, -1, -1 };
  int ez[] = { 0, 0, 0, 0, 0, 1, -1, 0, 0, 1, -1, 0, 0, 1, -1, 1, -1, 1, -1 };

  double Wt[] = { W0, W1, W1, W1, W1, W1, W1, W2, W2, W2, W2, W2, W2, W2, W2,
      W2, W2, W2, W2 };
  n.x = nx;
  n.y = ny;
  n.z = nz;
  UDIRS = 19;
  DIM = 3;

  W = new double[UDIRS];

  e = new int*[DIM];
  e[0] = new int[UDIRS];
  e[1] = new int[UDIRS];
  e[2] = new int[UDIRS];

  for (int d = 0; d < UDIRS; d++) {
    e[0][d] = ex[d];
    e[1][d] = ey[d];
    e[2][d] = ez[d];
    W[d] = Wt[d];
  }

  oppDirs = new int[UDIRS];
  fillOppdirs();

  cout << "done." << endl;

}

LatticeD3Q19::~LatticeD3Q19() {
  // TODO Auto-generated destructor stub
}

