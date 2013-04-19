/*
 * BounceBackNodes.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#ifndef BOUNCEBACKNODES_H_
#define BOUNCEBACKNODES_H_

#include "BoundaryNodes.h"
#include "../col/CollisionD2Q9BGKNSF.h"
#include "../col/CollisionD2Q9BGKNS.h"
#include "../col/CollisionBGKNSF.h"
//#include "../col/CollisionD2Q9BGKShanChenForce.h"
//#include "../col/CollisionD2Q9LNP.h"
//#include "../col/CollisionD2Q9LNPSource.h"
#include "../Aux.h"
#include "../Constants.h"


template <class T>
class BounceBackNodes : public BoundaryNodes{
public:
	BounceBackNodes();
	virtual ~BounceBackNodes();
	void updateF();
	void addNode(int x, int y, int z);
	void setCollisionModel(T *cm){this->cm = cm;};
	void writeNodesToFile();
	T *cm;
protected:
    vector<Node*> nodes;
};

#endif /* BOUNCEBACKNODES_H_ */
