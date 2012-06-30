/*
 * PeriodicStreamModel.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef PERIODICSTREAMMODEL_H_
#define PERIODICSTREAMMODEL_H_

#include <iostream>
#include "StreamModel.h"
#include "../Aux.h"

class PeriodicStreamModel : public StreamModel{
public:
	PeriodicStreamModel(int nx, int ny);
	virtual ~PeriodicStreamModel();
	void updateF(double ***f);
	void init();
private:
	double **fv;
	double **fh;

};

#endif /* PERIODICSTREAMMODEL_H_ */
