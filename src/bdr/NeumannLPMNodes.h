/*
 * NeumannLPMNodes.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef NEUMANNLPMNODES_H_
#define NEUMANNLPMNODES_H_

#include "BoundaryNodes.h"
#include "../col/CollisionD2Q9LPM.h"
#include "ValueNode.h"

class NeumannLPMNodes : public BoundaryNodes{
public:
	NeumannLPMNodes();
	virtual ~NeumannLPMNodes();
	void updateF();
	CollisionD2Q9LPM *cm;
	void setCollisionModel(CollisionD2Q9LPM *cm){this->cm = cm;};
	void addNode(int x, int y, double val);
};

#endif /* NEUMANNLPMNODES_H_ */
