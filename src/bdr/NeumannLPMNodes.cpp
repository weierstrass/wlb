/*
 * NeumannLPMNodes.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "NeumannLPMNodes.h"

NeumannLPMNodes::NeumannLPMNodes() {
	// TODO Auto-generated constructor stub

}

NeumannLPMNodes::~NeumannLPMNodes() {
	// TODO Auto-generated destructor stub
}

void NeumannLPMNodes::updateF(){
	cout<<"Neumann LPM"<<endl;
	ValueNode *node;
	int x, y;
	double psi0, sp, grhs;
	for(int n = 0; n < nodes.size(); n++){
		node = dynamic_cast<ValueNode*>(nodes[n]);
		grhs = 0;
		x = node->x;
		y = node->y;
		if(x == 0){//left side
		//	cout<<"left"<<endl;
			sp = f[0][y][x][7] +
				 f[0][y][x][3] +
				 f[0][y][x][6];
			psi0 = 3*sp;
			f[0][y][x][1] = cm->fEq(1, psi0);
			f[0][y][x][5] = cm->fEq(5, psi0);
			f[0][y][x][8] = cm->fEq(8, psi0);
		}else if(x == lm->n.x-1){//right side
			sp = f[0][y][x][1] +
				 f[0][y][x][5] +
				 f[0][y][x][8];
			psi0 = 3*sp;
			f[0][y][x][7] = cm->fEq(7, psi0);
			f[0][y][x][3] = cm->fEq(3, psi0);
			f[0][y][x][6] = cm->fEq(6, psi0);
		}
	}
}

void NeumannLPMNodes::addNode(int x, int y, double val){
	BoundaryNodes::addNode(new ValueNode(x, y, 0, val));
}
