/*
 * CollisionD2Q9LPMChai.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LPMCHAI_H_
#define COLLISIOND2Q9LPMCHAI_H_

#include "CollisionD2Q9LPM.h"
#include "../Constants.h"

class CollisionD2Q9LPMChai : public CollisionD2Q9LPM{
public:
	CollisionD2Q9LPMChai();
	virtual ~CollisionD2Q9LPMChai();
	void collide();
	double fEq(int d, double psi);
	double g_rhs(int i, int j);
protected:
	double getPsi(double *f, int i, int j);
};

#endif /* COLLISIOND2Q9LPMCHAI_H_ */
