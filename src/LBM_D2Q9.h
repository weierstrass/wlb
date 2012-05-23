/*
 * LBM-D2Q9.h
 * Andreas BŸlling, 2012
 *
 */

#ifndef LBM_D2Q9_H_
#define LBM_D2Q9_H_


#include <iostream>
#include <list>
#include <string.h>
#include <sstream>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include "Constants.h"
#include "Aux.h"
#include "BoundaryNodes.h"
#include "StreamModel.h"
#include "PeriodicStreamModel.h"
#include "DefaultStreamModel.h"
#include "HalfWayBBNodes.h"
#include "BFLBoundaryNodes.h"
#include "ConstantPressureBoundaryNodes.h"
#include "ConstantVelocityBoundaryNodes.h"


using namespace std;


class LBM_D2Q9{
private:
	int nx;
	int ny;
	double c;
	double w;
	double ***f;
	double **rho;
	double **ux;
	double **uy;
	double **fx;
	double **fy;
	bool **deadNodes;
	HalfWayBBNodes *hwbbNodes;
	BFLBoundaryNodes *bflNodes;
	ConstantPressureBoundaryNodes *cpNodes;
	ConstantVelocityBoundaryNodes *cvNodes;
	StreamModel *streamModel;
public:
	LBM_D2Q9(int nx, int ny);
	void init();
	void BGKCollision();
	void calcMacroscopicVars();
	void handleWetBoundaries();
	void handleHardBoundaries();
	void stream();
	void printfi(int n);
	void printu();
	void dataToFile();
	void addHalfWayBBNodes(HalfWayBBNodes *bbn);
	void addBFLNodes(BFLBoundaryNodes *bfl);
	void addConstantPressureBoundaryNodes(ConstantPressureBoundaryNodes *cpn);
	void addConstantVelocityBoundaryNodes(ConstantVelocityBoundaryNodes *cpn);
	void addDeadNode(int x, int y);
	void setStreamModel(StreamModel *s);
	void setW(double w);
	void setC(double c);
	void setF(double fxi, double fyi, int x, int y);
	double Si(int d, int i, int j);
};

#endif /* LBM_D2Q9_H_ */
