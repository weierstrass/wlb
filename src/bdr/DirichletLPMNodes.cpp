/*
 * DirichletLPMNodes.cpp
 * Andreas Bülling, 2012
 * Dirichlet boundary implementation from the
 * recipe in Wangs paper.
 */

#include "DirichletLPMNodes.h"
//#include "../col/CollisionD2Q9WangHelmholtz.h"
//#include "../col/CollisionD2Q9LPMWang1to1.h"

//template void DirichletLPMNodes<CollisionD2Q9WangHelmholtz>::addNode(int, int, double);
//template DirichletLPMNodes<CollisionD2Q9WangHelmholtz>::DirichletLPMNodes();

//template void DirichletLPMNodes<CollisionD2Q9LPMWang1to1>::addNode(int, int, double);
//template DirichletLPMNodes<CollisionD2Q9LPMWang1to1>::DirichletLPMNodes();

template <class T>
DirichletLPMNodes<T>::DirichletLPMNodes() {
	// TODO Auto-generated constructor stub

}

template <class T>
DirichletLPMNodes<T>::~DirichletLPMNodes() {
	// TODO Auto-generated destructor stub
}

template <class T>
void DirichletLPMNodes<T>::updateF(){
	cout<<"Updating Dirichlet LPM nodes..."<<endl;
	ValueNode *node;
	int x, y;
	double psi0, sp, grhs;

	for(int n = 0; n < nodes.size(); n++){
		node = dynamic_cast<ValueNode*>(nodes[n]);
		x = node->x;
		y = node->y;
		//cout<<"x: "<<x<<", y: "<<y<<endl;
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
		}else if(y == 0){
			bool unkowns[]  = {0, 0, 1, 0, 0, 1, 1, 0, 0};
			updateBorderNode(unkowns, x, y, node->v1);
		}else if(x == 0){
			bool unkowns[]  = {0, 1, 0, 0, 0, 1, 0, 0, 1};
			updateBorderNode(unkowns, x, y, node->v1);
		}else if(x == lm->n.x-1){
			bool unkowns[]  = {0, 0, 0, 1, 0, 0, 1, 1, 0};
			updateBorderNode(unkowns, x, y, node->v1);
		}
	}
}

/* update routine for border nodes */
template <class T>
void DirichletLPMNodes<T>::updateBorderNode(const bool unknowns[9], int x, int y, double val){
	double sp = 0, grhs = 0, psi0;
	for(int i = 0; i < 9; i++){
			if(!unknowns[i]) sp += f[0][y][x][i];
	}
	for(int i = 0; i < 9; i++) grhs += cm->W[i];
//	cout<<"RHS: "<<cm->g_rhs(x, y)<<endl;
	grhs *=  cm->g_rhs(x, y);
	psi0 = 3*val - 3*sp - 1.5*grhs;
	for(int i = 0; i < 9; i++){
		if(unknowns[i]) f[0][y][x][i] = cm->fEq(i, psi0);
	}
}

/* update routine for corner nodes which need special treatment */
template <class T>
void DirichletLPMNodes<T>::updateCornerNode(const bool unknowns[9], int x, int y, double val){
	double sp = 0, grhs = 0, psi0;
	for(int i = 0; i < 9; i++){
		if(!unknowns[i]) sp += f[0][y][x][i];
	}
	for(int i = 0; i < 9; i++) grhs += cm->W[i];
	grhs *= cm->g_rhs(x, y);
	psi0 = (12*val - 6*grhs - 12*sp)/7.0;

	for(int i = 0; i < 9; i++){
		if(unknowns[i]) f[0][y][x][i] = cm->fEq(i, psi0);
	}
}

template <class T>
void DirichletLPMNodes<T>::addNode(int x, int y, double val){
	BoundaryNodes::addNode(new ValueNode(x, y, 0, val));
}
