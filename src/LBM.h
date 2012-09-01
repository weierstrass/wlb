/*
 * LBM-D2Q9.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 */

#ifndef LBM_H_
#define LBM_H_


#include <iostream>
#include <list>
#include <string.h>
#include <sstream>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>

#include "Constants.h"
#include "Aux.h"

#include "bdr/BoundaryNodes.h"
#include "bdr/HalfWayBBNodes.h"
#include "bdr/Node.h"
#include "bdr/NodeNeighbors.h"
#include "bdr/BounceBackNodes.h"
#include "bdr/HeZouPressureNodes.h"
#include "bdr/DirichletLPMNodes.h"
#include "bdr/NeumannLPMNodes.h"
#include "bdr/HeZouLPMChaiNodes.h"
#include "bdr/SlipNodes.h"
//#include "BFLBoundaryNodes.h"
//#include "ConstantPressureBoundaryNodes.h"
//#include "ConstantVelocityBoundaryNodes.h"

#include "str/StreamModel.h"
//#include "str/PeriodicStreamModel.h"
//#include "str/DefaultStreamModel.h"
#include "str/StreamD2Q9.h"
#include "str/StreamD2Q9Periodic.h"

#include "col/CollisionModel.h"
#include "col/CollisionD2Q9.h"
#include "col/CollisionD2Q9BGK.h"
#include "col/CollisionD2Q9BGKShanChenForce.h"
#include "col/CollisionD2Q9LPM.h"
#include "col/CollisionD2Q9LPMChai.h"
#include "col/CollisionD2Q9LPMChaiRHS.h"
#include "col/CollisionD2Q9WangHelmholtz.h"
#include "col/CollisionD2Q9LPMChaiHelmholtz.h"
#include "col/CollisionD2Q9LPMWang1to1.h"
#include "col/CollisionD2Q9LPMChai1to1.h"
#include "col/CollisionD2Q9LNP.h"
#include "col/CollisionD2Q9LNPSource.h"

#include "lat/Lattice2D.h"
#include "lat/LatticeModel.h"

#include "unit/UnitHandler.h"
#include "unit/UnitHandlerLPM.h"
#include "unit/UnitHandlerNS.h"

using namespace std;


class LBM{
private:
	int nx;
	int ny;
	double ****f;
	//double ***rho;
	//double ***ux;
	//double ***uy;
	//double ***uz;
	//bool **deadNodes;
	//HalfWayBBNodes *hwbbNodes;
	vector<BoundaryNodes*> boundaryNodes;
	//BFLBoundaryNodes *bflNodes;
	//ConstantPressureBoundaryNodes *cpNodes;
	//ConstantVelocityBoundaryNodes *cvNodes;
	StreamModel *streamModel;
	CollisionModel *collisionModel;
	LatticeModel *latticeModel;
public:
	LBM(LatticeModel *lm, CollisionModel *c, StreamModel *sm);
	void init();

	void handleBoundaries();
	void addBoundaryNodes(BoundaryNodes *bn);

	void setStreamModel(StreamModel *s);
	void setCollisionModel(CollisionModel *cm);
	void setLatticeModel(LatticeModel *lm);

	void collideAndStream();
};

#endif /* LBM_H_ */
