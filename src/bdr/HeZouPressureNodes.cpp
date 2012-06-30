/*
 * HeZouPressureNodes.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "HeZouPressureNodes.h"

HeZouPressureNodes::HeZouPressureNodes() :
								BoundaryNodes(){
}

void HeZouPressureNodes::updateF(){
	cout<<"updating pressure nodes"<<endl;
	int i, j;
	double rho, ux, uy, temp;

	if(lm->DIM == 2){
		for(int k = 0; k < nodes.size(); k++){
			i = nodes[k]->x;
			j = nodes[k]->y;
			temp = f[0][j][i][0];
			f[0][j][i][0] = 0;
			//cout<<i<<", "<<j<<endl;
			if(i == 0){
				rho = nodes[k]->v1;
				ux = 1 - (f[0][j][i][0] + f[0][j][i][2] + f[0][j][i][4] +
						2*( f[0][j][i][3] + f[0][j][i][6] + f[0][j][i][7])) / rho;

				uy = 0; // -TODO
				f[0][j][i][1] = f[0][j][i][3] + 2.0/3.0*rho*ux;
				f[0][j][i][5] = f[0][j][i][7] + 0.5*(f[0][j][i][4] - f[0][j][i][2]) + 1.0/6.0*rho*ux;
				f[0][j][i][8] = f[0][j][i][7] - 0.5*(f[0][j][i][4] - f[0][j][i][2]) + 1.0/6.0*rho*ux;
			}else if( i == (lm->n.x-1) ){
				rho = nodes[k]->v1;
				ux = (f[0][j][i][0] + f[0][j][i][2] + f[0][j][i][4] +
						2*( f[0][j][i][1] + f[0][j][i][5] + f[0][j][i][8])) / rho - 1;
				uy = 0; // -TODO

				f[0][j][i][3] = f[0][j][i][1] - 2.0/3.0*rho*ux;
				f[0][j][i][7] = f[0][j][i][5] - 0.5*(f[0][j][i][4] - f[0][j][i][2]) - 1.0/6.0*rho*ux;
				f[0][j][i][6] = f[0][j][i][8] + 0.5*(f[0][j][i][4] - f[0][j][i][2]) - 1.0/6.0*rho*ux;
			}else{
				cerr<<"No implementation found for requested constant pressure boundary node ("<<i<<", "<<j<<")"<<endl;
			}
			f[0][j][i][0] = temp;
		}
	}
}


//void HeZouPressureNodes::updateF(double ***f, double ***u, double **rho){
//	int i, j;
//
//	for(int k = 0; k < bNodes.size(); k++){
//		i = bNodes[k].x;
//		j = bNodes[k].y;
//		if(i == 0){
//			rho[0][j] = bNodes[k].value;
//			u[X][0][j] = 1 - (f[0][0][j] + f[2][0][j] + f[4][0][j] +
//							2*( f[3][0][j] + f[6][0][j] + f[7][0][j])) / rho[0][j];
//
//			u[Y][0][j] = 0; // -TODO
//			f[1][0][j] = f[3][0][j] + 2.0/3.0*rho[0][j]*u[X][0][j];
//			f[5][0][j] = f[7][0][j] + 0.5*(f[4][0][j] - f[2][0][j]) + 1.0/6.0*rho[0][j]*u[X][0][j];
//			f[8][0][j] = f[6][0][j] - 0.5*(f[4][0][j] - f[2][0][j]) + 1.0/6.0*rho[0][j]*u[X][0][j];
//		}else if( i == (nx-1) ){
//			rho[nx-1][j] = bNodes[k].value;
//			u[X][nx-1][j] = (f[0][nx-1][j] + f[2][nx-1][j] + f[4][nx-1][j] +
//							2*( f[1][nx-1][j] + f[5][nx-1][j] + f[8][nx-1][j])) / rho[nx-1][j] - 1;
//			u[Y][nx-1][j] = 0; // -TODO
//
//			f[3][nx-1][j] = f[1][nx-1][j] - 2.0/3.0*rho[nx-1][j]*u[X][nx-1][j];
//			f[7][nx-1][j] = f[5][nx-1][j] - 0.5*(f[4][nx-1][j] - f[2][nx-1][j]) - 1.0/6.0*rho[nx-1][j]*u[X][nx-1][j];
//			f[6][nx-1][j] = f[8][nx-1][j] + 0.5*(f[4][nx-1][j] - f[2][nx-1][j]) - 1.0/6.0*rho[nx-1][j]*u[X][nx-1][j];
//		}else{
//			cerr<<"No implementation found for requested constant pressure boundary node!"<<endl;
//		}
//	}
//}

void HeZouPressureNodes::addNode(int x, int y, int z, double val){
	ValueNode *v = new ValueNode(x, y, z, val);
	nodes.push_back(v);
}

HeZouPressureNodes::~HeZouPressureNodes() {
	// TODO Auto-generated destructor stub
}

