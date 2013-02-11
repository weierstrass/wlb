/*
 * GeneralCol.cpp - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#include <iostream>
#include "../../src/LBM.h"

using namespace std;

int main(){
	cout << "General collision model test" << endl;

	CollisionBGKNS *cm = new CollisionBGKNS();
	LatticeModel *lm = new Lattice2D(16, 4);
	StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
	LBM *lbm = new LBM(lm ,cm, sm);
	lbm->init();

	for(int t = 0; t < 100; t++){
		lbm->collideAndStream();
	}

	return 0;
}



