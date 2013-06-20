/*
 * ConstantVelocityBoundaryNodes.h
 * Andreas B�lling, 2012
 * DESCRIPTION - TODO
 */

#ifndef CONSTANTVELOCITYBOUNDARYNODES_H_
#define CONSTANTVELOCITYBOUNDARYNODES_H_

#include <vector>
#include "BoundaryNodes.h"
#include "ValueNode.h"

class ConstantVelocityBoundaryNodes: public BoundaryNodes {
public:
  ConstantVelocityBoundaryNodes(int nx, int ny);
  virtual ~ConstantVelocityBoundaryNodes();
  void updateF(double ***f, double ***u, double **rho);
  void addNode(int x, int y, double vx, double vy);
  void clearNodes();
private:
  vector<ValueNode2D> bNodes;
};

#endif /* CONSTANTVELOCITYBOUNDARYNODES_H_ */
