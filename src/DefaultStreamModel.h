/*
 * DefaultStreamModel.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef DEFAULTSTREAMMODEL_H_
#define DEFAULTSTREAMMODEL_H_

#include "StreamModel.h"

class DefaultStreamModel : public StreamModel {
public:
	DefaultStreamModel(int nx, int ny);
	virtual ~DefaultStreamModel();
	void updateF(double ***f);
};

#endif /* DEFAULTSTREAMMODEL_H_ */
