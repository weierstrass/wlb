/*
 * AppMlups.cpp - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#include <iostream>
#include "../LBM.h"

using namespace std;

int main(){
	cout<<"Performance benchmark..."<<endl;
	cout<<"d_size: "<<sizeof(double)<<endl;
	int nx = 5000;
	int ny = 5000;
	int tMax = 100;

	/* Create necessary objects */
	CollisionD2Q9BGKNS *cm = new CollisionD2Q9BGKNS();
	StreamD2Q9 *sm = new StreamD2Q9();
	LatticeModel *lm = new Lattice2D(nx, ny);
	LBM *lbm = new LBM(lm, cm, sm);

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		//cout<<t<<endl;
		lbm->collideAndStream();
	}

	cout<<"DONE"<<endl;
	return 0;
}
