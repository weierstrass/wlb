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

class ValueNode2D : public ValueNode{
public:
	ValueNode2D(int x, int y, double v1, double v2);
	virtual ~ValueNode2D();
	double valueX, valueY;
private:
};

#endif /* VALUENODE_H_ */
