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

	int nx = 3;
	int ny = 128;
	int tMax = 5000;
	double l0 = 1e-5/(ny-1);
	double V0 = -100e-3;
	double dt = 1.0;
    double T = 273; //temperature [K]
    double cinf = 1e-4; //ion concentration at inf. [Mol]
    double epsilon = 80*PHYS_EPS0; //absolute permittivity [F/m]

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
	cm->setPermittivity(epsilon);
	cm->setTemperature(T);
	cm->setInfConcentration(cinf);

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
	bds->init();

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
