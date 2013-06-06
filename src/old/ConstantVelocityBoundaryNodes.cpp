/*
 * ConstantVelocityBoundaryNodes.cpp
 * Andreas B�lling, 2012
 * DESCRIPTION - TODO
 */

#include "ConstantVelocityBoundaryNodes.h"

ConstantVelocityBoundaryNodes::ConstantVelocityBoundaryNodes(int nx, int ny) :
    BoundaryNodes(nx, ny) {
  // TODO Auto-generated constructor stub
}

void ConstantVelocityBoundaryNodes::updateF(double ***f, double ***u,
    double **rho) {
  int i, j;
  for (int k = 0; k < bNodes.size(); k++) {
    i = bNodes[k].x;
    j = bNodes[k].y;
    //	cout<<"updating boundary node: ("<<i<<", "<<j<<")"<<", uy: "<<bNodes[k].valueY<<endl;
    //cout<<"i: "<<i<<", j: "<<j<<endl;
    if (i == 0 && j == ny - 1 - 1) { //todo
      u[X][0][j] = bNodes[k].valueX;
      u[Y][0][j] = bNodes[k].valueY;
      cout << "handeling down left" << i << ", " << j << endl;
      f[1][i][j] = f[3][i][j];
      f[2][i][j] = f[4][i][j];
      f[5][i][j] = f[7][i][j];
      rho[i][j] = 0.5 * (rho[i][j - 1] + rho[i + 1][j]);
      double foo = 0.5
          * (rho[i][j]
              - (f[0][i][j] + f[1][i][j] + f[2][i][j] + f[3][i][j] + f[4][i][j]
                  + f[5][i][j] + f[7][i][j]));
      f[6][i][j] = foo;
      f[8][i][j] = foo;
      //continue;
    } else if (i == 0 && j == 1) {
      u[X][0][j] = bNodes[k].valueX;
      u[Y][0][j] = bNodes[k].valueY;
      f[4][i][j] = f[2][i][j];
      f[8][i][j] = f[6][i][j];
      f[1][i][j] = f[3][i][j];
      rho[i][j] = rho[i + 1][j + 1];
      double foo = 0.5
          * (rho[i][j]
              - (f[0][i][j] + f[1][i][j] + f[2][i][j] + f[3][i][j] + f[4][i][j]
                  + f[6][i][j] + f[8][i][j]));
      f[5][i][j] = foo;
      f[7][i][j] = foo;
      //continue;
    } else if (i == nx - 1 && j == 1) {
      u[X][i][j] = bNodes[k].valueX;
      u[Y][i][j] = bNodes[k].valueY;
      f[3][i][j] = f[1][i][j];
      f[7][i][j] = f[5][i][j];
      f[4][i][j] = f[2][i][j];
      rho[i][j] = 0.5 * (rho[i - 1][j] + rho[i][j + 1]);
      double foo = 0.5
          * (rho[i][j]
              - (f[0][i][j] + f[1][i][j] + f[2][i][j] + f[3][i][j] + f[4][i][j]
                  + f[5][i][j] + f[7][i][j]));
      f[6][i][j] = foo;
      f[8][i][j] = foo;
    } else if (i == nx - 1 && j == ny - 1 - 1) {
      u[X][i][j] = bNodes[k].valueX;
      u[Y][i][j] = bNodes[k].valueY;
      f[2][i][j] = f[4][i][j];
      f[3][i][j] = f[1][i][j];
      f[6][i][j] = f[8][i][j];
      rho[i][j] = 0.5 * (rho[i - 1][j] + rho[i][j - 1]);
      double foo = 0.5
          * (rho[i][j]
              - (f[0][i][j] + f[1][i][j] + f[2][i][j] + f[3][i][j] + f[4][i][j]
                  + f[6][i][j] + f[8][i][j]));
      f[5][i][j] = foo;
      f[7][i][j] = foo;

    } else if (i == 0) {
      u[X][0][j] = bNodes[k].valueX;
      u[Y][0][j] = bNodes[k].valueY;
      rho[0][j] = 1 / (1 - u[X][0][j])
          * (f[0][0][j] + f[2][0][j] + f[4][0][j]
              + 2 * (f[3][0][j] + f[6][0][j] + f[7][0][j]));

      f[1][0][j] = f[3][0][j] + 2.0 / 3.0 * rho[0][j] * u[X][0][j];
      f[5][0][j] = f[7][0][j] + 0.5 * (f[4][0][j] - f[2][0][j])
          + 1.0 / 6.0 * rho[0][j] * u[X][0][j] + 0.5 * rho[0][j] * u[Y][0][j];
      f[8][0][j] = f[6][0][j] - 0.5 * (f[4][0][j] - f[2][0][j])
          + 1.0 / 6.0 * rho[0][j] * u[X][0][j] - 0.5 * rho[0][j] * u[Y][0][j];
    } else if (i == nx - 1) {
      u[X][i][j] = bNodes[k].valueX;
      u[Y][i][j] = bNodes[k].valueY;
      rho[i][j] = 1 / (1 + u[X][i][j])
          * (f[0][i][j] + f[2][i][j] + f[4][i][j]
              + 2 * (f[1][i][j] + f[5][i][j] + f[8][i][j]));
      f[3][i][j] = f[1][i][j] - 2.0 / 3.0 * rho[i][j] * u[X][i][j];
      f[7][i][j] = f[5][i][j] - 0.5 * (f[4][i][j] - f[2][i][j])
          - 1.0 / 6.0 * rho[i][j] * u[X][i][j] - 0.5 * rho[i][j] * u[Y][i][j];
      f[6][i][j] = f[8][i][j] + 0.5 * (f[4][i][j] - f[2][i][j])
          - 1.0 / 6.0 * rho[i][j] * u[X][i][j] + 0.5 * rho[i][j] * u[Y][i][j];
    } else if (j == ny - 1) {
      u[X][i][j] = bNodes[k].valueX;
      u[Y][i][j] = bNodes[k].valueY;
      rho[i][j] = 1 / (1 - u[Y][i][j])
          * (f[0][i][j] + f[1][i][j] + f[3][i][j]
              + 2 * (f[4][i][j] + f[7][i][j] + f[8][i][j]));

      f[2][i][j] = f[4][i][j] + 2.0 / 3.0 * rho[i][j] * u[Y][i][j];
      f[5][i][j] = f[7][i][j] - 0.5 * (f[1][i][j] - f[3][i][j])
          + 0.5 * rho[i][j] * u[X][i][j] + 1.0 / 6.0 * rho[i][j] * u[Y][i][j];
      f[6][i][j] = f[8][i][j] + 0.5 * (f[1][i][j] - f[3][i][j])
          - 0.5 * rho[i][j] * u[X][i][j] + 1.0 / 6.0 * rho[i][j] * u[Y][i][j];
    } else if (j == 0) {
      u[X][i][j] = bNodes[k].valueX;
      u[Y][i][j] = bNodes[k].valueY;
      rho[i][j] = 1 / (1 + u[Y][i][j])
          * (f[0][i][j] + f[1][i][j] + f[3][i][j]
              + 2 * (f[2][i][j] + f[6][i][j] + f[5][i][j]));

      f[4][i][j] = f[2][i][j] - 2.0 / 3.0 * rho[i][j] * u[Y][i][j];
      f[7][i][j] = f[5][i][j] + 0.5 * (f[1][i][j] - f[3][i][j])
          - 0.5 * rho[i][j] * u[X][i][j] - 1.0 / 6.0 * rho[i][j] * u[Y][i][j];
      f[8][i][j] = f[6][i][j] - 0.5 * (f[1][i][j] - f[3][i][j])
          + 0.5 * rho[i][j] * u[X][i][j] - 1.0 / 6.0 * rho[i][j] * u[Y][i][j];

    } else {
      cerr
          << "No implementation found for requested constant velocity boundary node!"
          << endl;
    }
  }
}

ConstantVelocityBoundaryNodes::~ConstantVelocityBoundaryNodes() {
  bNodes.clear();
}

void ConstantVelocityBoundaryNodes::addNode(int x, int y, double vx,
    double vy) {
  ValueNode2D *v = new ValueNode2D(x, y, vx, vy);
  bNodes.push_back(*v);
}

void ConstantVelocityBoundaryNodes::clearNodes() {
  bNodes.clear();
}
