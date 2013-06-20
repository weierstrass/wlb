/*
 * Output.cpp - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#include "Output.h"

template Output<CollisionBGKNS>::~Output();
template Output<CollisionBGKNSF>::~Output();
template Output<CollisionBGKNSF>::Output();
template Output<CollisionBGKNS>::Output();

template<class T>
Output<T>::Output() {
  // TODO Auto-generated constructor stub

}

template<class T>
Output<T>::~Output() {
  // TODO Auto-generated destructor stub
}

