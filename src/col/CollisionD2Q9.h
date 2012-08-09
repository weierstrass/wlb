/*
 * CollisionD2Q9.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9_H_
#define COLLISIOND2Q9_H_

#include <iostream>
#include "CollisionModel.h"
#include "../Aux.h"

using namespace std;

class CollisionD2Q9 : public CollisionModel{
public:
	CollisionD2Q9();
	virtual ~CollisionD2Q9();
	double fEq(int d, double rho, double ux, double uy);
	double *getRhoU(double *f);
	double getRho(double *f);
	void addNodeToSkip(int i, int j);
	static const double W[9];
protected:
    bool **skip;
	int ex[9];
	int ey[9];
};


#endif COLLISIOND2Q9_H_
