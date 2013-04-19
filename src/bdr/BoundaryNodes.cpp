/*
 * BoundaryNode.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Abstract mother class of boundary nodes implementations.
 * The idea is to collect all boundary nodes of the same
 * type in an encapsulation class derived from this class.
 */

#include "BoundaryNodes.h"

BoundaryNodes::BoundaryNodes() {
    PRESTREAM = 0;
    lm = NULL;
    f = NULL;
}

void BoundaryNodes::addNode(Node *n){
	//nodes.push_back(n);
}

BoundaryNodes::~BoundaryNodes() {
	// TODO Auto-generated destructor stub
}

