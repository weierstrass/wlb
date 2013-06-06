/*
 * CollisionD2Q9BGK.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Collision operator for incompressible flow.
 * General BGK type collision.
 * Equilibrium distribution is specified through
 * the chosen interface as a pointer to an array.
 */

#include "CollisionD2Q9BGK.h"
#include <omp.h>

CollisionD2Q9BGK::CollisionD2Q9BGK() :
    CollisionD2Q9() {
  rho = NULL;
  ux = NULL;
  uy = NULL;
  eq = NULL;
  w = 1.0;
}

CollisionD2Q9BGK::~CollisionD2Q9BGK() {
  delete[] eq;
}

void CollisionD2Q9BGK::collide() {
  //cout<<"D2Q9 BGK collision"<<endl;
  int j, i;
  for (j = 0; j < lm->n.y; j++) {
    for (i = 0; i < lm->n.x; i++) {

      if (skip != NULL && skip[j][i])
        continue;

      fEq(i, j, eq);
      for (int d = 0; d < lm->UDIRS; d++) {
        // cout<<"i: "<<i<<", j: "<<", d"<<d<<", thread: "<<omp_get_thread_num()<<endl;
        f[0][j][i][d] += w * (eq[d] - f[0][j][i][d]);
      }
    }
  }
}

void CollisionD2Q9BGK::setW(double w) {
  this->w = w;
}

double CollisionD2Q9BGK::get0moment(int i, int j) {
  double ret = 0;
  for (int d = 0; d < lm->UDIRS; d++)
    ret += f[0][j][i][d];
  return ret;
}

void CollisionD2Q9BGK::get1moment(int i, int j, double *ret) {
  ret[X] = 0;
  ret[Y] = 0;
  for (int d = 0; d < lm->UDIRS; d++) {
    ret[X] += f[0][j][i][d] * lm->e[0][d];
    ret[Y] += f[0][j][i][d] * lm->e[1][d];
    // cout << "ex: " << lm->e[0][d] << endl;
    // cout << "f_psi" << f[0][j][i][d] << endl;
  }
}

void CollisionD2Q9BGK::init() {
  cout << "Initializing BGK collision operator... ";
  eq = new double[lm->UDIRS];

  for (int j = 0; j < n.y; j++) {
    for (int i = 0; i < n.x; i++) {
      for (int d = 0; d < 9; d++) {
        f[0][j][i][d] = W[d];
      }
    }
  }

  cout << "done." << endl;
}

void CollisionD2Q9BGK::dataToFile(string path) {
  if (rho == NULL)
    rho = allocate2DArray(lm->n.y, lm->n.x);
  if (ux == NULL)
    ux = allocate2DArray(lm->n.y, lm->n.x);
  if (uy == NULL)
    uy = allocate2DArray(lm->n.y, lm->n.x);
  cout << "mem allocated" << endl;
  double *rhoUTemp = new double[3];
  for (int j = 0; j < lm->n.y; j++) {
    for (int i = 0; i < lm->n.x; i++) {
      rho[j][i] = get0moment(i, j);
      get1moment(i, j, rhoUTemp);
      ux[j][i] = rhoUTemp[X] / rho[j][i];
      uy[j][i] = rhoUTemp[Y] / rho[j][i];
    }
  }
  cout << "vals calced" << endl;
  stringstream ss, ssTemp;
  struct stat sb;
  ss.str("");
  ss << path;
  if (!stat(ss.str().c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)) {
    cout << "creating directory: " << ss.str() << endl;
    mkdir(ss.str().c_str(), 0775);
  }

//    stringstream ss, ssTemp;
//    struct stat sb;
//    for(int i = 0; ; i++){
//        ss.str("");
//        ss<<"vis_scripts/data";
//        ss<<""<<i<<"/";
//        if (!stat(ss.str().c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)){
//            cout<<"creating directory: "<<ss.str()<<endl;
//            mkdir(ss.str().c_str(), 0775);
//            break;
//        }
//    }
  cout << "bgk base..." << endl;
  ssTemp.str("");
  ssTemp << ss.str();
  ssTemp << "ux.csv";
  write2DArray(ux, ssTemp.str(), lm->n.x, lm->n.y);
  ssTemp.str("");
  ssTemp << ss.str();
  ssTemp << "uy.csv";
  write2DArray(uy, ssTemp.str(), lm->n.x, lm->n.y);
  ssTemp.str("");
  ssTemp << ss.str();
  ssTemp << "rho.csv";
  write2DArray(rho, ssTemp.str(), lm->n.x, lm->n.y);
}

//double CollisionD2Q9BGK::getRho(double *f){
//    double rho = 0;
//    for(int i = 0; i < 9; i++) rho += f[i];
//    return rho;
//}
//
//double *CollisionD2Q9BGK::getRhoU(double *f){
//    double *u = new double[3];
//    u[X] = f[1] + f[8] + f[5] - (f[3] + f[6] + f[7]);
//    u[Y] = f[2] + f[5] + f[6] - (f[7] + f[4] + f[8]);
//    u[Z] = -1;
//    return u;
//}

//double CollisionD2Q9BGK::fEq(int d, double rho, double ux, double uy){
//    double cu = lm->ex[d]*ux + lm->ey[d]*uy;
//    double c2 = c*c;
//    double u2 = ux*ux + uy*uy;
//    return W[d]*rho*(1 + 3.0/c2*(cu) \
//                       + 4.5/(c2*c2)*(cu*cu) \
//                       - 1.5/c2*u2);
//}
