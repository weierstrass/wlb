/*
 * PoiseuilleForce.cpp
 * Andreas Bülling, 2012
 *
 * Simulation of 2D Poisueille flow driven by a constant force.
 *
 */

#include <iostream>
#include "../../src/LBM.h"
#include <math.h>

using namespace std;

int main(){

    omp_set_num_threads(1);

	int nx = 3, ny = 128, tMax = 100000;
	double w = 0.75;
	double c = 1.0;

	double **fx = allocate2DArray(ny, nx);
    double **fy = allocate2DArray(ny, nx);

	cout<<"Forced Poiseuille flow..."<<endl;
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
		    fx[j][i] = 0.00001;
		    fy[j][i] = 0.0;
		}
	}
    cm->setForce(fx, fy);

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		//cout<<t<<endl;
		lbm->collideAndStream();
	}

	//cm->dataToFile("vis_scripts/bench_force_poi/");
	OutputCSV<CollisionD2Q9BGKNSF> *oFile =
			new OutputCSV<CollisionD2Q9BGKNSF>(cm, lm);
	oFile->writeData();

	cout<<"done cyl."<<endl;

	return 0;
}
