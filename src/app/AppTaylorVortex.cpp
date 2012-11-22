/*
 * AppTaylorVortex.cpp
 * Andreas Bülling, 2012
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

//void setForce(int t, double G, double nu, LBM *lbm);
//void setRho(int t, double u0, double nu, LBM_D2Q9 *lbm);
void updateForce(int t, double G, double nu, double **fx, double **fy, Lattice2D *lm);
//void setVelBdries(int t, double nu, double u0, LBM_D2Q9 *lbm);

int main(){
	int nx = 65, ny = 65, tMax = 50, tMod = 1; int tInit = 64;
	double nu = 0.005;
	cout<<"nu: "<<nu<<endl;
	double w = 1.0/(3*nu + 0.5);
    cout<<"omega: "<<w<<endl;
	double c = 1.0;//DX/DT;
	double u0 = sqrt(0.001);//sqrt(0.001);
	double G = u0*u0;
	//u0 *= DT/DX;
	cout<<"u0: "<<u0<<endl;
	cout<<"Taylor vortex flow..."<<endl;

	StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
	CollisionD2Q9BGKShanChenForce *cm = new CollisionD2Q9BGKShanChenForce();
	Lattice2D *lm = new Lattice2D(nx, ny);

	LBM *lbm = new LBM(lm, cm, sm);

	double **fx = allocate2DArray(nx, ny);
	double **fy = allocate2DArray(nx, ny);
	cm->setForce(fx, fy);
//	double **uxInit = new double*[nx];
//	double **uyInit = new double*[nx];
//	double **rhoInit = new double*[nx];
//	for(int i = 0; i < ny; i++){
//		uxInit[i] = new double[ny];
//		uyInit[i] = new double[ny];
//		rhoInit[i] = new double[ny];
//	}
//
//	double x, y;
//	for(int i = 0; i < nx; i++){
//		x = (((double)i)/(nx))*2*M_PI;
//		cout<<"cos: "<<cos(x)<<endl;
//		for(int j = 0; j < ny; j++){
//			y = (((double)j)/(ny))*2*M_PI;
//			uxInit[i][j] = -u0*cos(x)*sin(y);
//			uyInit[i][j] = u0*sin(x)*cos(y);
//			rhoInit[i][j] = 1.0 - u0*u0/4.0*(cos(2*x) + cos(2*y))*3;
//		}
//	}

	/* Initialize solver */

	cm->setW(w);
	cm->setC(c);
	//lbm->initVelocity(uxInit, uyInit);
	//lbm->initRho(rhoInit);
	lbm->init();
	//lbm->calcMacroscopicVars();
	//lbm->handleWetBoundaries();
	//lbm->dataToFile();

	/*init...*/
    updateForce(0, G, nu, fx, fy, lm);

	for(int t = 1; t < tInit; t++){
        lbm->collideAndStream();
    }

    cm->dataToFile("vis_scripts/dataNS0/");

	 stringstream ss;
     string base = "vis_scripts/data";
	/* Main loop */
	for(int t = 1; t < tMax; t++){
		cout<<t<<endl;
		updateForce(t, G, nu, fx, fy, lm);

		lbm->collideAndStream();

		if(t % tMod == 0){
		    ss.str("");
		    ss<<base<<"NS";
		    ss<<t/tMod<<"/";
		    createDirectory(ss.str());
		    cm->dataToFile(ss.str());
		}
	}

	cout<<"done T.-V."<<endl;

	return 0;
}

//void setRho(int t, double u0, double nu, LBM_D2Q9 *lbm){
//	cout<<"setting rho"<<endl;
//	double **rho = lbm->getRho();
//	int nx = lbm->getNx();
//	int ny = lbm->getNy();
//	double x, y;
//	double k1 = 1; double k2 = 1;
//
//	for(int i = 0; i < nx; i++){
//		x = (((double)i)/(nx))*2*M_PI;
//		cout<<"x: "<<x<<", exp(-4nut): "<<exp(-4*nu*t)<<endl;
//		for(int j = 0; j < ny; j++){
//			y = (((double)j)/(ny))*2*M_PI;
//			//rho[i][j] = 1.0 - u0*u0/4.0*(cos(2*x) + cos(2*y))*3*exp(-4*nu*t);
//			//cout<<"fx: "<<fx<<", fy: "<<fy<<endl;
//		}
//	}
//
//}

void updateForce(int t, double G, double nu, double **fx, double **fy, Lattice2D *lm){
	cout<<"calcing force..."<<endl;
	//double **rho = lbm->getRho();
	int nx = lm->n.x;
	int ny = lm->n.y;
	double x, y;
	double k1 = 1.0; double k2 = 1.0;

	for(int i = 0; i < nx; i++){
		x = (((double)i)/(nx-1))*2*M_PI;
		//cout<<"x: "<<x<<", exp(-4nut): "<<exp(-4*nu*t)<<endl;
		for(int j = 0; j < ny; j++){
			y = (((double)j)/(ny-1))*2*M_PI - M_PI/2;
			//cout<<"y: "<<y<<", exp(-4nut): "<<exp(-4*nu*t)<<endl;

			fx[j][i] = -1*G*0.5*sin(x)*sin(y)*exp(-4*nu*t);
			fy[j][i] = -1*G*0.5*cos(x)*cos(y)*exp(-4*nu*t);
		}
	}
    cout<<"fX: "<<fx[15][15]<<endl;
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
