/*
 * DefaultStreamModel.cpp
 * Andreas BŸlling, 2012
 * DESCRIPTION - TODO
 */

#include "DefaultStreamModel.h"

DefaultStreamModel::DefaultStreamModel(int nx, int ny) : StreamModel(nx, ny) {

}

void DefaultStreamModel::updateF(double ***f){
	StreamModel::updateF(f);
}

DefaultStreamModel::~DefaultStreamModel() {
	// TODO Auto-generated destructor stub
}

