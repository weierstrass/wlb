/*
 * CollisionModel.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Distribution function: f[z][y][x][dir].
 */

#include "CollisionModel.h"

CollisionModel::CollisionModel() {
	unitHandler = NULL;
	lm = NULL;
	f = NULL;
	c = 1.0;
    skip = NULL;
}

CollisionModel::~CollisionModel() {
	// Deallocate lm, f, unithandler.
}

void CollisionModel::registerF(double ****f) {
	this->f = f;
}

//Deprecated.. TBR!
void CollisionModel::registerN(struct LatticeModel::dimension &n) {
	this->n = n;
}

void CollisionModel::setC(double c) {
	this->c = c;
}

void CollisionModel::addNodeToSkip(int k, int j, int i) {
	cout << "No collision for node: (" << i << ", " << j << ", " << k << ")."
			<< endl;
	if (skip == NULL) {
		skip = allocate3DArrayT<bool>(lm->n.z, lm->n.y, lm->n.x);
	}
	skip[k][j][i] = true;
}
