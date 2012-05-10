/*
 * LBM-D2Q9.h
 *
 */

#ifndef LBM_D2Q9_H_
#define LBM_D2Q9_H_


#include <iostream>
#include <fstream>
#include <list>
#include <string.h>
#include "Aux.h"
//#include "BoundaryNode.h"
#include "HalfWayBBNodes.h"


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
public:
	LBM_D2Q9(int nx, int ny);
	void init();
	void BGKCollision();
	void calcMacroscopicVars();
	void handleBoundaries();
	void handleBounceBack();
	void handleHardBoundaries();
	void stream();
	void printfi(int n);
	void printu();
	void dataToFile();
	void addHalfWayBBNodes(HalfWayBBNodes *bbn);
};

#endif /* LBM_D2Q9_H_ */
