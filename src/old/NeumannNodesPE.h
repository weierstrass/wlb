/*
 * NeumannNodesPE.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef NEUMANNNODESPE_H_
#define NEUMANNNODESPE_H_

#include "NeumannNodes.h"
#include "../col/CollisionD2Q9LPMChaiRHS.h"

class NeumannNodesPE: public NeumannNodes<CollisionD2Q9LPMChaiRHS> { //todo
public:
  NeumannNodesPE();
  virtual ~NeumannNodesPE();
  void updateF();
protected:
  double fEq(int dir, int i, int j);
  double cu(int i, int j);
};

#endif /* NEUMANNNODESPE_H_ */
