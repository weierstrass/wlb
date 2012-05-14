/*
 * ConstantVelocityBoundaryNodes.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "ConstantVelocityBoundaryNodes.h"

ConstantVelocityBoundaryNodes::ConstantVelocityBoundaryNodes(int nx, int ny) :
								BoundaryNodes(nx, ny){
	// TODO Auto-generated constructor stub
}

void ConstantVelocityBoundaryNodes::updateF(double ***f, double **ux,
											double **uy, double **rho){
	int i,j;
	for(int k = 0; k < bNodes.size(); k++){
		i = bNodes[k].x;
		j = bNodes[k].y;
		if(i == 0){
			ux[0][j] = bNodes[k].value;
			rho[0][j] = 1/(1 - ux[0][j])*(f[0][0][j] + f[2][0][j] + f[4][0][j] +
							2*( f[3][0][j] + f[6][0][j] + f[7][0][j]));

			uy[0][j] = 0; // -TODO
			f[1][0][j] = f[3][0][j] + 2.0/3.0*rho[0][j]*ux[0][j];
			f[5][0][j] = f[7][0][j] + 0.5*(f[4][0][j] - f[2][0][j]) + 1.0/6.0*rho[0][j]*ux[0][j];
			f[8][0][j] = f[6][0][j] - 0.5*(f[4][0][j] - f[2][0][j]) + 1.0/6.0*rho[0][j]*ux[0][j];
		}else{
			cerr<<"No implementation found for requested constant pressure boundary node!"<<endl;
		}
	}
}

ConstantVelocityBoundaryNodes::~ConstantVelocityBoundaryNodes() {
	// TODO Auto-generated destructor stub
}

void ConstantVelocityBoundaryNodes::addNode(int x, int y, double val){
	ValueNode *v = new ValueNode(x, y, val);
	bNodes.push_back(*v);
}
