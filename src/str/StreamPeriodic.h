/*
 * StreamPeriodic.h
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#ifndef STREAMPERIODIC_H_
#define STREAMPERIODIC_H_

#include "Stream.h"
#include "../Aux.h"

class StreamPeriodic: public Stream {
public:
    StreamPeriodic();
    virtual ~StreamPeriodic();
    void stream();
    void init();
protected:
    double ****fb;
};

#endif /* STREAMPERIODIC_H_ */
