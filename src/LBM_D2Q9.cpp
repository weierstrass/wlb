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
	fx = new double*[nx];
	fy = new double*[nx];
	for(int i = 0; i < nx; i++){
		rho[i] = new double[ny];
		ux[i] = new double[ny];
		uy[i] = new double[ny];
		fx[i] = new double[ny];
		fy[i] = new double[nx];
	}

	hwbbNodes = NULL;
	cpNodes = NULL;
	cvNodes = NULL;
	bflNodes = NULL;

	/* Set default stream model */
	//streamModel = new StreamModel(nx, ny);
	streamModel = new DefaultStreamModel(nx, ny);

//	/*init f*/
//	for(int i = 0; i < DIRS; i++){
//		for(int j = 0; j < nx; j++){
//			for(int k = 0; k < ny; k++){
//				//f[i][j][k] = k*j + j; // COLS ARE ADJACENT IN MEMORY d d d d p d d d d p d d d
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

	/* Set default constants */
	this->w = 1.0;
	this->c = 1.0;

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

	//TEMP - TODO
	double poi = 0;
	for(int j = 0; j < ny; j++){
		for(int i = 0; i < nx; i++){
			//ux[i][j] = a_poiseuilleVelocity(j, 0, ny-1, 0.12);
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
	streamModel->updateF(f);
}

/*
 * Update f according to the hard boundaries.
 */
void LBM_D2Q9::handleHardBoundaries(){
	/* Half way bounce back boundaries */
	if( hwbbNodes != NULL ){
		hwbbNodes->updateF(f);
	}
	/* Hard boundary nodes with BFL */
	if(bflNodes != NULL){
		bflNodes->updateF(f);
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
	stringstream ss, ssTemp;
	struct stat sb;
	for(int i = 0; ; i++){
		ss.str("");
		ss<<"vis_scripts/data";
		ss<<""<<i<<"/";
		if (!stat(ss.str().c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)){
			cout<<"creating directory: "<<ss.str()<<endl;
			mkdir(ss.str().c_str(), 0775);
			break;
		}
	}
	ssTemp.str("");
	ssTemp << ss.str();
	ssTemp << "ux.csv";
	write2DArray(ux, ssTemp.str(), nx, ny);
	ssTemp.str("");
	ssTemp << ss.str();
	ssTemp << "uy.csv";
	write2DArray(uy, ssTemp.str(), nx, ny);
	ssTemp.str("");
	ssTemp << ss.str();
	ssTemp << "rho.csv";
	write2DArray(rho, ssTemp.str(), nx, ny);
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

void LBM_D2Q9::setStreamModel(StreamModel *s){
	streamModel = s;
}

void LBM_D2Q9::setW(double w){
	this->w = w;
}

void LBM_D2Q9::setC(double c){
	this->c = c;
}

void LBM_D2Q9::addBFLNodes(BFLBoundaryNodes *bfl){
	bflNodes = bfl;
}
