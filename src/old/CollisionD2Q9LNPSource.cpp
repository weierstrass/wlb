/*
 * CollisionD2Q9LNPSource.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9LNPSource.h"

CollisionD2Q9LNPSource::CollisionD2Q9LNPSource() {
  // TODO Auto-generated constructor stub

}

CollisionD2Q9LNPSource::~CollisionD2Q9LNPSource() {
  // TODO Auto-generated destructor stub
}

void CollisionD2Q9LNPSource::init() {
  cout << "init LNP with source..." << endl;
  double initConc = 0.0;
  ni = allocate2DArray(lm->n.y, lm->n.x);
  rhs = allocate2DArray(lm->n.y, lm->n.x);
  for (int j = 0; j < lm->n.y; j++) {
    for (int i = 0; i < lm->n.x; i++) {
      for (int d = 0; d < lm->UDIRS; d++) {
        f[0][j][i][d] = fEq(d, 0, 0, j * j);
      }
    }
  }

  double colPrefactor = (1 - 0.5 * w);

  updateNi();
}

void CollisionD2Q9LNPSource::collide() {
  cout << "D2Q9 LNP with source collision" << endl;
  cout << "pe:" << Pe << endl;
  for (int j = 0; j < n.y; j++) {
    for (int i = 0; i < n.x; i++) {
      for (int d = 0; d < 9; d++) {
        f[0][j][i][d] += w
            * (fEq(d, ux[j][i], uy[j][i], ni[j][i]) - f[0][j][i][d])
            + W[d] * colPrefactor * rhs[j][i];
      }
    }
  }

  updateNi();
}
