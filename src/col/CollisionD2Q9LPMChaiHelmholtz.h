/*
 * CollisionD2Q9LPMChaiHelmholtz.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LPMCHAIHELMHOLTZ_H_
#define COLLISIOND2Q9LPMCHAIHELMHOLTZ_H_

#include "CollisionD2Q9LPMChai.h"

class CollisionD2Q9LPMChaiHelmholtz: public CollisionD2Q9LPMChai {
public:
	CollisionD2Q9LPMChaiHelmholtz();
	virtual ~CollisionD2Q9LPMChaiHelmholtz();
	double g_rhs(int i, int j);
	void setLambda(double lambda){this->lambda = lambda;};
	void init();
private:
	double lambda;
};

#endif /* COLLISIOND2Q9LPMCHAIHELMHOLTZ_H_ */
