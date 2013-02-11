/*
 * HalfWayBBNodes.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#ifndef HALFWAYBBNODES_H_
#define HALFWAYBBNODES_H_

#include <iostream>
#include <vector>
#include "BoundaryNodes.h"
#include "Node.h"
#include "NodeNeighbors.h"

class HalfWayBBNodes: public BoundaryNodes{
public:
	HalfWayBBNodes();
	virtual ~HalfWayBBNodes();
	void updateF();
	void addNode(int x, int y, int z);
protected:
	vector<NodeNeighbors*> nodes;

};

#endif /* HALFWAYBBNODES_H_ */
