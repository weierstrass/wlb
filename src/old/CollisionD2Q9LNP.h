/*
 * CollisionD2Q9LNP.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LNP_H_
#define COLLISIOND2Q9LNP_H_

#include <string.h>
#include "CollisionD2Q9.h"
#include "../Aux.h"

class CollisionD2Q9LNP: public CollisionD2Q9 {
public:
  CollisionD2Q9LNP();
  virtual ~CollisionD2Q9LNP();
  void collide();
  void init();
  double fEq(int d, double ux, double uy, double ni);
  double fEq(int d, int i, int j);
  double calcConc(double *f, int i, int j);
  void setUx(double **ux) {
    this->ux = ux;
  }
  ;
  void setUy(double **uy) {
    this->uy = uy;
  }
  ;
  void setDPsix(double **dPsix) {
    this->dPsix = dPsix;
  }
  ;
  void setDPsiy(double **dPsiy) {
    this->dPsiy = dPsiy;
  }
  ;
  void setPe(double Pe) {
    this->Pe = Pe;
  }
  ;
  void setZ(double z) {
    this->z = z;
  }
  ;
  void setT(double T) {
    this->T = T;
  }
  ;
  void setW(double w) {
    this->w = w;
  }
  ;
  void setInitC(double C) {
    this->initC = C;
  }
  ;
  void setRHS(double **rhs) {
    this->rhs = rhs;
  }
  ;
  void dataToFile(string path);
  double **getNi() {
    return ni;
  }
  ;
  double **getdPsix() {
    return dPsix;
  }
  ;
  double **getdPsiy() {
    return dPsiy;
  }
  ;
  double getZ() {
    return z;
  }
  ;
  double getT() {
    return T;
  }
  ;
  void reset();
  double getSourceTerm(int i, int j);
  double getf0(int i, int j);
protected:
  double **ux, **uy, **dPsix, **dPsiy, **ni, **rhs;
  double Pe, z, T, w, initC;
  double colPrefactor;
  // void updateDivTerm();
  void updateNi();
};

#endif /* COLLISIOND2Q9LNP_H_ */
