/*
 * HeZouNodes.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef HEZOUNODES_H_
#define HEZOUNODES_H_

#include "BoundaryNodes.h"
#include "TypeValueNode.h"
//#include "../col/CollisionD2Q9LNP.h"
//#include "../col/CollisionD2Q9LPMChaiRHS.h"
//#include "../col/CollisionD2Q9LPMChai1to1.h"

template<class T>
class HeZouNodes: public BoundaryNodes {
public:
  HeZouNodes();
  virtual ~HeZouNodes();
  void updateF();
  void addNode(int x, int y, int z, double rho, int dir);
  void setCollisionModel(T *cm) {
    this->cm = cm;
  }
  ;
  void init();
  virtual double fEq(int dir, int i, int j) = 0;
protected:
  vector<TypeValueNode*> nodes;
  void updateNode(int i, int j, double rho, int bdr);
  void updateCornerNode(int i, int j, double rho, int bdr);
  T *cm;
};

#endif /* HEZOUNODES_H_ */
