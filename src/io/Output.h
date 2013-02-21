/*
 * Output.h - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <string.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <fstream>

#include "../Aux.h"
#include "../lat/LatticeModel.h"
#include "../col/CollisionD2Q9BGKNSF.h"
#include "../col/CollisionBGKNSF.h"
#include "../col/CollisionBGKNS.h"

template <class T>
class Output {
public:
	Output();
	virtual ~Output();
	void setCollisionModel(T *cm){this->cm = cm;};
	void setLatticeModel(LatticeModel *lm){this->lm = lm;};
	void setPath(string path){this->path = path;};
protected:
	T *cm;
	LatticeModel *lm;
	string path;
};

#endif /* OUTPUT_H_ */
