/*
 * CollisionD2Q9LNP.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Nernst-Planck collision operator
 */

#include "CollisionD2Q9LNP.h"
//#define DT  1.0

CollisionD2Q9LNP::CollisionD2Q9LNP() {
    ux = NULL;
    uy = NULL;
    dPsix = NULL;
    dPsiy = NULL;
    skip = NULL;
}

CollisionD2Q9LNP::~CollisionD2Q9LNP() {
    // TODO Auto-generated destructor stub
}

void CollisionD2Q9LNP::init(){
    cout<<"init LNP..."<<endl;

    ni = allocate2DArray(lm->n.y, lm->n.x);
   // rhs = allocate2DArray(lm->n.y, lm->n.x);
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            ni[j][i] = initC;
            for(int d = 0; d < lm->UDIRS; d++){
                f[0][j][i][d] = fEq(d, 0, 0, initC);
            }
        }
    }

    colPrefactor = (( 1 - 0.5 * w ) * PHYS_E_CHARGE * z) / \
            (PHYS_KB * T * Pe);
    cout<<"!!!!!!!!colpref: "<<colPrefactor<<endl;
    cout<<"pe "<<Pe<<endl;
    cout<<"T "<<T<<endl;
    cout<<"z "<<z<<endl;

    updateNi();
}

void CollisionD2Q9LNP::reset(){
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            for(int d = 0; d < lm->UDIRS; d++){
              //  cout<<"PRE: "<<f[0][j][i][d]<<endl;
                f[0][j][i][d] = fEq(d, 0, 0, ni[j][i]);
                //cout<<"POST: "<<f[0][j][i][d]<<endl;
            }
        }
    }
}

void CollisionD2Q9LNP::collide(){
    updateNi();
    // cout<<"D2Q9 LNP collision"<<endl;
    // cout<<"pe:"<<Pe<<endl;
    double pref = (PHYS_E_CHARGE * z) / (PHYS_KB * T * Pe);
    cout<<"pref: "<<pref<<endl;
    cout<<"dPsiY: "<<dPsiy[1][lm->n.x/2]<<endl;
    cout<<"dPsiX: "<<dPsix[1][lm->n.x/2]<<endl;
    cout<<"RHS: "<<rhs[1][lm->n.x/2]<<endl;
    cout<<"F_2: "<<f[0][1][lm->n.x/2][2]<<endl;
    cout<<"d2psi = "<<dPsiy[2][lm->n.x/2] - dPsiy[1][lm->n.x/2]<<" = "<<
            (rhs[1][lm->n.x/2] + rhs[2][lm->n.x/2])*0.5<<endl;
    cout<<"pref*dpsiy: "<<-dPsiy[1][lm->n.x/2]*pref<<endl;
    for(int j = 0; j < n.y; j++){
        for(int i = 0; i < n.x; i++){
           // cout<<"i: "<<i<<endl;
           // cout<<"j: "<<j<<endl;
           // if(skip != NULL && skip[j][i]){continue;}
            for(int d = 0; d < 9; d++){
                f[0][j][i][d] += w*( fEq(d, ux[j][i] - pref*dPsix[j][i],
                                            uy[j][i] - pref*dPsiy[j][i],
                                            ni[j][i]) - f[0][j][i][d] ) +
                                 W[d] * colPrefactor *ni[j][i] * rhs[j][i];
             //   cout<<"RHS: "<<rhs[j][i]<<endl;
            }
        }
    }
    cout<<"colprefactor: "<<colPrefactor;
    updateNi();

    double sum = 0;
    double sumCol = 0;
    for(int j = 0; j < lm->n.y; j++){
        sumCol += ni[j][lm->n.x/2];
        for(int i = 0; i < lm->n.x; i++){
            sum += ni[j][1];
        }
    }

    cout<<"SUM: "<<sum<<", SUMCOL: "<<sumCol<<", SUM/3: "<<sum/3.0<<endl;

}

void CollisionD2Q9LNP::updateNi(){
    double temp;
   // cout<<"Z: "<<z<<endl;
   // cout<<"rhs: "<<rhs[1][lm->n.x/2]<<endl;
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            //if(skip != NULL && skip[j][i]){continue;}
            temp = 0;
            for(int d = 0; d < lm->UDIRS; d++) temp += f[0][j][i][d];
            //cout<<"Z: "<<z<<endl;
            ni[j][i] = temp + 0.5*PHYS_E_CHARGE*z*ni[j][i]*rhs[j][i] /\
                    ( PHYS_KB * T * Pe );
           // cout<<"temp: "<<temp<<endl;
          ///
        }
    }
 //   cout<<"RHS2: "<<rhs[1][lm->n.x/2]<<endl;
 //   cout<<"ni: "<<ni[1][lm->n.x/2]<<endl<<endl;
}

//void CollisionD2Q9LNP::updateDivTerm(){
//    for(int j = 0; j < lm->n.y; j++){
//        for(int i = 0; i < lm->n.x; i++){
//            //x part
//            if(i < lm->n.x - 1){
//                divTerm[j][i] = ni[j][i] * dPsix[j][i] - ni[j][i+1] * dPsix[j][i+1];
//            }else{
//                divTerm[j][i] = ni[j][i-1] * dPsix[j][i-1] - ni[j][i] * dPsix[j][i];
//            }
//
//            //y part
//            if(j < lm->n.y - 1){
//                divTerm[j][i] = ni[j][i] * dPsix[j][i] - ni[j+1][i] * dPsix[j+1][i];
//            }else{
//                divTerm[j][i] = ni[j-1][i] * dPsix[j-1][i] - ni[j][i] * dPsix[j][i];
//            }
//
//            //DIVIDE BY dx
//        }
//    }
//}

double CollisionD2Q9LNP::fEq(int d, double ux, double uy, double ni){
    double ret;
   // cout<<"uy: "<<uy<<endl;
    double u2 = ux*ux + uy*uy;
    double cu = lm->ex[d]*ux + lm->ey[d]*uy;
  //  cout<<"CU: "<<cu<<endl;
    double c2 = c*c;
    if(d == 0){
        //cout<<"D = 0: "<<-2.0/3.0*ni*u2/c2<<endl;
        return -2.0/3.0*ni*u2/c2;
    }else if(d > 0 && d < 5){
       /// cout<<"D = 1234: "<<ni/9.0*(1.5 + 1.5*cu/c2 + 4.5*cu*cu/(c2*c2) - 1.5*u2/c2)<<endl;
        return ni/9.0*(1.5 + 1.5*cu/c2 + 4.5*cu*cu/(c2*c2) - 1.5*u2/c2);
    }else if(d > 4 && d < 9){
       // cout<<"D = 5678: "<<ni/36.0*(3.0 + 6.0*cu/c2 + 4.5*cu*cu/(c2*c2) - 1.5*u2/c2)<<endl;
        return ni/36.0*(3.0 + 6.0*cu/c2 + 4.5*cu*cu/(c2*c2) - 1.5*u2/c2);
    }else{
        cerr<<"Unexpected state..."<<endl;
    }
    return ret;
}

double CollisionD2Q9LNP::fEq(int d, int i, int j){
    return fEq(d, ux[j][i], uy[j][i], ni[j][i]);
}

void CollisionD2Q9LNP::dataToFile(string path){
    write2DArray(ni, NULL, path, n.x, n.y);
}
