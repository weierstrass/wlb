/*
 * HeZouLPMChaiNodes.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include "HeZouLPMChaiNodes.h"

#define DIR1(i) 1 + (bdr + (i-1))%4
#define DIR5(i) 5 + (bdr + (i-1))%4

HeZouLPMChaiNodes::HeZouLPMChaiNodes() {
	// TODO Auto-generated constructor stub

}

HeZouLPMChaiNodes::~HeZouLPMChaiNodes() {
	// TODO Auto-generated destructor stub
}

void HeZouLPMChaiNodes::updateF(){
    cout<<"Chai bdry"<<endl;
	int i, j;
	double temp, rho, psi;
	for(int k = 0; k < nodes.size(); k++){
		i = nodes[k]->x;
		j = nodes[k]->y;
		rho = nodes[k]->v1;
		psi = cm->getPsi(f[0][j][i], i, j);
		if(i == 0 && j == 0){
			updateCornerNode(i, j, rho, psi, 0);
		}else if(i == lm->n.x-1 && j == 0){
			updateCornerNode(i, j, rho, psi, 1);
		} else if(i == lm->n.x-1 && j == lm->n.y-1){
			updateCornerNode(i, j, rho, psi, 2);
		}else if(i == 0 && j == lm->n.y-1){
			updateCornerNode(i, j, rho, psi, 3);
		}else if(i == 0){
			//cout<<"i == 0"<<endl;
			updateNode(i, j, rho, psi, 0);
		}else if(j == 0){
			//cout<<"j == 0"<<endl;
			updateNode(i, j, rho, psi, 1);
		}else if(i == lm->n.x-1){
			//cout<<"i == n.x-1"<<endl;
			updateNode(i, j, rho, psi, 2);
		}else if(j == lm->n.y-1){
			//cout<<"j == n.y-1"<<endl;
			updateNode(i, j, rho, psi, 3);
		}
	}
}

void HeZouLPMChaiNodes::updateNode(int i, int j, double rho, double psi, int bdr){
	double feqDiff = (cm->fEq(DIR1(1), psi) - cm->fEq(DIR1(3), psi));
	//cout<<"f_"<<DIR1(1)<<" = f_"<<DIR1(3)<<endl;
	f[0][j][i][DIR1(1)] = f[0][j][i][DIR1(3)] + feqDiff;
	//cout<<"f_"<<DIR5(5)<<"= -f_"<<DIR5(6)<<endl;
	f[0][j][i][DIR5(5)] = - f[0][j][i][DIR1(3)] \
						  - f[0][j][i][DIR5(6)] \
						  - f[0][j][i][DIR1(2)] \
						  - 0.5*feqDiff + 0.5*rho;
	//cout<<"f_"<<DIR5(8)<<endl;
	f[0][j][i][DIR5(8)] = - f[0][j][i][DIR1(3)] \
						  - f[0][j][i][DIR1(4)] \
						  - f[0][j][i][DIR5(7)] \
						  - 0.5*feqDiff + 0.5*rho;
}

void HeZouLPMChaiNodes::updateCornerNode(int i, int j, double rho, double psi, int bdr){
	double feqDiff1_3 = cm->fEq(DIR1(1), psi) - cm->fEq(DIR1(3), psi);
	double feqDiff2_4 = cm->fEq(DIR1(2), psi) - cm->fEq(DIR1(4), psi);
	f[0][j][i][DIR1(1)] = f[0][j][i][DIR1(3)] + feqDiff1_3;
	f[0][j][i][DIR1(2)] = f[0][j][i][DIR1(4)] + feqDiff2_4;
	f[0][j][i][DIR5(5)] = f[0][j][i][DIR5(7)] - 0.5*(feqDiff1_3 + feqDiff2_4);
	f[0][j][i][DIR5(8)] = - f[0][j][i][DIR1(3)] \
						  - f[0][j][i][DIR1(4)] \
						  - f[0][j][i][DIR5(7)] \
						  - 0.5*feqDiff1_3 + 0.5*rho;
	f[0][j][i][DIR5(6)] = - f[0][j][i][DIR1(3)] \
			  	  	  	  - f[0][j][i][DIR1(4)] \
			  	  	  	  - f[0][j][i][DIR5(7)] \
						  - 0.5*feqDiff2_4 + 0.5*rho;

}
void HeZouLPMChaiNodes::addNode(int x, int y, int z, double val){
	ValueNode *v = new ValueNode(x, y, z, val);
	nodes.push_back(v);
}
