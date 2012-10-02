/*
 * ValueNode.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include "ValueNode.h"

ValueNode::ValueNode(int x, int y, int z, double v1) :
		Node(x, y, z){
	this->v1 = v1;
}

ValueNode::ValueNode(int x, int y, int z,
                     double v1, double v2) :
                     Node(x, y, z){
    this->v1 = v1;
    this->v2 = v2;
}

ValueNode::~ValueNode() {
	// TODO Auto-generated destructor stub
}

