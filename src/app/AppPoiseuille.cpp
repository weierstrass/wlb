/*
 * AppPoiseuille.cpp
 * Poi example...
*/
#include <iostream>
#include "../LBM.h"

using namespace std;

int main(){
    cout<<"Poiseuille flow..."<<endl;
    int nx = 101;
	int ny = 21;
	int tMax = 5000;
	double w = 1.0;
	double c = 1.0;

	CollisionD2Q9BGK *cm = new CollisionD2Q9BGK();
	StreamD2Q9 *sm = new StreamD2Q9();
	LatticeModel *lm = new Lattice2D(nx, ny);
	LBM *lbm = new LBM(lm, cm, sm);

    cm->setW(w);
    cm->setC(c);

	/* Add boundary nodes */
	BounceBackNodes<CollisionD2Q9BGK> *bbns =
	        new BounceBackNodes<CollisionD2Q9BGK>();
	bbns->setCollisionModel(cm);
	for(int i = 0; i < nx; i++){
		bbns->addNode(i, 0, 0);
		bbns->addNode(i, ny-1, 0);
	}
	//bbns->addNode(nx/2, ny/2, 0);
    lbm->addBoundaryNodes(bbns);

	/* Set in/outlet conditions*/
	HeZouPressureNodes *cpBdry = new HeZouPressureNodes();
	for(int j = 1; j < ny-1; j++){
		cpBdry->addNode(nx-1, j, 0, 1.0);
		cpBdry->addNode(0, j, 0, 1.1);
	}
	lbm->addBoundaryNodes(cpBdry);

	/* Initialize solver */
	lbm->init();

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		cout<<t<<endl;
		lbm->collideAndStream();
	}

	//lbm->calcMacroscopicVars();
	cm->dataToFile("bench_poi/");
	cout<<"DONE!"<<endl;

	return 0;
}
