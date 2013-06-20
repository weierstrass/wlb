/*
 * BFLBoundaryNodes.cpp
 * Andreas B�lling, 2012
 * DESCRIPTION - TODO
 */

#include "BFLBoundaryNodes.h"

BFLBoundaryNodes::BFLBoundaryNodes(int nx, int ny) :
    BoundaryNodes(nx, ny) {
  bNodes.resize(9);
  // TODO Auto-generated constructor stub

}

BFLBoundaryNodes::~BFLBoundaryNodes() {
  // TODO Auto-generated destructor stub
}

void BFLBoundaryNodes::updateF(double ***f, double **ux, double **uy) {
  //cout<<"performing BFL update"<<endl;
  int opdir[9] = { 0, 3, 4, 1, 2, 7, 8, 5, 6 };
  int xt[9] = { 0, 1, 0, -1, 0, 1, -1, -1, 1 };
  int yt[9] = { 0, 0, -1, 0, 1, -1, -1, 1, 1 };
  for (int i = 0; i < bNodes.size(); i++) {
    for (int j = 0; j < bNodes[i].size(); j++) {
      ValueNode vn = bNodes[i][j];
      if (vn.value <= 0.5 && vn.value >= 0) {
        f[opdir[i]][vn.x][vn.y] = f[i][vn.x + xt[i]][vn.y + yt[i]]
            + (1 - 2 * vn.value)
                * (f[i][vn.x][vn.y] - f[i][vn.x + xt[i]][vn.y + yt[i]]);
      } else if (vn.value > 0.5 && vn.value < 1) {
        f[opdir[i]][vn.x][vn.y] = (f[i][vn.x + xt[i]][vn.y + yt[i]]
            + (1 - 2 * vn.value)
                * (-f[opdir[i]][vn.x + xt[opdir[i]]][vn.y + yt[opdir[i]]]))
            / (2 * vn.value);
      } else {
        cerr << "q out of range, q: " << vn.value << endl;
      }
      //f[i][vn.x + xt[i]][vn.y + yt[i]] = 0;
      //cout<<"BFL: "<<vn.x<<", "<<vn.y<<", dir: "<<i<<", q: "<<vn.value<<endl;
    }
  }
}

void BFLBoundaryNodes::addNode(int x, int y, int dir, double q) {
  ValueNode *v = new ValueNode(x, y, q);
  bNodes[dir].push_back(*v);
}

bool BFLBoundaryNodes::isNode(int x, int y) { //TODO
  return false;
}
