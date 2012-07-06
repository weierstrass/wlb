/*
 * AppLPMTest.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include <iostream>
#include "../LBM.h"

using namespace std;

int main(){
	cout<<"LPM Chai test.."<<endl;

	int nx = 32;
	int ny = 8;
	int tMax = 25000;
	double l0 = 0.8e-6/nx;
	double V0 = -10e-3;

	CollisionD2Q9LPMChai *cm = new CollisionD2Q9LPMChai();
	StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
	LatticeModel *lm = new Lattice2D(nx, ny);
	UnitHandlerLPM *uh = new UnitHandlerLPM();

	uh->setCharLength(l0);
	uh->setCharVoltage(V0);
	cm->setUnitHandler(uh);
	cm->setW(0.5);
	cm->setC(1.0);

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
