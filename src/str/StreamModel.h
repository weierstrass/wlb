/*
 * StreamModel.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef STREAMMODEL_H_
#define STREAMMODEL_H_

#include <iostream>
#include "../lat/LatticeModel.h"

using namespace std;

class StreamModel {
protected:
	double ****f;
	struct LatticeModel::dimension n;
public:
	StreamModel();
	virtual ~StreamModel();
	virtual void stream() = 0;
	virtual void init() = 0;
	void registerN(struct LatticeModel::dimension &n);
	void registerF(double ****f);

};

#endif /* STREAMMODEL_H_ */
