/*
 * CollisionModel.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Abstract mother class for collision operators.
 */

#include "CollisionModel.h"

CollisionModel::CollisionModel() {
	unitHandler = NULL;
	lm = NULL;
}

CollisionModel::~CollisionModel() {
	// TODO Auto-generated destructor stub
}
//
void CollisionModel::registerF(double ****f){
	this->f = f;
}
//
void CollisionModel::registerN(struct LatticeModel::dimension &n){
	this->n = n;
}

void CollisionModel::setC(double c){
	this->c = c;
}
