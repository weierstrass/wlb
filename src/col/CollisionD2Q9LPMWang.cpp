/*
 * CollisionD2Q9LPMWang.cpp
 * Andreas B�lling, 2012
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9LPMWang.h"

CollisionD2Q9LPMWang::CollisionD2Q9LPMWang() {
	// TODO Auto-generated constructor stub

}

CollisionD2Q9LPMWang::~CollisionD2Q9LPMWang() {
	// TODO Auto-generated destructor stub
}

void CollisionD2Q9LPMWang::collide(){
	cout<<"WANG"<<endl;
	double dQ;

	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x; i++){
			psi[j][i] = getPsi(f[0][j][i], i, j);
			dQ = (1 - 0.5*w)*g_rhs(i, j);
			for(int d = 0; d < 9; d++){
				f[0][j][i][d] += w*( fEq(d, psi[j][i]) - f[0][j][i][d] ) + W[d]*dQ;
			}
			psi[j][i] = getPsi(f[0][j][i], i, j);
		}
	}
}

void CollisionD2Q9LPMWang::init(){
	psi = allocate2DArray(n.y, n.x);
	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x; i++){
			psi[j][i] = 0.0;
			for(int d = 0; d < 9; d++) f[0][j][i][d] = fEq(d, psi[j][i]);
		}
	}
}

double CollisionD2Q9LPMWang::getPsi(double *fIn, int i, int j){
	double ret = 0;
	for(int d = 0; d < 9; d++){
		ret += fIn[d] + 0.5*g_rhs(i, j)*W[d];
	}
	return ret;
}

double CollisionD2Q9LPMWang::fEq(int d, double psi){
	return Wa[d]*psi;
}
