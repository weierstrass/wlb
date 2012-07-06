/*
 * CollisionD2Q9LPM.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "CollisionD2Q9LPM.h"


const double CollisionD2Q9LPM::Wa[9] = {0.0, 1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/12, 1.0/12, 1.0/12, 1.0/12};

CollisionD2Q9LPM::CollisionD2Q9LPM() {
}

CollisionD2Q9LPM::~CollisionD2Q9LPM() {
	// TODO Auto-generated destructor stub
}

void CollisionD2Q9LPM::dataToFile(){
	write2DArray(psi, NULL, "vis_scripts/data0/rho.csv", n.x, n.y);
}
