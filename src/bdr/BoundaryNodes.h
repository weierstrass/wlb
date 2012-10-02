/*
 * BoundaryNodes.h
 *
 *  Created on: 8 maj 2012
 *      Author: andreasbulling
 */

#ifndef BOUNDARYNODE_H_
#define BOUNDARYNODE_H_

#include <iostream>
#include <vector>
#include <cstring>
#include "../lat/LatticeModel.h"
#include "Node.h"

using namespace std;

class BoundaryNodes {
public:
	BoundaryNodes();
	virtual ~BoundaryNodes();
	virtual void updateF() = 0;
	void registerF(double ****f){this->f = f;};
	void registerN(struct LatticeModel::dimension &n){this->n = n;};
	void registerQ(int Q){this->Q = Q;};
	void registerLatticeModel(LatticeModel *lm){this->lm = lm;};
	char PRESTREAM;
    double ****f;
protected:
	void addNode(Node *n);
	LatticeModel *lm;
	struct LatticeModel::dimension n;
	int Q;
	vector<Node*> nodes;
};


#endif /* BOUNDARYNODE_H_ */
