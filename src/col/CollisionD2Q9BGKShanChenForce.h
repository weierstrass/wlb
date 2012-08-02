/*
 * CollisionD2Q9BGKShanChenForce.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9BGKSHANCHENFORCE_H_
#define COLLISIOND2Q9BGKSHANCHENFORCE_H_

#include "CollisionD2Q9BGK.h"

class CollisionD2Q9BGKShanChenForce: public CollisionD2Q9BGK {
public:
    CollisionD2Q9BGKShanChenForce();
    virtual ~CollisionD2Q9BGKShanChenForce();
    void init();
    void collide();
    void setForce(double **fx, double **fy){this->fx = fx; this->fy = fy;};
    void dataToFile(string path);
    double ***getVelocityField();
protected:
    double **fx;
    double **fy;
    double *getRhoU(double *f, double ffx, double ffy);
    double *getRhoUEq(double *f, double ffx, double ffy);
};

#endif /* COLLISIOND2Q9BGKSHANCHENFORCE_H_ */
