/*
 * CollisionD2Q9LNPSource.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef COLLISIOND2Q9LNPSOURCE_H_
#define COLLISIOND2Q9LNPSOURCE_H_

#include "CollisionD2Q9LNP.h"

class CollisionD2Q9LNPSource: public CollisionD2Q9LNP {
public:
  CollisionD2Q9LNPSource();
  virtual ~CollisionD2Q9LNPSource();
  void collide();
  void init();
  // void setSource(double **source){this->divTerm = source;};
  // double **getSource(){return divTerm;};
protected:
};

#endif /* COLLISIOND2Q9LNPSOURCE_H_ */
