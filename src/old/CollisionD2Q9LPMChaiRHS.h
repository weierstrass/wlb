/*
 * CollisionD2Q9LPMChaiRHS.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LPMCHAIRHS_H_
#define COLLISIOND2Q9LPMCHAIRHS_H_

#include "CollisionD2Q9LPMChai.h"

class CollisionD2Q9LPMChaiRHS: public CollisionD2Q9LPMChai {
public:
  CollisionD2Q9LPMChaiRHS();
  virtual ~CollisionD2Q9LPMChaiRHS();
  double g_rhs(int i, int j);
  void setRHS(double **rhs) {
    this->rhs = rhs;
  }
  ;
protected:
  double **rhs;
};

#endif /* COLLISIOND2Q9LPMCHAIRHS_H_ */
