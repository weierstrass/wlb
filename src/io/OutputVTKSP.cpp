/*
 * OutputVTKSP.cpp - LBM
 *
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 */

#include "OutputVTKSP.h"

template OutputVTKSP<CollisionBGKNSF>::OutputVTKSP(CollisionBGKNSF *cm,
    LatticeModel *lm);
template void OutputVTKSP<CollisionBGKNSF>::writeData();

template<class T>
OutputVTKSP<T>::OutputVTKSP(T *cm, LatticeModel *lm) {
  this->cm = cm;
  this->lm = lm;
  path = ".";

}
template<class T>
OutputVTKSP<T>::~OutputVTKSP() {
  // TODO Auto-generated destructor stub
}

template<class T>
void OutputVTKSP<T>::writeData() {
  const string file = "data.vtk";

  cout << "Writing data to " << file << "..." << endl;

  stringstream ss0;

  //check if path directory exists, if not create directory
  struct stat sb;
  if (!stat(path.c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)) {
    cout << "creating directory: " << path << endl;
    mkdir(path.c_str(), 0775);
  }

  //open files
  ofstream oFile0, oFile1;
  ss0 << path << "/" << file;
  oFile0.open(ss0.str().c_str());

  //write headers
  oFile0 << "# vtk DataFile Version 2.0\n";
  oFile0 << "WLB generated data file.\nASCII\n\n";
  oFile0 << "DATASET STRUCTURED_GRID\n";
  oFile0 << "DIMENSIONS  " << lm->n.x << " " << lm->n.y << " " << lm->n.z
      << endl;

  // write point data
  int dim = lm->n.x * lm->n.y * lm->n.z;
  oFile0 << "POINTS " << dim << " int" << endl;
  for (int k = 0; k < lm->n.z; k++) {
    for (int j = 0; j < lm->n.y; j++) {
      for (int i = 0; i < lm->n.x; i++) {
        oFile0 << i << " " << " " << j << " " << k << endl;
      }
    }
  }
  oFile0 << "POINT_DATA " << dim << endl;

  //write vector data
  oFile0 << "VECTORS velocity float" << endl;
  double rho;
  double *rhoUTemp = new double[3];

  for (int k = 0; k < lm->n.z; k++) {
    for (int j = 0; j < lm->n.y; j++) {
      for (int i = 0; i < lm->n.x; i++) {
        rho = cm->get0moment(k, j, i);

        //cout << "rho: " << rho << endl;

        cm->get1moment(k, j, i, rhoUTemp);
        //oFile0 << i << ", " << j << ", " << k << ", " << rho << "\n";
        oFile0 << rhoUTemp[0] / rho << " " << rhoUTemp[1] / rho << " "
            << rhoUTemp[2] / rho << endl;
      }
    }
  }

  //clean up
  oFile0.close();
  oFile1.close();
  delete[] rhoUTemp;
}
