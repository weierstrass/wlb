/*
 * aux.h
 * Andreas BŸlling, 2012
 * Auxillary routines
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
