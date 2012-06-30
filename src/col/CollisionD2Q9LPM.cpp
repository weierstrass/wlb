/*
 * CollisionD2Q9LPM.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9LPM.h"


const double CollisionD2Q9LPM::Wa[9] = {0.0, 1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/12, 1.0/12, 1.0/12, 1.0/12};

CollisionD2Q9LPM::CollisionD2Q9LPM() {
}

CollisionD2Q9LPM::~CollisionD2Q9LPM() {
	// TODO Auto-generated destructor stub
}

void CollisionD2Q9LPM::collide(){
	//double W[9] = {W0, W1, W1, W1, W1, W2, W2, W2, W2};
	//double *rhoU = new double[3];
	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x; i++){
			//cout<<"pre:"<<i<<","<<j<<endl;
			for(int d = 0; d < 9; d++){
				//cout<<"pre:"<<i<<","<<j<<", f: "<<f[0][j][i][d]<<endl;
				f[0][j][i][d] += w*( fEq(d, psi[j][i]) - f[0][j][i][d] ) + (1 - 0.5*w)*W[d]*g_rhs(i, j);//todo
				//cout<<"post"<<i<<","<<j<<", f: "<<f[0][j][i][d]<<endl;
				//cout<<"aaa: "<<(1 - 0.5*w)*W[d]*g_rhs(i, j)<<endl;
				//cout<<"W: "<<W[d]<<endl;
			}
			//cout<<"w:"<<w<<endl;
		//	cout<<"g: "<<g_rhs(i, j)<<endl;
			psi[j][i] = getPsi(f[0][j][i], i, j);
			//cout<<"psi: "<<psi[j][i]<<endl;
		}
	}
}

void CollisionD2Q9LPM::init(){
	double ninf = 1e-4*PHYS_N_A;
	double z = 1.0;
	double eps = 6.95*1e-10;
	double T = 273;
	double k = sqrt(2*ninf*z*z*PHYS_E_CHARGE*PHYS_E_CHARGE/(eps*PHYS_KB*T));

	double l2 = 0.8e-5/n.x; l2 *=l2;
	double V0 = -10e-3;

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

double CollisionD2Q9LPM::g_rhs(int i, int j){
	return -prefactor*sinh(psi[j][i]*inSinh);
}

double CollisionD2Q9LPM::getPsi(double *fIn, int i, int j){
	double ret = 0;
	//cout<<"ffi"<<fIn[1]<<endl;
	for(int d = 0; d < 9; d++){
		ret += fIn[d] + 0.5*g_rhs(i, j)*W[d];
	//	cout<<fIn[d]<<endl;
	}
	return ret;
}

double CollisionD2Q9LPM::fEq(int d, double psi){
	//cout<<"f_eq: "<<Wa[d]*psi<<endl;
	return Wa[d]*psi;
}

void CollisionD2Q9LPM::dataToFile(){
	write2DArray(psi, NULL, "vis_scripts/data0/rho.csv", n.x, n.y);
}
