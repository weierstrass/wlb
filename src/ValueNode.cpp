/*
 * ValueNode.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "ValueNode.h"

ValueNode::ValueNode(int x, int y, double value) {
	this->x = x;
	this->y = y;
	this->value = value;
}

ValueNode2D::ValueNode2D(int x, int y, double v1, double v2) : ValueNode(x, y, 0.0){
//	this->x = x;
	//this->y = y;
	valueX = v1;
	valueY = v2;
}

ValueNode2D::~ValueNode2D() {
	// TODO Auto-generated destructor stub
}

ValueNode::~ValueNode() {
	// TODO Auto-generated destructor stub
}

