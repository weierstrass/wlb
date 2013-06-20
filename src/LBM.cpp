/*
 * LBM.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Core class in the lattice-Boltzmann solver.
 *
 */

#include "LBM.h"

/*
 * Constructor, requires a lattice, collision operator and a streaming model
 */
LBM::LBM(LatticeModel *lm, CollisionModel *cm, StreamModel *sm) {
	/* Register lattice, collision and stream objects */
	setLatticeModel(lm);
	setCollisionModel(cm);
	setStreamModel(sm);

	/* Allocate memory for distribution function */
	f = allocate4DArray(lm->n.z, lm->n.y, lm->n.x, lm->UDIRS);
}

/*
 * Initialize solver
 */
void LBM::init() {
  collisionModel->init();
  streamModel->init();
}

/*
 * Perform a collision step followed by a streaming step.
 *
 * Boundary conditions are automatically handled here. Depending on whether the
 * condition is of pre or post stream type it is performed before or after the
 * streaming step respectively.
 */
void LBM::collideAndStream() {
	/* Collide */
	collisionModel->collide();

	/* Perform pre-stream boundary conditions */
	for (int i = 0; i < boundaryNodes.size(); i++) {
		if (boundaryNodes[i]->PRESTREAM) {
			boundaryNodes[i]->updateF();
		}
	}

	/* Stream */
	streamModel->stream();

	/* Perform post-stream boundary conditions */
	for (int i = 0; i < boundaryNodes.size(); i++) {
		if (!boundaryNodes[i]->PRESTREAM) {
			boundaryNodes[i]->updateF();
		}
	}
}

/*
 * Register boundary nodes at the solver.
 * The boundary nodes are supplied with pointers to the distribution function
 * and lattice model.
 */
void LBM::addBoundaryNodes(BoundaryNodes *bn) {
	boundaryNodes.push_back(bn);
	bn->setF(f);
	bn->setLatticeModel(latticeModel);
}

/*
 * Register stream model at the solver.
 */
void LBM::setStreamModel(StreamModel *s) {
	streamModel = s;
	streamModel->setF(f);
	streamModel->setLatticeModel(latticeModel);
}
/*
 * Register collision operator at the solver.
 */
void LBM::setCollisionModel(CollisionModel *cm) {
  collisionModel = cm;
  collisionModel->setF(f);
  collisionModel->setLatticeModel(latticeModel);
}

/*
 * Register lattice model at the solver
 */
void LBM::setLatticeModel(LatticeModel *lm) {
  latticeModel = lm;
}
