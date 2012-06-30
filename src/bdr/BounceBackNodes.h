/*
 * BounceBackNodes.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef BOUNCEBACKNODES_H_
#define BOUNCEBACKNODES_H_

#include "BoundaryNodes.h"
#include "../Aux.h"

class BounceBackNodes : public BoundaryNodes{
public:
	BounceBackNodes();
	virtual ~BounceBackNodes();
	void updateF();
	void addNode(int x, int y, int z);
};

#endif /* BOUNCEBACKNODES_H_ */
