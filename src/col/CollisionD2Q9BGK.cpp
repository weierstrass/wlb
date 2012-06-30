/*
 * CollisionD2Q9BGK.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9BGK.h"

CollisionD2Q9BGK::CollisionD2Q9BGK() : CollisionD2Q9(){
	// TODO Auto-generated constructor stub

}

CollisionD2Q9BGK::~CollisionD2Q9BGK() {
	// TODO Auto-generated destructor stub
}

void CollisionD2Q9BGK::collide(){

	//double ***f2 = f[0];
	double rho;
	double *rhoU = new double[3];
	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x; i++){
			rho = getRho(f[0][j][i]);
			rhoU = getRhoU(f[0][j][i]);
			for(int d = 0; d < 9; d++){
				f[0][j][i][d] += w*( fEq(d, rho, rhoU[X]/rho, rhoU[Y]/rho) - f[0][j][i][d] );
				//cout<<"d: "<<d<<", rho: "<<rho<<", rhoU: "<<rhoU<<endl;
			}
		}
	}
}

void CollisionD2Q9BGK::setW(double w){
	cout<<"w: "<<w<<endl;
	this->w = w;
}

double CollisionD2Q9BGK::fEq(int d, double rho, double ux, double uy){
	return CollisionD2Q9::fEq(d, rho, ux, uy);
}

void CollisionD2Q9BGK::init(){
	cout<<"init f: f=f_eq"<<endl;
	double rho;
	double *rhoU;
	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x; i++){
			rho = 1.0;//getRho(f[0][j][i]);
			//rhoU = 0;//getRhoU(f[0][j][i]);
			for(int d = 0; d < 9; d++){
				f[0][j][i][d] = fEq(d, rho, 0, 0);
				//f[0][j][i][d] = i*j;
			}
		}
	}
	print2DArray(f[0], n.x, n.y, 4);
}

