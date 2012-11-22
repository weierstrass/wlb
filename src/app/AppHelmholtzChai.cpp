/*
 * AppHelmholtzChai.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#define YBDR(Y) sinh(mu*(1 - ((double)Y)/(ny-1)))/sinh(mu)
#define SCALE_BDRY 1/1.8

#include <iostream>
#include <math.h>
#include "../LBM.h"

using namespace std;

int main(){
	cout<<"LPM Chai Helmholtz..."<<endl;
	int nx = 65;
	int ny = 65;
	int tMax = 20000;
	double lambda = 2.0;
	double dt = 1.0/(nx-1);

	CollisionD2Q9LPMChaiHelmholtz *cm = new CollisionD2Q9LPMChaiHelmholtz();
	UnitHandlerLPM *uh = new UnitHandlerLPM();
	StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
	LatticeModel *lm = new Lattice2D(nx, ny);
	LBM *lbm = new LBM(lm, cm, sm);

	cm->setW(1.0);
	cm->setC(1.0);
	cm->setUnitHandler(uh);
	cm->setLambda(lambda);
	uh->setTimeStep(dt);

	/* Boundaries */
	double mu = sqrt(lambda*lambda + M_PI*M_PI);
	cout<<"mu: "<<mu<<endl;

	HeZouLPMChaiNodes *bds = new HeZouLPMChaiNodes();
	bds->setCollisionModel(cm);
	for(int i = 0; i < nx; i++){
	    bds->addNode(i, 0, 0, cos(M_PI/(nx-1)*i)*SCALE_BDRY);
	    cout<<"i: "<<i<<"bdr: "<<cos(M_PI/(nx-1)*i)*SCALE_BDRY<<endl;
	    bds->addNode(i, ny-1, 0, 0.0);
	}
	for(int j = 1; j < ny-1; j++){
	    bds->addNode(0, j, 0, YBDR(j)*SCALE_BDRY);
	    bds->addNode(nx-1, j, 0, -YBDR(j)*SCALE_BDRY);
	}

	lbm->addBoundaryNodes(bds);
	bds->init();

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		cout<<t<<endl;
		lbm->collideAndStream();
		//lbm->handleBoundaries();
	}

	cm->dataToFile();
	cout<<"done LPM."<<endl;

	return 0;
}
