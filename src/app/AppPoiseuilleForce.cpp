/*
 * AppPoiseuilleForce.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include <iostream>
#include "../LBM.h"
#include <math.h>

using namespace std;

int main(){
	int nx = 3, ny = 50, tMax = 20000;
	double w = 0.75;
	double c = 1.0;

	double **fx = allocate2DArray(ny, nx);
    double **fy = allocate2DArray(ny, nx);

	cout<<"Forced poiseuille flow..."<<endl;
	LatticeModel *lm = new Lattice2D(nx, ny);
	StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
	CollisionD2Q9BGKNSF *cm = new CollisionD2Q9BGKNSF();

    cm->setW(w);
    cm->setC(c);

	LBM *lbm = new LBM(lm, cm, sm);

	/* Set boundary conditions*/
	BounceBackNodes<CollisionD2Q9BGKNSF> *bbns =
	        new BounceBackNodes<CollisionD2Q9BGKNSF>();
	bbns->setCollisionModel(cm);
	for(int i = 0; i < nx; i++){
        bbns->addNode(i, 0, 0);
        bbns->addNode(i, ny-1, 0);
	}
	lbm->addBoundaryNodes(bbns);

	/* Set force */
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
		    fx[j][i] = 0.0001;
		    fy[j][i] = 0.0;
		}
	}
    cm->setForce(fx, fy);

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		cout<<t<<endl;
		lbm->collideAndStream();
	}

	cm->dataToFile("vis_scripts/bench_force_poi/");
	cout<<"done cyl."<<endl;

	return 0;
}
