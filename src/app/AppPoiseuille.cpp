/*
 * AppPoiseuille.cpp
 * Poi example...
*/
#include <iostream>
#include "../LBM.h"

using namespace std;

int main(){
	int nx = 128, ny = 32, tMax = 1000;
	cout<<"Poiseuille flow..."<<endl;

	CollisionD2Q9BGK *cm = new CollisionD2Q9BGK();
	cm->setW(1.5);
	cm->setC(1.0);
	StreamD2Q9 *sm = new StreamD2Q9();//todo
	LatticeModel *lm = new Lattice2D(nx, ny);

	LBM *lbm = new LBM(lm, cm, sm);

	/* Add boundary nodes */
	BounceBackNodes *bbns = new BounceBackNodes();
	lbm->addBoundaryNodes(bbns);
	for(int i = 0; i < nx; i++){
		bbns->addNode(i, 0, 0);
		bbns->addNode(i, ny-1, 0);
	}

	/* Set in/outlet conditions*/

	HeZouPressureNodes *cpBdry = new HeZouPressureNodes();
	//ConstantVelocityBoundaryNodes *cvBdry = new ConstantVelocityBoundaryNodes(nx, ny);
	for(int j = 1; j < ny-1; j++){
		cpBdry->addNode(nx-1, j, 0, 1.0);
		cpBdry->addNode(0, j, 0, 1.05);
		//cvBdry->addNode(0, j, poiseuilleVelocity(j, 0, ny-1, 0.15), 0);
		//cvBdry->addNode(nx-1, j, poiseuilleVelocity(j, 0, ny-1, 0.15), 0);
		//cout<<"p: "<<poiseuilleVelocity(j, 0, ny-1, 0.15)<<endl;
	}
	lbm->addBoundaryNodes(cpBdry);
	//lbm->addConstantVelocityBoundaryNodes(cvBdry);

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		cout<<t<<endl;
		lbm->collideAndStream();
		lbm->handleBoundaries();
		//lbm->printu();
		//lbm->handleWetBoundaries();//wet
		//lbm->printu();
		//lbm->printfi(5);
	}

	lbm->calcMacroscopicVars();
	//lbm->dataToFile();
	cout<<"done poi."<<endl;

	return 0;
}
