/*
 * CollisionD2Q9BGKNS.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9BGKNS.h"

CollisionD2Q9BGKNS::CollisionD2Q9BGKNS() {
    cout<<"allocating u memory"<<endl;
    u = new double[2];
}

CollisionD2Q9BGKNS::~CollisionD2Q9BGKNS() {
    delete[] u;
}

void CollisionD2Q9BGKNS::fEq(int i, int j, double *eq){
    double rho = get0moment(i, j);
    get1moment(i, j, u);
    fEq(rho, u, eq);
}

void CollisionD2Q9BGKNS::fEq(double rho, double *u, double *eq){
    u[X] /= rho;
    u[Y] /= rho;

    double c2inv = 1.0/c*c;
    double u2 = u[X]*u[X] + u[Y]*u[Y];

    for(int d = 0; d < lm->UDIRS; d++){
        double cu = lm->ex[d]*u[X] + lm->ey[d]*u[Y];

        eq[d] = W[d]*rho*(1 + 3.0*c2inv*(cu) \
                + 4.5*(c2inv*c2inv)*(cu*cu) \
                - 1.5*c2inv*u2);
    }
}
