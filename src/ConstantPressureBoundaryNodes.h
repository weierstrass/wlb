/*
 * ConstantPressureBoundaryNodes.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef CONSTANTPRESSUREBOUNDARYNODES_H_
#define CONSTANTPRESSUREBOUNDARYNODES_H_

#include <vector>;
#include "BoundaryNodes.h"
#include "ValueNode.h"

class ConstantPressureBoundaryNodes :
		public BoundaryNodes{
public:
	ConstantPressureBoundaryNodes(int nx, int ny);
	virtual ~ConstantPressureBoundaryNodes();
	void updateF(double ***f, double **ux,
					double **uy, double **rho);
	void addNode(int x, int y, double rho);
private:
	vector<ValueNode> bNodes;
};

#endif /* CONSTANTPRESSUREBOUNDARYNODES_H_ */
