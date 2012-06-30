/*
 * AppTaylorVortex.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */
#define _USE_MATH_DEFINES
//#define DT ((2*M_PI/65.0)*(2*M_PI/65.0)*8)
//#define DT (2*M_PI/65.0)
//#define DX (2*M_PI/65.0)
#define DX 1.0
#define DT 1.0
//#define K (2*M_PI/65.0)

#include <iostream>
#include "../LBM.h"
#include <math.h>

using namespace std;

void setForce(int t, double G, double nu, LBM_D2Q9 *lbm);
//void setRho(int t, double u0, double nu, LBM_D2Q9 *lbm);

//void setVelBdries(int t, double nu, double u0, LBM_D2Q9 *lbm);

int main(){
	int nx = 65, ny = 65, tMax = 50, writeMod = 1;
	double nu = 0.05;
	nu = nu*DT/(DX*DX); //TODO
	cout<<"nu: "<<nu<<endl;
	double w = 1.0/(3*nu + 0.5);
	double c = 1.0;//DX/DT;
	double u0 = sqrt(0.001);//sqrt(0.001);
	double G = u0*u0;
	//u0 *= DT/DX;
	cout<<"u0: "<<u0<<endl;
	cout<<"Taylor vortex flow..."<<endl;
	LBM_D2Q9 *lbm = new LBM_D2Q9(nx, ny);

	double **uxInit = new double*[nx];
	double **uyInit = new double*[nx];
	double **rhoInit = new double*[nx];
	for(int i = 0; i < ny; i++){
		uxInit[i] = new double[ny];
		uyInit[i] = new double[ny];
		rhoInit[i] = new double[ny];
	}

	double x, y;
	for(int i = 0; i < nx; i++){
		x = (((double)i)/(nx))*2*M_PI;
		cout<<"cos: "<<cos(x)<<endl;
		for(int j = 0; j < ny; j++){
			y = (((double)j)/(ny))*2*M_PI;
			uxInit[i][j] = -u0*cos(x)*sin(y);
			uyInit[i][j] = u0*sin(x)*cos(y);
			rhoInit[i][j] = 1.0 - u0*u0/4.0*(cos(2*x) + cos(2*y))*3;
		}
	}

	/* Initialize solver */
	StreamModel *sm = new PeriodicStreamModel(nx, ny);
	lbm->setStreamModel(sm);
	lbm->setW(w);
	lbm->setC(c);
	lbm->initVelocity(uxInit, uyInit);
	lbm->initRho(rhoInit);
	lbm->init();
	//lbm->calcMacroscopicVars();
	//lbm->handleWetBoundaries();
	lbm->dataToFile();

	/* Main loop */
	for(int t = 1; t < tMax; t++){
		cout<<t<<endl;
	//	setForce(t, G, nu, lbm);
		lbm->BGKCollision();

		lbm->stream();

		lbm->calcMacroscopicVars();

		if(t % writeMod == 0){
			lbm->dataToFile();
		}
	}

	cout<<"done T.-V."<<endl;

	return 0;
}

void setRho(int t, double u0, double nu, LBM_D2Q9 *lbm){
	cout<<"setting rho"<<endl;
	double **rho = lbm->getRho();
	int nx = lbm->getNx();
	int ny = lbm->getNy();
	double x, y;
	double k1 = 1; double k2 = 1;

	for(int i = 0; i < nx; i++){
		x = (((double)i)/(nx))*2*M_PI;
		cout<<"x: "<<x<<", exp(-4nut): "<<exp(-4*nu*t)<<endl;
		for(int j = 0; j < ny; j++){
			y = (((double)j)/(ny))*2*M_PI;
			//rho[i][j] = 1.0 - u0*u0/4.0*(cos(2*x) + cos(2*y))*3*exp(-4*nu*t);
			//cout<<"fx: "<<fx<<", fy: "<<fy<<endl;
		}
	}

}

void setForce(int t, double G, double nu, LBM_D2Q9 *lbm){
	cout<<"calcing force..."<<endl;
	double **rho = lbm->getRho();
	int nx = lbm->getNx();
	int ny = lbm->getNy();
	double fx, fy, x, y;
	double k1 = 1.0; double k2 = 1.0;

	for(int i = 0; i < nx; i++){
		x = (((double)i)/(nx))*2*M_PI;
	//	cout<<"x: "<<x<<", exp(-4nut): "<<exp(-4*nu*t)<<endl;
		for(int j = 0; j < ny; j++){
			y = (((double)j)/(ny))*2*M_PI;
			fx = -1*G*0.5*sin(2*x)*exp(-4*nu*t*DT)*rho[i][j]*DT*DT/DX;//TODO
			fy = -1*G*0.5*sin(2*y)*exp(-4*nu*t*DT)*rho[i][j]*DT*DT/DX; //TODO
			//cout<<"fx: "<<fx<<", fy: "<<fy<<endl;
			lbm->setF(fx, fy, i, j);
		}
	}
}
//
//void setVelBdries(int t, double nu, double u0, LBM_D2Q9 *lbm){
//	int nx = lbm->getNx();
//	int ny = lbm->getNy();
//	double ux, uy, y ,x;
//
//	lbm->clearConstantVelocityBoundaryNodes();
//	ConstantVelocityBoundaryNodes *cvInlet = new ConstantVelocityBoundaryNodes(nx, ny);
//	/* Add corner nodes*/
//	cvInlet->addNode(0, 0, 0, 0);
//	cvInlet->addNode(0, ny-1, 0, 0);
//	cvInlet->addNode(nx-1, 0, 0, 0);
//	cvInlet->addNode(nx-1, ny-1, 0, 0);
//
//	/* Set west/east boundary conditions */
//	for(int j = 1; j < ny-1; j++){
//		y = (((double)j)/(ny-1) - 0.5)*M_PI;
//		uy = -u0*cos(y)*exp(-1*nu*2*t);
//		cvInlet->addNode(0, j, 0, -uy);
//		cvInlet->addNode(nx-1, j, 0, uy);
//	}
//
//	/* Set north/south boundary conditions*/
//	for(int j = 1; j < ny-1; j++){
//		x = (((double)j)/(ny-1) - 0.5)*M_PI;
//		ux = -1*u0*cos(x)*exp(-1*nu*2*t);
//		cvInlet->addNode(j, 0, -ux, 0.0);
//		cvInlet->addNode(j, ny-1, ux, 0.0);
//	}
//	lbm->addConstantVelocityBoundaryNodes(cvInlet);
//}
//
