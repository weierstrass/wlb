/*
 * Lattice2D.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "Lattice2D.h"

Lattice2D::Lattice2D(int nx, int ny){
	// TODO Auto-generated constructor stub
	cout<<"lattice D2Q9"<<endl;
	cout<<"aakaka"<<endl;
	n.x = nx;
	cout<<"aaaaa"<<endl;
	n.y = ny;
	n.z = 1;
	UDIRS = 9;
	DIM = 2;
	cout<<"cotfl"<<endl;
	int oppTemp[] = {0, 3, 4, 1, 2, 7, 8, 5, 6};
	int exTemp[] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
	int eyTemp[] = {0, 0, 1, 0, -1, 1, 1, -1, -1};
	//int ezTemp[] = {0};
	cout<<"omg"<<endl;
	oppDirs = new int[UDIRS];
	ex = new int[UDIRS];
	ey = new int[UDIRS];
	cout<<"aa"<<endl;
	memcpy(oppDirs, oppTemp, UDIRS*sizeof(int));
	cout<<"aa"<<endl;
	//memcpy(ex, exTemp, UDIRS*sizeof(int));
	cout<<"aa"<<endl;
	//memcpy(ey, eyTemp, UDIRS*sizeof(int));
	cout<<"aa"<<endl;
	}

Lattice2D::~Lattice2D() {
	// TODO Auto-generated destructor stub
}

