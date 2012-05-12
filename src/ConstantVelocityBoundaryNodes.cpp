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
/* u(inlet) = u0;
 u(inlet + nx*ny) = 0;
 rho(inlet) = 1./(1 - u(inlet)) .* (fi(inlet) + fi(inlet + 2*nx*ny) + fi(inlet + 4*nx*ny)...
        + 2*(fi(inlet + 3*nx*ny) + fi(inlet + 6*nx*ny) + fi(inlet + 7*nx*ny)));
 fi(inlet + nx*ny) = fi(inlet + 3*nx*ny) + 2/3*rho(inlet).*u(inlet);%f1
 fi(inlet + 5*nx*ny) = fi(inlet + nx*ny*7) + 0.5*(fi(inlet + nx*ny*4) - fi(inlet + 2*nx*ny)) + 1/6*rho(inlet).*u(inlet);%f_5 , uy = 0
 fi(inlet + 8*nx*ny) = fi(inlet + nx*ny*6) - 0.5*(fi(inlet + nx*ny*4) - fi(inlet + 2*nx*ny)) + 1/6*rho(inlet).*u(inlet);%f8 , uy = 0
 */
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
