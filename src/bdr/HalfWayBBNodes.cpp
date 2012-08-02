/*
 * HalfWayBBNodes.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
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
	cerr<<"Currently not implented use full way BB instead!"<<endl;
	NodeNeighbors *bbn;
	cout<<"sixe: "<<nodes.size()<<endl;
	for(int n = 0; n < nodes.size(); n++){
		bbn = dynamic_cast<NodeNeighbors*>(nodes[n]);
		cout<<bbn->nbs[0]<<endl;
		cout<<"("<<bbn->x<<", "<<bbn->y<<", "<<bbn->z<<")"<<endl;

	}

}

//OOOOOOOBBBBBBBSSSSSS!!!!!!!
//void HalfWayBBNodes::updateF_old(double ****f){
//	cout<<"Performing HWBB"<<endl;
//	for(int i = 1; i < nx-1; i++){
//		for(int j = 1; j < ny-1; j++){
//			if(boundries[i][j]){//hard node
//				f[3][i-1][j] = f[1][i][j];
//				f[6][i-1][j-1] = f[8][i][j];
//				f[7][i-1][j+1] = f[5][i][j];
//				f[1][i+1][j] = f[3][i][j];
//				f[5][i+1][j-1] = f[7][i][j];
//				f[8][i+1][j+1] = f[6][i][j];
//				f[2][i][j-1] = f[4][i][j];
//				f[4][i][j+1] = f[2][i][j];
//				//cout<<"inner"<<i<<", "<<j<<endl;
//			}
//		}
//		if(boundries[i][0]){//upper bdry
//			f[3][i-1][0] = f[1][i][0];
//			f[7][i-1][1] = f[5][i][0];
//			f[1][i+1][0] = f[3][i][0];
//			f[8][i+1][1] = f[6][i][0];
//			f[4][i][1] = f[2][i][0];
//		}
//		if(boundries[i][ny-1]){//lower bdry
//			f[3][i-1][ny-1] = f[1][i][ny-1];
//			f[6][i-1][ny-2] = f[8][i][ny-1];
//			f[1][i+1][ny-1] = f[3][i][ny-1];
//			f[5][i+1][ny-2] = f[7][i][ny-1];
//			f[2][i][ny-2] = f[4][i][ny-1];
//		}
//	}
//	if(boundries[0][0]){//LUC
//		f[1][1][0] = f[3][0][0];
//		f[4][0][1] = f[2][0][0];
//		f[8][1][1] = f[6][0][0];
//	}
//	if(boundries[nx-1][0]){//RUC
//		f[3][nx-2][0] = f[1][nx-1][0];
//		f[4][nx-1][1] = f[2][nx-1][0];
//		f[7][nx-2][1] = f[5][nx-1][0];
//	}
//	if(boundries[nx-1][ny-1]){//RLC
//		f[3][nx-2][ny-1] = f[1][nx-1][ny-1];
//		f[6][nx-2][ny-2] = f[8][nx-1][ny-1];
//		f[2][nx-1][ny-2] = f[4][nx-1][ny-1];
//	}
//	if(boundries[0][ny-1]){//LLC
//		f[1][1][ny-1] = f[3][0][ny-1];
//		f[5][1][ny-2] = f[7][0][ny-1];
//		f[2][0][ny-2] = f[4][0][ny-1];
//	}
//	for(int i = 0; i < nx; i++){
//		for(int j = 0; j < ny; j++){
//			if(boundries[i][j]){
//				for(int k = 0; k < DIRS; k++){
//					f[k][i][j] = 0;
//				}
//			}
//		}
//	}
//}

void HalfWayBBNodes::addNode(int x, int y, int z){
	cout<<"adding: ";
	cout<<"("<<x<<", "<<y<<", "<<z<<")"<<endl;
	NodeNeighbors *n = new NodeNeighbors(x, y, z, Q);
	cout<<"bajs"<<endl;
	nodes.push_back(n);
	cout<<"kiss"<<endl;
}

HalfWayBBNodes::~HalfWayBBNodes() {
	// TODO Auto-generated destructor stub
}

