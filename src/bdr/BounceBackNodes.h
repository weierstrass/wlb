/*
 * BounceBackNodes.h
 * Andreas B�lling, 2012
 * DESCRIPTION - TODO
 */

#ifndef BOUNCEBACKNODES_H_
#define BOUNCEBACKNODES_H_

#include "BoundaryNodes.h"
#include "../col/CollisionD2Q9BGK.h"
#include "../col/CollisionD2Q9BGKShanChenForce.h"
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
	T *cm;
};

#endif /* BOUNCEBACKNODES_H_ */
