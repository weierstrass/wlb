/*
 * StreamModel.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Abstract mother class for streaming models.
 */

#include "StreamModel.h"

StreamModel::StreamModel() {
}

StreamModel::~StreamModel() {
	// TODO Auto-generated destructor stub
}

void StreamModel::setF(double ****f){
	this->f = f;
}

