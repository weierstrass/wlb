/*
 * BoundaryNode.cpp
 *
 *  Created on: 8 maj 2012
 *      Author: andreasbulling
 */

#include "BoundaryNode.h"

BoundaryNode::BoundaryNode(int x, int y) {
	BoundaryNode::x = x;
	BoundaryNode::y = y;
}

void BoundaryNode::updateF(double ***f){
	cout<<"updating f"<<endl;
	cout<<f[0][2][3]<<endl;
}

BoundaryNode::~BoundaryNode() {
	// TODO Auto-generated destructor stub
}

