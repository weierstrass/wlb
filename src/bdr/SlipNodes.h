/*
 * SlipNodes.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef SLIPNODES_H_
#define SLIPNODES_H_

#include "BoundaryNodes.h"
#include "../col/CollisionD2Q9LNP.h"
#include "../col/CollisionD2Q9AD.h"


template <class T>
class SlipNodes: public BoundaryNodes {
public:
    SlipNodes();
    virtual ~SlipNodes();
    void updateF();
    void init();
    void addNode(int x, int y, int z);
    void setCollisionModel(T *cm){this->cm = cm;};
    T *cm;
protected:
    char **slipNodes;
};

#endif /* SLIPNODES_H_ */
