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
#include "../Aux.h"
#include "../lat/LatticeModel.h"
#include "../unit/UnitHandler.h"

class CollisionModel {
public:
	CollisionModel();
	virtual ~CollisionModel();
	void setC(double c);
	void setLatticeModel(LatticeModel *lm){this->lm = lm;};
	void setUnitHandler(UnitHandler *u){unitHandler = u;};
	void setF(double ****f){this->f = f;};
	virtual void collide() = 0;
	virtual void init() = 0;
	void addNodeToSkip(int k, int j, int i);

	//deprecated to be removed...
	void registerF(double ****f);
	void registerN(struct LatticeModel::dimension &n);
	void registerLatticeModel(LatticeModel *lm){this->lm = lm;};
protected:
	LatticeModel *lm;
	UnitHandler *unitHandler;
	double ****f;
	double c;
    bool ***skip;

	//deprecated to be removed in the future
	struct LatticeModel::dimension n;
};

#endif /* COLLISIONMODEL_H_ */
