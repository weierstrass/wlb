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
	//double *rhoU = new double[3];
	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x; i++){
			//cout<<"pre:"<<i<<","<<j<<endl;
			for(int d = 0; d < 9; d++){
				//cout<<"pre:"<<i<<","<<j<<", f: "<<f[0][j][i][d]<<endl;
				f[0][j][i][d] += w*( fEq(d, psi[j][i]) - f[0][j][i][d] ) - (0.5 - 1.0/w)/3.0*Wa[d]*g_rhs(i, j);
				//cout<<"aadasd: "<< (0.5 - 1.0/w)/3.0*Wa[d]*g_rhs(i, j)<<endl;
				//cout<<"post"<<i<<","<<j<<", f: "<<f[0][j][i][d]<<endl;
				//cout<<"aaa: "<<(1 - 0.5*w)*W[d]*g_rhs(i, j)<<endl;
				//cout<<"W: "<<W[d]<<endl;
			}
			//cout<<"w:"<<w<<endl;
			//cout<<"g: "<<g_rhs(i, j)<<endl;
			psi[j][i] = getPsi(f[0][j][i], i, j);
			//cout<<"psi: "<<psi[j][i]<<endl;
		}
	}
}

double CollisionD2Q9LPMChai::getPsi(double *f, int i, int j){
	//cout<<"W:"<<Wa[1]<<endl;
	double ret = 0;
	for(int d = 1; d < 9; d++) ret += f[d];
	return 1/(1 - W[0])*ret;
}

double CollisionD2Q9LPMChai::fEq(int d, double psi){
	if(d == 0) return (W[0] - 1)*psi;
	return W[d]*psi;
}

double CollisionD2Q9LPMChai::g_rhs(int i, int j){
	//cout<<"olalal"<<endl;
	return CollisionD2Q9LPM::g_rhs(i, j);
}
