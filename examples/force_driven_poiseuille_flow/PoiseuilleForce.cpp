/*
 * PoiseuilleForce.cpp
 * Andreas Bülling, 2012
 *
 * Simulation of 2D Poisueille flow driven by a constant force.
 *
 */

#include <iostream>
#include "../../src/LBM.h"
#include <math.h>

using namespace std;

int main() {

    omp_set_num_threads(1);

    int nx = 3, ny = 128, nz = 1, tMax = 100000;
    double w = 0.75;
    double c = 1.0;

    double ****force = NULL;
    force = allocate4DArray(2, nz, ny, nx);
    if (isNull(force))
        return 1;

    cout << "Forced Poiseuille flow..." << endl;

    LatticeModel *lm = new Lattice2D(nx, ny);
    StreamPeriodic *sm = new StreamPeriodic();
    CollisionBGKNSF *cm = new CollisionBGKNSF();

    cm->setW(w);
    cm->setC(c);

    LBM *lbm = new LBM(lm, cm, sm);

    /* Set boundary conditions */
    BounceBackNodes<CollisionBGKNSF> *bbns =
            new BounceBackNodes<CollisionBGKNSF>();
    bbns->setCollisionModel(cm);
    for (int i = 0; i < nx; i++) {
        bbns->addNode(i, 0, 0);
        bbns->addNode(i, ny - 1, 0);
    }
    lbm->addBoundaryNodes(bbns);

    /* Set force */
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            force[0][0][j][i] = 0.00001; //X force
        }
    }

    cm->setForce(force);

    /* Initialize solver */
    lbm->init();

    /* Main loop */
    for (int t = 0; t < tMax; t++) {
        //cout<<t<<endl;
        lbm->collideAndStream();
    }

    /* Write result to file */
    OutputCSV<CollisionBGKNSF> *oFile = new OutputCSV<CollisionBGKNSF>(cm, lm);
    oFile->writeData();

    cout << "done." << endl;

    return 0;
}
