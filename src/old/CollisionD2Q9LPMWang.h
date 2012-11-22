/*
 * CollisionD2Q9LPMWang.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LPMWANG_H_
#define COLLISIOND2Q9LPMWANG_H_

#include "CollisionD2Q9LPM.h"

class CollisionD2Q9LPMWang: public CollisionD2Q9LPM {
public:
	CollisionD2Q9LPMWang();
	virtual ~CollisionD2Q9LPMWang();
	double fEq(int d, double psi);
	void collide();
	void init();
	//double g_rhs(int i, int j);
protected:
	double getPsi(double *f, int i, int j);
};

#endif /* COLLISIOND2Q9LPMWANG_H_ */
