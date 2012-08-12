/*
 * CollisionD2Q9BGK.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Collision operator for incompressible flow.
 * Navier-stokes.
 * BGK type collision
 */

#include "CollisionD2Q9BGK.h"

CollisionD2Q9BGK::CollisionD2Q9BGK() : CollisionD2Q9(){
    rho = NULL;
    ux = NULL;
    uy = NULL;
}

CollisionD2Q9BGK::~CollisionD2Q9BGK() {
	// TODO Auto-generated destructor stub
}

void CollisionD2Q9BGK::collide(){
    cout<<"D2Q9 BGK collision"<<endl;

	double rho;
	double *rhoU = new double[3];
	for(int j = 0; j < n.y; j++){
	    for(int i = 0; i < n.x; i++){
	        //skip the fullway bb nodes..
	        if(skip[j][i]) continue;
			rho = getRho(f[0][j][i]);
			rhoU = getRhoU(f[0][j][i]);
			for(int d = 0; d < 9; d++){
				f[0][j][i][d] += w*( fEq(d, rho, rhoU[X]/rho, rhoU[Y]/rho) - f[0][j][i][d] );
			}
		}
	}
}

void CollisionD2Q9BGK::setW(double w){
	cout<<"w: "<<w<<endl;
	this->w = w;
}

double CollisionD2Q9BGK::fEq(int d, double rho, double ux, double uy){
    double cu = lm->ex[d]*ux + lm->ey[d]*uy;
    double c2 = c*c;
    double u2 = ux*ux + uy*uy;
    return W[d]*rho*(1 + 3.0/c2*(cu) \
                       + 4.5/(c2*c2)*(cu*cu) \
                       - 1.5/c2*u2);
}


double CollisionD2Q9BGK::getRho(double *f){
    double rho = 0;
    for(int i = 0; i < 9; i++) rho += f[i];
    return rho;
}

double *CollisionD2Q9BGK::getRhoU(double *f){
    double *u = new double[3];
    u[X] = f[1] + f[8] + f[5] - (f[3] + f[6] + f[7]);
    u[Y] = f[2] + f[5] + f[6] - (f[7] + f[4] + f[8]);
    u[Z] = -1;
    return u;
}

void CollisionD2Q9BGK::init(){
	cout<<"init f: f=f_eq"<<endl;
	double rho;
	//double *rhoU;
	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x; i++){
			rho = 1.0;
			for(int d = 0; d < 9; d++){
				f[0][j][i][d] = fEq(d, rho, 0, 0);
			}
		}
	}

   //print2DArray(f[0], lm->n.x, lm->n.y, 0);
}

void CollisionD2Q9BGK::dataToFile(string path){
    if(rho == NULL) rho = allocate2DArray(lm->n.y, lm->n.x);
    if(ux == NULL) ux = allocate2DArray(lm->n.y, lm->n.x);
    if(uy == NULL) uy = allocate2DArray(lm->n.y, lm->n.x);
    cout<<"mem allocated"<<endl;
    double *rhoUTemp = new double[3];
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            rho[j][i] = getRho(f[0][j][i]);
            rhoUTemp = getRhoU(f[0][j][i]);
            ux[j][i] = rhoUTemp[X]/rho[j][i];
            uy[j][i] = rhoUTemp[Y]/rho[j][i];
        }
    }
    cout<<"vals calced"<<endl;
    stringstream ss, ssTemp;
    struct stat sb;
    ss.str("");
    ss<<"vis_scripts/"<<path;
    if (!stat(ss.str().c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)){
        cout<<"creating directory: "<<ss.str()<<endl;
        mkdir(ss.str().c_str(), 0775);
    }

//    stringstream ss, ssTemp;
//    struct stat sb;
//    for(int i = 0; ; i++){
//        ss.str("");
//        ss<<"vis_scripts/data";
//        ss<<""<<i<<"/";
//        if (!stat(ss.str().c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)){
//            cout<<"creating directory: "<<ss.str()<<endl;
//            mkdir(ss.str().c_str(), 0775);
//            break;
//        }
//    }
    ssTemp.str("");
    ssTemp << ss.str();
    ssTemp << "ux.csv";
    write2DArray(ux, NULL, ssTemp.str(), lm->n.x, lm->n.y);
    ssTemp.str("");
    ssTemp << ss.str();
    ssTemp << "uy.csv";
    write2DArray(uy, NULL, ssTemp.str(), lm->n.x, lm->n.y);
    ssTemp.str("");
    ssTemp << ss.str();
    ssTemp << "rho.csv";
    write2DArray(rho, NULL, ssTemp.str(), lm->n.x, lm->n.y);
}

