/*
 * CollisionD2Q9LPMChaiRHS.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9LPMChaiRHS.h"

CollisionD2Q9LPMChaiRHS::CollisionD2Q9LPMChaiRHS() {
    // TODO Auto-generated constructor stub

}

CollisionD2Q9LPMChaiRHS::~CollisionD2Q9LPMChaiRHS() {
    // TODO Auto-generated destructor stub
}

double CollisionD2Q9LPMChaiRHS::g_rhs(int i, int j){
    //cout<<"PE RHS: "<<rhs[j][i]<<endl;
    return rhs[j][i];
}
