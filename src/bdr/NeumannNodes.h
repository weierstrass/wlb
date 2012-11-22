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
#include "HeZouNodes.h"
//#include "../col/CollisionD2Q9LNP.h"
#include "../col/CollisionD2Q9LPMChaiRHS.h"
#include "../col/CollisionD2Q9LPMChai1to1.h"

template <class T>
class NeumannNodes : public HeZouNodes<T>{
public:
    NeumannNodes();
    virtual ~NeumannNodes();
    void addNode(int x, int y, int z,
                 double val, int dir);
    void updateF();
    void init();
    //void setCollisionModel(T *cm){this->cm = cm;};
    void updateNodes(double **vx, double **vy, double **vz);
protected:
    virtual double cu(int i, int j) = 0;
    //vector<ValueNode*> neumannNodes;
    double getDirichletValue(int x, int y, int dx, int dy, double val);
    //T *cm;
};

#endif /* NEUMANNNODES_H_ */
