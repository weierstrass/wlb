/*
 * BoundaryNodes.h
 *
 *  Created on: 8 maj 2012
 *      Author: andreasbulling
 *
 *  Mother class for boundary conditions.
 *  Handles registration of common quantities.
 *  Children must implement a void updateF() function.
 */

#ifndef BOUNDARYNODE_H_
#define BOUNDARYNODE_H_

#include <iostream>
#include <vector>
#include <cstring>
#include "../lat/LatticeModel.h"
#include "ValueNode.h"


using namespace std;

class BoundaryNodes {
public:
	BoundaryNodes();
	virtual ~BoundaryNodes();
	virtual void updateF() = 0;
	void setF(double ****f){this->f = f;};
	void setLatticeModel(LatticeModel *lm){this->lm = lm;};
	char PRESTREAM;
protected:
    double ****f;
	void addNode(Node *n);
	LatticeModel *lm;
	vector<ValueNode*> nodes;
};


#endif /* BOUNDARYNODE_H_ */
