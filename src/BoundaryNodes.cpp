/*
 * BoundaryNode.cpp
 *
 *  Created on: 8 maj 2012
 *      Author: andreasbulling
 */

#include "BoundaryNodes.h"

BoundaryNodes::BoundaryNodes(int nx, int ny) {
	BoundaryNodes::nx = nx;
	BoundaryNodes::ny = ny;

	boundries = new bool*[nx];
	for(int i = 0; i < nx; i++){
		boundries[i] = new bool[ny];
	}
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			boundries[i][j] = false;
		}
	}
}

//void BoundaryNodes::updateF(double ***f){
//	cout<<"updating f"<<endl;
//	cout<<f[0][2][3]<<endl;
//}

void BoundaryNodes::addNode(int i, int j){
	boundries[i][j] = true;
}

BoundaryNodes::~BoundaryNodes() {
	// TODO Auto-generated destructor stub
}

