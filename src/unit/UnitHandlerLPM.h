/*
 * UnitHandlerLPM.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#ifndef UNITHANDLERLPM_H_
#define UNITHANDLERLPM_H_

#include "UnitHandler.h"

class UnitHandlerLPM: public UnitHandler {
public:
  UnitHandlerLPM();
  virtual ~UnitHandlerLPM();
  void setCharLength(double l) {
    charLength = l;
  }
  ;
  void setCharVoltage(double V) {
    charVoltage = V;
  }
  ;
  void setTimeStep(double dt) {
    this->dt = dt;
  }
  ;
  double getCharVoltage() {
    return charVoltage;
  }
  ;
  double getCharLength() {
    return charLength;
  }
  ;
  double getTimeStep() {
    return dt;
  }
  ;
private:
  double charLength;
  double charVoltage;
  double dt;
};

#endif /* UNITHANDLERLPM_H_ */
