/*
 * CollisionD2Q9.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9.h"


const double CollisionD2Q9::W[9] = {W0, W1, W1, W1, W1, W2, W2, W2, W2};

CollisionD2Q9::CollisionD2Q9() :CollisionModel() {
}

CollisionD2Q9::~CollisionD2Q9() {
	// TODO Auto-generated destructor stub
}

double CollisionD2Q9::fEq(int d, double rho, double ux, double uy){
    //cout<<"orig"<<endl;
	double cu = lm->ex[d]*ux + lm->ey[d]*uy;
	double c2 = c*c;
	double u2 = ux*ux + uy*uy;
	return W[d]*rho*(1 + 3.0/c2*(cu) \
					   + 4.5/(c2*c2)*(cu*cu) \
				       - 1.5/c2*u2);
}

double CollisionD2Q9::getRho(double *f){
	double rho = 0;
	for(int i = 0; i < 9; i++) rho += f[i];
	return rho;
}

double *CollisionD2Q9::getRhoU(double *f){
	double *u = new double[3];
	u[X] = f[1] + f[8] + f[5] - (f[3] + f[6] + f[7]);
	u[Y] = f[2] + f[5] + f[6] - (f[7] + f[4] + f[8]);
	u[Z] = -1;
	return u;
}
