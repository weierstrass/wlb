/*
 * CollisionD2Q9BGKPE.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9BGKPE.h"

CollisionD2Q9BGKPE::CollisionD2Q9BGKPE() {
    rhs = NULL;

}

CollisionD2Q9BGKPE::~CollisionD2Q9BGKPE() {
    // TODO Auto-generated destructor stub
}

void CollisionD2Q9BGKPE::collide(){
    //cout<<"Chai collision"<<endl;

    CollisionD2Q9BGK::collide();

    for(int j = 0; j < n.y; j++){
        for(int i = 0; i < n.x; i++){

            if(skip != NULL && skip[j][i]) continue;

            for(int d = 0; d < 9; d++){
                f[0][j][i][d] +=  (0.5 - 1.0/w)/3.0*W[d]*rhs[j][i];
            }
        }
    }
}

void CollisionD2Q9BGKPE::fEq(int i, int j, double *eq){
    double rho = get0moment(i, j);
    for(int d = 0; d < lm->UDIRS; d++) eq[d] = W[d]*rho;
}

double CollisionD2Q9BGKPE::g_rhs(int i, int j){
//    cout<<"PE RHS: "<<rhs[j][i]<<endl;
//    if(i == lm->n.x/2 && j == 1){
//        cout<<rhs[j][i]<<endl;
//    }
    return rhs[j][i];
}

void CollisionD2Q9BGKPE::reset(){
    cout<<"Resetting PE solver... ";
    init();
    cout<<"done"<<endl;
}

void CollisionD2Q9BGKPE::getDPsi(double **jx, double **jy){
    double *res = new double[2];

    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            get1moment(i, j, res);
            jx[j][i] = -3.0*res[X];
            jy[j][i] = -3.0*res[Y];
        }
    }
}

void CollisionD2Q9BGKPE::dataToFile(string path){
    if(rho == NULL) rho = allocate2DArray(lm->n.y, lm->n.x);

    cout<<"mem allocated k k k k "<<endl;

    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            rho[j][i] = get0moment(i, j);
        }
    }

    write2DArray(rho, NULL, path, lm->n.x, lm->n.y);
}
