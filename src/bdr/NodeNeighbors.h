/*
 * NodeNeighbors.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef NODENEIGHBORS_H_
#define NODENEIGHBORS_H_

#include <iostream>
#include "Node.h"

using namespace std;


class NodeNeighbors : public Node {
public:
	NodeNeighbors(int x, int y, int z, int dim);
	virtual ~NodeNeighbors();
	bool *nbs;
protected:
};

#endif /* NODENEIGHBORS_H_ */
