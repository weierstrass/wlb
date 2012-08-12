/*
 * CollisionModel.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
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
	virtual void collide() = 0;
	virtual void init() = 0;
	void setC(double c);
	void setUnitHandler(UnitHandler *u){unitHandler = u;};
protected:
	LatticeModel *lm;
	UnitHandler *unitHandler;
	struct LatticeModel::dimension n;
	double ****f;
	double c;
};

#endif /* COLLISIONMODEL_H_ */
