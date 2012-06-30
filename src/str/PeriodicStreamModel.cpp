/*
 * PeriodicStreamModel.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "PeriodicStreamModel.h"

PeriodicStreamModel::PeriodicStreamModel(int nx, int ny) : StreamModel(){
	cout<<"intin per"<<endl;
fv = new double*[6];
fh = new double*[6];
for(int i = 0; i < 6; i++){
	fv[i] = new double[nx];
	fh[i] = new double[ny];
}
}

void PeriodicStreamModel::init(){


	//init arrays...
}

void PeriodicStreamModel::updateF(double ***f){
//	//cout<<"pre:"<<endl;
//	//print2DArray(f[0], nx, ny);
//	//save boundaries...
//	for(int i = 0; i < nx; i++){
//		fv[0][i] = f[2][i][0];
//		fv[1][i] = f[5][i][0];
//		fv[2][i] = f[6][i][0];
//		fv[3][i] = f[4][i][ny-1];
//		fv[4][i] = f[7][i][ny-1];
//		fv[5][i] = f[8][i][ny-1];
//	}
//	for(int j = 0; j < ny; j++){
//		fh[0][j] = f[1][nx-1][j];
//		fh[1][j] = f[5][nx-1][j];
//		fh[2][j] = f[8][nx-1][j];
//		fh[3][j] = f[3][0][j];
//		fh[4][j] = f[6][0][j];
//		fh[5][j] = f[7][0][j];
//	}
//	StreamModel::updateF(f);
//	//periodic..
//	for(int i = 0; i < nx; i++){
//		f[4][i][0] = fv[3][i];
//		f[7][i][0] = fv[4][(i+1)%nx];
//		f[8][(i+1)%nx][0] = fv[5][i];
//		f[2][i][ny-1] = fv[0][i];
//		f[6][i][ny-1] = fv[2][(i+1)%nx];
//		f[5][(i+1)%nx][ny-1] = fv[1][i];
//	}
//	for(int j = 0; j < ny; j++){
//		f[1][0][j] = fh[0][j];
//		f[5][0][j] = fh[1][(j+1)%ny];
//		f[8][0][(j+1)%ny] = fh[2][j];
//		f[3][nx-1][j] = fh[3][j];
//		f[6][nx-1][j] = fh[4][(j+1)%ny];
//		f[7][nx-1][(j+1)%ny] = fh[5][j];
//	}
////	cout<<"post1:"<<endl;
////		print2DArray(f[0], nx, ny);
////		cout<<"post2:"<<endl;
////		print2DArray(f[2], nx, ny);
////		cout<<"post3:"<<endl;
////		print2DArray(f[3], nx, ny);
////		cout<<"post4:"<<endl;
////		print2DArray(f[4], nx, ny);
////		cout<<"post5:"<<endl;
////		print2DArray(f[5], nx, ny);
////		cout<<"post6:"<<endl;
////		print2DArray(f[6], nx, ny);
////		cout<<"post7:"<<endl;
////		print2DArray(f[7], nx, ny);
////		cout<<"post8:"<<endl;
////		print2DArray(f[8], nx, ny);
}

PeriodicStreamModel::~PeriodicStreamModel() {
	// TODO Auto-generated destructor stub
}

