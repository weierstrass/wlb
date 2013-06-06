/*
 * OutputCSV.cpp - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#include "OutputCSV.h"

//template OutputCSV<CollisionD2Q9BGKNSF>::OutputCSV(CollisionD2Q9BGKNSF *cm, LatticeModel *lm);
//template void OutputCSV<CollisionD2Q9BGKNSF>::writeData();

template OutputCSV<CollisionBGKNSF>::OutputCSV(CollisionBGKNSF *cm,
    LatticeModel *lm);
template void OutputCSV<CollisionBGKNSF>::writeData();

template OutputCSV<CollisionBGKNS>::OutputCSV(CollisionBGKNS *cm,
    LatticeModel *lm);
template void OutputCSV<CollisionBGKNS>::writeData();

template<class T>
OutputCSV<T>::OutputCSV(T *cm, LatticeModel *lm) {
  this->cm = cm;
  this->lm = lm;
  path = ".";
}

template<class T>
OutputCSV<T>::~OutputCSV() {
  // TODO Auto-generated destructor stub
}

template<class T>
void OutputCSV<T>::writeData() {
  cout << "Writing data to " << path << endl;
  const string mom0File = "rho.csv";
  const string mom1File = "u.csv";
  stringstream ss0, ss1;

  //check if path directory exists, if not create directory
  struct stat sb;
  if (!stat(path.c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)) {
    cout << "creating directory: " << path << endl;
    mkdir(path.c_str(), 0775);
  }

  //open files
  ofstream oFile0, oFile1;
  ss0 << path << "/" << mom0File;
  ss1 << path << "/" << mom1File;
  oFile0.open(ss0.str().c_str());
  oFile1.open(ss1.str().c_str());

  //write headers
  oFile0 << "x, y, z, rho\n";
  oFile1 << "x, y, z, ux, uy, uz\n";

  //write data to files
  double rho;
  double *rhoUTemp = new double[3];
  cout << "mem allocated" << endl;
  for (int k = 0; k < lm->n.z; k++) {
    for (int j = 0; j < lm->n.y; j++) {
      for (int i = 0; i < lm->n.x; i++) {
        rho = cm->get0moment(k, j, i);

        //cout << "rho: " << rho << endl;

        cm->get1moment(k, j, i, rhoUTemp);
        oFile0 << i << ", " << j << ", " << k << ", " << rho << "\n";
        oFile1 << i << ", " << j << ", " << k << ", " << rhoUTemp[X] / rho
            << ", " << rhoUTemp[Y] / rho << ", " << rhoUTemp[Z] / rho << "\n";
      }
    }
  }

  //clean up
  oFile0.close();
  oFile1.close();
  delete[] rhoUTemp;
}
