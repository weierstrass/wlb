/*
 * HeZouLPMChaiNodes.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef HEZOULPMCHAINODES_H_
#define HEZOULPMCHAINODES_H_

#include "BoundaryNodes.h"
#include "../col/CollisionD2Q9LPMChai.h"
#include "ValueNode.h"

class HeZouLPMChaiNodes: public BoundaryNodes {
public:
	HeZouLPMChaiNodes();
	virtual ~HeZouLPMChaiNodes();
	void updateF();
	void addNode(int x, int y, int z, double rho);
	void setCollisionModel(CollisionD2Q9LPMChai *cm){this->cm = cm;};
private:
	vector<ValueNode*> nodes;
	void updateNode(int i, int j, double rho, double psi, int bdr);
	void updateCornerNode(int i, int j, double rho, double psi, int bdr);
	CollisionD2Q9LPMChai *cm;
};

#endif /* HEZOULPMCHAINODES_H_ */
