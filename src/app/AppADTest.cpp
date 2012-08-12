/*
 * AppADTest.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */


#include <iostream>
#include <sstream>
#include "../LBM.h"

using namespace std;

int main(){
    cout<<"1D Advection-diffusion test.."<<endl;

    int nx = 8;
    int ny = 200;
    int tMax = 550;
    int tMod = 10;

    double l0 = 1.0;
    double C0 = 1.0;
    double u0 = 1.0e-1;
    double dt = 1.0;

    double D = 1.0e-2;
    double T = 273;
    double Pe = u0*l0/D;
    double w = 1/(1.5/Pe + 0.5);

    double **ux = allocate2DArray(ny, nx);
    double **uy = allocate2DArray(ny, nx);
    double **dPsix = allocate2DArray(ny, nx);
    double **dPsiy = allocate2DArray(ny, nx);
    for(int j = 0; j < ny; j++){
        for(int i = 0; i < nx; i++){
            ux[j][i] = 0;
            uy[j][i] = u0;
            dPsix[j][i] = 0.0;
            dPsiy[j][i] = 0.0;
        }
    }

    CollisionD2Q9LNP *cm = new CollisionD2Q9LNP();
    StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
    LatticeModel *lm = new Lattice2D(nx, ny);

    cout<<"w: "<<w<<endl;
    cm->setW(w);
    cm->setC(1.0);
    cm->setUx(ux);
    cm->setUy(uy);
    cm->setDPsix(dPsix);
    cm->setDPsiy(dPsiy);
    cm->setT(T);
    cm->setPe(Pe);

    LBM *lbm = new LBM(lm, cm, sm);

    /* Boundaries */
    BounceBackNodes<CollisionD2Q9LNP> *bbn =
            new BounceBackNodes<CollisionD2Q9LNP>();
    bbn->setCollisionModel(cm);
    for(int i = 0; i < nx; i++){
        bbn->addNode(i, 0, 0);
        bbn->addNode(i, ny-1, 0);
    }
    lbm->addBoundaryNodes(bbn);

    /* Initialize solver */
    lbm->init();

    /* Main loop */
    stringstream ss;
    string base = "vis_scripts/data";
    for(int t = 0; t < tMax; t++){
        cout<<t<<endl;
        lbm->collideAndStream();
        if(t % tMod == 0){
            ss.str("");
            ss<<base;
            ss<<t/tMod<<"/";
            createDirectory(ss.str());
            ss<<"ni.csv";
            cm->dataToFile(ss.str());
        }
    }

    cout<<"done LNP."<<endl;

    return 0;
}
