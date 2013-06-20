/*
 * OutputVTKSP.h - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#ifndef OUTPUTVTKSP_H_
#define OUTPUTVTKSP_H_

#include "Output.h"

template<class T>
class OutputVTKSP: public Output<T> {
public:
  OutputVTKSP(T *cm, LatticeModel *lm);
  virtual ~OutputVTKSP();
  void writeData();
protected:
  T *cm;
  LatticeModel *lm;
  string path;
};

#endif /* OUTPUTVTKSP_H_ */
