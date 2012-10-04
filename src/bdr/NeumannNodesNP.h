/*
 * NeumannNodesNP.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef NEUMANNNODESNP_H_
#define NEUMANNNODESNP_H_

#include "NeumannNodes.h"
#include "../col/CollisionD2Q9LNP.h"

class NeumannNodesNP: public NeumannNodes<CollisionD2Q9LNP> {
public:
    NeumannNodesNP();
    virtual ~NeumannNodesNP();
    void updateF();
protected:
    double fEq(int dir, int i, int j);
    double cu(int i, int j);
};

#endif /* NEUMANNNODESNP_H_ */
