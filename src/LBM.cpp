/*
 * LBM-D2Q9.cpp
 * Andreas BŸlling, 2012
 * Core file in 2D LBM solver.
 */

#include "LBM.h"

LBM::LBM(LatticeModel *lm, CollisionModel *cm, StreamModel *sm){
	//LBM::nx = lm->n.x;
	//LBM::ny = lm->n.y;
	latticeModel = lm;

	/* Allocate memory */
	f = allocate4DArray(lm->n.z, lm->n.y, lm->n.x, lm->UDIRS);

	rho = allocate3DArray(latticeModel->n.z,
			latticeModel->n.y,
			latticeModel->n.x);

	ux = allocate3DArray(latticeModel->n.z,
			latticeModel->n.y,
			latticeModel->n.x);

	uy = allocate3DArray(latticeModel->n.z,
			latticeModel->n.y,
			latticeModel->n.x);

	uz = allocate3DArray(latticeModel->n.z,
			latticeModel->n.y,
			latticeModel->n.x);

	cout<<"mem allocated.."<<endl;
	//u = allocate3DArray(lm->UDIRS, lm->n.x, lm->n.y);
	//rho = allocate2DArray(lm->n.x, lm->n.y);
	//f = allocate4DArray(lm->UDIRS, lm->n.x, lm->n.y, lm->n.z);
	//u = allocate4DArray(lm->DIM, lm->n.x, lm->n.y, lm->n.z);
	//rho = (double***)allocate4DArray(0, lm->n.x, lm->n.y, lm->n.z);
//	f = new double**[lm->UDIRS];
//	u = new double**[2];
//	force = new double**[lm->UDIRS];
//	for(int i = 0; i < DIRS; i++){
//		f[i] = new double*[nx];
//	}
//	for(int i = 0; i < DIRS; i++){
//		for(int j = 0; j < nx; j++){
//			f[i][j] = new double[ny];
//		}
//	}
//	for(int i = 0; i < 2; i++){
//		u[i] = new double*[nx];
//	}
//	for(int i = 0; i < 2; i++){
//		for(int j = 0; j < nx; j++){
//			u[i][j] = new double[ny];
//		}
//	}
//
//	rho = new double*[nx];
//	ux = new double*[nx];
//	uy = new double*[nx];
//	fx = new double*[nx];
//	fy = new double*[nx];
//	deadNodes = new bool*[latticeModel->n.x];
//	for(int i = 0; i < nx; i++){
////		rho[i] = new double[ny];
////		ux[i] = new double[ny];
////		uy[i] = new double[ny];
////		fx[i] = new double[ny];
////		fy[i] = new double[ny];
//		deadNodes[i] = new bool[ny];
//	}

//	hwbbNodes = NULL;
//	cpNodes = NULL;
//	cvNodes = NULL;
//	bflNodes = NULL;

//	for(int j = 0; j < nx; j++){
//		for(int k = 0; k < ny; k++){
//			rho[j][k] = 1.0;
//			ux[j][k] = 0;
//			uy[j][k] = 0;
//			fx[j][k] = 0;
//			fy[j][k] = 0;
//			deadNodes[j][k] = false;
//		}
//	}

	setCollisionModel(cm);
	cout<<"pk"<<endl;
	setStreamModel(sm);
}

/*
 * Initialize f, for now, start by just setting f = f_eq.
 */
void LBM::init(){
	collisionModel->init();
}

void LBM::collideAndStream(){
	cout<<"colliding..."<<endl;
	collisionModel->collide();
	cout<<"streaming..."<<endl;
	streamModel->stream();
}

void LBM::addBoundaryNodes(BoundaryNodes *bn){
	boundaryNodes.push_back(bn);
	bn->registerF(f);
	bn->registerLatticeModel(latticeModel);
}

/*
 * Calculate macroscopic variables: density and velocity field.
 */
void LBM::calcMacroscopicVars(){
	double *uTemp = new double[3];
	for(int k = 0; k < latticeModel->n.z; k++){
		for(int j = 0; j < latticeModel->n.y; j++){
			for(int i = 0; i < latticeModel->n.x; i++){
				rho[k][j][i] = collisionModel->getRho(f[k][j][i]);
				uTemp = collisionModel->getRhoU(f[k][j][i]);
				ux[k][j][i] = uTemp[X]/rho[k][j][i];
				uy[k][j][i] = uTemp[Y]/rho[k][j][i];
				uz[k][j][i] = uTemp[Z]/rho[k][j][i];
			}
		}
	}

}

void LBM::handleBoundaries(){
	for(int i = 0; i < boundaryNodes.size(); i++){
			boundaryNodes[i]->updateF();
	}
	cout<<"post:"<<endl;
	//print2DArray(f[0], latticeModel->n.x, latticeModel->n.y, 8);
}

/*
 * Write macroscopic variables to file.
 */
void LBM::dataToFile(){
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
	write2DArray(ux[0], NULL, ssTemp.str(), latticeModel->n.x, latticeModel->n.y);
	ssTemp.str("");
	ssTemp << ss.str();
	ssTemp << "uy.csv";
	write2DArray(uy[0], NULL, ssTemp.str(), latticeModel->n.x, latticeModel->n.y);
	ssTemp.str("");
	ssTemp << ss.str();
	ssTemp << "rho.csv";
	write2DArray(rho[0], NULL, ssTemp.str(), latticeModel->n.x, latticeModel->n.y);
}

/*
 * Print u components to stdout
 */
void LBM::printu(){
	cout<<"ux:"<<endl;
	print2DArray(ux[0], nx, ny);
	cout<<"uy:"<<endl;
	print2DArray(uy[0], nx, ny);
}

void LBM::printfi(int n){
	cout<<"f_"<<n<<":"<<endl;
	//print2DArray(f[0], nx, ny);todo
}

void LBM::addHalfWayBBNodes(HalfWayBBNodes *bbn){
	hwbbNodes = bbn;
	bbn->registerF(f);
	bbn->registerN(latticeModel->n);
	bbn->registerQ(latticeModel->UDIRS);
}

void LBM::setStreamModel(StreamModel *s){
	streamModel = s;
	streamModel->registerF(f);
	streamModel->registerN(latticeModel->n);
	streamModel->init();
}

void LBM::setCollisionModel(CollisionModel *cm){
	collisionModel = cm;
	collisionModel->registerF(f);
	collisionModel->registerN(latticeModel->n);
	collisionModel->registerLatticeModel(latticeModel);
	//cm->registerParams(c, w);
	//cm->registerRho(rho);
	//cm->registerU(u);
	//cm->registerUDIRS(latticeModel->UDIRS);
}

void LBM::setLatticeModel(LatticeModel *lm){
	latticeModel = lm;
}

void LBM::initVelocity(double** uxInit, double** uyInit){
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			//ux[i][j] = uxInit[i][j];
			//uy[i][j] = uyInit[i][j];
		}
	}
}

void LBM::initRho(double** rhoInit){
	for(int i = 0; i < nx; i++){
		for(int j = 0; j < ny; j++){
			//rho[i][j] = rhoInit[i][j];
		}
	}
}

//void LBM::setF(double fxi, double fyi, int x, int y){
//	//fx[x][y] = fxi;
//	//fy[x][y] = fyi;
//}

//
//void LBM::addConstantPressureBoundaryNodes(
//				ConstantPressureBoundaryNodes *cp){
//	cpNodes = cp;
//}
//
//void LBM::addConstantVelocityBoundaryNodes(
//				ConstantVelocityBoundaryNodes *cv){
//	cvNodes = cv;
//}
//
//void LBM::clearConstantVelocityBoundaryNodes(){
//	delete cvNodes;
//}

//
//void LBM::setW(double w){
//	this->w = w;
//}
//
//void LBM::setC(double c){
//	this->c = c;
//}
//
//void LBM::addBFLNodes(BFLBoundaryNodes *bfl){
//	bflNodes = bfl;
//}
//
//void LBM::addDeadNode(int x, int y){
//	deadNodes[x][y] = true;
//}
//
//double*** LBM::getRho(){
//	return rho;
//}
//
//int LBM::getNx(){
//	return nx;
//}
//
//int LBM::getNy(){
//	return ny;
//}

//double LBM::Si(int d, int i, int j){
//	int xt[9] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
//	//int yt[9] = {0, 0, -1, 0, 1, -1, -1, 1, 1};
//	int yt[9] = {0, 0, 1, 0, -1, 1, 1, -1, -1};
//	double W[9] = {W0, W1, W1, W1, W1, W2, W2, W2, W2};
//	double si = 0.0;
//	si = 3*W[d]*((xt[d] - ux[i][j])*fx[i][j] + (yt[d] - uy[i][j])*fy[i][j])/(c*c);
//	//cout<<"si_mid. "<<si<<", xt: "<<xt[d]<<endl;
//	//OOOOOOBBBBBBSSSSSSSS
//	si += 9*W[d]*( (ux[i][j]*xt[d] + yt[d]*uy[i][j]) * xt[d]*fx[i][j] +
//					(ux[i][j]*xt[d] + yt[d]*uy[i][j]) * yt[d]*fy[i][j] )/(c*c*c*c);
//
//	si *= (1 - 0.5*w);
//
//	//si *= 2*M_PI/65.0; //TODO
//
//	//si = W[d]*(xt[d]*fx[i][j] + yt[d]*fy[i][j])*3;
//	//cout<<"dir: "<<d<<", fx: "<<fx[i][j]<<", si: "<<si<<", ux: "<<ux[i][j]<<endl;
//	return si;
//}
//
//
////NIIIIII
//double LBM::Si2(int d, int i, int j){
//	int xt[9] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
//	//int yt[9] = {0, 0, -1, 0, 1, -1, -1, 1, 1};
//	int yt[9] = {0, 0, 1, 0, -1, 1, 1, -1, -1};
//	double W[9] = {W0, W1, W1, W1, W1, W2, W2, W2, W2};
//	double si = 0.0;
//
//	//si = -3*W[d]*((xt[d] - ux[i][j])*fx[i][j] + (yt[d] - uy[i][j])*fy[i][j])/(c*c);
//	//cout<<"si_mid. "<<si<<", xt: "<<xt[d]<<endl;
//	//si += -9*W[d]*( (ux[i][j]*xt[d] + yt[d]*uy[i][j]) * xt[d]*fx[i][j] +
//	//				(ux[i][j]*xt[d] + yt[d]*uy[i][j]) * yt[d]*fy[i][j] )/(c*c*c*c);
//	//cout<<"dir: "<<d<<", fx: "<<fx[i][j]<<", si: "<<si<<", ux: "<<ux[i][j]<<endl;
//	return si;
//}

//	for(int d = 0; d < latticeModel->UDIRS; d++){
//		for(int i = 0; i < nx; i++){
//			for(int j = 0; j < ny; j++){
//				//for(int k = 0; )
//				//f[d][i][j] = collisionModel->fEq(i, j, d);
//			}
//		}
//	}
	//cout<<"nx:"<<nx<<", ny:"<<ny<<", w:"<<w<<", c:"<<c<<endl;
	//	/*init f for debugging*/
	//	for(int i = 0; i < DIRS; i++){
	//		for(int j = 0; j < nx; j++){
	//			for(int k = 0; k < ny; k++){
	//				//f[i][j][k] = k*j + j; // COLS ARE ADJACENT IN MEMORY d d d d p d d d d p d d d
	//			}
	//		}
	//	}
/*
 * Apply chosen boundary conditions for
 * inlet and outlet
 */
void LBM::handleWetBoundaries(){
	/* Constant pressure boundaries */
//	if( cpNodes != NULL ){
		//cpNodes->updateF(f, u, rho);
	//}
	/* Constant velocity boundaries */
	//if( cvNodes != NULL ){
		//cvNodes->updateF(f, u, rho);
	//}
}

/*
 * Update f according to the hard boundaries.
 */
void LBM::handleHardBoundaries(){
	/* Half way bounce back boundaries */
	if( hwbbNodes != NULL ){
		//hwbbNodes->updateF();
	}
	/* Hard boundary nodes with BFL */
	//if(bflNodes != NULL){
		//bflNodes->updateF(f[0], ux, uy);
	//}

}
