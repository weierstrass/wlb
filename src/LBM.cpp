/*
 * LBM.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Core class in lattice-Boltzmann solver.
 *
 */

#include "LBM.h"

LBM::LBM(LatticeModel *lm, CollisionModel *cm, StreamModel *sm) {
	setLatticeModel(lm);
	setCollisionModel(cm);
	setStreamModel(sm);

	/* Allocate memory */
	cout << "Allocating memory for f array... ";
	f = allocate4DArray(lm->n.z, lm->n.y, lm->n.x, lm->UDIRS);
	cout << "done." << endl;

	setCollisionModel(cm);
	setStreamModel(sm);
}

/*
 * Initialize f
 */
void LBM::init() {
	collisionModel->init();
	streamModel->init();
}

void LBM::collideAndStream() {
	// collide
	collisionModel->collide();

	// pre-stream boundary conditions
	for (int i = 0; i < boundaryNodes.size(); i++) {
		if (boundaryNodes[i]->PRESTREAM) {
			//  cout<<"PRESTREAM"<<endl;
			boundaryNodes[i]->updateF();
		}
	}

	// stream
	streamModel->stream();

	//post-stream boundary conditions
	for (int i = 0; i < boundaryNodes.size(); i++) {
		if (!boundaryNodes[i]->PRESTREAM) {
			boundaryNodes[i]->updateF();
		}
	}
}

void LBM::addBoundaryNodes(BoundaryNodes *bn) {
	boundaryNodes.push_back(bn);
	bn->registerF(f);
	bn->registerLatticeModel(latticeModel);
}

void LBM::setStreamModel(StreamModel *s) {
	streamModel = s;
	streamModel->setF(f);
	streamModel->setLatticeModel(latticeModel);

	//deprecated
    streamModel->registerN(latticeModel->n);
}

void LBM::setCollisionModel(CollisionModel *cm) {
	collisionModel = cm;
	collisionModel->setF(f);
	collisionModel->setLatticeModel(latticeModel);
}

void LBM::setLatticeModel(LatticeModel *lm) {
	latticeModel = lm;
}

// deprecated
void LBM::handleBoundaries() {
	cout << "WARNING: NOTHING DONE HERE!" << endl;
}
