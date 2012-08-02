/*
 * UnitHandlerNS.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef UNITHANDLERNS_H_
#define UNITHANDLERNS_H_

#include "UnitHandler.h"

class UnitHandlerNS: public UnitHandler {
public:
    UnitHandlerNS();
    virtual ~UnitHandlerNS();
    double getCharVelocity(){return u0;};
    double getCharLength(){return l0;};
    double getCharDensity(){return rho0;};
    void setCharVelocity(double u0){this->u0 = u0;};
    void setCharLength(double l0){this->l0 = l0;};
    void setcharDensity(double rho0){this->rho0 = rho0;};
protected:
    double u0;
    double l0;
    double rho0;
};

#endif /* UNITHANDLERNS_H_ */
