/*
 * HeZouLPMChaiNodes.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include "HeZouLPMChaiNodes.h"

#define TYPE_LINE_NODE 1
#define TYPE_CORNER_NODE 2
#define TYPE_TIP_NODE 3

#define DIR1(i) 1 + (bdr + (i-1))%4
#define DIR5(i) 5 + (bdr + (i-1))%4

HeZouLPMChaiNodes::HeZouLPMChaiNodes() {
}

HeZouLPMChaiNodes::~HeZouLPMChaiNodes() {
  //deallocate deadNodes - TODO
}

void HeZouLPMChaiNodes::init() {
  //allocate memory for deadnode matrix.
  deadNodes = allocate2DArrayT<bool>(lm->n.y, lm->n.x);
  for (int j = 0; j < lm->n.y; j++) {
    for (int i = 0; i < lm->n.x; i++) {
      deadNodes[j][i] = false;
    }
  }

  cout << "Preprocessing Chai nodes..." << endl;
  int i, j;
  TypeValueNode *n;
  for (int k = 0; k < nodes.size(); k++) {
    n = nodes[k];
    i = n->x;
    j = n->y;

    //corner nodes...
    if (i == 0 && j == 0) {
      n->type = TYPE_CORNER_NODE;
      n->param = 0;
      continue;
    } else if (i == lm->n.x - 1 && j == 0) {
      n->type = TYPE_CORNER_NODE;
      n->param = 1;
      continue;
    } else if (i == lm->n.x - 1 && j == lm->n.y - 1) {
      n->type = TYPE_CORNER_NODE;
      n->param = 2;
      continue;
    } else if (i == 0 && j == lm->n.y - 1) {
      n->type = TYPE_CORNER_NODE;
      n->param = 3;
      continue;
    }

    //border nodes
    if (i == 0) {
      if (!deadNodes[j - 1][i] && !deadNodes[j + 1][i]) {
        n->type = TYPE_LINE_NODE;
        n->param = 0;
      }
    } else if (i == lm->n.x - 1) {
      if (!deadNodes[j - 1][i] && !deadNodes[j + 1][i]) {
        n->type = TYPE_LINE_NODE;
        n->param = 2;
      }
    } else if (j == 0) {
      //cout<<"found line node at ("<<i<<", "<<j<<")"<<endl;
      if (!deadNodes[j][i - 1] && !deadNodes[j][i + 1]) {
        n->type = TYPE_LINE_NODE;
        n->param = 1;
      }
    } else if (j == lm->n.y - 1) {
      if (!deadNodes[j][i - 1] && !deadNodes[j][i + 1]) {
        n->type = TYPE_LINE_NODE;
        n->param = 3;
      }
    }

    //inner nodes
    for (int bdr = 0; bdr < 4; bdr++) { //four eq. cases

    }
  }
}

void HeZouLPMChaiNodes::updateF() {
  cout << "Updating Chai boundary nodes..." << endl;
  int i, j;
  double temp, rho, psi;
  for (int k = 0; k < nodes.size(); k++) {
    i = nodes[k]->x;
    j = nodes[k]->y;
    rho = nodes[k]->v1;
    psi = cm->getPsi(f[0][j][i], i, j);
    switch (nodes[k]->type) {
    case TYPE_LINE_NODE:
      updateNode(i, j, rho, psi, nodes[k]->param);
      break;
    case TYPE_CORNER_NODE:
      updateCornerNode(i, j, rho, psi, nodes[k]->param);
      break;
    case TYPE_TIP_NODE:
      //updateCornerNode(i, j, rho, psi, nodes[k]->param);
      cerr << "NO IMPLEMENTATION FOR TIP NODES!" << endl;
      break;
    }
  }
}

void HeZouLPMChaiNodes::updateNode(int i, int j, double rho, double psi,
    int bdr) {
  //cout<<"aadasd "<<endl;
  double feqDiff = (cm->fEq(DIR1(1), psi) - cm->fEq(DIR1(3), psi));
  //cout<<"f_"<<DIR1(1)<<" = f_"<<DIR1(3)<<endl;
  f[0][j][i][DIR1(1)] = f[0][j][i][DIR1(3)] + feqDiff;
  //cout<<"f_"<<DIR5(5)<<"= -f_"<<DIR5(6)<<endl;
  f[0][j][i][DIR5(5)] = -f[0][j][i][DIR1(3)] - f[0][j][i][DIR5(6)]
      - f[0][j][i][DIR1(2)] - 0.5 * feqDiff + 0.5 * rho;
  //cout<<"f_"<<DIR5(8)<<endl;
  f[0][j][i][DIR5(8)] = -f[0][j][i][DIR1(3)] - f[0][j][i][DIR1(4)]
      - f[0][j][i][DIR5(7)] - 0.5 * feqDiff + 0.5 * rho;
}

void HeZouLPMChaiNodes::updateCornerNode(int i, int j, double rho, double psi,
    int bdr) {
  double feqDiff1_3 = cm->fEq(DIR1(1), psi) - cm->fEq(DIR1(3), psi);
  double feqDiff2_4 = cm->fEq(DIR1(2), psi) - cm->fEq(DIR1(4), psi);
  f[0][j][i][DIR1(1)] = f[0][j][i][DIR1(3)] + feqDiff1_3;
  f[0][j][i][DIR1(2)] = f[0][j][i][DIR1(4)] + feqDiff2_4;
  f[0][j][i][DIR5(5)] = f[0][j][i][DIR5(7)] - 0.5 * (feqDiff1_3 + feqDiff2_4);
  f[0][j][i][DIR5(8)] = -f[0][j][i][DIR1(3)] - f[0][j][i][DIR1(4)]
      - f[0][j][i][DIR5(7)] - 0.5 * feqDiff1_3 + 0.5 * rho;
  f[0][j][i][DIR5(6)] = -f[0][j][i][DIR1(3)] - f[0][j][i][DIR1(4)]
      - f[0][j][i][DIR5(7)] - 0.5 * feqDiff2_4 + 0.5 * rho;

}

void HeZouLPMChaiNodes::addNode(int x, int y, int z, double val) {
  TypeValueNode *v = new TypeValueNode(x, y, z, val, -1, 0);
  nodes.push_back(v);
}

void HeZouLPMChaiNodes::addDeadNode(int x, int y) {
  deadNodes[y][x] = true;
}
