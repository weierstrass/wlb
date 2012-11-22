/*
 * CollisionD2Q9BGK.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9BGK_H_
#define COLLISIOND2Q9BGK_H_

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>
#include <cstdio>
#include <string.h>
#include "CollisionD2Q9.h"
#include "../Aux.h"

using namespace std;

class CollisionD2Q9BGK : public CollisionD2Q9 {
protected:
	double w;
    double **rho;
    double **ux;
    double **uy;
public:
	CollisionD2Q9BGK();
	virtual ~CollisionD2Q9BGK();
	void collide();
	void init();
	virtual void fEq(int i, int j, double *eq) = 0;
	double get0moment(int i, int j);
    void get1moment(int i, int j, double *ret);
	void setW(double w);
	void dataToFile(string path);
    //double getRho(double *f);
    //double *getRhoU(double *f);
    //double fEq(int d, double rho, double ux, double uy);
protected:
	double *eq;
};

#endif /* COLLISIOND2Q9BGK_H_ */
