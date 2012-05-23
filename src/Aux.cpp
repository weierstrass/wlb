/*
 * aux.h
 * Andreas BŸlling, 2012
 * Auxiliary routines
 */

#include "Aux.h"

/*
 * Array print routine for debugging.
 */
void print2DArray(double **f, int ni, int nj){
	for(int j = 0; j < nj; j++){
		for(int i = 0; i < ni; i++){
			cout<<" "<<f[i][j]<<" ";
			if(f[i][j] < 10) cout<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

/*
 *  Write 2D Array csv to file
 */
void write2DArray(double **a, bool **deadNodes, string file, int nx, int ny){
	cout<<"Writing data to "<<file<<"...";
	ofstream oFile;
		oFile.open(file.c_str());
		for(int i = 0; i < ny; i++){
			for(int j = 0; j < nx; j++){
				if(deadNodes[j][i]){
					oFile << "nan";
				}else{
					oFile << a[j][i];
				}
				if(j < nx-1) oFile << ",";
			}
			oFile << "\n";
		}
		oFile.close();
		cout<<" done."<<endl;
}

/*
 * Poiseuille velocity profile
 */
double poiseuilleVelocity(int x, int n1, int n2, double uMax){
	return -uMax * (x - n1) * (x - n2) / ( n2*n2/4 - n1*n2/2 - 3*n1*n1/4);
}

