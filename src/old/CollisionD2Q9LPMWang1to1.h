/*
 * CollisionD2Q9LPMWang1to1.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LPMWANG1TO1_H_
#define COLLISIOND2Q9LPMWANG1TO1_H_

#include "CollisionD2Q9LPMWang.h"

class CollisionD2Q9LPMWang1to1: public CollisionD2Q9LPMWang {
public:
  CollisionD2Q9LPMWang1to1();
  virtual ~CollisionD2Q9LPMWang1to1();
  double g_rhs(int i, int j);
  void init();
private:
  double prefactor, inSinh;
};

#endif /* COLLISIOND2Q9LPMWANG1TO1_H_ */
