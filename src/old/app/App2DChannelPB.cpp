/*
 * AppADSource.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * Benchmarking of the PB solver
 * The PB case will be reproduced by simulating
 * a system that fulfills the PB assumptions.
 *
 */

#include <iostream>
#include <sstream>
#include <math.h>
#include "../LBM.h"

using namespace std;

void updateRho(double **rho_eps, double **psi, LatticeModel *lm, double eps_r,
    double V0, double l0, double C0);
//
//void initC(CollisionD2Q9LNP     *cmNPneg,
//           CollisionD2Q9LNP     *cmNPpos,
//           LatticeModel         *lm);

int main() {
  cout << "2D, NS <-> PE <-> NP" << endl;

  /* Parameter definitions */
  int nx = 3;
  int ny = 101;

  int tNP = 20;
  int tPE = 10000;
  int tNS = 1;
  int tMain = 1;

  int tMod = 1;

  double l0 = 1e-6 / (ny - 1); //PE, NP
  double C0 = 1e-4 * PHYS_N_A; //NP
  double u0 = 1e-3; //NP
  double dt = 1.0;
  double V0 = -50e-3; //PE

  double D = 1.0e-11;
  double u0x = 0.0;
  double T = 293;
  double eps_r = 80;
  double rho_surface = -1e-3; //-50e-3*eps_r*PHYS_EPS0/1e-7/V0*l0;
  double bulk_charge = 1.0;
  double gamma = PHYS_E_CHARGE / (PHYS_KB * T);

  double Pe = u0 * l0 / D;
  double wNP = 1 / (3.0 / Pe + 0.5);
  double wPE = 1.0;

  /*print parameters*/
  printLine(20);
  cout << "DIM = (" << nx << ", " << ny << ")" << endl;
  cout << "T = " << T << endl;
  cout << "RHO_SURFACE = " << rho_surface << ", "
      << rho_surface * V0 / l0 * PHYS_EPS0 * eps_r << " C/M^2" << endl;
  cout << "BULK_CHARGE = " << bulk_charge << endl;
  cout << "PE = " << Pe << endl;
  cout << endl;
  cout << "w_np = " << wNP << endl;
  cout << "w_pe = " << wPE << endl;
  cout << endl;
  cout << "l0 = " << l0 << endl;
  cout << "V0 = " << V0 << endl;
  cout << "GAMMA: " << gamma << endl;
  cout << "l0*gamma/Pe *V0/l0 = " << l0 * gamma / Pe * V0 / l0 << endl;
  cout << "l0^2*gamma/Pe *V0/l0^2 = " << l0 * l0 * gamma / Pe * V0 / l0 / l0
      << endl;
  cout << "1/Pe = " << 1 / Pe << endl;
  printLine(20);

  /* Allocate memory for velocity and grad. potential arrays */
  double **psi = allocate2DArray(ny, nx);
  double **rho_eps = allocate2DArray(ny, nx);

  for (int j = 0; j < ny; j++) {
    for (int i = 0; i < nx; i++) {
      psi[j][i] = 0;
      rho_eps[j][i] = 0.0; //-l0*l0/V0*2*PHYS_E_CHARGE*C0/(eps_r *PHYS_EPS0)*\
                            (cos(j*2*M_PI/(ny-1)) + 1)*0.5;
    }
  }

  /* Poisson eq. solver */
  CollisionD2Q9BGKPE *cmPE = new CollisionD2Q9BGKPE();
  StreamD2Q9Periodic *smPE = new StreamD2Q9Periodic();
  Lattice2D *lmPE = new Lattice2D(nx, ny);
  UnitHandlerLPM *uhPE = new UnitHandlerLPM();

  cmPE->setRHS(rho_eps);
  cmPE->setW(wPE);
  cmPE->setC(1.0);
  cmPE->setUnitHandler(uhPE);
  uhPE->setCharLength(l0);
  uhPE->setCharVoltage(V0);
  uhPE->setTimeStep(1.0);

  LBM *lbmPE = new LBM(lmPE, cmPE, smPE);
  lbmPE->init();

//    HeZouLPMChaiNodes *bds = new HeZouLPMChaiNodes();
//    bds->setCollisionModel(cmPE);
//    for(int i = 0; i < nx; i++){
//        bds->addNode(i, 0, 0, 1.0/1.8);
//        bds->addNode(i, ny-1, 0, 1.0/1.8);
//    }

  /* Boundary conds. for Poission solver */
  NeumannNodesPESlip *bds = new NeumannNodesPESlip();
  lbmPE->addBoundaryNodes(bds);
  bds->setCollisionModel(cmPE);
  for (int i = 0; i < nx; i++) {
    bds->addNode(i, 0, 0, rho_surface, 2);
    bds->addNode(i, ny - 1, 0, rho_surface, 4);
  }
  bds->init();

  /* Main loops */
  for (int tt = 0; tt < tMain; tt++) {
    cout << "TT: " << tt << endl;

    /* Update net charge density */
    cmPE->reset();

    for (int t = 0; t < tPE; t++) {
      //cout<<"tPE "<<t<<endl;
      cmPE->getPsi(psi);
      updateRho(rho_eps, psi, lmPE, eps_r, V0, l0, C0);
      lbmPE->collideAndStream();
    }
    //cmPE->getDPsi(dPsix, dPsiy);

    /*write result to file*/
    stringstream ss;
    string base = "vis_scripts/data";
    if (tt % tMod == 0) {

      //potential
      ss.str("");
      ss << base << "PBE";
      ss << tt / tMod << "/";
      createDirectory(ss.str());
      ss << "rho.csv";
      cmPE->dataToFile(ss.str());
    }
  }

  cout << "done LNP." << endl;

  return 0;
}

/* updates rho_eps = -rho/(eps_r*eps_0)
 * return value in: lattice units.
 */
void updateRho(double **rho_eps, double **psi, LatticeModel *lm, double eps_r,
    double V0, double l0, double C0) {

  double prefactor = -2 * PHYS_E_CHARGE * l0 * l0 * C0
      / (eps_r * PHYS_EPS0 * V0);
  //cout<<"PREF: "<<prefactor<<endl;
  //prefactorChargeSI = prefactor*V0/l2*eps;
  double inSinh = PHYS_E_CHARGE * V0 / PHYS_KB / 293.0;
  //cout<<"insinh: "<<inSinh<<endl;
  for (int j = 0; j < lm->n.y; j++) {
    for (int i = 0; i < lm->n.x; i++) {
      rho_eps[j][i] = sinh(inSinh * psi[j][i]);
      //cout<<"psi: "<<psi[j][i]<<endl;
      rho_eps[j][i] *= prefactor;
    }
  }
}

///*TODO modified C_neg*/
//void initC(CollisionD2Q9LNP *cmNPneg,
//           CollisionD2Q9LNP *cmNPpos,
//           LatticeModel     *lm){
//
//    double **Cpos = cmNPpos->getNi();
//    double **Cneg = cmNPneg->getNi();
//    for(int j = 0; j < lm->n.y; j++){
//        for(int i = 0; i < lm->n.x; i++){
//            Cpos[j][i] = 1.0;//(1.0 + cos((double)(j-1)*2.0*M_PI/(lm->n.y-1-2))*0.3);
//          //  cout<<"cpos: "<<Cpos[j][i]<<endl;
//            Cneg[j][i] = 1.0;//(1.0 - cos((j-1)*2.0*M_PI/(lm->n.y-1-2))*0.3+0.6/(lm->n.y-2));
//        }
//    }
//}
