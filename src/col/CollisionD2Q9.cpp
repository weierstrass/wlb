/*
 * CollisionD2Q9.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 */

#include "CollisionD2Q9.h"

/* Define lattice weights */
const double CollisionD2Q9::W[9] = {W0, W1, W1, W1, W1, W2, W2, W2, W2};

CollisionD2Q9::CollisionD2Q9() :CollisionModel() {
    skip = NULL;
}

CollisionD2Q9::~CollisionD2Q9() {
	if( skip != NULL){
		//Deallocate skip array TODO
	}
}

void CollisionD2Q9::addNodeToSkip(int i, int j){
    cout<<"No collision for node: ("<<i<<", "<<j<<")"<<endl;
    if(skip == NULL){
        skip = allocate2DArrayT<bool>(lm->n.y, lm->n.x);
    }
    skip[j][i] = true;
}
