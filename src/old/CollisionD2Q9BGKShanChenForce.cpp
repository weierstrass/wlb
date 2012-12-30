/*
 * CollisionD2Q9BGKShanChenForce.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9BGKShanChenForce.h"

CollisionD2Q9BGKShanChenForce::CollisionD2Q9BGKShanChenForce() {
}

CollisionD2Q9BGKShanChenForce::~CollisionD2Q9BGKShanChenForce() {
    // TODO Auto-generated destructor stub
}
void CollisionD2Q9BGKShanChenForce::collide(){
   // cout<<"D2Q9 BGK SC collision"<<endl;

    double rho;
    double *rhoU = new double[3];
    for(int j = 0; j < n.y; j++){
        for(int i = 0; i < n.x; i++){
            if(skip != NULL && skip[j][i]) continue;
            rho = getRho(f[0][j][i]);
            rhoU = getRhoUEq(f[0][j][i], fx[j][i], fy[j][i]);
            for(int d = 0; d < 9; d++){
                f[0][j][i][d] += w*( fEq(d, rho, rhoU[X]/rho, rhoU[Y]/rho) - f[0][j][i][d] );
                //cout<<"d: "<<d<<", rho: "<<rho<<", rhoU: "<<rhoU<<endl;
            }
        }
    }
    //print2DArray(f[0], n.x, n.y, 4);
}


double*** CollisionD2Q9BGKShanChenForce::getVelocityField(){
    double ***ret = allocate3DArray(2, lm->n.y, lm->n.x);
    double rho;
    double *rhoU;
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            rho = getRho(f[0][j][i]);
            rhoU = getRhoU(f[0][j][i], fx[j][i], fy[j][i]);
            ret[X][j][i] = rhoU[X]/rho;
            ret[Y][j][i] = rhoU[Y]/rho;
        }
    }

    return ret;
}

void CollisionD2Q9BGKShanChenForce::getU(double **ux, double **uy){
    double rho;
    double *rhoU;
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            rho = getRho(f[0][j][i]);
            rhoU = getRhoU(f[0][j][i], fx[j][i], fy[j][i]);
            ux[j][i] = rhoU[X]/rho;
            uy[j][i] = rhoU[Y]/rho;
        }
    }
}

double *CollisionD2Q9BGKShanChenForce::getRhoUEq(double *f, double ffx, double ffy){
    double *u = new double[3];
    u[X] = f[1] + f[8] + f[5] - (f[3] + f[6] + f[7]) + ffx/w;
    u[Y] = f[2] + f[5] + f[6] - (f[7] + f[4] + f[8]) + ffy/w;
    u[Z] = -1;
    return u;
}

double *CollisionD2Q9BGKShanChenForce::getRhoU(double *f, double ffx, double ffy){
    double *u = new double[3];
    u[X] = f[1] + f[8] + f[5] - (f[3] + f[6] + f[7]) + ffx*0.5;
    u[Y] = f[2] + f[5] + f[6] - (f[7] + f[4] + f[8]) + ffy*0.5;
    u[Z] = -1;
    return u;
}

void CollisionD2Q9BGKShanChenForce::init(){
    cout<<"init shan chen..."<<endl;
    //fx = allocate2DArray(lm->n.y, lm->n.x);
    //fy = allocate2DArray(lm->n.y, lm->n.x);

    CollisionD2Q9BGK::init();
}

void CollisionD2Q9BGKShanChenForce::dataToFile(string path){
    if(rho == NULL) rho = allocate2DArray(lm->n.y, lm->n.x);
    if(ux == NULL) ux = allocate2DArray(lm->n.y, lm->n.x);
    if(uy == NULL) uy = allocate2DArray(lm->n.y, lm->n.x);
    cout<<"mem allocated"<<endl;
    double *rhoUTemp = new double[3];
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            rho[j][i] = getRho(f[0][j][i]);
            rhoUTemp = getRhoU(f[0][j][i], fx[j][i], fy[j][i]);
            ux[j][i] = rhoUTemp[X]/rho[j][i];
            uy[j][i] = rhoUTemp[Y]/rho[j][i];
        }
    }
    cout<<"vals calced"<<endl;
    stringstream ss, ssTemp;
    createDirectory(path);
//    struct stat sb;
//    ss.str("");
//    ss<<"vis_scripts/"<<path;
//    if (!stat(ss.str().c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)){
//        cout<<"creating directory: "<<ss.str()<<endl;
//        mkdir(ss.str().c_str(), 0775);
//    }

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
    ssTemp.str("");
    ssTemp << path;
    ssTemp << "ux.csv";
    write2DArray(ux, NULL, ssTemp.str(), lm->n.x, lm->n.y);
    ssTemp.str("");
    ssTemp << path;
    ssTemp << "uy.csv";
    write2DArray(uy, NULL, ssTemp.str(), lm->n.x, lm->n.y);
    ssTemp.str("");
    ssTemp << path;
    ssTemp << "rho.csv";
    write2DArray(rho, NULL, ssTemp.str(), lm->n.x, lm->n.y);
}
