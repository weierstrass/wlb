/*
 * BoundaryNode.h
 *
 *  Created on: 8 maj 2012
 *      Author: andreasbulling
 */

#ifndef BOUNDARYNODE_H_
#define BOUNDARYNODE_H_

#include <iostream>

using namespace std;

class BoundaryNode {
public:
	BoundaryNode(int x, int y);
	virtual ~BoundaryNode();
	void updateF(double ***f);
protected:
	int x, y;
};


#endif /* BOUNDARYNODE_H_ */
