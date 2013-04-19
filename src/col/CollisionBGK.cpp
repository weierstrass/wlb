/*
 * CollisionBGK.cpp - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#include "CollisionBGK.h"

CollisionBGK::CollisionBGK() {
	w = 1.0;
	wInv = 1.0;
	eq = NULL;
}

CollisionBGK::~CollisionBGK() {
	delete[] eq;
}

void CollisionBGK::collide() {
	//cout << "General BGK collision..." << endl;
	if (isNull(eq))
		return;

	for (int k = 0; k < lm->n.z; k++) {
		for (int j = 0; j < lm->n.y; j++) {
			for (int i = 0; i < lm->n.x; i++) {

				if (skip != NULL && skip[k][j][i])
					continue;

				fEq(k, j, i, eq);
				for (int d = 0; d < lm->UDIRS; d++) {
					//cout << "eq[d]: " << eq[d] << endl;
					f[k][j][i][d] += w * (eq[d] - f[k][j][i][d]);
				}
			}
		}
	}
}

void CollisionBGK::init() {
	if (isNull(lm) || isNull(f))
		return;

	eq = new double[lm->UDIRS];

	for (int k = 0; k < lm->n.z; k++) {
		for (int j = 0; j < lm->n.y; j++) {
			for (int i = 0; i < lm->n.x; i++) {
				for (int d = 0; d < lm->UDIRS; d++) {
					f[k][j][i][d] = lm->W[d];
					//cout<<"wd: "<<	f[k][j][i][d]<<endl;
				}
			}
		}
	}
}

double CollisionBGK::get0moment(int k, int j, int i) {
	double ret = 0;
	for (int d = 0; d < lm->UDIRS; d++)
		ret += f[k][j][i][d];
	return ret;
}

void CollisionBGK::get1moment(int k, int j, int i, double *ret) {
	for (int l = 0; l < lm->DIM; l++) {
		ret[l] = 0;
		for (int d = 0; d < lm->UDIRS; d++) {
			ret[l] += f[k][j][i][d] * lm->e[l][d];
		}
	}
}

