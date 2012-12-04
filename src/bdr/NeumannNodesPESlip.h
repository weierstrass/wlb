/*
 * NeumannNodesPESlip.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef NEUMANNNODESPESLIP_H_
#define NEUMANNNODESPESLIP_H_

#include "SlipNodes.h"
#include "../col/CollisionD2Q9BGKPE.h"
#include "ValueNode.h"

class NeumannNodesPESlip: public SlipNodes<CollisionD2Q9BGKPE> { //todo
public:
    NeumannNodesPESlip();
    virtual ~NeumannNodesPESlip();
    void updateF();
    vector<ValueNode*> nodes;
    void addNode(int x, int y, int z,
            double val, int dir);
protected:
    double fEq(int dir, int i, int j);
    double cu(int i, int j);
};

#endif /* NEUMANNNODESPESLIP_H_ */
