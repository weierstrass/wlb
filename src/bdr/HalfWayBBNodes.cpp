/*
 * HalfWayBBNodes.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Half-way implementation of the bounce back rule.
 *
 * NOT YET FULLY IMPLEMENTED!
 */

#include "HalfWayBBNodes.h"

HalfWayBBNodes::HalfWayBBNodes() : BoundaryNodes(){
	//preprocessing step, find neighbors
	NodeNeighbors *bbn;
	cout<<"sixe: "<<nodes.size()<<endl;
	for(int n = 0; n < nodes.size(); n++){
		bbn = dynamic_cast<NodeNeighbors*>(nodes[n]);
		for(int i = 0; i < Q; i++) bbn->nbs[i] = true;
		if(1){

		}
	}
}

void HalfWayBBNodes::updateF(){
	cout<<"Performing HWBB"<<endl;
	cerr<<"Currently not implemented use full way BB instead!"<<endl;
	NodeNeighbors *bbn;
//	cout<<"size: "<<nodes.size()<<endl;
//	for(int n = 0; n < nodes.size(); n++){
//		bbn = dynamic_cast<NodeNeighbors*>(nodes[n]);
//		cout<<bbn->nbs[0]<<endl;
//		cout<<"("<<bbn->x<<", "<<bbn->y<<", "<<bbn->z<<")"<<endl;
//
//	}

}

void HalfWayBBNodes::addNode(int x, int y, int z){
	NodeNeighbors *n = new NodeNeighbors(x, y, z, Q);
	nodes.push_back(n);
}

HalfWayBBNodes::~HalfWayBBNodes() {
	// TODO Auto-generated destructor stub
}

