/*
 * AppCylinder.cpp
 * Andreas BŸlling, 2012
 * A circular obstacle in the flow.
 */

#include <iostream>
#include "../LBM_D2Q9.h"
#include <math.h>

using namespace std;

int main(){
	int nx = 400, ny = 101, tMax = 15000, writeMod = 50;
	double uMaxInlet = 0.1;

	cout<<"Cylinder flow..."<<endl;
	LBM_D2Q9 *lbm = new LBM_D2Q9(nx, ny);

	/* Set inlet conditions */
	ConstantVelocityBoundaryNodes *cvInlet = new ConstantVelocityBoundaryNodes(nx, ny);
	for(int j = 1; j < ny-1; j++){
		cvInlet->addNode(0, j, poiseuilleVelocity(j, 0, ny-1, uMaxInlet), 0);
	}
	lbm->addConstantVelocityBoundaryNodes(cvInlet);

	/* Set outlet conditions*/
	ConstantPressureBoundaryNodes *cpOutlet = new ConstantPressureBoundaryNodes(nx, ny);
	for(int j = 1; j < ny-1; j++){
		cpOutlet->addNode(nx-1, j, 1.0);
	}
	lbm->addConstantPressureBoundaryNodes(cpOutlet);

	/* Add boundary nodes */
	HalfWayBBNodes *hwbb = new HalfWayBBNodes(nx, ny);
	lbm->addHalfWayBBNodes(hwbb);
	for(int i = 0; i < nx; i++){
		hwbb->addNode(i, 0);
		hwbb->addNode(i, ny-1);
	}
	int xc = nx/4, yc = ny/2;
	double r = 20.0;
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			if(sqrt((double)((i - xc)*(i - xc) + (j - yc)*(j - yc))) < r){
				hwbb->addNode(i, j);
			}
		}
	}

	/* Initialize solver */
	lbm->init();
	StreamModel *ps = new PeriodicStreamModel(nx, ny);
	lbm->setStreamModel(ps);
	lbm->setW(0.9);
	lbm->setC(1.0);

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		cout<<t<<endl;
		lbm->calcMacroscopicVars();
		lbm->handleWetBoundaries();//wet
		lbm->BGKCollision();
		lbm->stream();
		lbm->handleHardBoundaries();
		if(t % writeMod == 0){
			lbm->dataToFile();
		}
	}

	cout<<"done cyl."<<endl;

	return 0;
}



