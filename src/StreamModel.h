/*
 * StreamModel.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef STREAMMODEL_H_
#define STREAMMODEL_H_

#include <iostream>

using namespace std;

class StreamModel {
public:
	StreamModel(int nx, int ny);
	virtual ~StreamModel();
	virtual void updateF(double ***f) = 0;
protected:
	int nx, ny;

};

#endif /* STREAMMODEL_H_ */
