/*
 * Node.h
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#ifndef NODE_H_
#define NODE_H_

class Node {
public:
	Node(int x, int y, int z);
	virtual ~Node();
	int x, y, z;
};

#endif /* NODE_H_ */
