/*
 * CollisionD2Q9BGKNS.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Collision operator for solving the
 * incompressible Navier-Stokes equations.
 */

#ifndef COLLISIOND2Q9BGKNS_H_
#define COLLISIOND2Q9BGKNS_H_

#include "CollisionD2Q9BGK.h"

class CollisionD2Q9BGKNS: public CollisionD2Q9BGK {
public:
  CollisionD2Q9BGKNS();
  virtual ~CollisionD2Q9BGKNS();
  void fEq(int i, int j, double *eq);
  void init(double **rho, double **ux, double **uy);
  void getU(double **ux, double **uy);
protected:
  double *u;
  void fEq(double rho, double *u, double *eq);
  double c1, c2, c3;

};

#endif /* COLLISIOND2Q9BGKNS_H_ */
