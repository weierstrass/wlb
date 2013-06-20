/*
 * Stream.cpp
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "Stream.h"

Stream::Stream() {
  // TODO Auto-generated constructor stub
}

Stream::~Stream() {
  // TODO Auto-generated destructor stub
}

void Stream::stream() {
  //cout << "general streaming" << endl;
  int sx, sy, sz;

  for (int d = 0; d < lm->UDIRS; d++) {
    for (int l = 0; l < lm->DIM; l++) {
      if (lm->e[l][d] == 0) {
        continue;
      }

      sx = l == 0;
      sy = l == 1;
      sz = l == 2;

      //cout << l << ", sx: " << sx << ", sy: " << sy << ", sz: " << sz
      //        << endl;

      if (lm->e[l][d] > 0) {
        //cout << "forward stream..." << endl;
        forwardStream(d, sz, sy, sx);
      } else {
        //cout << "backward stream..." << endl;
        backwardStream(d, sz, sy, sx);
      }
    }
  }
}

void Stream::init() {
//empty
}

void Stream::backwardStream(int d, int sz, int sy, int sx) {
  //cout << "back" << endl;
  for (int k = 0; k < lm->n.z - sz; k++) {
    for (int j = 0; j < lm->n.y - sy; j++) {
      for (int i = 0; i < lm->n.x - sx; i++) {
        //cout << "a: " << k << ", " << j << ", " << i << endl;
        //cout << "b: " << sz << ", " << sy << ", " << sx << endl;
        //cout<<"d: "<<d<<endl;
        f[k][j][i][d] = f[k + sz][j + sy][i + sx][d];
      }
    }
  }
}

void Stream::forwardStream(int d, int sz, int sy, int sx) {
  //cout << "forward" << endl;
  for (int k = lm->n.z - 1; k >= sz; k--) {
    for (int j = lm->n.y - 1; j >= sy; j--) {
      for (int i = lm->n.x - 1; i >= sx; i--) {
        //cout << k << ", " << j << ", " << i << endl;
        f[k][j][i][d] = f[k - sz][j - sy][i - sx][d];
      }
    }
  }
}
