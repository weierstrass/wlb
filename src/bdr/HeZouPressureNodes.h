/*
 * ConstantPressureBoundaryNodes.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef CONSTANTPRESSUREBOUNDARYNODES_H_
#define CONSTANTPRESSUREBOUNDARYNODES_H_

#include <vector>
#include "BoundaryNodes.h"
#include "ValueNode.h"

class HeZouPressureNodes :
		public BoundaryNodes{
public:
	HeZouPressureNodes();
	virtual ~HeZouPressureNodes();
	void updateF();
	void addNode(int x, int y, int z, double rho);
private:
	vector<ValueNode*> nodes;
	void updateCornerNode(const bool knowns[], int i, int j, double val);
};

#endif /* CONSTANTPRESSUREBOUNDARYNODES_H_ */
