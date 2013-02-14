#include <iostream>
#include "../../src/LBM.h"

using namespace std;

int main() {
	cout << "D3Q19 lattice test" << endl;

	int nx = 5, ny = 3, nz = 3;
	double t1, t2;

	CollisionBGKNS *cm = new CollisionBGKNS();
	LatticeModel *lm = new LatticeD3Q19(nx, ny, nz);
	StreamPeriodic *sm = new StreamPeriodic();

	LBM *lbm = new LBM(lm, cm, sm);

	lbm->init();

	double ****f = allocate4DArray(nz, ny, nx, lm->UDIRS);

	for (int k = 0; k < nz; k++) {
		for (int j = 0; j < ny; j++) {
			for (int i = 0; i < nx; i++) {
				for (int d = 0; d < lm->UDIRS; d++) {
					f[k][j][i][d] = (i + 1) * (j + 1) * (k + 1);
				}
			}
		}
	}
	sm->setF(f);

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
	cout << "T_old = " << csecond() - t2 << endl;

	cout << "POSTSTREAM: " << endl;
	for (int d = 0; d < lm->UDIRS; d++) {
		print3DArray(f, nx, ny, nz, 0);
		print3DArray(f, nx, ny, nz, d);
	}
//	cout << "DIM: " << lm->DIM << endl;

	return 0;
}
