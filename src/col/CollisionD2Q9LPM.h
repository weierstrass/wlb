/*
 * CollisionD2Q9LPM.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LPM_H_
#define COLLISIOND2Q9LPM_H_

#include <math.h>
#include <string.h>
#include "CollisionD2Q9.h"
#include "../Aux.h"
#include "../unit/UnitHandlerLPM.h"

class CollisionD2Q9LPM: public CollisionD2Q9 {
public:
	CollisionD2Q9LPM();
	virtual ~CollisionD2Q9LPM();
	void setW(double w){this->w = w;};
	void dataToFile();
	void dataToFile(string str);
	virtual double g_rhs(int i, int j) = 0;
	double** getPotential(){return psi;};
protected:
	double w;
	double **psi;
	static const double Wa[];
};

#endif COLLISIOND2Q9LPM_H_
