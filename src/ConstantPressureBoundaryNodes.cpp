/*
 * ConstantPressureBoundaryNodes.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "ConstantPressureBoundaryNodes.h"

ConstantPressureBoundaryNodes::ConstantPressureBoundaryNodes(int nx, int ny) :
								BoundaryNodes(nx, ny){
}

void ConstantPressureBoundaryNodes::updateF(double ***f, double **ux,
											double **uy, double **rho){
	int i, j;

	for(int k = 0; k < bNodes.size(); k++){
		i = bNodes[k].x;
		j = bNodes[k].y;
		if(i == 0){
			rho[0][j] = bNodes[k].value;
			ux[0][j] = 1 - (f[0][0][j] + f[2][0][j] + f[4][0][j] +
							2*( f[3][0][j] + f[6][0][j] + f[7][0][j])) / rho[0][j];

			uy[0][j] = 0; // -TODO
			f[1][0][j] = f[3][0][j] + 2.0/3.0*rho[0][j]*ux[0][j];
			f[5][0][j] = f[7][0][j] + 0.5*(f[4][0][j] - f[2][0][j]) + 1.0/6.0*rho[0][j]*ux[0][j];
			f[8][0][j] = f[6][0][j] - 0.5*(f[4][0][j] - f[2][0][j]) + 1.0/6.0*rho[0][j]*ux[0][j];
		}else if( i == (nx-1) ){
			rho[nx-1][j] = bNodes[k].value;
			ux[nx-1][j] = (f[0][nx-1][j] + f[2][nx-1][j] + f[4][nx-1][j] +
							2*( f[1][nx-1][j] + f[5][nx-1][j] + f[8][nx-1][j])) / rho[nx-1][j] - 1;
			uy[nx-1][j] = 0; // -TODO

			f[3][nx-1][j] = f[1][nx-1][j] - 2.0/3.0*rho[nx-1][j]*ux[nx-1][j];
			f[7][nx-1][j] = f[5][nx-1][j] - 0.5*(f[4][nx-1][j] - f[2][nx-1][j]) - 1.0/6.0*rho[nx-1][j]*ux[nx-1][j];
			f[6][nx-1][j] = f[8][nx-1][j] + 0.5*(f[4][nx-1][j] - f[2][nx-1][j]) - 1.0/6.0*rho[nx-1][j]*ux[nx-1][j];
		}else{
			cerr<<"No implementation found for requested constant pressure boundary node!"<<endl;
		}
	}
}

void ConstantPressureBoundaryNodes::addNode(int x, int y, double val){
	ValueNode *v = new ValueNode(x, y, val);
	bNodes.push_back(*v);
}

ConstantPressureBoundaryNodes::~ConstantPressureBoundaryNodes() {
	// TODO Auto-generated destructor stub
}

