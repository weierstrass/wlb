/*
 * AppHelmholtzWang.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#define SCALE_BDRY 1.0
#define YBDR(Y) sinh(mu*(1 - ((double)Y)/(ny-1)))/sinh(mu)/SCALE_BDRY

#include <iostream>
#include <math.h>
#include "../LBM.h"

using namespace std;

int main(){
	cout<<"LPM Wang Helmholtz..."<<endl;

	int nx = 101;
	int ny = 101;
	int tMax = 5000;
	double l0 = 1;
	double V0 = 1;
	double lambda = 2.0;
	double dt = 1.0/(nx-1)/(nx-1);
	double dx = 1.0/(nx-1);
	double c = dx/dt;
	double omega = 1.0/(1.5*dt/dx/dx + 0.5);

	cout<<"dx: "<<dx<<", dt: "<<dt<<endl;
	cout<<"OMEGA: "<<omega<<endl;

	CollisionD2Q9WangHelmholtz *cm = new CollisionD2Q9WangHelmholtz();
	UnitHandlerLPM *uh = new UnitHandlerLPM();
	StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();//todo
	LatticeModel *lm = new Lattice2D(nx, ny);
	LBM *lbm = new LBM(lm, cm, sm);

	cm->setW(omega);
	cm->setC(c);
	cm->setUnitHandler(uh);
	cm->setLambda(lambda);
	uh->setCharLength(l0);
	uh->setCharVoltage(V0);
	uh->setTimeStep(dt);

	/* Boundaries */
	double mu = sqrt(lambda*lambda + M_PI*M_PI);

	DirichletLPMNodes<CollisionD2Q9WangHelmholtz> *bds =
				new DirichletLPMNodes<CollisionD2Q9WangHelmholtz>();
	bds->setCollisionModel(cm);
	for(int i = 0; i < nx; i++){
		bds->addNode(i, 0, cos(M_PI/(nx-1)*i)/SCALE_BDRY);
		cout<<cos(M_PI/(nx-1)*i)<<endl;
		bds->addNode(i, ny-1, 0.0);
	}
	for(int j = 1; j < ny-1; j++){//no redundancy on corners..
		bds->addNode(0, j, YBDR(j));
		bds->addNode(nx-1, j, -YBDR(j));
	}

	lbm->addBoundaryNodes(bds);

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		cout<<t<<endl;
		lbm->collideAndStream();
		lbm->handleBoundaries();
	}

	cm->dataToFile();
	cout<<"done LPM."<<endl;

	return 0;
}
