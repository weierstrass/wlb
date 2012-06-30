/*
 * ValueNode.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "ValueNode.h"

ValueNode::ValueNode(int x, int y, int z, double value) :
		Node(x, y, z){
	v1 = value;
}

ValueNode::~ValueNode() {
	// TODO Auto-generated destructor stub
}

