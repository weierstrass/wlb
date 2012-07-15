/*
 * CollisionD2Q9LPMWang1to1.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9LPMWang1to1.h"

CollisionD2Q9LPMWang1to1::CollisionD2Q9LPMWang1to1() {
    // TODO Auto-generated constructor stub

}

CollisionD2Q9LPMWang1to1::~CollisionD2Q9LPMWang1to1() {
    // TODO Auto-generated destructor stub
}

double CollisionD2Q9LPMWang1to1::g_rhs(int i, int j){
    UnitHandlerLPM *uh = dynamic_cast<UnitHandlerLPM*>(unitHandler);
    return -prefactor*sinh(inSinh*psi[j][i])*uh->getTimeStep();
}

void CollisionD2Q9LPMWang1to1::init(){
    UnitHandlerLPM *uh = dynamic_cast<UnitHandlerLPM*>(unitHandler);

    double ninf = 1e-4*PHYS_N_A;
    double z = 1.0;
    double eps = 6.95*1e-10;
    double T = 273;
    double k = sqrt(2*ninf*z*z*PHYS_E_CHARGE*PHYS_E_CHARGE/(eps*PHYS_KB*T));

    cout<<"kkkdk: "<<PHYS_KB*T/(z*PHYS_E_CHARGE)<<endl;

    double l2 = uh->getCharLength();
    cout<<"l2: "<<l2<<endl;
    l2 *=l2;
    double V0 = uh->getCharVoltage();

    prefactor = l2/V0*2*z*PHYS_E_CHARGE*ninf/eps;
    inSinh = z*PHYS_E_CHARGE*V0/PHYS_KB/T;

    cout<<"k: "<<k<<", k^-1: "<<1/k<<endl;
    cout<<"l: "<<sqrt(l2)<<", V0: "<<V0<<endl;
    cout<<"pre: "<<prefactor<<"inSinh"<<inSinh<<endl;

    psi = allocate2DArray(n.y, n.x);
    for(int j = 0; j < n.y; j++){
        for(int i = 0; i < n.x; i++){
            psi[j][i] = 0.0;
            for(int d = 0; d < 9; d++) f[0][j][i][d] = fEq(d, psi[j][i]);
        }
    }
}
