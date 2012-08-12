/*
 * Node.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Mother class of a boundary node object.
 */

#include "Node.h"

Node::Node(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

