/*
 * OutputCSV.h - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#ifndef OUTPUTCSV_H_
#define OUTPUTCSV_H_

#include <string.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <fstream>

#include "../Aux.h"
#include "../col/CollisionD2Q9BGKNSF.h"
#include "../lat/LatticeModel.h"

template <class T>
class OutputCSV {
public:
	OutputCSV(T *cm, LatticeModel *lm);
	virtual ~OutputCSV();
	void setCollisionModel(T *cm){this->cm = cm;};
	void writeData();
	void setPath(string path){this->path = path;};
private:
	T *cm;
	LatticeModel *lm;
	string path;
};

#endif /* OUTPUTCSV_H_ */
