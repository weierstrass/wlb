/*
 * CollisionModel.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
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
//
//void CollisionModel::registerParams(double c, double w){
//	this->c = c;
//	this->w = w;
//}
//
//void CollisionModel::registerRho(double **rho){
//	//this->rho = rho;
//}
//
//void CollisionModel::registerU(double ***u){
//	//this->u = u;
//}
//
//void CollisionModel::registerUDIRS(int UDIRS){
//	this->UDIRS = UDIRS;
//}

