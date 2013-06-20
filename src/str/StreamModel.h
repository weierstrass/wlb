/*
 * StreamModel.h
 * Andreas B�lling, 2012
 * DESCRIPTION - TODO
 */

#ifndef STREAMMODEL_H_
#define STREAMMODEL_H_

#include <iostream>
#include "../lat/LatticeModel.h"

using namespace std;

class StreamModel {
public:
  StreamModel();
  virtual ~StreamModel();
  virtual void stream() = 0;
  virtual void init() = 0;
  void setF(double ****f);
  void setLatticeModel(LatticeModel *lm) {
    this->lm = lm;
  };
protected:
  double ****f;
  LatticeModel *lm;
};

#endif /* STREAMMODEL_H_ */
