/*
 * BoundaryNodes.h
 *
 *  Created on: 8 maj 2012
 *      Author: andreasbulling
 */

#ifndef BOUNDARYNODE_H_
#define BOUNDARYNODE_H_

#include <iostream>
#include "Constants.h"

using namespace std;

class BoundaryNodes {
public:
	BoundaryNodes(int x, int y);
	virtual ~BoundaryNodes();
	//virtual void updateF(double ***f) = 0;
	void addNode(int i, int j);
protected:
	int nx, ny;
	bool **boundries;
};


#endif /* BOUNDARYNODE_H_ */
