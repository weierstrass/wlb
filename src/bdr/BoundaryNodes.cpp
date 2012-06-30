/*
 * BoundaryNode.cpp
 *
 *  Created on: 8 maj 2012
 *      Author: andreasbulling
 */

#include "BoundaryNodes.h"

BoundaryNodes::BoundaryNodes() {
}

void BoundaryNodes::addNode(Node *n){
	nodes.push_back(n);
}

BoundaryNodes::~BoundaryNodes() {
	// TODO Auto-generated destructor stub
}
