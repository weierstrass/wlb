/*
 * LatticeModel.h
 * Andreas B�lling, 2012
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
    static const int slipDirsH[];
    static const int slipDirsV[];
    static const int slipDirsC[];
	//int ex[];
	//int ey[];
	//int ez[];
	int **e;
	double *W;
protected:
	void fillOppdirs();
};

#endif /* LATTICEMODEL_H_ */
