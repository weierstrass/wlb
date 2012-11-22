/*
 * NeumannLPMNodes.h
 * Andreas B�lling, 2012
 * DESCRIPTION - TODO
 */

#ifndef NEUMANNLPMNODES_H_
#define NEUMANNLPMNODES_H_

#include "BoundaryNodes.h"
//#include "../col/CollisionD2Q9LPM.h"
#include "ValueNode.h"

template <class T>
class NeumannLPMNodes : public BoundaryNodes{
public:
	NeumannLPMNodes();
	virtual ~NeumannLPMNodes();
	void updateF();
	T *cm;
	void setCollisionModel(T *cm){this->cm = cm;};
	void addNode(int x, int y, double val);
};

#endif /* NEUMANNLPMNODES_H_ */
