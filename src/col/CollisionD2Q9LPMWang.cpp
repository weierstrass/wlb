/*
 * CollisionD2Q9LPMWang.cpp
 * Andreas BŸlling, 2012
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
	UnitHandlerLPM *uh = dynamic_cast<UnitHandlerLPM*>(unitHandler);

	double ninf = 1e-4*PHYS_N_A;
	double z = 1.0;
	double eps = 6.95*1e-10;
	double T = 273;
	double k = sqrt(2*ninf*z*z*PHYS_E_CHARGE*PHYS_E_CHARGE/(eps*PHYS_KB*T));

	double l2 = uh->getCharLength();
	cout<<"l2: "<<l2<<endl;
	l2 *=l2;
	double V0 = uh->getCharVoltage();

	prefactor = l2/V0*2*z*PHYS_E_CHARGE*ninf/eps;
	inSinh = z*PHYS_E_CHARGE*V0/PHYS_KB/T;

	cout<<"k: "<<k<<", k^-1: "<<1/k<<endl;
	cout<<"l: "<<sqrt(l2)<<", V0: "<<V0<<endl;
	cout<<"pre: "<<prefactor<<"inSinh"<<inSinh<<endl;

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
