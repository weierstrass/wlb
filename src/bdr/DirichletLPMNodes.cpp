/*
 * DirichletLPMNodes.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "DirichletLPMNodes.h"

DirichletLPMNodes::DirichletLPMNodes() {
	// TODO Auto-generated constructor stub

}

DirichletLPMNodes::~DirichletLPMNodes() {
	// TODO Auto-generated destructor stub
}

void DirichletLPMNodes::updateF(){
	cout<<"Dirichlet LPM"<<endl;
	//double W[9] = {W0, W1, W1, W1, W1, W2, W2, W2, W2};
	double dt = 1.0;
	ValueNode *node;
	int x, y;
	double psi0, sp, grhs;
	cout<<"sixe: "<<nodes.size()<<endl;
	for(int n = 0; n < nodes.size(); n++){
		node = dynamic_cast<ValueNode*>(nodes[n]);
		grhs = 0;
		x = node->x;
		y = node->y;

	//	cout<<bbn->nod[0]<<endl;
	//	cout<<"("<<node->x<<", "<<node->y<<"), v1: "<<node->v1<<endl;

		//corners...
		if(x == lm->n.x-1 && y == lm->n.y-1){//bot right
			sp = f[0][y][x][0] +
				 f[0][y][x][1] +
				 f[0][y][x][2] +
				 f[0][y][x][5];
			for(int i = 0; i < 9; i++) grhs += cm->g_rhs(x, y)*cm->W[i];//todo common
			psi0 = 12*node->v1 - dt*6*grhs - 12*sp;
			psi0 /= 7;
			f[0][y][x][6] = cm->fEq(6, psi0);
			f[0][y][x][3] = cm->fEq(3, psi0);
			f[0][y][x][7] = cm->fEq(7, psi0);
			f[0][y][x][4] = cm->fEq(4, psi0);
			f[0][y][x][8] = cm->fEq(8, psi0);
		}else if(x == 0 && y == 0){//top left
			sp = f[0][y][x][0] +
				 f[0][y][x][4] +
				 f[0][y][x][7] +
				 f[0][y][x][3];
			for(int i = 0; i < 9; i++) grhs += cm->g_rhs(x, y)*cm->W[i];//todo common
			psi0 = 12*node->v1 - dt*6*grhs - 12*sp;
			psi0 /= 7;
			f[0][y][x][8] = cm->fEq(8, psi0);
			f[0][y][x][1] = cm->fEq(1, psi0);
			f[0][y][x][5] = cm->fEq(5, psi0);
			f[0][y][x][2] = cm->fEq(2, psi0);
			f[0][y][x][6] = cm->fEq(6, psi0);
		}else if(x == 0 && y == lm->n.y-1){//bot left
			sp = f[0][y][x][0] +
				 f[0][y][x][3] +
				 f[0][y][x][6] +
				 f[0][y][x][2];
			for(int i = 0; i < 9; i++) grhs += cm->g_rhs(x, y)*cm->W[i];//todo common
			psi0 = 12*node->v1 - dt*6*grhs - 12*sp;
			psi0 /= 7.0;
			f[0][y][x][7] = cm->fEq(7, psi0);
			f[0][y][x][4] = cm->fEq(4, psi0);
			f[0][y][x][8] = cm->fEq(8, psi0);
			f[0][y][x][1] = cm->fEq(1, psi0);
			f[0][y][x][5] = cm->fEq(5, psi0);
		}else if(x == lm->n.x-1 && y == 0){//top right
			sp = f[0][y][x][0] +
				 f[0][y][x][4] +
				 f[0][y][x][8] +
				 f[0][y][x][1];
			for(int i = 0; i < 9; i++) grhs += cm->g_rhs(x, y)*cm->W[i];//todo common
			psi0 = 12*node->v1 - dt*6*grhs - 12*sp;
			psi0 /= 7;
			f[0][y][x][7] = cm->fEq(7, psi0);
			f[0][y][x][3] = cm->fEq(3, psi0);
			f[0][y][x][6] = cm->fEq(6, psi0);
			f[0][y][x][2] = cm->fEq(2, psi0);
			f[0][y][x][5] = cm->fEq(5, psi0);
		}else if(y == lm->n.y-1){
			sp = f[0][y][x][0] +
				 f[0][y][x][1] +
				 f[0][y][x][2] +
				 f[0][y][x][3] +
				 f[0][y][x][5] +
				 f[0][y][x][6];
			for(int i = 0; i < 9; i++) grhs += cm->g_rhs(x, y)*cm->W[i];
			psi0 = 3*node->v1 - 3*sp - dt*1.5*grhs;
			f[0][y][x][7] = cm->fEq(7, psi0);
			f[0][y][x][4] = cm->fEq(4, psi0);
			f[0][y][x][8] = cm->fEq(8, psi0);
		}else if(y == 0){
			sp = f[0][y][x][0] +
				 f[0][y][x][1] +
				 f[0][y][x][4] +
				 f[0][y][x][3] +
				 f[0][y][x][8] +
				 f[0][y][x][7];
			//cout<<"sp: "<<sp<<endl;
			for(int i = 0; i < 9; i++) grhs += cm->g_rhs(x, y)*cm->W[i];
			psi0 = 3*node->v1 - 3*sp - dt*1.5*grhs;
			cout<<"psi0: "<<psi0<<endl;
			//cout<<"f_6pre: "<<f[0][y][x][6]<<endl;
			f[0][y][x][6] = cm->fEq(6, psi0);
			//cout<<"f_6post: "<<f[0][y][x][6]<<endl;
			f[0][y][x][2] = cm->fEq(2, psi0);
			f[0][y][x][5] = cm->fEq(5, psi0);
		}
	}
}


void DirichletLPMNodes::addNode(int x, int y, double val){
	BoundaryNodes::addNode(new ValueNode(x, y, 0, val));
}
