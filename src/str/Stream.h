/*
 * Stream.h
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef STREAM_H_
#define STREAM_H_

#include <cstdio>
#include "StreamModel.h"

class Stream: public StreamModel {
public:
    Stream();
    virtual ~Stream();
    void stream();
    void init();
protected:
    void backwardStream(int d, int sz, int sy, int sx);
    void forwardStream(int d, int sz, int sy, int sx);
};

#endif /* STREAM_H_ */
