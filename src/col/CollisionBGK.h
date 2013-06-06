/*
 * CollisionBGK.h - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#ifndef COLLISIONBGK_H_
#define COLLISIONBGK_H_

#include "CollisionModel.h"
#include "../Aux.h"

class CollisionBGK: public CollisionModel {
public:
  CollisionBGK();
  virtual ~CollisionBGK();
  void collide();
  void init();
  void setW(double w) {
    this->w = w;
    wInv = 1 / w;
  }
  ;
  virtual void fEq(int k, int j, int i, double *eq) = 0;
  double get0moment(int k, int j, int i);
  void get1moment(int k, int j, int i, double *ret);
protected:
  double w, wInv;
  double *eq;
};

#endif /* COLLISIONBGK_H_ */
