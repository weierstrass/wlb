/*
 * AppLPMTest.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include <iostream>
#include "../LBM.h"

using namespace std;

int main(){
	int nx = 256, ny = 8, tMax = 2000;
	cout<<"LPM test.."<<endl;

	CollisionD2Q9LPMChai *cm = new CollisionD2Q9LPMChai();
	cm->setW(0.5);
	cm->setC(1.0);
	StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();//todo
	LatticeModel *lm = new Lattice2D(nx, ny);

	LBM *lbm = new LBM(lm, cm, sm);

	/* Boundaries */
	HeZouPressureNodes *bds = new HeZouPressureNodes();
	//bds->setCollisionModel(cm);
	for(int i = 0; i < ny; i++){
		bds->addNode(0, i, 0, 1.0/1.8);
		bds->addNode(nx-1, i, 0, 1.0/1.8);
	}
	lbm->addBoundaryNodes(bds);

	//NeumannLPMNodes *iobds = new NeumannLPMNodes();
	//iobds->setCollisionModel(cm);
	for(int j = 0; j < ny; j++){
		//iobds->addNode(0, j, 0.0);
		//iobds->addNode(nx-1, j, 0.0);
	}
	//lbm->addBoundaryNodes(iobds);

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		cout<<t<<endl;
		lbm->collideAndStream();
		lbm->handleBoundaries();
	}

	//lbm->calcMacroscopicVars();
	cm->dataToFile();
	cout<<"done LPM."<<endl;

	return 0;
}
