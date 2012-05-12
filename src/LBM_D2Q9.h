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
#include "Constants.h"
#include "Aux.h"
#include "BoundaryNodes.h"
#include "HalfWayBBNodes.h"
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
	HalfWayBBNodes *hwbbNodes;
	ConstantPressureBoundaryNodes *cpNodes;
	ConstantVelocityBoundaryNodes *cvNodes;
public:
	LBM_D2Q9(int nx, int ny);
	void init();
	void BGKCollision();
	void calcMacroscopicVars();
	//void handleBoundaries();
	void handleWetBoundaries();
	//void handleBounceBack();
	void handleHardBoundaries();
	void stream();
	void printfi(int n);
	void printu();
	void dataToFile();
	void addHalfWayBBNodes(HalfWayBBNodes *bbn);
	void addConstantPressureBoundaryNodes(ConstantPressureBoundaryNodes *cpn);
	void addConstantVelocityBoundaryNodes(ConstantVelocityBoundaryNodes *cpn);
};

#endif /* LBM_D2Q9_H_ */
