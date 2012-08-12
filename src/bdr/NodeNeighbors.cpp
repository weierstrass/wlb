/*
 * NodeNeighbors.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include "NodeNeighbors.h"

NodeNeighbors::NodeNeighbors(int x, int y, int z, int dim) : Node(x, y, z){
	cout<<dim<<endl;
	nbs = new bool[dim];
}

NodeNeighbors::~NodeNeighbors() {
	// TODO Auto-generated destructor stub
}

