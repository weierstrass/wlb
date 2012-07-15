/*
 * AppLPMTest.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include <iostream>
#include "../LBM.h"

using namespace std;

int main(){
	cout<<"LPM Chai test.."<<endl;

	int nx = 8;
	int ny = 65;
	int tMax = 10000;
	double l0 = 1e-5/(ny-1);
	double V0 = -15e-3;
	double dt = 1.0/(ny-1);

	CollisionD2Q9LPMChai1to1 *cm = new CollisionD2Q9LPMChai1to1();
	StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
	LatticeModel *lm = new Lattice2D(nx, ny);
	UnitHandlerLPM *uh = new UnitHandlerLPM();

	uh->setCharLength(l0);
	uh->setCharVoltage(V0);
	uh->setTimeStep(dt);
	cm->setUnitHandler(uh);
	cm->setW(1.0);
	cm->setC(1.0);

	LBM *lbm = new LBM(lm, cm, sm);

	/* Boundaries */
	HeZouLPMChaiNodes *bds = new HeZouLPMChaiNodes();
	bds->setCollisionModel(cm);
	for(int i = 0; i < nx; i++){
		bds->addNode(i, 0, 0, 1.0/1.8);
		bds->addNode(i, ny-1, 0, 1.0/1.8);
	}
	lbm->addBoundaryNodes(bds);

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		cout<<t<<endl;
		lbm->collideAndStream();
		//lbm->handleBoundaries();
	}

	//lbm->calcMacroscopicVars();
	cm->dataToFile();
	cout<<"done LPM."<<endl;

	return 0;
}
