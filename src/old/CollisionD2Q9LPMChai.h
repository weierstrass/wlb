/*
 * CollisionD2Q9LPMChai.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LPMCHAI_H_
#define COLLISIOND2Q9LPMCHAI_H_

#include <math.h>
//#include "CollisionD2Q9LPM.h"
#include "CollisionD2Q9BGK.h"
#include "../Constants.h"

class CollisionD2Q9LPMChai: public CollisionD2Q9BGK {
public:
  CollisionD2Q9LPMChai();
  virtual ~CollisionD2Q9LPMChai();
  void collide();
  double fEq(int d, double psi);
  double fEq(int d, int i, int j);
  void init();
  double getPsi(double *f, int i, int j);
  double getPsi(int i, int j);
  void reset();
  void getDPsi(double **retX, double **retY);
protected:
};

#endif /* COLLISIOND2Q9LPMCHAI_H_ */
