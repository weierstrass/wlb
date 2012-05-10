/*
 * AppPoiseuille.cpp
 * Poi example...
*/
#include <iostream>
#include "../LBM_D2Q9.h"

using namespace std;

int main(){
	int nx = 256, ny = 32, tMax = 2000;
	cout<<"Poiseuille flow..."<<endl;

	LBM_D2Q9 *lbm = new LBM_D2Q9(nx, ny);

	/* Add boundary nodes */
	HalfWayBBNodes *hwbb = new HalfWayBBNodes(nx, ny);
	lbm->addHalfWayBBNodes(hwbb);
	for(int i = 0; i < nx; i++){
		hwbb->addNode(i, 0);
		hwbb->addNode(i, ny-1);
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
