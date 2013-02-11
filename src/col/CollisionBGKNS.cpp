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
	u = NULL;
	rho = 1.0;
}

CollisionBGKNS::~CollisionBGKNS() {
	delete[] u;
}

void CollisionBGKNS::fEq(int k, int j, int i, double *eq){
	rho = get0moment(k, j, i);
	get1moment(k, j, i, u);
	fEq(eq);
}

void CollisionBGKNS::fEq(double *eq) {
	double cu, u2 = 0;
	double rho_inv = 1 / rho;
	double c2inv = 1.0 / c * c;

	for(int l = 0; l < lm->DIM; l++){
		u[l] *= rho_inv;
		u2 += u[l]*u[l];
	}

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
