/*
 * LatticeModel.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef LATTICEMODEL_H_
#define LATTICEMODEL_H_

#include <iostream>

using namespace std;


class LatticeModel {
public:
	LatticeModel();
	virtual ~LatticeModel();
	struct dimension{
		int x;
		int y;
		int z;
	} n;
	int UDIRS;
	int DIM;
	int *oppDirs;
	int *ex;
	int *ey;
	int *ez;
private:
};

#endif /* LATTICEMODEL_H_ */
