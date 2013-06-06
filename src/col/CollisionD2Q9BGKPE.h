/*
 * CollisionD2Q9BGKPE.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9BGKPE_H_
#define COLLISIOND2Q9BGKPE_H_

#include "CollisionD2Q9BGK.h"

class CollisionD2Q9BGKPE: public CollisionD2Q9BGK {
public:
  CollisionD2Q9BGKPE();
  virtual ~CollisionD2Q9BGKPE();
  void fEq(int i, int j, double *eq);
  double g_rhs(int i, int j);
  void collide();
  void setRHS(double **rhs) {
    this->rhs = rhs;
  }
  ;
  void reset();
  void getPsi(double **psi);
  void getDPsi(double **jx, double **jy);
  void dataToFile(string path);
protected:
  double **rhs;
};

#endif /* COLLISIOND2Q9BGKPE_H_ */
