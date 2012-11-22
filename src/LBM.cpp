/*
 * LBM-D2Q9.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Core class in lattice boltzmann solver.
 *
 */

#include "LBM.h"

LBM::LBM(LatticeModel *lm, CollisionModel *cm, StreamModel *sm){
	setLatticeModel(lm);

	/* Allocate memory */
	f = allocate4DArray(lm->n.z, lm->n.y, lm->n.x, lm->UDIRS);
	cout<<"Memory for f array allocated.."<<endl;

	setCollisionModel(cm);
	setStreamModel(sm);
}

/*
 * Initialize f, for now, start by just setting f = f_eq.
 */
void LBM::init(){
	collisionModel->init();
    streamModel->init();
}

void LBM::collideAndStream(){
	//cout<<"colliding..."<<endl;
	//print2DArray(f[0], latticeModel->n.x, latticeModel->n.y, 1);
	collisionModel->collide();

    for(int i = 0; i < boundaryNodes.size(); i++){
        if(boundaryNodes[i]->PRESTREAM){
          //  cout<<"PRESTREAM"<<endl;
            boundaryNodes[i]->updateF();
        }
    }

	//cout<<"streaming..."<<endl;
	//print2DArray(f[0], latticeModel->n.x, latticeModel->n.y, 1);
	streamModel->stream();

	for(int i = 0; i < boundaryNodes.size(); i++){
	    if(!boundaryNodes[i]->PRESTREAM){
	        boundaryNodes[i]->updateF();
	    }
	}
	//cout<<"post streaming"<<endl;
	//print2DArray(f[0], latticeModel->n.x, latticeModel->n.y, 1);
}

void LBM::addBoundaryNodes(BoundaryNodes *bn){
	boundaryNodes.push_back(bn);
	bn->registerF(f);
	bn->registerLatticeModel(latticeModel);
}

void LBM::handleBoundaries(){
    cout<<"NOTHING DONE HERE"<<endl;
}

void LBM::setStreamModel(StreamModel *s){
	streamModel = s;
	streamModel->registerF(f);
	streamModel->registerN(latticeModel->n);
}

void LBM::setCollisionModel(CollisionModel *cm){
	collisionModel = cm;
	collisionModel->registerF(f);
	collisionModel->registerN(latticeModel->n);
	collisionModel->registerLatticeModel(latticeModel);
}

void LBM::setLatticeModel(LatticeModel *lm){
	latticeModel = lm;
}

