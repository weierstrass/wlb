/*
 * CollisionD2Q9BGKNSF.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9BGKNSF.h"
#include <omp.h>

CollisionD2Q9BGKNSF::CollisionD2Q9BGKNSF() : CollisionD2Q9BGKNS(){
	fx = NULL;
	fy = NULL;
}

CollisionD2Q9BGKNSF::~CollisionD2Q9BGKNSF(){
}

void CollisionD2Q9BGKNSF::fEq(int i, int j, double *eq){
    double rho = get0moment(i, j);
    get1momentEq(i, j, u);
    CollisionD2Q9BGKNS::fEq(rho, u, eq);
}

void CollisionD2Q9BGKNSF::get1moment(int i, int j, double *ret){
    CollisionD2Q9BGK::get1moment(i, j, ret);
    ret[X] += fx[j][i]*0.5;
    ret[Y] += fy[j][i]*0.5;
}

void CollisionD2Q9BGKNSF::get1momentEq(int i, int j, double *ret){
    CollisionD2Q9BGK::get1moment(i, j, ret);
    ret[X] += fx[j][i]/w;
    ret[Y] += fy[j][i]/w;
}

void CollisionD2Q9BGKNSF::dataToFile(string path){
	cerr<<"WARNING: Deprecated - use io/OutputCSV instead!"<<endl;
}
