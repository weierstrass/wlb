#include <iostream>
#include "../../src/LBM.h"

using namespace std;

int main() {
    cout << "D3Q19 lattice test" << endl;

    int nx = 2, ny = 4, nz = 2;
    double t1, t2;

    double ****f = allocate4DArray(nz, ny, nx, 9);
    double ****f2 = allocate4DArray(nz, ny, nx, 9);

    for (int k = 0; k < nz; k++) {
        for (int j = 0; j < ny; j++) {
            for (int i = 0; i < nx; i++) {
                for (int d = 0; d < 9; d++) {
                    f[k][j][i][d] = (i + 1) * (j + 1) * (k + 1);
                    f2[k][j][i][d] = (i + 1) * (j + 1) * (k + 1);
                }
            }
        }
    }
    CollisionBGKNS *cm = new CollisionBGKNS();
    LatticeModel *lm = new LatticeD3Q19(nx, ny, nz);
    StreamPeriodic *sm = new StreamPeriodic();
    StreamD2Q9Periodic *sm2 = new StreamD2Q9Periodic();

    LBM *lbm = new LBM(lm, cm, sm);
    LBM *lbm2 = new LBM(lm, cm, sm2);

    lbm->init();
    lbm2->init();

    sm->setF(f);
    sm2->setF(f2);

    //sm->setLatticeModel(lm);

    cout << "PRESTREAM: " << endl;
    for (int d = 0; d < 2; d++) {
        // print2DArray(f2[0], nx, ny, d);
        //print2DArray(f[0], nx, ny, d);
    }

    t1 = csecond();
    sm->stream();
    cout << "T_new = " << csecond() - t1 << endl;

    t2 = csecond();
    sm2->stream();
    cout << "T_old = " << csecond() - t2 << endl;

    cout << "POSTSTREAM: " << endl;
    for (int d = 0; d < 9; d++) {
        print2DArray(f2[0], nx, ny, 0);
        print2DArray(f2[0], nx, ny, d);
        print2DArray(f[0], nx, ny, d);
    }
//	cout << "DIM: " << lm->DIM << endl;

    return 0;
}
