/*
 * Lattice2D.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef LATTICE2D_H_
#define LATTICE2D_H_

#include "LatticeModel.h"
#include <cstring>

class Lattice2D  : public LatticeModel{
public:
	Lattice2D(int nx, int ny);
	virtual ~Lattice2D();
};

#endif /* LATTICE2D_H_ */
