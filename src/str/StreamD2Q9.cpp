/*
 * StreamD2Q9.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "StreamD2Q9.h"

StreamD2Q9::StreamD2Q9() {
	// TODO Auto-generated constructor stub

}

StreamD2Q9::~StreamD2Q9() {
	// TODO Auto-generated destructor stub
}

void StreamD2Q9::stream(){
	cout<<"stream D2Q9"<<endl;
	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x-1; i++){
			//horizontal streaming neg
			f[0][j][i][3] = f[0][j][i+1][3];
			f[0][j][i][6] = f[0][j][i+1][6];
			f[0][j][i][7] = f[0][j][i+1][7];
		}
		for(int i = n.x-1; i > 0; i--){
			//horizontal streaming pos
			f[0][j][i][1] = f[0][j][i-1][1];
			f[0][j][i][5] = f[0][j][i-1][5];
			f[0][j][i][8] = f[0][j][i-1][8];
		}
	}
	for(int i = 0; i < n.x; i++){
		for(int j = 0; j < n.y-1; j++){
			//vertical streaming neg
			f[0][j][i][4] = f[0][j+1][i][4];
			f[0][j][i][7] = f[0][j+1][i][7];
			f[0][j][i][8] = f[0][j+1][i][8];
		}
		for(int j = n.y-1; j > 0; j--){
			//vertical streaming pos
			f[0][j][i][2] = f[0][j-1][i][2];
			f[0][j][i][5] = f[0][j-1][i][5];
			f[0][j][i][6] = f[0][j-1][i][6];
		}
	}

	//print2DArray(f[0], n.x, n.y, 8);
}
