/*
 * LatticeModel.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Abstract mother class for the lattice models.
 */

#include "LatticeModel.h"

LatticeModel::LatticeModel() {
  e = NULL;
  oppDirs = NULL;
  W = NULL;
  //W = {0};
  UDIRS = -1;
  DIM = -1;
}

LatticeModel::~LatticeModel() {
  //Empty
}

void LatticeModel::fillOppdirs() {
  for (int d = 0; d < UDIRS; d++) {
    for (int dp = 0; dp < UDIRS; dp++) {
      if (e[0][dp] == -e[0][d] && e[1][dp] == -e[1][d]
          && e[2][dp] == -e[2][d]) {
        cout << dp << " is opposite to " << d << endl;
        oppDirs[d] = dp;
        continue;
      }
    }
  }
}
