/*
 * ValueNode.h
 * Andreas B�lling, 2012
 * DESCRIPTION - TODO
 */

#ifndef VALUENODE_H_
#define VALUENODE_H_

#include "Node.h"

class ValueNode: public Node {
public:
  ValueNode(int x, int y, int z, double v);
  ValueNode(int x, int y, int z, double v1, double v2);
  virtual ~ValueNode();
  double v1;
  double v2;
  double v3;
private:
};

#endif /* VALUENODE_H_ */
