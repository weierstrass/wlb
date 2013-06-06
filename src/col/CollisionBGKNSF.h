/*
 * CollisionBGKNSF.h - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#ifndef COLLISIONBGKNSF_H_
#define COLLISIONBGKNSF_H_

#include "CollisionBGKNS.h"

class CollisionBGKNSF: public CollisionBGKNS {
public:
  CollisionBGKNSF();
  virtual ~CollisionBGKNSF();
  void setForce(double ****force) {
    this->force = force;
  }
  ;
  void fEq(int k, int j, int i, double *eq);
  void get1moment(int k, int j, int i, double *ret);
protected:
  double ****force; //force[x/y/z][k][j][i]
private:
  void get1momentEq(int k, int j, int i, double *ret);

};

#endif /* COLLISIONBGKNSF_H_ */
