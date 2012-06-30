/*
 * BounceBackNodes.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "BounceBackNodes.h"

BounceBackNodes::BounceBackNodes() {
	// TODO Auto-generated constructor stub

}

BounceBackNodes::~BounceBackNodes() {
	// TODO Auto-generated destructor stub
}

void BounceBackNodes::updateF(){
	cout<<"updating BB nodes"<<endl;
	double *fTemp = new double[lm->UDIRS];
	Node *node;
	int x, y, z, *opp, opp2;

	//print2DArray(f[0], lm->n.x, lm->n.y, 2);
	//print2DArray(f[0], lm->n.x, lm->n.y, 4);

	for(int i = 0; i < nodes.size(); i++){
		node = nodes[i];
		x = node->x;
		y = node->y;
		z = node->z;
	//	cout<<x<<", "<<y<<", "<<z<<endl;
	//	memcpy(fTemp, f[z][y][x], (lm->UDIRS)*sizeof(double));
		for(int j = 0; j < lm->UDIRS; j++){
			fTemp[j] = f[z][y][x][j];
			//cout<<"fpre: "<<f[z][y][x][j]<<endl;
			//cout<<"temppre: "<<fTemp[j]<<endl;
		}
		for(int d = 0; d < lm->UDIRS; d++){
			f[z][y][x][d] = fTemp[lm->oppDirs[d]];
			//cout<<"temp: "<<fTemp[d]<<endl;
			//cout<<"f: "<<f[z][y][x][d]<<endl;
			//cout<<d<<" har "<<lm->oppDirs[d]<<"som motsatt riktning.."<<endl;
		}
	}

	//print2DArray(f[0], lm->n.x, lm->n.y, 2);
	//print2DArray(f[0], lm->n.x, lm->n.y, 4);
}

void BounceBackNodes::addNode(int x, int y, int z){
	BoundaryNodes::addNode(new Node(x, y, z));
}
