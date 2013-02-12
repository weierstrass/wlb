/*
 * StreamD2Q9Periodic.h
 * Andreas Bülling, 2012
 * DESCRIPTION - TODO
 */

#ifndef STREAMD2Q9PERIODIC_H_
#define STREAMD2Q9PERIODIC_H_

#include "StreamD2Q9.h"

class StreamD2Q9Periodic : public StreamD2Q9{
public:
	StreamD2Q9Periodic();
	virtual ~StreamD2Q9Periodic();
	void stream();
	void init();
private:
	double **fv;
	double **fh;
};

#endif /* STREAMD2Q9PERIODIC_H_ */
