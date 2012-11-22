/*
 * CollisionD2Q9BGKNS.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9BGKNS_H_
#define COLLISIOND2Q9BGKNS_H_

#include "CollisionD2Q9BGK.h"

class CollisionD2Q9BGKNS : public CollisionD2Q9BGK {
public:
    CollisionD2Q9BGKNS();
    virtual ~CollisionD2Q9BGKNS();
    void fEq(int i, int j, double *eq);
    double *u;
protected:
    void fEq(double rho, double *u, double *eq);
};

#endif /* COLLISIOND2Q9BGKNS_H_ */
