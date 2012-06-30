/*
 * CollisionD2Q9BGK.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9BGK_H_
#define COLLISIOND2Q9BGK_H_

#include <iostream>
#include "CollisionD2Q9.h"
#include "../Aux.h"

using namespace std;

class CollisionD2Q9BGK : public CollisionD2Q9 {
private:
	double w;
public:
	CollisionD2Q9BGK();
	virtual ~CollisionD2Q9BGK();
	void collide();
	void init();
	double fEq(int d, double rho, double ux, double uy);
	double getRho(double *f){ return CollisionD2Q9::getRho(f);};
	double *getRhoU(double *f){return CollisionD2Q9::getRhoU(f);};
	void setW(double w);
};

#endif /* COLLISIOND2Q9BGK_H_ */
