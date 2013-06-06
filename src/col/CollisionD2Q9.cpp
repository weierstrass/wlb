/*
 * CollisionD2Q9.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 */

#include "CollisionD2Q9.h"

/* Define lattice weights */
const double CollisionD2Q9::W[9] = { W0, W1, W1, W1, W1, W2, W2, W2, W2 };

CollisionD2Q9::CollisionD2Q9() :
    CollisionModel() {
}

CollisionD2Q9::~CollisionD2Q9() {
  if (skip != NULL) {
    //Deallocate skip array TODO
  }
}

