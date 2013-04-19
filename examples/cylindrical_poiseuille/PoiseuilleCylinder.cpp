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

	int nx = 3, ny = 101, nz = 101, tMax = 10000;

	double w = 0.75;
	cout<<"W: "<<w<<endl;
	double c = 1.0;

	double ****force = NULL;
	force = allocate4DArray(3, nz, ny, nx);
	if (isNull(force))
		return 1;

	cout << "Forced Poiseuille flow..." << endl;

	LatticeModel *lm = new LatticeD3Q19(nx, ny, nz);
	StreamPeriodic *sm = new StreamPeriodic();
	CollisionBGKNSF *cm = new CollisionBGKNSF();

	cm->setW(w);
	cm->setC(c);

	LBM *lbm = new LBM(lm, cm, sm);

	/* Set boundary conditions */
	BounceBackNodes<CollisionBGKNSF> *bbns =
			new BounceBackNodes<CollisionBGKNSF>();
	bbns->setCollisionModel(cm);

	int r = ny / 2;
	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			for (int k = 0; k < nz; k++) {
				int jp = j - ny / 2;
				int kp = k - nz / 2;
				//cout << jp << ", " << kp << ", " << r << endl;
				if (sqrt(jp * jp + kp * kp) >= r) {
					bbns->addNode(i, j, k);
				}
			}
		}
	}

	lbm->addBoundaryNodes(bbns);

	bbns->writeNodesToFile();

	/* Set force */
	for (int k = 0; k < nz; k++) {
		for (int i = 0; i < nx; i++) {
			for (int j = 0; j < ny; j++) {
				force[0][k][j][i] = 0.00001; //X force
			}
		}
	}

	cm->setForce(force);

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for (int t = 0; t < tMax; t++) {
		cout<<t<<endl;
		lbm->collideAndStream();
	}

	/* Write result to file */
	OutputVTKSP<CollisionBGKNSF> *oFileVTK = new OutputVTKSP<CollisionBGKNSF>(cm,
			lm);
	oFileVTK->writeData();

	OutputCSV<CollisionBGKNSF> *oFileCSV = new OutputCSV<CollisionBGKNSF>(cm,
			lm);
	oFileCSV->writeData();

	cout << "done." << endl;

	return 0;
}
