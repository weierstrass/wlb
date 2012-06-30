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
	//void HeZouPressureNodes::updateF(double ***f, double ***u, double **rho);
	void addNode(int x, int y, int z, double rho);
private:
	vector<ValueNode*> nodes;
};

#endif /* CONSTANTPRESSUREBOUNDARYNODES_H_ */
