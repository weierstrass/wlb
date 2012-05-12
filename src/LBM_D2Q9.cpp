/*
 * LBM-D2Q9.cpp
 * Andreas BŸlling, 2012
 * Core file in 2D LBM solver.
 */

#include "LBM_D2Q9.h"

LBM_D2Q9::LBM_D2Q9(int nx, int ny){
	LBM_D2Q9::nx = nx;
	LBM_D2Q9::ny = ny;

	/* Allocate memory */
	f = new double**[9];
	for(int i = 0; i < DIRS; i++){
		f[i] = new double*[nx];
	}
	for(int i = 0; i < DIRS; i++){
		for(int j = 0; j < nx; j++){
			f[i][j] = new double[ny];
		}
	}

	rho = new double*[nx];
	ux = new double*[nx];
	uy = new double*[nx];
	for(int i = 0; i < nx; i++){
		rho[i] = new double[ny];
		ux[i] = new double[ny];
		uy[i] = new double[ny];
	}

	hwbbNodes = NULL;
	cpNodes = NULL;
	cvNodes = NULL;

	/*init f*/
//	for(int i = 0; i < DIRS; i++){
//		for(int j = 0; j < nx; j++){
//			for(int k = 0; k < ny; k++){
//				//f[i][j][k] = k*j; // COLS ARE ADJACENT IN MEMORY d d d d p d d d d p d d d
//			}
//		}
//	}
//	for(int j = 0; j < nx; j++){
//		for(int k = 0; k < ny; k++){
//			rho[j][k] = 0;
//			ux[j][k] = 0;
//			uy[j][k] = 0;
//		}
//	}

	/* Set constants */
	w = 1.67;
	c = 1.0;

	cout<<"nx:"<<nx<<", ny:"<<ny<<", w:"<<w<<", c:"<<c<<endl;
}

/*
 * Initialize f, for now, start by just setting f = f_eq.
 */
void LBM_D2Q9::init(){
	double u2, ux2, uy2, uxy;
	double  c23i = 3.0/(c*c), c23i_5 = 0.5*c23i, c23i2_5 = c23i*c23i*0.5;

	/* Constant rho */
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			rho[i][j] = 1.0;
		}
	}

	/* f = f_eq */
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			ux2 = ux[i][j]*ux[i][j];
			uy2 = uy[i][j]*uy[i][j];
			uxy = ux[i][j]*uy[i][j];
			u2 = ux2 + uy2;

			f[0][i][j] = W0*rho[i][j]*( 1 - u2*c23i_5 );
			f[1][i][j] = W1*rho[i][j]*( 1 + ux[i][j]*c23i + ux2*c23i2_5 - u2*c23i_5 );
			f[2][i][j] = W1*rho[i][j]*( 1 + uy[i][j]*c23i + uy2*c23i2_5 - u2*c23i_5 );
			f[3][i][j] = W1*rho[i][j]*( 1 - ux[i][j]*c23i + ux2*c23i2_5 - u2*c23i_5 );
			f[4][i][j] = W1*rho[i][j]*( 1 - uy[i][j]*c23i + uy2*c23i2_5 - u2*c23i_5 );
			f[5][i][j] = W2*rho[i][j]*( 1 + ( ux[i][j] + uy[i][j] )*c23i + (ux2 + uxy + uy2)*c23i2_5 -
											u2*c23i_5 );
			f[6][i][j] = W2*rho[i][j]*( 1 + ( -ux[i][j] + uy[i][j] )*c23i + (ux2 - uxy + uy2)*c23i2_5 -
											u2*c23i_5 );
			f[7][i][j] = W2*rho[i][j]*( 1 - ( ux[i][j] + uy[i][j] )*c23i + (ux2 + uxy + uy2)*c23i2_5 -
											u2*c23i_5 );
			f[8][i][j] = W2*rho[i][j]*( 1 + ( ux[i][j] - uy[i][j] )*c23i + (ux2 - uxy + uy2)*c23i2_5 -
											u2*c23i_5 );
		}
	}
}

/*
 * Collision step according to a simple BGK relaxation
 */
void LBM_D2Q9::BGKCollision(){
	double u2, ux2, uy2, uxy;
	double  c23i = 3.0/(c*c), c23i_5 = 0.5*c23i, c23i2_5 = c23i*c23i*0.5;
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){

			u2 = ux[i][j]*ux[i][j] + uy[i][j]*uy[i][j];
			ux2 = ux[i][j]*ux[i][j];
			uy2 = uy[i][j]*uy[i][j];
			uxy = ux[i][j]*uy[i][j];

			//update f
			f[0][i][j] += w*( W0*rho[i][j]*( 1 - u2*c23i_5 ) - f[0][i][j] );
			f[1][i][j] += w*( W1*rho[i][j]*( 1 + ux[i][j]*c23i + ux2*c23i2_5 - u2*c23i_5 ) - f[1][i][j] );
			f[2][i][j] += w*( W1*rho[i][j]*( 1 + uy[i][j]*c23i + uy2*c23i2_5 - u2*c23i_5 ) - f[2][i][j] );
			f[3][i][j] += w*( W1*rho[i][j]*( 1 - ux[i][j]*c23i + ux2*c23i2_5 - u2*c23i_5 ) - f[3][i][j] );
			f[4][i][j] += w*( W1*rho[i][j]*( 1 - uy[i][j]*c23i + uy2*c23i2_5 - u2*c23i_5 ) - f[4][i][j] );
			f[5][i][j] += w*( W2*rho[i][j]*( 1 + ( ux[i][j] + uy[i][j] )*c23i + (ux2 + uxy + uy2)*c23i2_5 -
											u2*c23i_5 ) - f[5][i][j] );
			f[6][i][j] += w*( W2*rho[i][j]*( 1 + ( -ux[i][j] + uy[i][j] )*c23i + (ux2 - uxy + uy2)*c23i2_5 -
											u2*c23i_5 ) - f[6][i][j] );
			f[7][i][j] += w*( W2*rho[i][j]*( 1 - ( ux[i][j] + uy[i][j] )*c23i + (ux2 + uxy + uy2)*c23i2_5 -
											u2*c23i_5 ) - f[7][i][j] );
			f[8][i][j] += w*( W2*rho[i][j]*( 1 + ( ux[i][j] - uy[i][j] )*c23i + (ux2 - uxy + uy2)*c23i2_5 -
											u2*c23i_5 ) - f[8][i][j] );
		}
	}
}

/*
 * Calculate macroscopic variables: density and velocity field.
 */
void LBM_D2Q9::calcMacroscopicVars(){
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			rho[i][j] = 0;
			for(int k = 0; k < DIRS; k++) rho[i][j] += f[k][i][j];
			ux[i][j] = f[1][i][j] + f[8][i][j] + f[5][i][j] - (f[3][i][j] + f[6][i][j] + f[7][i][j]);
			ux[i][j] /= rho[i][j];
			uy[i][j] = f[2][i][j] + f[5][i][j] + f[6][i][j] - (f[7][i][j] + f[4][i][j] + f[8][i][j]);
			uy[i][j] /= rho[i][j];
		}
	}
}

/*
 * Streaming step
 * Periodic boundaries might be a good idea here
 * then if no other boundary conds. per is used. - TODO
 * note: memmove(dest, source, length)
 */
void LBM_D2Q9::stream(){
	//cout<<"pre:"<<endl;
	//print2DArray(f[1], nx, ny);
	for(int i = 0; i < nx; i++){
		memmove(&f[2][i][0],&f[2][i][1],(ny-1)*sizeof(double));
		memmove(&f[4][i][1],&f[4][i][0],(ny-1)*sizeof(double));
		memmove(&f[5][i][0],&f[5][i][1],(ny-1)*sizeof(double));
		memmove(&f[6][i][0],&f[6][i][1],(ny-1)*sizeof(double));
		memmove(&f[7][i][1],&f[7][i][0],(ny-1)*sizeof(double));
		memmove(&f[8][i][1],&f[8][i][0],(ny-1)*sizeof(double));
	}

	for(int j = 0; j < ny; j++){
		for(int i = 0; i < nx-1; i++){
			f[3][i][j] = f[3][i+1][j];
			f[6][i][j] = f[6][i+1][j];
			f[7][i][j] = f[7][i+1][j];
		}
		for(int i = nx-1; i > 0; i--){
			f[1][i][j] = f[1][i-1][j];
			f[5][i][j] = f[5][i-1][j];
			f[8][i][j] = f[8][i-1][j];
		}
	}

	//print2DArray(f[2], nx, ny);

	//printfi(3);
/*
	cout<<"post1:"<<endl;
	print2DArray(f[1], nx, ny);
	cout<<"post2:"<<endl;
	print2DArray(f[2], nx, ny);
	cout<<"post3:"<<endl;
	print2DArray(f[3], nx, ny);
	cout<<"post4:"<<endl;
	print2DArray(f[4], nx, ny);
	cout<<"post5:"<<endl;
	print2DArray(f[5], nx, ny);
	cout<<"post6:"<<endl;
	print2DArray(f[6], nx, ny);
	cout<<"post7:"<<endl;
	print2DArray(f[7], nx, ny);
	cout<<"post8:"<<endl;
	print2DArray(f[8], nx, ny);*/
}

/*
 * Update f according to the hard boundaries.
 */
void LBM_D2Q9::handleHardBoundaries(){
	/* Half way bounce back boundaries*/
	if( hwbbNodes != NULL ){
		hwbbNodes->updateF(f);
	}
}

/*
 * Apply chosen boundary conditions for
 * inlet and outlet
 */
void LBM_D2Q9::handleWetBoundaries(){
	/* Constant pressure boundaries */
	if( cpNodes != NULL ){
		cpNodes->updateF(f, ux, uy, rho);
	}
	/* Constant velocity boundaries */
	if( cvNodes != NULL ){
		cvNodes->updateF(f, ux, uy, rho);
	}
}

/*
 * Write macroscopic variables to file.
 */
void LBM_D2Q9::dataToFile(){
	write2DArray(ux, "vis_scripts/ux.csv", nx, ny);
	write2DArray(uy, "vis_scripts/uy.csv", nx, ny);
	write2DArray(rho, "vis_scripts/rho.csv", nx, ny);
}

/*
 * Print u components to stdout
 */
void LBM_D2Q9::printu(){
	cout<<"ux:"<<endl;
	print2DArray(ux, nx, ny);
	cout<<"uy:"<<endl;
	print2DArray(uy, nx, ny);
}

void LBM_D2Q9::printfi(int n){
	cout<<"f_"<<n<<":"<<endl;
	print2DArray(f[n], nx, ny);
}

void LBM_D2Q9::addHalfWayBBNodes(HalfWayBBNodes *bbn){
	hwbbNodes = bbn;
}

void LBM_D2Q9::addConstantPressureBoundaryNodes(
				ConstantPressureBoundaryNodes *cp){
	cpNodes = cp;
}

void LBM_D2Q9::addConstantVelocityBoundaryNodes(
				ConstantVelocityBoundaryNodes *cv){
	cvNodes = cv;
}
