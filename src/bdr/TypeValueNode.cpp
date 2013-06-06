/*
 * TypeValueNode.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "TypeValueNode.h"

TypeValueNode::TypeValueNode(int x, int y, int z, double val, char type,
    int param) :
    ValueNode(x, y, z, val) {
  this->type = type;
  this->param = param;

}

TypeValueNode::~TypeValueNode() {
  // TODO Auto-generated destructor stub
}

