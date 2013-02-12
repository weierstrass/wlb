#include <iostream>
#include "../../src/LBM.h"

using namespace std;

int main() {
	cout << "Stream test" << endl;

	CollisionBGKNS *cm = new CollisionBGKNS();
	Lattice2D *lm = new Lattice2D(10, 5);
	Stream *sm = new Stream();

	LBM *lbm = new LBM(lm, cm, sm);

	lbm->init();

	sm->setLatticeModel(lm);
	sm->stream();
	cout << "DIM: " << lm->DIM << endl;

	return 0;
}
