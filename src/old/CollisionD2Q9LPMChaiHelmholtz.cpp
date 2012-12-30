/*
 * CollisionD2Q9LPMChaiHelmholtz.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9LPMChaiHelmholtz.h"

#define YBDR(Y) sinh(mu*(1 - ((double)Y)/(n.y-1)))/sinh(mu)
#define SCALE_BDRY 1.0

CollisionD2Q9LPMChaiHelmholtz::CollisionD2Q9LPMChaiHelmholtz() {
	// TODO Auto-generated constructor stub

}

CollisionD2Q9LPMChaiHelmholtz::~CollisionD2Q9LPMChaiHelmholtz() {
	// TODO Auto-generated destructor stub
}

double CollisionD2Q9LPMChaiHelmholtz::g_rhs(int i, int j){
   // cout<<"bajs: "<<lambda*lambda*psi[j][i]<<endl;
	return lambda*lambda*psi[j][i];
}

/* Set boundaries */
void CollisionD2Q9LPMChaiHelmholtz::init(){
	CollisionD2Q9LPMChai::init();
	double mu = sqrt(2*2 + M_PI*M_PI);
//	for(int i = 0; i < n.x; i++){
//		psi[0][i] = cos(M_PI/(n.x-1)*i);
//		psi[n.y-1][i] = 0.0;
//	}
//	for(int j = 1; j < n.y-1; j++){
//		psi[j][0] = YBDR(j);
//		psi[j][n.x-1] = -YBDR(j);
//	}
}
