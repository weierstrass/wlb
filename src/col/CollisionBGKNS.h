/*
 * CollisionBGKNS.h - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#ifndef COLLISIONBGKNS_H_
#define COLLISIONBGKNS_H_

#include "CollisionBGK.h"

class CollisionBGKNS: public CollisionBGK {
public:
	CollisionBGKNS();
	virtual ~CollisionBGKNS();
	void fEq(int k, int j, int i, double *eq);
	void init();
	void getU(double **ux, double **uy);
protected:
	void fEq(double *eq);
    double *u;
    double c1, c2, c3, rho;
};

#endif /* COLLISIONBGKNS_H_ */
