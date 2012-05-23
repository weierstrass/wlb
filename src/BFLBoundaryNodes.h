/*
 * BFLBoundaryNodes.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef BFLBOUNDARYNODES_H_
#define BFLBOUNDARYNODES_H_

#include <vector>;
#include "BoundaryNodes.h"
#include "ValueNode.h"

class BFLBoundaryNodes : public BoundaryNodes {
public:
	BFLBoundaryNodes(int nx, int ny);
	virtual ~BFLBoundaryNodes();
	void updateF(double ***f, double **ux, double **uy);
	void addNode(int x, int y, int dir, double q);
	bool isNode(int x, int y);
private:
	vector<vector<ValueNode> > bNodes;
};

#endif /* BFLBOUNDARYNODES_H_ */
