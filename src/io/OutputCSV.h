/*
 * OutputCSV.h - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#ifndef OUTPUTCSV_H_
#define OUTPUTCSV_H_



#include "Output.h"

template <class T>
class OutputCSV : public Output<T>{
public:
	OutputCSV(T *cm, LatticeModel *lm);
	virtual ~OutputCSV();
	void writeData();
	void setPath(string path){this->path = path;};
protected:
	T *cm;
	LatticeModel *lm;
	string path;
};

#endif /* OUTPUTCSV_H_ */
