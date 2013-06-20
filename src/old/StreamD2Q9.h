/*
 * StreamD2Q9.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#ifndef STREAMD2Q9_H_
#define STREAMD2Q9_H_

#include "StreamModel.h"
#include "../Aux.h"

class StreamD2Q9: public StreamModel {
public:
  StreamD2Q9();
  virtual ~StreamD2Q9();
  void stream();
  void init() {
    cout << "init";
  }
  ;
};

#endif /* STREAMD2Q9_H_ */
