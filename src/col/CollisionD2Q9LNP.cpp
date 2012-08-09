/*
 * CollisionD2Q9LNP.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9LNP.h"

CollisionD2Q9LNP::CollisionD2Q9LNP() {

}

CollisionD2Q9LNP::~CollisionD2Q9LNP() {
    // TODO Auto-generated destructor stub
}

void CollisionD2Q9LNP::init(){
    cout<<"init LNP..."<<endl;
    double initConc = 1.0;
    ni = allocate2DArray(lm->n.y, lm->n.x);
    divTerm = allocate2DArray(lm->n.y, lm->n.x);
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            for(int d = 0; d < lm->UDIRS; d++){
                if(j == n.y/2){
                    f[0][j][i][d] = fEq(d, 0, 0, 1.0);
                }else{
                    f[0][j][i][d] = 0;
                }
            }
        }
    }

    double colPrefactor = ( 1 - 0.5 * w ) * PHYS_E_CHARGE * z / \
            (PHYS_KB * T * Pe);

    updateNi();
}

void CollisionD2Q9LNP::collide(){
    cout<<"D2Q9 LNP collision"<<endl;
    cout<<"pe:"<<Pe<<endl;
    updateDivTerm();
    updateNi();
    for(int j = 0; j < n.y; j++){
        for(int i = 0; i < n.x; i++){
            for(int d = 0; d < 9; d++){
                f[0][j][i][d] += w*( fEq(d, ux[j][i], uy[j][i], ni[j][i]) - f[0][j][i][d] ) +
                                 W[d] * colPrefactor * divTerm[j][i];
            }
        }
    }
    updateDivTerm();
    updateNi();
}

void CollisionD2Q9LNP::updateNi(){
    double temp;
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            temp = 0;
            for(int d = 0; d < lm->UDIRS; d++) temp += f[0][j][i][d];
            ni[j][i] = temp + 0.5*PHYS_E_CHARGE*z*divTerm[j][i] / \
                    ( PHYS_KB * T * Pe);
        }
    }
}

void CollisionD2Q9LNP::updateDivTerm(){
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            //x part
            if(i < lm->n.x - 1){
                divTerm[j][i] = ni[j][i] * dPsix[j][i] - ni[j][i+1] * dPsix[j][i+1];
            }else{
                divTerm[j][i] = ni[j][i-1] * dPsix[j][i-1] - ni[j][i] * dPsix[j][i];
            }

            //y part
            if(j < lm->n.y - 1){
                divTerm[j][i] = ni[j][i] * dPsix[j][i] - ni[j+1][i] * dPsix[j+1][i];
            }else{
                divTerm[j][i] = ni[j-1][i] * dPsix[j-1][i] - ni[j][i] * dPsix[j][i];
            }

            //DIVIDE BY dx
        }
    }
}

double CollisionD2Q9LNP::fEq(int d, double ux, double uy, double ni){
    double ret;
    double u2 = ux*ux + uy*uy;
    double cu = lm->ex[d]*ux + lm->ey[d]*uy;
    double c2 = c*c;
    if(d == 0){
        return -2.0/3.0*ni*u2/c2;
    }else if(d > 0 && d < 5){
        return ni/9.0*(1.5 + 1.5*cu/c2 + 4.5*cu*cu/(c2*c2) - 1.5*u2/c2);
    }else if(d > 4 && d < 9){
        return ni/36.0*(3.0 + 6.0*cu/c2 + 4.5*cu*cu/(c2*c2) - 1.5*u2/c2);
    }else{
        cerr<<"Unexpected state..."<<endl;
    }
    return ret;
}

void CollisionD2Q9LNP::dataToFile(string path){
    write2DArray(ni, NULL, path, n.x, n.y);
}
