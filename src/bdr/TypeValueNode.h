/*
 * TypeValueNode.h
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef TYPEVALUENODE_H_
#define TYPEVALUENODE_H_

#include "ValueNode.h"

class TypeValueNode: public ValueNode {
public:
  TypeValueNode(int x, int y, int z, double val, char type, int param);
  virtual ~TypeValueNode();
  char type;
  int param;
};

#endif /* TYPEVALUENODE_H_ */
