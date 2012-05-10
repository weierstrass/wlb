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
	int nx = 600, ny = 101, tMax = 10000;
	cout<<"Cylinder flow..."<<endl;

	LBM_D2Q9 *lbm = new LBM_D2Q9(nx, ny);

	/* Add boundary nodes */
	HalfWayBBNodes *hwbb = new HalfWayBBNodes(nx, ny);
	lbm->addHalfWayBBNodes(hwbb);
	for(int i = 0; i < nx; i++){
		hwbb->addNode(i, 0);
		hwbb->addNode(i, ny-1);
	}
	int xc = nx/4, yc = ny/2;
	double r = 10;
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			if(sqrt((double)((i - xc)*(i - xc) + (j - yc)*(j - yc))) < r){
				hwbb->addNode(i, j);
			}
		}
	}

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		cout<<t<<endl;
		lbm->calcMacroscopicVars();
		lbm->handleBoundaries();//wet
		lbm->BGKCollision();
		lbm->stream();
		lbm->handleHardBoundaries();
	}

	lbm->dataToFile();
	cout<<"done poi."<<endl;

	return 0;
}



