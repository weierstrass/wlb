/*
 * DirichletLPMNodes.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#ifndef DIRICHLETLPMNODES_H_
#define DIRICHLETLPMNODES_H_

#include "BoundaryNodes.h"
//#include "../col/CollisionD2Q9LPM.h"
#include "ValueNode.h"

template <class T>
class DirichletLPMNodes: public BoundaryNodes {
public:
	DirichletLPMNodes();
	virtual ~DirichletLPMNodes();
	void updateF();
	T *cm;
	void setCollisionModel(T *cm){this->cm = cm;};
	void addNode(int x, int y, double val);
private:
	void updateCornerNode(const bool unknowns[9], int x, int y, double val);
	void updateBorderNode(const bool unknowns[9], int x, int y, double val);
};

#endif /* DIRICHLETLPMNODES_H_ */
