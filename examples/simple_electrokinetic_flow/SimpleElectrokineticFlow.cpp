/*
 * AppADSource.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include <iostream>
#include <sstream>
#include <math.h>
#include "../../src/LBM.h"

using namespace std;

void updateRho(double **rho_eps, CollisionD2Q9AD *cmNPneg,
    CollisionD2Q9AD *cmNPpos, LatticeModel *lm, double eps_r, double V0,
    double l0, double C0);

void updateForce(double ****force, double **ux, double **uy, double **rho_eps,
    Lattice2D *lm, double eps_r, double u0, double l0, double V0, double C0,
    double bulkCond, double dPdx, CollisionD2Q9AD *cmNPpos,
    CollisionD2Q9AD *cmNPneg);

//void addRect(int x, int y, int w, int h, double rho_surface, BounceBackNodes<CollisionD2Q9BGKNSF> *bbNS,
//		NeumannNodesPESlip *bds, SlipNodes<CollisionD2Q9AD> *bbnNeg,
//		SlipNodes<CollisionD2Q9AD> *bbnPos);

<<<<<<< HEAD
int main() {
  cout << "Charged 2D channel flow" << endl << endl;

  /* Parameter definitions */
  int nx = 3;
  int ny = 1001;

  double dx = 1.0/(ny-1);
  double dt = dx*dx;

  int tNP = 150;
  int tPE = 10000;
  int tNS = 1500; //tNP;
  int tMain = 10000;
  int tMod = 1;//

  double d = 0.01e-6;//m
  double nu = 1.0e-6;//m^2/s
  double D = 1.0e-10;//m^2/s
  double T = 293;//K
  double dPdx = 1e6;// Pa
  double eps_r = 80;
  double rho_surface = PHYS_E_CHARGE / (1000e-10*1000e-10);//C/m^2
  //rho_surface = 0.0;
  double bulk_charge = 1.0;
  double bulkConductivity = 1;//conductivity [S/m]
  double C0M = 1e0;//M / m^3

  printLine(40);
  cout << "PHYSICAL SYSTEM:" << endl;
  cout << " channel dim., d: " << d << " m" << endl;
  cout << " viscosity, nu: " << nu << " m^2/s" << endl;
  cout << " diffusion coef., D: " << D << " m^2/s" << endl;
  cout << " temperature, T: " << T << " K" << endl;
  cout << " pressure grad., dPdx: " << dPdx << " Pa/m" << endl;
  cout << " rel. permittivity, eps_r: " << eps_r << "" << endl;
  cout << " surface charge, sigma_s: " << rho_surface << " C/m^2" << endl;
  cout << " bulk conductivity, sigma_c: " << bulkConductivity << " S/m" << endl;
  cout << " molar concentration, C_m: " << C0M << " M/m^3" << endl;
  printLine(40);

  double l0 = d * dx;//PE, NP
  double l0NP = l0;
  double C0 = C0M*PHYS_N_A;//NP
  double u0 = 1e-3 * dx / dt;//NP, NS
  double V0 = -50e-3;//PE
  double rho0 = 1e3;//NS

  double Pe = u0*l0/D;
  double Re = u0*l0/nu*1e4;
  double wNP = 1.0/(3.0/Pe + 0.5);
  double wPE = 1.0;
  double wNS = 1.0/(3.0/Re + 0.5);

  dPdx *= l0/(rho0 * u0 * u0);
  cout << "DESIRED RHO_SURF: " <<rho_surface*1.0/V0/(eps_r*PHYS_EPS0) * l0 <<endl;
  rho_surface *= 1.0/V0/(eps_r*PHYS_EPS0) * l0;
  double gamma = PHYS_E_CHARGE/(PHYS_KB*T)*V0;

  /*print parameters*/
  printLine(40);
  cout << "DIMENSIONLESS SYSTEM:" << endl;
  cout<<" lattice: ("<<nx<<", "<<ny<<")"<<endl;
  cout<<" PHYS_E_CHARGE/(PHYS_KB*T)*V0, gamma = "<<gamma<<endl;
  cout<<" surface charge: "<<rho_surface<<endl;
  cout<<" bulk charge: "<<bulk_charge<<endl;
  cout << " pressure grad., dPdx: " << dPdx << endl;
  cout<<endl;
  cout<<" Pe: "<<Pe<<endl;
  cout<<" Re: "<<Re<<endl;
  cout<<endl;
  cout<<" w_np = "<<wNP<<endl;
  cout<<" w_pe = "<<wPE<<endl;
  cout<<" w_ns = "<<wNS<<endl;
  cout<<endl;
  cout<<" l0 = "<<l0<<endl;
  cout<<" V0 = "<<V0<<endl;
  cout<<" u0 = "<<u0<<endl;
  cout<<" C0 = "<<C0<<endl;
  cout<<" rho0 = "<<rho0<<endl;
  printLine(40);

  /* Allocate memory for velocity and grad. potential arrays */
  double **ux = allocate2DArray(ny, nx);
  double **uy = allocate2DArray(ny, nx);
  double **dPsix = allocate2DArray(ny, nx);
  double **dPsiy = allocate2DArray(ny, nx);
  double **rho_eps = allocate2DArray(ny, nx);
  double ****force = allocate4DArray(2, 1, ny, nx);

  for(int j = 0; j < ny; j++) {
    for(int i = 0; i < nx; i++) {
      ux[j][i] = 0;
      uy[j][i] = 0;
      dPsix[j][i] = 0.0;
      dPsiy[j][i] = 0.0;
      rho_eps[j][i] = 0.0;
    }
    =======
    int main() {
      cout << "Charged 2D channel flow" << endl << endl;

      /* Parameter definitions */
      int nx = 3;
      int ny = 30001;

      double dx = 1.0 / (ny - 1);
      double dt = dx * dx;

      int tNP = 15;
      int tPE = 10000;
      int tNS = 150; //tNP;
      int tMain = 10000;
      int tMod = 1;//

      double d = 0.1e-6;//m
      double nu = 1.0e-6;//m^2/s
      double D = 1.0e-10;//m^2/s
      double T = 293;//K
      double dPdx = 1e6;// Pa
      double eps_r = 80;
      double rho_surface = PHYS_E_CHARGE / (1000e-10 * 1000e-10);//C/m^2
      //rho_surface = 0.0;
      double bulk_charge = 1.0;
      double bulkConductivity = 1;//conductivity [S/m]
      double C0M = 150e0;//M / m^3

      printLine(40);
      cout << "PHYSICAL SYSTEM:" << endl;
      cout << " channel dim., d: " << d << " m" << endl;
      cout << " viscosity, nu: " << nu << " m^2/s" << endl;
      cout << " diffusion coef., D: " << D << " m^2/s" << endl;
      cout << " temperature, T: " << T << " K" << endl;
      cout << " pressure grad., dPdx: " << dPdx << " Pa/m" << endl;
      cout << " rel. permittivity, eps_r: " << eps_r << "" << endl;
      cout << " surface charge, sigma_s: " << rho_surface << " C/m^2" << endl;
      cout << " bulk conductivity, sigma_c: " << bulkConductivity << " S/m" << endl;
      cout << " molar concentration, C_m: " << C0M << " M/m^3" << endl;
      printLine(40);

      double l0 = d * dx;//PE, NP
      double l0NP = l0;
      double C0 = C0M * PHYS_N_A;//NP
      double u0 = 1e-3 * dx / dt;//NP, NS
      double V0 = -50e-3;//PE
      double rho0 = 1e3;//NS

      double Pe = u0 * l0 / D;
      double Re = u0 * l0 / nu * 1e4;
      double wNP = 1.0 / (3.0 / Pe + 0.5);
      double wPE = 1.0;
      double wNS = 1.0 / (3.0 / Re + 0.5);

      dPdx *= l0 / (rho0 * u0 * u0);
      cout << "DESIRED RHO_SURF: "
      << rho_surface * 1.0 / V0 / (eps_r * PHYS_EPS0) * l0 << endl;
      rho_surface *= 1.0 / V0 / (eps_r * PHYS_EPS0) * l0;
      double gamma = PHYS_E_CHARGE / (PHYS_KB * T) * V0;

      /*print parameters*/
      printLine(40);
      cout << "DIMENSIONLESS SYSTEM:" << endl;
      cout << " lattice: (" << nx << ", " << ny << ")" << endl;
      cout << " PHYS_E_CHARGE/(PHYS_KB*T)*V0, gamma = " << gamma << endl;
      cout << " surface charge: " << rho_surface << endl;
      cout << " bulk charge: " << bulk_charge << endl;
      cout << " pressure grad., dPdx: " << dPdx << endl;
      cout << endl;
      cout << " Pe: " << Pe << endl;
      cout << " Re: " << Re << endl;
      cout << endl;
      cout << " w_np = " << wNP << endl;
      cout << " w_pe = " << wPE << endl;
      cout << " w_ns = " << wNS << endl;
      cout << endl;
      cout << " l0 = " << l0 << endl;
      cout << " V0 = " << V0 << endl;
      cout << " u0 = " << u0 << endl;
      cout << " C0 = " << C0 << endl;
      cout << " rho0 = " << rho0 << endl;
      printLine(40);

      /* Allocate memory for velocity and grad. potential arrays */
      double **ux = allocate2DArray(ny, nx);
      double **uy = allocate2DArray(ny, nx);
      double **dPsix = allocate2DArray(ny, nx);
      double **dPsiy = allocate2DArray(ny, nx);
      double **rho_eps = allocate2DArray(ny, nx);
      double ****force = allocate4DArray(2, 1, ny, nx);

      for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
          ux[j][i] = 0;
          uy[j][i] = 0;
          dPsix[j][i] = 0.0;
          dPsiy[j][i] = 0.0;
          rho_eps[j][i] = 0.0;
          >>>>>>> be0085aa8c172e2e67c81b77b2d5932ce2e0768c
        }
      }

      /* Poisson eq. solver */
      CollisionD2Q9BGKPE *cmPE = new CollisionD2Q9BGKPE();
      StreamD2Q9Periodic *smPE = new StreamD2Q9Periodic();
      Lattice2D *lmPE = new Lattice2D(nx, ny);
      //UnitHandlerLPM *uhPE = new UnitHandlerLPM();

      cmPE->setRHS(rho_eps);
      cmPE->setW(wPE);
      cmPE->setC(1.0);
      //cmPE->setUnitHandler(uhPE);
//    uhPE->setCharLength(l0);
//    uhPE->setCharVoltage(V0);
//    uhPE->setTimeStep(1.0);

      LBM *lbmPE = new LBM(lmPE, cmPE, smPE);
      lbmPE->init();

      /* Boundary conds. for Poission solver */
      NeumannNodesPESlip *bds = new NeumannNodesPESlip();
      lbmPE->addBoundaryNodes(bds);
      bds->setCollisionModel(cmPE);
      for (int i = 0; i < nx; i++) {
        bds->addNode(i, 0, 0, rho_surface, 2);
        bds->addNode(i, ny - 1, 0, rho_surface, 4);
      }
      bds->init();

      /* Nernst Planck solver */
      CollisionD2Q9AD *cmNPneg = new CollisionD2Q9AD();
      CollisionD2Q9AD *cmNPpos = new CollisionD2Q9AD();
      StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
      LatticeModel *lm = new Lattice2D(nx, ny);
      StreamD2Q9Periodic *sm2 = new StreamD2Q9Periodic();
      LatticeModel *lm2 = new Lattice2D(nx, ny);

      cmNPneg->setW(wNP);
      cmNPneg->setC(1);
      cmNPneg->setZ(-1);
      cmNPneg->setInitC(bulk_charge);
      cmNPneg->setUx(ux);
      cmNPneg->setUy(uy);
      cmNPneg->setDPsix(dPsix);
      cmNPneg->setDPsiy(dPsiy);
      cmNPneg->setT(T);
      cmNPneg->setPe(Pe);
      //cmNPneg->setRHS(rho_eps);

      cmNPpos->setW(wNP);
      cmNPpos->setC(1);
      cmNPpos->setZ(1);
      cmNPpos->setInitC(bulk_charge);
      cmNPpos->setUx(ux);
      cmNPpos->setUy(uy);
      cmNPpos->setDPsix(dPsix);
      cmNPpos->setDPsiy(dPsiy);
      cmNPpos->setT(T);
      cmNPpos->setPe(Pe);
      //cmNPpos->setRHS(rho_eps);

      LBM *lbmNPneg = new LBM(lm, cmNPneg, sm);
      LBM *lbmNPpos = new LBM(lm2, cmNPpos, sm2);

      /* Boundary conds for NP solver*/
      SlipNodes<CollisionD2Q9AD> *bbnNeg = new SlipNodes<CollisionD2Q9AD>();
      lbmNPneg->addBoundaryNodes(bbnNeg);
      bbnNeg->setCollisionModel(cmNPneg);
      for (int i = 0; i < nx; i++) {
        bbnNeg->addNode(i, 0, 0, 2);
        bbnNeg->addNode(i, ny - 1, 0, 4);
      }
      bbnNeg->init();

      SlipNodes<CollisionD2Q9AD> *bbnPos = new SlipNodes<CollisionD2Q9AD>();
      lbmNPpos->addBoundaryNodes(bbnPos);
      bbnPos->setCollisionModel(cmNPpos);
      for (int i = 0; i < nx; i++) {
        bbnPos->addNode(i, 0, 0, 2);
        bbnPos->addNode(i, ny - 1, 0, 4);
      }
      bbnPos->init();

      /* Initialize solver */
      lbmNPneg->init();
      lbmNPpos->init();

      /* NS Solver */
      CollisionBGKNSF *cmNS = new CollisionBGKNSF();
      StreamPeriodic *smNS = new StreamPeriodic();
      Lattice2D *lmNS = new Lattice2D(nx, ny);
      LBM *lbmNS = new LBM(lmNS, cmNS, smNS);

      cmNS->setW(wNS);
      cmNS->setC(1.0);
      cmNS->setForce(force);

      /* Set boundary conditions for flow */
      BounceBackNodes<CollisionBGKNSF> *bbNS =
      new BounceBackNodes<CollisionBGKNSF>();
      bbNS->setCollisionModel(cmNS);
      lbmNS->addBoundaryNodes(bbNS);
      for (int i = 0; i < nx; i++) {
        bbNS->addNode(i, 0, 0);
        bbNS->addNode(i, ny - 1, 0);
      }

      //bds->init();
      //bbnPos->init();
      //bbnNeg->init();
      lbmNS->init();

      OutputCSV<CollisionBGKNSF> *nsFile = new OutputCSV<CollisionBGKNSF>(cmNS, lm);

      /* Main loops */
      for (int tt = 0; tt < tMain; tt++) {
        cout << "TT: " << tt << endl;

        //if(tt % 10 == 0){ tNP += tt; tNS += tt;}

//        /* Update net charge density */
        updateRho(rho_eps, cmNPneg, cmNPpos, lm, eps_r, V0, l0, C0);
        cmPE->reset();

        for (int t = 0; t < tPE; t++) {
          //cout<<"tPE "<<t<<endl;
          lbmPE->collideAndStream();
        }
        cmPE->getDPsi(dPsix, dPsiy);

        //scale potential gradients to SI units *l0
        rescale2DArray(dPsix, V0, ny, nx);
        rescale2DArray(dPsiy, V0, ny, nx);
        cout << "dPsix " << dPsix[2][1] << endl;
        cout << "dPsiy " << dPsiy[2][1] << endl;
        rescale2DArray(ux, 1e-4, ny, nx);
        rescale2DArray(uy, 1e-4, ny, nx);

        for (int t = 0; t < tNP; t++) {
          lbmNPneg->collideAndStream();
          lbmNPpos->collideAndStream();
        }
////
////
        updateForce(force, ux, uy, rho_eps, lmNS, eps_r, u0, l0, V0, C0,
            bulkConductivity, dPdx, cmNPpos, cmNPneg);
        for (int t = 0; t < tNS; t++) {
          //cout << t <<endl;
          lbmNS->collideAndStream();
        }

        /* update velocities */
        cmNS->getU(ux, uy);
        cout << "ux " << ux[ny / 2][1] << endl;
        cout << "uy " << uy[ny / 2][1] << endl;

        /*write result to file*/
        stringstream ss;
        string base = "vis_scripts/data";
        if (tt % tMod == 0) {
          //dPsiY
          ss.str("");
          ss << base << "PSI";
          ss << tt / tMod << "/";
          createDirectory(ss.str());
          ss << "dpsiy.csv";
          //write2DArray(dPsiy, NULL, ss.str(), nx, ny);

          //potential
          ss.str("");
          ss << base << "PE";
          ss << tt / tMod << "/";
          createDirectory(ss.str());
          ss << "rho.csv";
          cmPE->dataToFile(ss.str());

          //C_neg
          ss.str("");
          ss << base << "NP";
          ss << tt / tMod << "/";
          createDirectory(ss.str());
          ss << "ni_neg.csv";
          cmNPneg->dataToFile(ss.str());

          //C_pos
          ss.str("");
          ss << base << "NP";
          ss << tt / tMod << "/";
          ss << "ni_pos.csv";
          cmNPpos->dataToFile(ss.str());

          //U and rho_m
          ss.str("");
          ss << base << "NS";
          ss << tt / tMod << "/";
          nsFile->setPath(ss.str());
          nsFile->writeData();

          //fx
          ss.str("");
          ss << base << "FX";
          ss << tt / tMod << "/";
          createDirectory(ss.str());
          ss << "fx.csv";
          write2DArray(force[0][0], ss.str(), nx, ny);
        }
      }

      cout << "done LNP." << endl;

      return 0;
    }

    void updateForce(double ****force, double **ux, double **uy, double **rho_eps,
        Lattice2D *lm, double eps_r, double u0, double l0, double V0, double C0,
        double bulkCond, double dPdx, CollisionD2Q9AD *cmNPpos,
        CollisionD2Q9AD *cmNPneg) {

      double rho0 = 1e3;
      double rs = eps_r * PHYS_EPS0 * V0 / l0 / l0;
      cout << "RS: " << rs << endl;
      //double prefactor = u0*rs*rs/bulkCond *l0 / (u0 * u0 * rho0); //rescale to L.U.
      //cout << "PREF: "<< prefactor <<endl;

      double jx = 0;
      double jy = 0;
      double prefactorJ = PHYS_E_CHARGE * C0 * PHYS_E_CHARGE * C0 * rs * u0
      / bulkCond * l0 / (u0 * u0 * rho0) * 1e-4;
      cout << "PREFJ: " << prefactorJ << endl;

      for (int j = 0; j < lm->n.y; j++) {
        for (int i = 0; i < lm->n.x; i++) {
          //fx[j][i] = -prefactor*ux[j][i]*rho_eps[j][i]*rho_eps[j][i] + dPdx;
          //fx[j][i] = dPdx;
          //cout<<"ux: "<<ux[j][i]<<endl;
          //cout<<"FX_ADV: "<<fx[j][i]<<endl;

          jx = (cmNPpos->getXFlux(j, i) - cmNPneg->getXFlux(j, i));
          jy = (cmNPpos->getYFlux(j, i) - cmNPneg->getYFlux(j, i));

          force[0][0][j][i] = prefactorJ * jx * rho_eps[j][i] + dPdx;

          // cout<<"FX_FLUX: "<<fx[j][i]<<endl;

          force[1][0][j][i] = prefactorJ * jy * rho_eps[j][i];
          // cout << rho_eps[j][i] <<endl;
          // cout<<"jy: "<<jy<<endl;
          // cout<<"rho_eps: "<<rho_eps[j][i]<<endl;
        }
        <<<<<<< HEAD
        cout<<"FY_FORCE: "<<force[1][0][lm->n.y/2][1]<<endl;
        jx = ( cmNPpos->getXFlux(lm->n.y/2, 1) - cmNPneg->getXFlux(lm->n.y/2, 1) );
        cout<<"JX: " << jx << endl;
        cout<<"EL_VIS: "<<prefactorJ*jx*rho_eps[lm->n.y/2][1]<<endl;
        cout<<"FX_FORCE: "<<force[0][0][lm->n.y/2][1]<<endl;
        =======
      }
      cout << "FY_FORCE: " << force[1][0][500][1] << endl;
      jx = (cmNPpos->getXFlux(500, 1) - cmNPneg->getXFlux(500, 1));
      cout << "JX: " << jx << endl;
      cout << "EL_VIS: " << prefactorJ * jx * rho_eps[500][1] << endl;
      cout << "FX_FORCE: " << force[0][0][500][1] << endl;
      >>>>>>> be0085aa8c172e2e67c81b77b2d5932ce2e0768c
    }

    /* updates rho_eps = -rho/(eps_r*eps_0)
     * return value in: lattice units.
     */
    void updateRho(double **rho_eps, CollisionD2Q9AD *cmNPneg,
        CollisionD2Q9AD *cmNPpos, LatticeModel *lm, double eps_r, double V0,
        double l0, double C0) {

      double **Cpos = cmNPpos->getNi();
      double **Cneg = cmNPneg->getNi();
      double zPos = cmNPpos->getZ();
      double zNeg = cmNPneg->getZ();
      double prefactor = -PHYS_E_CHARGE * l0 * l0 * C0 / (eps_r * PHYS_EPS0 * V0); //dimension less.
      cout << "rho_prefactor: " << prefactor << endl;
      for (int j = 0; j < lm->n.y; j++) {
        for (int i = 0; i < lm->n.x; i++) {
          //cout << "cpos: " << Cpos[j][i] << endl;
          //cout << "cneg: " << Cneg[j][i] << endl;
          rho_eps[j][i] = zPos * Cpos[j][i] + zNeg * Cneg[j][i];
          rho_eps[j][i] *= prefactor;
        }
      }
      cout << "cpos: " << Cpos[2][1] << endl;
      cout << "cneg: " << Cneg[2][1] << endl;
      cout << "rho_eps: " << rho_eps[2][1] << endl;
    }

//
//void addRect(int x, int y, int w, int h, double rho_surface, BounceBackNodes<CollisionD2Q9BGKNSF> *bbNS,
//		NeumannNodesPESlip *bds, SlipNodes<CollisionD2Q9AD> *bbnNeg,
//		SlipNodes<CollisionD2Q9AD> *bbnPos){
//	//NS
//	for(int i = x; i < x + w + 1; i++){
//		bbNS->addNode(i, y, 0);
//		bbNS->addNode(i, y + h, 0);
//	}
//
//	for(int j = y + 1; j < y + h; j++){
//		bbNS->addNode(x, j, 0);
//		bbNS->addNode(x + w, j, 0);
//	}
//
//	//PE + NP
//    for(int i = x + 1; i < x + w; i++){
//        bds->addNode(i, y, 0, rho_surface, 2);
//        bbnPos->addNode(i, y, 0, 2);
//        bbnNeg->addNode(i, y, 0, 2);
//
//        bds->addNode(i, y + h, 0, rho_surface, 4);
//        bbnNeg->addNode(i, y + h, 0, 4);
//        bbnPos->addNode(i, y + h, 0, 4);
//    }
//
//	for(int j = y + 1; j < y + h; j++){
//        bds->addNode(x, j, 0, rho_surface, 1);
//        bbnNeg->addNode(x, j, 0, 1);
//        bbnPos->addNode(x, j, 0, 1);
//
//        bds->addNode(x + w, j, 0, rho_surface, 3);
//        bbnNeg->addNode(x + w, j, 0, 3);
//        bbnPos->addNode(x + w, j, 0, 3);
//	}
//
//    bds->addNode(x, y, 0, rho_surface, 6);
//    bbnNeg->addNode(x, y, 0, 6);
//    bbnPos->addNode(x, y, 0, 6);
//    bds->addNode(x, y + h, 0, rho_surface, 7);//7
//    bbnNeg->addNode(x, y + h, 0, 7);//7
//    bbnPos->addNode(x, y + h, 0, 7);//7
//    bds->addNode(x + w, y, 0, rho_surface, 5);//5
//    bbnNeg->addNode(x + w, y, 0, 5);//5
//    bbnPos->addNode(x + w, y, 0, 5);//5
//    bds->addNode(x + w, y + h, 0, rho_surface, 8);//8
//    bbnNeg->addNode(x + w, y + h, 0, 8);//8
//    bbnPos->addNode(x + w, y + h, 0, 8);//8
//}
/////*TODO modified C_neg*/
////void initC(CollisionD2Q9LNP *cmNPneg,
////           CollisionD2Q9LNP *cmNPpos,
////           LatticeModel     *lm){
////
////    double **Cpos = cmNPpos->getNi();
////    double **Cneg = cmNPneg->getNi();
////    for(int j = 0; j < lm->n.y; j++){
////        for(int i = 0; i < lm->n.x; i++){
////            Cpos[j][i] = 1.0;//(1.0 + cos((double)(j-1)*2.0*M_PI/(lm->n.y-1-2))*0.3);
////          //  cout<<"cpos: "<<Cpos[j][i]<<endl;
////            Cneg[j][i] = 1.0;//(1.0 - cos((j-1)*2.0*M_PI/(lm->n.y-1-2))*0.3+0.6/(lm->n.y-2));
////        }
////    }
////}
