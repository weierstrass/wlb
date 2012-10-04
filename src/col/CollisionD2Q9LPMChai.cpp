/*
 * CollisionD2Q9LPMChai.cpp
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9LPMChai.h"

CollisionD2Q9LPMChai::CollisionD2Q9LPMChai() {
	// TODO Auto-generated constructor stub

}

CollisionD2Q9LPMChai::~CollisionD2Q9LPMChai() {
	// TODO Auto-generated destructor stub
}

void CollisionD2Q9LPMChai::collide(){
	UnitHandlerLPM *uh = dynamic_cast<UnitHandlerLPM*>(unitHandler);
	//cout<<"Chai collision"<<endl;
	//cout<<"GRHS: "<<g_rhs(lm->n.x/2, 1)<<endl;
	for(int j = 0; j < n.y; j++){
		for(int i = 0; i < n.x; i++){
			psi[j][i] = getPsi(f[0][j][i], i, j);
			for(int d = 0; d < 9; d++){
				f[0][j][i][d] += w*( fEq(d, psi[j][i]) - f[0][j][i][d] ) + (0.5 - 1.0/w)/3.0*Wa[d]*g_rhs(i, j) *
								 uh->getTimeStep() * uh->getTimeStep();
			}
			psi[j][i] = getPsi(f[0][j][i], i, j);
		}
	}
}

/* allocate mem for psi  */
void CollisionD2Q9LPMChai::init(){
	psi = allocate2DArray(n.y, n.x);
	reset();
}

void CollisionD2Q9LPMChai::reset(){
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            psi[j][i] = 0.0;
            for(int d = 0; d < lm->UDIRS; d++){
                f[0][j][i][d] = fEq(d, psi[j][i]);
            }
        }
    }
}

double CollisionD2Q9LPMChai::getPsi(double *f, int i, int j){
	double ret = 0;
	for(int d = 1; d < 9; d++) ret += f[d];
	return 1/(1 - W[0])*ret;
}

double CollisionD2Q9LPMChai::fEq(int d, double psi){
	if(d == 0) return (W[0] - 1)*psi;
	return W[d]*psi;
}


/* Calculate first velocity moment of psi */
void CollisionD2Q9LPMChai::getDPsi(double **retX, double **retY){
    if(psi == NULL){
        cerr<<"Unable to compute grad(Psi), MEM ERROR!"<<endl;
        return;
    }
    //cout<<"lol"<<endl;
    double sum;
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            //sum = 0;
            for(int d = 1; d < lm->UDIRS; d++){
              //  cout<<"f: "<<f[0][j][i][d]<<endl;
              retX[j][i] += (f[0][j][i][d] - fEq(d, psi[j][i])) * lm->ex[d];
              retY[j][i] += (f[0][j][i][d] - fEq(d, psi[j][i])) * lm->ey[d];
              if(i == 0 && j == 0){
                  cout<<"f"<<d<<": "<<f[0][j][i][d]<<endl;
                  cout<<"fEQ"<<d<<": "<<fEq(d, psi[j][i])<<endl;
                  cout<<"RETY: "<<retY[j][i]<<endl;
              }
              //  sum += f[0][j][i][d];
            }
            if(j == 0){
                cout<<"i: "<<i<<endl;
                cout<<"retY_i: "<<retY[j][i]<<endl;
            }
          //  cout<<"SUM: "<<sum<<endl;
          //  cout<<"PSI: "<<psi[j][i]<<endl;
        }
    }

    cout<<"RETY0: "<<retY[0][0]<<endl;
    cout<<"RETY1: "<<retY[0][1]<<endl;
    cout<<"RETY2: "<<retY[0][2]<<endl;
    retY[0][0] = retY[0][1];
    retY[0][2] = retY[0][1];
    retY[lm->n.y-1][0] = retY[lm->n.y-1][1];
    retY[lm->n.y-1][2] = retY[lm->n.y-1][1];

//    cout<<"f_eq: "<<fEq(2, psi[1][lm->n.x/2])<<endl;
//    cout<<"f: "<<f[0][1][lm->n.x/2][2]<<endl;
//    for(int j = 0; j < lm->n.y-1; j++){
//        for(int i = 0; i < lm->n.x-1; i++){
//            retX[j][i] = psi[j][i+1] - psi[j][i];
//            retY[j][i] = psi[j+1][i] - psi[j][i];
//        }
//    }
//    for(int j = 0; j < lm->n.y; j++){
//        retY[j][lm->n.x-1] = retY[j][lm->n.x-2];
//    }
//
//    for(int i = 0; i < lm->n.x; i++){
//        retY[lm->n.y-1][i] = retY[lm->n.y-2][i];
//    }
}

