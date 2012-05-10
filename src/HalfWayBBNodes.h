/*
 * HalfWayBBNodes.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef HALFWAYBBNODE_H_
#define HALFWAYBBNODE_H_

#include <iostream>
#include "BoundaryNode.h"

class HalfWayBBNodes{
public:
	HalfWayBBNodes(int nx, int ny);
	virtual ~HalfWayBBNodes();
	void updateF(double ***f);
	void addNode(int i, int j);
private:
	bool **boundries;
	int nx, ny;
};

#endif /* HALFWAYBBNODE_H_ */
