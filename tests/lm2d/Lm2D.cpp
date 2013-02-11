#include <iostream>
#include "../../src/LBM.h"

using namespace std;

int main() {
	cout << "Lattice model 2D test" << endl;


	Lattice2D *lm = new Lattice2D(10, 5);

	cout << "DIM: " << lm->DIM << endl;

	cout << "ex: ";
	for (int d = 0; d < lm->UDIRS; d++) {
		cout << lm->e[0][d] << ",";
	}
	cout << endl;

	return 0;
}
