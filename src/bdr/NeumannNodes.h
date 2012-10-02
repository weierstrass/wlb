/*
 * NeumannNodes.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef NEUMANNNODES_H_
#define NEUMANNNODES_H_

#include "ValueNode.h"
#include "SlipNodes.h"

template <class T>
class NeumannNodes : public SlipNodes<T>{
public:
    NeumannNodes();
    virtual ~NeumannNodes();
    void addNode(int x, int y, int z,
                 double val, double dir);
    void updateF();
    void init();
    //void setCollisionModel(T *cm){this->cm = cm;};
    void updateNodes(double **vx, double **vy, double **vz);
protected:
    vector<ValueNode*> nodes;
    //T *cm;
};

#endif /* NEUMANNNODES_H_ */
