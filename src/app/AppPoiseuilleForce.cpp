/*
 * AppPoiseuilleForce.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include <iostream>
#include "../LBM_D2Q9.h"
#include <math.h>

using namespace std;

int main(){
	int nx = 20, ny = 20, tMax = 50000, writeMod = 1000;
	double w = 1.1, c = 1.0;
	double f0 = 0.0010641;
	cout<<"Forced poiseuille flow..."<<endl;
	LBM_D2Q9 *lbm = new LBM_D2Q9(nx, ny);

	/* Set force */
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			if(j < ny/2){
				lbm->setF(f0, 0, i, j);
			}else{
				lbm->setF(-f0, 0, i, j);
			}
		}
	}

	/* Initialize solver */
	lbm->init();
	StreamModel *ps = new PeriodicStreamModel(nx, ny);
	lbm->setStreamModel(ps);
	lbm->setW(w);
	lbm->setC(c);

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
