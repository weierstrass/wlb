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
	double rho, temp, rhouy, rhoux;

	if(lm->DIM == 2){
		for(int k = 0; k < nodes.size(); k++){
			i = nodes[k]->x;
			j = nodes[k]->y;
			temp = f[0][j][i][0];
			f[0][j][i][0] = 0;
			rho = nodes[k]->v1;
			//cout<<i<<", "<<j<<endl;
			if(i == 0 && j == 0){
				bool knowns[]  = {1, 0, 0, 1, 1, 0, 0, 1, 0};
				updateCornerNode(knowns, i, j, rho);
			}else if(i == 0 && j == (lm->n.y-1)){
				cout<<"BOT LEFT"<<endl;
				bool knowns[]  = {1, 0, 1, 1, 0, 0, 1, 0, 0};
				updateCornerNode(knowns, i, j, rho);
			}else if(i == (lm->n.x-1) && j == 0){
				bool knowns[]  = {1, 1, 0, 0, 1, 0, 0, 0, 1};
				updateCornerNode(knowns, i, j, rho);
			}else if(i == (lm->n.x-1) && j == (lm->n.y-1)){
				bool knowns[]  = {1, 1, 1, 0, 0, 1, 0, 0, 0};
				updateCornerNode(knowns, i, j, rho);
			}else if(i == 0){
				rhoux = rho - (f[0][j][i][0] + f[0][j][i][2] + f[0][j][i][4] +
						2*( f[0][j][i][3] + f[0][j][i][6] + f[0][j][i][7]));

				rhouy = 0; // -TODO
				f[0][j][i][1] = f[0][j][i][3] + 2.0/3.0*rhoux;
				f[0][j][i][5] = f[0][j][i][7] + 0.5*(f[0][j][i][4] - f[0][j][i][2]) + 1.0/6.0*rhoux;
				f[0][j][i][8] = f[0][j][i][6] - 0.5*(f[0][j][i][4] - f[0][j][i][2]) + 1.0/6.0*rhoux;
			}else if( i == (lm->n.x-1) ){//RIGHT
				rho = nodes[k]->v1;
				rhoux = (f[0][j][i][0] + f[0][j][i][2] + f[0][j][i][4] +
						2*( f[0][j][i][1] + f[0][j][i][5] + f[0][j][i][8])) - rho;
				rhouy = 0; // -TODO
				f[0][j][i][3] = f[0][j][i][1] - 2.0/3.0*rhoux;
				f[0][j][i][7] = f[0][j][i][5] - 0.5*(f[0][j][i][4] - f[0][j][i][2]) - 1.0/6.0*rhoux;
				f[0][j][i][6] = f[0][j][i][8] + 0.5*(f[0][j][i][4] - f[0][j][i][2]) - 1.0/6.0*rhoux;
			}else if(j == 0){//bott node?
				rho = nodes[k]->v1;
				//cout<<"rho: "<<rho<<endl;
				rhouy = rho - (f[0][j][i][0] + f[0][j][i][1] + f[0][j][i][3] +
						2*( f[0][j][i][7] + f[0][j][i][4] + f[0][j][i][8]));

				//cout<<"uy: "<<uy<<endl;
				rhoux = 0; // -TODO
				f[0][j][i][2] = f[0][j][i][4] + 2.0/3.0*rhouy;
				f[0][j][i][5] = f[0][j][i][7] - 0.5*(f[0][j][i][1] - f[0][j][i][3]) + 1.0/6.0*rhouy;
				f[0][j][i][6] = f[0][j][i][8] + 0.5*(f[0][j][i][1] - f[0][j][i][3]) + 1.0/6.0*rhouy;
			}else if( j == (lm->n.y-1) ){
				rho = nodes[k]->v1;
				rhouy = (f[0][j][i][0] + f[0][j][i][1] + f[0][j][i][3] +
						2*( f[0][j][i][2] + f[0][j][i][5] + f[0][j][i][6])) - rho;
				rhoux = 0; // -TODO
				f[0][j][i][4] = f[0][j][i][2] - 2.0/3.0*rhouy;
				f[0][j][i][7] = f[0][j][i][5] + 0.5*(f[0][j][i][1] - f[0][j][i][3]) - 1.0/6.0*rhouy;
				f[0][j][i][8] = f[0][j][i][6] - 0.5*(f[0][j][i][1] - f[0][j][i][3]) - 1.0/6.0*rhouy;
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

void HeZouPressureNodes::updateCornerNode(const bool knowns[], int i, int j, double val){
	cout<<"handeling corner "<<endl;
	for(int d = 0; d < lm->UDIRS; d++){
		if(knowns[d]){
			f[0][j][i][lm->oppDirs[d]] = f[0][j][i][d];
			//cout<<"knowns d: "<<d<<endl;
		}
	}
	double temp = 0;
	for(int d = 0; d < lm->UDIRS; d++){
		if(knowns[d] || knowns[lm->oppDirs[d]]){
			temp += f[0][j][i][d];

		}
	}
	temp = 0.5*(val - temp);
	for(int d = 0; d < lm->UDIRS; d++){
		if(!knowns[d] && !knowns[lm->oppDirs[d]]){
			f[0][j][i][d] = temp;
			//cout<<"d: "<<d<<endl;
		}
	}
}
