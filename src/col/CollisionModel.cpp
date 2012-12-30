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
}

CollisionModel::~CollisionModel() {
	// Deallocate lm, f, unithandler.
}

void CollisionModel::registerF(double ****f){
	this->f = f;
}

//Deprecated.. TBR!
void CollisionModel::registerN(struct LatticeModel::dimension &n){
	this->n = n;
}

void CollisionModel::setC(double c){
	this->c = c;
}
