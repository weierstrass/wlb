/*
 * aux.h
 * Andreas Bülling, 2012
 */

#ifndef AUX_H_
#define AUX_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void print2DArray(double **f, int ni, int nj);
void print2DArray(double ***f, int ni, int nj, int d);
void write2DArray(double **a, bool **deadNodes, string file, int nx, int ny);
double poiseuilleVelocity(int x, int n1, int n2, double uMax);
double**** allocate4DArray(int dirs, int nx, int ny, int nz);
double*** allocate3DArray(int nx, int ny, int nz);
double** allocate2DArray(int nx, int ny);

template <typename T>
T** allocate2DArrayT(int nx, int ny);
#endif /* AUX_H_ */
