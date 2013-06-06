/*
 * CollisionD2Q9.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Abstract base class for D2Q9 collision operators.
 */

#ifndef COLLISIOND2Q9_H_
#define COLLISIOND2Q9_H_

#include <iostream>
#include "CollisionModel.h"
#include "../Aux.h"

using namespace std;

class CollisionD2Q9: public CollisionModel {
public:
  CollisionD2Q9();
  virtual ~CollisionD2Q9();
  static const double W[9];
protected:
  //int ex[9];
  //int ey[9];
};

#endif /* COLLISIOND2Q9_H_ */
