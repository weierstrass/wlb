/*
 * Lattice2D.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Lattice class for 2D lattices. (D2Q9)
 */

#include "Lattice2D.h"

#define W0 0.44444444444444444
#define W1 0.11111111111111111
#define W2 0.02777777777777778

const int LatticeModel::oppDirs[] = { 0, 3, 4, 1, 2, 7, 8, 5, 6 };
const int LatticeModel::slipDirsH[] = { 0, 1, 4, 3, 2, 8, 7, 6, 5 };
const int LatticeModel::slipDirsV[] = { 0, 3, 2, 1, 4, 6, 5, 8, 7 };
const double W[] = { W0, W1, W1, W1, W1, W2, W2, W2, W2 };

Lattice2D::Lattice2D(int nx, int ny) {
	cout << "Creating D2Q9 lattice... ";

	int ex[] = { 0, 1, 0, -1, 0, 1, -1, -1, 1 };
	int ey[] = { 0, 0, 1, 0, -1, 1, 1, -1, -1 };

	n.x = nx;
	n.y = ny;
	n.z = 1;
	UDIRS = 9;
	DIM = 2;

	e = new int*[DIM];
	e[0] = new int[UDIRS];
	e[1] = new int[UDIRS];
	for (int d = 0; d < UDIRS; d++) {
		e[0][d] = ex[d];
		e[1][d] = ey[d];
	}
	cout << "done." << endl;
}

Lattice2D::~Lattice2D() {
    delete[] e;
}

