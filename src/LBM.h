/*
 * LBM.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Core class.
 * Couples the lattice, streaming, boundary conditions  and collision operator.
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
#include <omp.h>

#include "Constants.h"
#include "Aux.h"

#include "bdr/BoundaryNodes.h"
#include "bdr/Node.h"
#include "bdr/NodeNeighbors.h"
#include "bdr/BounceBackNodes.h"
#include "bdr/HeZouPressureNodes.h"
#include "bdr/DirichletLPMNodes.h"
#include "bdr/NeumannLPMNodes.h"
#include "bdr/HeZouNodes.h"
#include "bdr/SlipNodes.h"
#include "bdr/NeumannNodesPESlip.h"

#include "str/StreamModel.h"
#include "str/Stream.h"
#include "str/StreamPeriodic.h"
//#include "str/StreamD2Q9.h"
//#include "str/StreamD2Q9Periodic.h"

#include "col/CollisionModel.h"
#include "col/CollisionBGK.h"
#include "col/CollisionBGKNS.h"
#include "col/CollisionBGKNSF.h"

#include "col/CollisionD2Q9.h"
#include "col/CollisionD2Q9BGK.h"
#include "col/CollisionD2Q9AD.h"
#include "col/CollisionD2Q9BGKNS.h"
#include "col/CollisionD2Q9BGKNSF.h"
#include "col/CollisionD2Q9BGKPE.h"

#include "lat/LatticeModel.h"
#include "lat/Lattice2D.h"
#include "lat/LatticeD3Q19.h"

#include "unit/UnitHandler.h"
#include "unit/UnitHandlerLPM.h"
#include "unit/UnitHandlerNS.h"

#include "io/Output.h"
#include "io/OutputCSV.h"
#include "io/OutputVTKSP.h"

using namespace std;

class LBM{
private:
	double ****f; //distribution function, outermost index is for direction
	vector<BoundaryNodes*> boundaryNodes;
	StreamModel *streamModel;
	CollisionModel *collisionModel;
	LatticeModel *latticeModel;
public:
	LBM(LatticeModel *lm, CollisionModel *c, StreamModel *sm);
	void init();

	void addBoundaryNodes(BoundaryNodes *bn);

	void setStreamModel(StreamModel *s);
	void setCollisionModel(CollisionModel *cm);
	void setLatticeModel(LatticeModel *lm);

	void collideAndStream();
};

#endif /* LBM_H_ */
