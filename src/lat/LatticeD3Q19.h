/*
 * LatticeD3Q19.h
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef LATTICED3Q19_H_
#define LATTICED3Q19_H_

#include "LatticeModel.h"

class LatticeD3Q19: public LatticeModel {
public:
  LatticeD3Q19(int nx, int ny, int nz);
  virtual ~LatticeD3Q19();
};

#endif /* LATTICED3Q19_H_ */
