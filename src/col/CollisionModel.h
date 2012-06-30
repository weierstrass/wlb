/*
 * CollisionModel.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef COLLISIONMODEL_H_
#define COLLISIONMODEL_H_

#include "../Constants.h"
#include "../lat/LatticeModel.h"

class CollisionModel {
public:
	CollisionModel();
	virtual ~CollisionModel();
	void registerF(double ****f);
	//void registerU(double ***u);
	//void registerRho(double **rho);
	void registerN(struct LatticeModel::dimension &n);
	void registerLatticeModel(LatticeModel *lm){this->lm = lm;};
	//void registerUDIRS(int ud);
	//void registerParams(double c, double w);
	virtual void collide() = 0;
	//virtual double fEq(int d, int j, int d) = 0;
	virtual void init() = 0;
	virtual double getRho(double *f) = 0;
	virtual double *getRhoU(double *f) = 0;
	//int UDIRS;
	void setC(double c);
protected:
	LatticeModel *lm;
	struct LatticeModel::dimension n;
	double ****f;
	//double ***u;
	//double **rho;
	double c;
	//ForceModel *f;
};

#endif /* COLLISIONMODEL_H_ */
