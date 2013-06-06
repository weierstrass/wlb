/*
 * AppSquareArray.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */


#include <iostream>
#include "../LBM.h"
#include <math.h>

using namespace std;

int main(){
    int nx = 65, ny = 65, tMax = 12000;
    int sd = 32;
    double w = 0.5;
    double c = 1.0;
    double dPdx = 1e-6;

    double **fx = allocate2DArray(ny, nx);
    double **fy = allocate2DArray(ny, nx);

    cout<<"Square array flow..."<<endl;
    LatticeModel *lm = new Lattice2D(nx, ny);
    StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
    CollisionD2Q9BGKShanChenForce *cm = new CollisionD2Q9BGKShanChenForce();

    cm->setW(w);
    cm->setC(c);

    LBM *lbm = new LBM(lm, cm, sm);

    /* Set boundary conditions*/
    BounceBackNodes<CollisionD2Q9BGKShanChenForce> *bbns =
            new BounceBackNodes<CollisionD2Q9BGKShanChenForce>();
    bbns->setCollisionModel(cm);

    //add square
    int start = ((nx-1) - sd)/2;
    for(int i = start; i < start + sd +1; i++){
        bbns->addNode(i, start, 0);
        bbns->addNode(i, ny-1-start, 0);
    }

    for(int i = start + 1; i < start + sd; i++){
        bbns->addNode(start, i, 0);
        bbns->addNode(nx-1-start, i, 0);
    }
    lbm->addBoundaryNodes(bbns);

    /* Set force */
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            fx[j][i] = dPdx;
            fy[j][i] = 0.0;
        }
    }

    /* Initialize solver */
    lbm->init();

    cm->setForce(fx, fy);

    /* Main loop */
    for(int t = 0; t < tMax; t++){
        cout<<t<<endl;
        lbm->collideAndStream();
    }

    cm->dataToFile("vis_scripts/bench_square_array/");
    cout<<"done array."<<endl;

    return 0;
}
