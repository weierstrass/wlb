/*
 * CollisisonD2Q9AD.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9AD.h"

CollisionD2Q9AD::CollisionD2Q9AD() {
    // TODO Auto-generated constructor stub

}

CollisionD2Q9AD::~CollisionD2Q9AD() {
    // TODO Auto-generated destructor stub
}

void CollisionD2Q9AD::init(){
    cout<<"Initializing AD collision model...";

    rho = allocate2DArray(lm->n.y, lm->n.x);
    cout<<"initC: "<<initC<<endl;
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            rho[j][i] = initC;
            for(int d = 0; d < lm->UDIRS; d++){
                f[0][j][i][d] = fEq(d, initC, 0, 0);
            }
        }
    }

    cout<<" done."<<endl;
}

void CollisionD2Q9AD::collide(){
   // cout<<"D2Q9 AD collision"<<endl;
    updateRho();
    double gamma = PHYS_E_CHARGE*z/( Pe*PHYS_KB*T);
    //cout<<"gamma: "<<gamma<<endl;
    double jx, jy;
    for(int j = 0; j < n.y; j++){
        for(int i = 0; i < n.x; i++){
            //skip the fullway bb nodes..
            if(skip != NULL && skip[j][i]) continue;
            jx = ux[j][i] - gamma*dPsix[j][i];
            jy = uy[j][i] - gamma*dPsiy[j][i];
            //cout<<"jy: "<<jy<<endl;
            //cout<<"uy: "<<uy[j][i]<<endl;
            for(int d = 0; d < 9; d++){
                f[0][j][i][d] += w * ( fEq(d, rho[j][i], jx, jy) - f[0][j][i][d] );
            }
        }
    }
    updateRho();
}

void CollisionD2Q9AD::updateRho(){
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
         //  if(skip != NULL && skip[j][i]) continue;
            rho[j][i] = 0;
            for(int d = 0; d < lm->UDIRS; d++){
                rho[j][i] += f[0][j][i][d];
            }
        }
    }
}

void CollisionD2Q9AD::getFlux(double **jx, double **jy){

    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            jx[j][i] = getXFlux(j, i);
            jy[j][i] = getYFlux(j, i);
        }
    }
}

double CollisionD2Q9AD::getXFlux(int j, int i){
    double ret = 0;
    for(int d = 0; d < lm->UDIRS; d++) ret += f[0][j][i][d]*lm->ex[d];
    return ret;
}

double CollisionD2Q9AD::getYFlux(int j, int i){
    double ret = 0;
    for(int d = 0; d < lm->UDIRS; d++) ret += f[0][j][i][d]*lm->ey[d];
    return ret;
}

double CollisionD2Q9AD::fEq(int d, double rho, double jx, double jy){
    double cu = lm->ex[d]*jx + lm->ey[d]*jy;
    double c2 = c*c;
    double u2 = jx*jx + jy*jy;
    return W[d] * rho * ( 1 + 3.0/c2*(cu) );
    //return W[d] * ( rho + 3.0/c2*(cu) );
}

void CollisionD2Q9AD::dataToFile(string path){
    write2DArray(rho, path, n.x, n.y);
}
