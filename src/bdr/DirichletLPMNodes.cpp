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
	cout<<"Updating Dirichlet LPM nodes..."<<endl;
	ValueNode *node;
	int x, y;
	double psi0, sp, grhs;

	for(int n = 0; n < nodes.size(); n++){
		node = dynamic_cast<ValueNode*>(nodes[n]);
		x = node->x;
		y = node->y;

		if(x == lm->n.x-1 && y == lm->n.y-1){//bot right
			bool unkowns[]  = {0, 0, 0, 1, 1, 0, 1, 1, 1};
			updateCornerNode(unkowns, x, y, node->v1);
		}else if(x == 0 && y == 0){//top left
			bool unkowns[]  = {0, 1, 1, 0, 0, 1, 1, 0, 1};
			updateCornerNode(unkowns, x, y, node->v1);
		}else if(x == 0 && y == lm->n.y-1){//bot left
			bool unkowns[]  = {0, 1, 0, 0, 1, 1, 0, 1, 1};
			updateCornerNode(unkowns, x, y, node->v1);
		}else if(x == lm->n.x-1 && y == 0){//top right
			bool unkowns[]  = {0, 0, 1, 1, 0, 1, 1, 1, 0};
			updateCornerNode(unkowns, x, y, node->v1);
		}else if(y == lm->n.y-1){//lower
			bool unkowns[]  = {0, 0, 0, 0, 1, 0, 0, 1, 1};
			updateBorderNode(unkowns, x, y, node->v1);
		}else if(y == 0){//upper
			bool unkowns[]  = {0, 0, 1, 0, 0, 1, 1, 0, 0};
			updateBorderNode(unkowns, x, y, node->v1);
		}
	}
}

/* update routine for border nodes */
void DirichletLPMNodes::updateBorderNode(const bool unknowns[9], int x, int y, double val){
	double sp = 0, grhs = 0, psi0;
	for(int i = 0; i < 9; i++){
			if(!unknowns[i]) sp += f[0][y][x][i];
	}
	for(int i = 0; i < 9; i++) grhs += cm->W[i];
	grhs *=  cm->g_rhs(x, y);
	psi0 = 3*val - 3*sp - 1.5*grhs;
	for(int i = 0; i < 9; i++){
		if(unknowns[i]) f[0][y][x][i] = cm->fEq(i, psi0);
	}
}

/* update routine for corner nodes which need special treatment */
void DirichletLPMNodes::updateCornerNode(const bool unknowns[9], int x, int y, double val){
	double sp = 0, grhs = 0, psi0;
	for(int i = 0; i < 9; i++){
		if(!unknowns[i]) sp += f[0][y][x][i];
	}
	for(int i = 0; i < 9; i++) grhs += cm->W[i];
	grhs *= cm->g_rhs(x, y);
	psi0 = (12*val - 6*grhs - 12*sp) * FRAC_1OVER7;
	for(int i = 0; i < 9; i++){
		if(unknowns[i]) f[0][y][x][i] = cm->fEq(i, psi0);
	}
}

void DirichletLPMNodes::addNode(int x, int y, double val){
	BoundaryNodes::addNode(new ValueNode(x, y, 0, val));
}
