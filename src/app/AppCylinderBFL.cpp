/*
 * AppCylinder.cpp
 * Andreas BŸlling, 2012
 * A circular obstacle in the flow.
 */

#include <iostream>
#include "../LBM_D2Q9.h"
#include <math.h>
#define RR(A, B) sqrt((double)((i + A - xc)*(i + A - xc) + (j + B - yc)*(j + B - yc)))

using namespace std;

int main(){
	int nx = 400, ny = 100, tMax = 50000, writeMod = 100;
	double uMaxInlet = 0.1;
	double w = 1.7668;
	int xc = nx/5+1, yc = ny/2+2;
	double r = ny/10+1;

	cout<<"BFL Cylinder flow..."<<endl;
	LBM_D2Q9 *lbm = new LBM_D2Q9(nx, ny);

	/* Set inlet conditions */
	ConstantVelocityBoundaryNodes *cvInlet = new ConstantVelocityBoundaryNodes(nx, ny);
	for(int j = 1; j < ny-1; j++){
		cvInlet->addNode(0, j, poiseuilleVelocity(j, 0, ny-1, uMaxInlet));
	}
	lbm->addConstantVelocityBoundaryNodes(cvInlet);

	/* Set outlet conditions*/
	ConstantPressureBoundaryNodes *cpOutlet = new ConstantPressureBoundaryNodes(nx, ny);
	for(int j = 1; j < ny-1; j++){
		cpOutlet->addNode(nx-1, j, 1.0);
	}
	lbm->addConstantPressureBoundaryNodes(cpOutlet);

	/* Add boundary nodes */
	HalfWayBBNodes *hwbb = new HalfWayBBNodes(nx, ny);
	lbm->addHalfWayBBNodes(hwbb);
	for(int i = 0; i < nx; i++){
		hwbb->addNode(i, 0);
		hwbb->addNode(i, ny-1);
	}

	BFLBoundaryNodes *bfl = new BFLBoundaryNodes(nx, ny);
	lbm->addBFLNodes(bfl);
	double rTemp1, rTemp2, q;
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			rTemp1 = RR(0, 0);
			q = rTemp1 - r;
			//cout<<"i: "<<i<<", j: "<<j<<", q: "<<q<<endl;
			if(rTemp1 >= r){
				q = rTemp1 - r;
				if(RR(1, 0) < r){
					bfl->addNode(i, j, 1, q);
				}
				if(RR(0, -1) < r){
					bfl->addNode(i ,j , 2, q);
				}
				if(RR(-1, 0) < r){
					bfl->addNode(i ,j , 3, q);
				}
				if(RR(0, 1) < r){
					bfl->addNode(i ,j , 4, q);
				}
				if(RR(1, -1) < r){//cheat
					bfl->addNode(i ,j , 5, q / sqrt(2));
				}
				if(RR(-1, -1) < r){//cheat
					bfl->addNode(i ,j , 6, q / sqrt(2));
				}
				if(RR(-1, 1) < r){//cheat
					bfl->addNode(i ,j , 7, q / sqrt(2));
				}
				if(RR(1, 1) < r){//cheat
					bfl->addNode(i ,j , 8, q / sqrt(2));
				}
			}
		}
	}
	/* Add dead nodes */
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			if(sqrt((double)((i - xc)*(i - xc) + (j - yc)*(j - yc))) < r){
				lbm->addDeadNode(i, j);
			}
		}
	}

	/* Initialize solver */
	lbm->init();
	StreamModel *ps = new PeriodicStreamModel(nx, ny);
	lbm->setStreamModel(ps);
	lbm->setW(w);
	lbm->setC(1.0);

	/* Main loop */
	for(int t = 0; t < tMax; t++){
		cout<<t<<endl;
		lbm->calcMacroscopicVars();
		lbm->handleWetBoundaries();//wet
		lbm->BGKCollision();
		lbm->stream();
		lbm->handleHardBoundaries();
		if(t % writeMod == 0){
			lbm->dataToFile();
		}
	}

	cout<<"done cyl."<<endl;

	return 0;
}



