/*
 * CollisionD2Q9LPMChai.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9LPMChai.h"

CollisionD2Q9LPMChai::CollisionD2Q9LPMChai() {
	// TODO Auto-generated constructor stub

}

CollisionD2Q9LPMChai::~CollisionD2Q9LPMChai() {
	// TODO Auto-generated destructor stub
}

void CollisionD2Q9LPMChai::collide(){
	UnitHandlerLPM *uh = dynamic_cast<UnitHandlerLPM*>(unitHandler);
	cout<<"Chai collision"<<endl;
	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x; i++){
			psi[j][i] = getPsi(f[0][j][i], i, j);
			for(int d = 0; d < 9; d++){
				f[0][j][i][d] += w*( fEq(d, psi[j][i]) - f[0][j][i][d] ) + (0.5 - 1.0/w)/3.0*Wa[d]*g_rhs(i, j) *
								 uh->getTimeStep() * uh->getTimeStep();
			}
			psi[j][i] = getPsi(f[0][j][i], i, j);
		}
	}
}

/* allocate mem for psi todo not needed... */
void CollisionD2Q9LPMChai::init(){
	psi = allocate2DArray(n.y, n.x);
	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x; i++){
			psi[j][i] = 0.0;
			for(int d = 0; d < 9; d++) f[0][j][i][d] = fEq(d, psi[j][i]);
		}
	}
}

double CollisionD2Q9LPMChai::getPsi(double *f, int i, int j){
	double ret = 0;
	for(int d = 1; d < 9; d++) ret += f[d];
	return 1/(1 - W[0])*ret;
}

double CollisionD2Q9LPMChai::fEq(int d, double psi){
	if(d == 0) return (W[0] - 1)*psi;
	return W[d]*psi;
}
