/*
 * CollisionBGKNS.cpp - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#include "CollisionBGKNS.h"

CollisionBGKNS::CollisionBGKNS() : CollisionBGK() {
	double c2inv = 1.0 / c * c;
	c1 = 3.0 * c2inv;
	c2 = 4.5 * (c2inv * c2inv);
	c3 = -1.5 * c2inv;
}

CollisionBGKNS::~CollisionBGKNS() {
	// TODO Auto-generated destructor stub
}

void CollisionBGKNS::fEq(int k, int j, int i, double *eq) {
	double rho = get0moment(k, j, i);
	double cu;
	double rho_inv = 1 / rho;
	get1moment(k, j, i, u);

	for(int l = 0; l < lm->DIM; l++){
		u[l] *= rho_inv;
	}

	double c2inv = 1.0 / c * c;
	double u2 = u[X] * u[X] + u[Y] * u[Y];

	for (int d = 0; d < lm->UDIRS; d++) {
		double cu = 0;

		for (int l = 0; l < lm->DIM; l++) {
			cu += lm->e[l][d] * u[l];
		}

		eq[d] = rho * lm->W[d] * (1 + c1 * cu + c2 * cu * cu + c3 * u2);
	}
}

void CollisionBGKNS::init(){
	CollisionBGK::init();
	u = new double[lm->DIM];
}
