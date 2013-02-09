/*
 * aux.h
 * Andreas Bülling, 2012
 */

#ifndef AUX_H_
#define AUX_H_

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <fstream>

using namespace std;

void print2DArray(double **f, int ni, int nj);
void print2DArray(double ***f, int ni, int nj, int d);
void printLine(int n);

void write2DArray(double **a, string file, int nx, int ny);
void createDirectory(string path);
double poiseuilleVelocity(int x, int n1, int n2, double uMax);
double**** allocate4DArray(int dirs, int nx, int ny, int nz);
double*** allocate3DArray(int nx, int ny, int nz);
double** allocate2DArray(int nx, int ny);
void rescale2DArray(double **arr, double sc, int ny, int nx);

template <typename T>
T** allocate2DArrayT(int nx, int ny);

#endif /* AUX_H_ */
