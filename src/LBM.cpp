/*
 * LBM-D2Q9.cpp
 * Andreas Bülling, 2012
 * Core file in 2D LBM solver.
 */

#include "LBM.h"

LBM::LBM(LatticeModel *lm, CollisionModel *cm, StreamModel *sm){
	setLatticeModel(lm);

	/* Allocate memory */
	f = allocate4DArray(lm->n.z, lm->n.y, lm->n.x, lm->UDIRS);
	cout<<"memory allocated.."<<endl;

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
            cout<<"PRESTREAM"<<endl;
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


///*
// * Print u components to stdout
// */
//void LBM::printu(){
//	cout<<"ux:"<<endl;
//	print2DArray(ux[0], nx, ny);
//	cout<<"uy:"<<endl;
//	print2DArray(uy[0], nx, ny);
//}
//
//void LBM::addHalfWayBBNodes(HalfWayBBNodes *bbn){
//	hwbbNodes = bbn;
//	bbn->registerF(f);
//	bbn->registerN(latticeModel->n);
//	bbn->registerQ(latticeModel->UDIRS);
//}

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
//
//void LBM::initVelocity(double** uxInit, double** uyInit){
//	for(int i = 0; i < nx; i++){
//		for(int j = 0; j < ny; j++){
//			//ux[i][j] = uxInit[i][j];
//			//uy[i][j] = uyInit[i][j];
//		}
//	}
//}
//
//void LBM::initRho(double** rhoInit){
//	for(int i = 0; i < nx; i++){
//		for(int j = 0; j < ny; j++){
//			//rho[i][j] = rhoInit[i][j];
//		}
//	}
//}
