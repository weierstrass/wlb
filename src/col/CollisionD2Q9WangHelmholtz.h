/*
 * CollisionD2Q9WangHelmholtz.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9WANGHELMHOLTZ_H_
#define COLLISIOND2Q9WANGHELMHOLTZ_H_

#include "CollisionD2Q9LPMWang.h"

class CollisionD2Q9WangHelmholtz: public CollisionD2Q9LPMWang {
public:
	CollisionD2Q9WangHelmholtz();
	virtual ~CollisionD2Q9WangHelmholtz();
	double g_rhs(int i, int j);
	void setLambda(double l){lambda = l;};
protected:
	double lambda;
};

#endif /* COLLISIOND2Q9WANGHELMHOLTZ_H_ */
