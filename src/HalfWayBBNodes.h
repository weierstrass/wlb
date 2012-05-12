/*
 * HalfWayBBNodes.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef HALFWAYBBNODES_H_
#define HALFWAYBBNODES_H_

#include <iostream>
#include "BoundaryNodes.h"

class HalfWayBBNodes: public BoundaryNodes{
public:
	HalfWayBBNodes(int nx, int ny);
	virtual ~HalfWayBBNodes();
	void updateF(double ***f);
private:

};

#endif /* HALFWAYBBNODES_H_ */
