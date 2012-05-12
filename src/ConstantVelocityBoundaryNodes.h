/*
 * ConstantVelocityBoundaryNodes.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef CONSTANTVELOCITYBOUNDARYNODES_H_
#define CONSTANTVELOCITYBOUNDARYNODES_H_

#include <vector>
#include "BoundaryNodes.h"
#include "ValueNode.h"

class ConstantVelocityBoundaryNodes : public BoundaryNodes  {
public:
	ConstantVelocityBoundaryNodes(int nx, int ny);
	virtual ~ConstantVelocityBoundaryNodes();
	void updateF(double ***f, double **ux,
					double **uy, double **rho);
	void addNode(int x, int y, double rho);
private:
	vector<ValueNode> bNodes;
};

#endif /* CONSTANTVELOCITYBOUNDARYNODES_H_ */
