/*
 * Lattice2D.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Lattice class for 2D lattices. (D2Q9)
 */

#include "Lattice2D.h"

const int LatticeModel::oppDirs[] = {0, 3, 4, 1, 2, 7, 8, 5, 6};
const int LatticeModel::ex[] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
const int LatticeModel::ey[] = {0, 0, 1, 0, -1, 1, 1, -1, -1};

Lattice2D::Lattice2D(int nx, int ny){
	cout<<"lattice D2Q9"<<endl;
	n.x = nx;
	n.y = ny;
	n.z = 1;
	UDIRS = 9;
	DIM = 2;
}

Lattice2D::~Lattice2D() {
	// TODO Auto-generated destructor stub
}

