/*
 * AppLPMTest.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include <iostream>
#include "../LBM.h"

using namespace std;

int main(){
	cout<<"LPM test..."<<endl;

	int nx = 8;
	int ny = 32;
	int tMax = 30000;
	double l0 = 0.8e-6/ny;
	double V0 = -10e-3;

	CollisionD2Q9LPM *cm = new CollisionD2Q9LPM();
	UnitHandlerLPM *uh = new UnitHandlerLPM();
	StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();//todo
	LatticeModel *lm = new Lattice2D(nx, ny);

	cm->setW(0.5);
	cm->setC(1.0);
	cm->setUnitHandler(uh);
	uh->setCharLength(l0);
	uh->setCharVoltage(V0);

	LBM *lbm = new LBM(lm, cm, sm);

	/* Boundaries */
	DirichletLPMNodes *bds = new DirichletLPMNodes();
	bds->setCollisionModel(cm);
	for(int i = 0; i < nx; i++){
		bds->addNode(i, 0, 1.0);
		bds->addNode(i, ny-1, 1.0);
	}
	lbm->addBoundaryNodes(bds);

	NeumannLPMNodes *iobds = new NeumannLPMNodes();
	iobds->setCollisionModel(cm);
	for(int j = 0; j < ny; j++){
		iobds->addNode(0, j, 0.0);
		iobds->addNode(nx-1, j, 0.0);
	}
	lbm->addBoundaryNodes(iobds);

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
