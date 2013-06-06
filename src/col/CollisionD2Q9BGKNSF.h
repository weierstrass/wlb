/*
 * CollisionD2Q9BGKNSF.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Collision operator for solving the
 * incompressible Navier-Stokes equations
 * with a force term present.
 *
 * Force is implemented using the
 * Shan-Chen method.
 *
 */

#ifndef COLLISIOND2Q9BGKNSF_H_
#define COLLISIOND2Q9BGKNSF_H_

#include "CollisionD2Q9BGKNS.h"

class CollisionD2Q9BGKNSF: public CollisionD2Q9BGKNS {
public:
  CollisionD2Q9BGKNSF();
  virtual ~CollisionD2Q9BGKNSF();
  void fEq(int i, int j, double *eq);
  void get1moment(int i, int j, double *ret);
  void setForce(double **fx, double **fy) {
    this->fx = fx;
    this->fy = fy;
  }
  ;
  void dataToFile(string path);
protected:
  double **fx;
  double **fy;
private:
  void get1momentEq(int i, int j, double *ret);
};

#endif /* COLLISIOND2Q9BGKNSF_H_ */
