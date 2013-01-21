/*
 * CollisionModel.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Abstract mother class for collision operators.
 *
 * All children must implement a collide() and init()
 * function, defining the collision rule and
 * the distribution function initialisation
 * respectively.
 */

#ifndef COLLISIONMODEL_H_
#define COLLISIONMODEL_H_

#include "../Constants.h"
#include "../lat/LatticeModel.h"
#include "../unit/UnitHandler.h"

class CollisionModel {
public:
	CollisionModel();
	virtual ~CollisionModel();
	void registerF(double ****f);
	void registerN(struct LatticeModel::dimension &n);
	void registerLatticeModel(LatticeModel *lm){this->lm = lm;};
	void setC(double c);
	void setUnitHandler(UnitHandler *u){unitHandler = u;};
	virtual void collide() = 0;
	virtual void init() = 0;
protected:
	LatticeModel *lm;
	UnitHandler *unitHandler;
	struct LatticeModel::dimension n;
	double ****f;
	double c;
};

#endif /* COLLISIONMODEL_H_ */
