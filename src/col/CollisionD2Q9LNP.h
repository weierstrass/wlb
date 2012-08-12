/*
 * CollisionD2Q9LNP.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LNP_H_
#define COLLISIOND2Q9LNP_H_

#include <string.h>
#include "CollisionD2Q9.h"
#include "../Aux.h"

class CollisionD2Q9LNP: public CollisionD2Q9 {
public:
    CollisionD2Q9LNP();
    virtual ~CollisionD2Q9LNP();
    void collide();
    void init();
    double fEq(int d, double ux, double uy, double ni);
    double calcConc(double *f, int i, int j);
    void setUx(double **ux){this->ux = ux;};
    void setUy(double **uy){this->uy = uy;};
    void setDPsix(double **dPsix){this->dPsix = dPsix;};
    void setDPsiy(double **dPsiy){this->dPsiy = dPsiy;};
    void setPe(double Pe){this->Pe = Pe;};
    void setZ(double z){this->z = z;};
    void setT(double T){this->T =T;};
    void setW(double w){this->w = w;};
    void dataToFile(string path);
protected:
    double **ux, **uy, **dPsix, **dPsiy, **ni, **divTerm;
    double Pe, z, T, w;
    double colPrefactor;
    void updateDivTerm();
    void updateNi();
};

#endif /* COLLISIOND2Q9LNP_H_ */