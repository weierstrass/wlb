/*
 * StreamD2Q9Periodic.cpp
 * Andreas Bülling, 2012
 *
 * Peridoic 2D streaming.
 */

#include "StreamD2Q9Periodic.h"

StreamD2Q9Periodic::StreamD2Q9Periodic() {
	fh = NULL;
	fv = NULL;
}

void StreamD2Q9Periodic::init(){
	cout<<"Allocating memory for aux. array in periodic stream..."<<endl;
	fv = new double*[6];
	fh = new double*[6];
	for(int i = 0; i < 6; i++){
		fv[i] = new double[n.x];
		fh[i] = new double[n.y];
	}
}

StreamD2Q9Periodic::~StreamD2Q9Periodic() {
	// TODO Auto-generated destructor stub
}

void StreamD2Q9Periodic::stream(){
	//cout<<"pre:"<<endl;
	//print2DArray(f[0], nx, ny);

	//save boundaries...
	for(int i = 0; i < n.x; i++){
		fv[0][i] = f[0][0][i][7];
		fv[1][i] = f[0][0][i][4];
		fv[2][i] = f[0][0][i][8];
		fv[3][i] = f[0][n.y-1][i][2];
		fv[4][i] = f[0][n.y-1][i][5];
		fv[5][i] = f[0][n.y-1][i][6];
	}
	for(int j = 0; j < n.y; j++){
		fh[0][j] = f[0][j][n.x-1][1];
		fh[1][j] = f[0][j][n.x-1][5];
		fh[2][j] = f[0][j][n.x-1][8];
		fh[3][j] = f[0][j][0][3];
		fh[4][j] = f[0][j][0][6];
		fh[5][j] = f[0][j][0][7];
	}
	StreamD2Q9::stream();
	//periodic..
	for(int i = 0; i < n.x; i++){
		f[0][0][i][2] = fv[3][i];
		f[0][0][(i+1)%n.x][5] = fv[4][i];
		f[0][0][i][6] = fv[5][(i+1)%n.x];
		f[0][n.y-1][i][4] = fv[1][i];
		f[0][n.y-1][i][7] = fv[0][(i+1)%n.x];
		f[0][n.y-1][(i+1)%n.x][8] = fv[2][i];
	}
	for(int j = 0; j < n.y; j++){
		f[0][j][0][1] = fh[0][j];
		f[0][(j+1)%n.y][0][5] = fh[1][j];
		f[0][j][0][8] = fh[2][(j+1)%n.y];
		f[0][j][n.x-1][3] = fh[3][j];
		f[0][(j+1)%n.y][n.x-1][6] = fh[4][j];
		f[0][j][n.x-1][7] = fh[5][(j+1)%n.y];
	}
//	cout<<"post1:"<<endl;
//		print2DArray(f[0], nx, ny);
//		cout<<"post2:"<<endl;
//		print2DArray(f[2], nx, ny);
//		cout<<"post3:"<<endl;
//		print2DArray(f[3], nx, ny);
//		cout<<"post4:"<<endl;
//		print2DArray(f[4], nx, ny);
//		cout<<"post5:"<<endl;
//		print2DArray(f[5], nx, ny);
//		cout<<"post6:"<<endl;
//		print2DArray(f[6], nx, ny);
//		cout<<"post7:"<<endl;
//		print2DArray(f[7], nx, ny);
//		cout<<"post8:"<<endl;
//		print2DArray(f[8], nx, ny);
}

