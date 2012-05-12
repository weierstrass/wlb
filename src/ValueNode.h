/*
 * ValueNode.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef VALUENODE_H_
#define VALUENODE_H_

class ValueNode {
public:
	ValueNode(int x, int y, double v);
	virtual ~ValueNode();
	int x, y;
	double value;
private:
};

#endif /* VALUENODE_H_ */
