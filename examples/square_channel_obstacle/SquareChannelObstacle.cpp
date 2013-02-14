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

int main() {

	omp_set_num_threads(1);

	int nx = 100, ny = 20, nz = 20, tMax = 500;
	double w = 0.75;
	double c = 1.0;

	double ****force = NULL;
	force = allocate4DArray(3, nz, ny, nx);
	if (isNull(force))
		return 1;

	cout << "Square channel - obstacle flow..." << endl;

	LatticeD3Q19 *lm = new LatticeD3Q19(nx, ny, nz);
	StreamPeriodic *sm = new StreamPeriodic();
	CollisionBGKNSF *cm = new CollisionBGKNSF();

	cm->setW(w);
	cm->setC(c);

	LBM *lbm = new LBM(lm, cm, sm);

	/* Set boundary conditions */
	BounceBackNodes<CollisionBGKNSF> *bbns =
			new BounceBackNodes<CollisionBGKNSF>();
	bbns->setCollisionModel(cm);

	//the walls
	for (int j = 0; j < ny; j++) {
		for (int i = 0; i < nx; i++) {
			bbns->addNode(i, j, 0);
			bbns->addNode(i, j, nz - 1);
		}
	}

	for (int k = 0; k < nz - 1; k++) {
		for (int i = 0; i < nx; i++) {
			bbns->addNode(i, 0, k);
			bbns->addNode(i, ny - 1, k);
		}
	}

	//the obstacle
	int scale = 0.5;
	for (int k = nz*0.25; k < nz*0.75; k++) {
		for (int j = ny*0.25; j < ny*0.75; j++) {
			bbns->addNode(nx/2, j, k);
			bbns->addNode(nx/2, j, k);
		}
	}
	lbm->addBoundaryNodes(bbns);

	/* Set force */
	for (int k = 0; k < nz; k++) {
		for (int i = 0; i < nx; i++) {
			for (int j = 0; j < ny; j++) {
				force[0][k][j][i] = 0.000001; //X force
			}
		}
	}
	cm->setForce(force);

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for (int t = 0; t < tMax; t++) {
		//cout<<t<<endl;
		lbm->collideAndStream();
	}

	/* Write result to file */
	OutputCSV<CollisionBGKNSF> *oFile = new OutputCSV<CollisionBGKNSF>(cm, lm);
	oFile->writeData();

	cout << "done." << endl;

	return 0;
}
