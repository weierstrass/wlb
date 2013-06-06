/*
 * CollisionD2Q9LPMChai1to1.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LPMCHAI1TO1_H_
#define COLLISIOND2Q9LPMCHAI1TO1_H_

#include "CollisionD2Q9LPMChai.h"

class CollisionD2Q9LPMChai1to1: public CollisionD2Q9LPMChai {
public:
  CollisionD2Q9LPMChai1to1();
  virtual ~CollisionD2Q9LPMChai1to1();
  void init();
  double g_rhs(int i, int j);
  double getSIChargeDensity(double psi);
  double prefactor;
  double inSinh;
  double prefactorChargeSI;
  void setPermittivity(double e) {
    this->eps = e;
  }
  ;
  void setInfConcentration(double c) {
    this->cinf = c;
  }
  ;
  void setTemperature(double T) {
    this->T = T;
  }
  ;
  double getPermittivity() {
    return eps;
  }
  ;
  double getTemperature() {
    return T;
  }
  ;
  double getInfConcentration() {
    return cinf;
  }
  ;
protected:
  double eps;
  double cinf;
  double T;

};

#endif /* COLLISIOND2Q9LPMCHAI1TO1_H_ */
