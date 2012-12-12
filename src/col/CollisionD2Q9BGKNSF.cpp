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
    if(rho == NULL) rho = allocate2DArray(lm->n.y, lm->n.x);
    if(ux == NULL) ux = allocate2DArray(lm->n.y, lm->n.x);
    if(uy == NULL) uy = allocate2DArray(lm->n.y, lm->n.x);
    cout<<"mem allocated"<<endl;
    double *rhoUTemp = new double[3];
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            rho[j][i] = get0moment(i, j);
            get1moment(i, j, rhoUTemp);
            ux[j][i] = rhoUTemp[X]/rho[j][i];
            uy[j][i] = rhoUTemp[Y]/rho[j][i];
        }
    }
    cout<<"vals calced"<<endl;
    stringstream ss, ssTemp;
    struct stat sb;
    ss.str("");
    ss<<path;
    if (!stat(ss.str().c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)){
        cout<<"creating directory: "<<ss.str()<<endl;
        mkdir(ss.str().c_str(), 0775);
    }

//    stringstream ss, ssTemp;
//    struct stat sb;
//    for(int i = 0; ; i++){
//        ss.str("");
//        ss<<"vis_scripts/data";
//        ss<<""<<i<<"/";
//        if (!stat(ss.str().c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)){
//            cout<<"creating directory: "<<ss.str()<<endl;
//            mkdir(ss.str().c_str(), 0775);
//            break;
//        }
//    }
    cout<<"lål"<<omp_get_thread_num()<<endl;
    ssTemp.str("");
    ssTemp << ss.str();
    ssTemp << "ux.csv";
    cout<<"lål"<<endl;
    write2DArray(ux, NULL, ssTemp.str(), lm->n.x, lm->n.y);
    ssTemp.str("");
    ssTemp << ss.str();
    ssTemp << "uy.csv";
    cout<<"lål"<<endl;
    write2DArray(uy, NULL, ssTemp.str(), lm->n.x, lm->n.y);
    ssTemp.str("");
    ssTemp << ss.str();
    ssTemp << "rho.csv";
    cout<<"lål"<<endl;
    write2DArray(rho, NULL, ssTemp.str(), lm->n.x, lm->n.y);
}
