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
#include "../LBM.h"

using namespace std;

void updateRho(double           **rho_eps,
               CollisionD2Q9AD *cmNPneg,
               CollisionD2Q9AD *cmNPpos,
               LatticeModel     *lm,
               double           eps_r,
               double           V0,
               double           l0,
               double           C0);

void updateForce(double **fx, double **fy, double **ux, double **uy, double **rho_eps,
                 Lattice2D *lm, double eps_r, double u0, double l0, double V0, double C0,
                 double bulkCond, double dPdx, CollisionD2Q9AD *cmNPpos, CollisionD2Q9AD *cmNPneg);

int main(){
    cout<<"2D, NS <-> PE <-> NP"<<endl;

    /* Parameter definitions */
    int nx = 3;
    int ny = 101;

    int tNP = 10;
    int tPE = 10000;
      int tNS = tNP;//tNP;
    int tMain = 1000;

    int tMod = 1; //undersök i detalj.... ok.

    double l0 = 1e-5/(ny-1); //PE, NP
    double C0 = 1e-4*PHYS_N_A; //NP
    double u0 = 1e-1; //NP, NS
    double dt = 1.0;
    double V0 = -50e-3; //PE
    double rho0 = 1e3; //NS

    double D = 1.0e-8;
    double u0x = 0.0;
    double T = 293;
    double eps_r = 80;
    double rho_surface = -0.75e-1;//-50e-3*eps_r*PHYS_EPS0/1e-7/V0*l0;
    double bulk_charge = 1.0;
    double gamma = PHYS_E_CHARGE/(PHYS_KB*T);
    double dPdx = 1e-6;//1e3 * l0/(rho0 * u0 * u0); //lattice units
    double bulkConductivity = 1.2639e-6; //conductivity [S/m]

    double Pe = u0*l0/D;
    double wNP = 1/(3.0/Pe + 0.5);
    double wPE = 1.0;
    double wNS = 0.5;

    /*print parameters*/
    printLine(20);
    cout<<"DIM = ("<<nx<<", "<<ny<<")"<<endl;
    cout<<"T = "<<T<<endl;
    cout<<"RHO_SURFACE = "<<rho_surface<<", "<<rho_surface*V0/l0*PHYS_EPS0*eps_r<<" C/M^2"<<endl;
    cout<<"BULK_CHARGE = "<<bulk_charge<<endl;
    cout<<"PE = "<<Pe<<endl;
    cout<<endl;
    cout<<"w_np = "<<wNP<<endl;
    cout<<"w_pe = "<<wPE<<endl;
    cout<<endl;
    cout<<"l0 = "<<l0<<endl;
    cout<<"V0 = "<<V0<<endl;
    cout<<"GAMMA: "<<gamma<<endl;
    cout<<"l0*gamma/Pe *V0/l0 = "<<l0*gamma/Pe*V0/l0<<endl;
    cout<<"l0^2*gamma/Pe *V0/l0^2 = "<<l0*l0*gamma/Pe*V0/l0/l0<<endl;
    cout<<"1/Pe = "<<1/Pe<<endl;
    cout<<"dPdx = "<<dPdx<<endl;
    printLine(20);

    /* Allocate memory for velocity and grad. potential arrays */
    double **ux = allocate2DArray(ny, nx);
    double **uy = allocate2DArray(ny, nx);
    double **dPsix = allocate2DArray(ny, nx);
    double **dPsiy = allocate2DArray(ny, nx);
    double **rho_eps = allocate2DArray(ny, nx);
    double **fx = allocate2DArray(ny, nx);
    double **fy = allocate2DArray(ny, nx);

    for(int j = 0; j < ny; j++){
        for(int i = 0; i < nx; i++){
            ux[j][i] = 0;
            uy[j][i] = 0;
            fx[j][i] = 0;
            fy[j][i] = 0;
            dPsix[j][i] = 0.0;
            dPsiy[j][i] = 0.0;
            rho_eps[j][i] = 0.0;//-l0*l0/V0*2*PHYS_E_CHARGE*C0/(eps_r *PHYS_EPS0)*\
                            (cos(j*2*M_PI/(ny-1)) + 1)*0.5;
        }
    }

    /* Poisson eq. solver */
    CollisionD2Q9LPMChaiRHS *cmPE = new CollisionD2Q9LPMChaiRHS();
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
    for(int i = 0; i < nx; i++){
        bds->addNode(i, 0, 0, rho_surface, 2);
        bds->addNode(i, ny-1, 0, rho_surface, 4);
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
    for(int i = 0; i < nx; i++){
        bbnNeg->addNode(i, 0, 0, 2);
        bbnNeg->addNode(i, ny-1, 0, 4);
    }
    bbnNeg->init();

    SlipNodes<CollisionD2Q9AD> *bbnPos = new SlipNodes<CollisionD2Q9AD>();
    lbmNPpos->addBoundaryNodes(bbnPos);
    bbnPos->setCollisionModel(cmNPpos);
    for(int i = 0; i < nx; i++){
        bbnPos->addNode(i, 0, 0, 2);
        bbnPos->addNode(i, ny-1, 0, 4);
    }
    bbnPos->init();

    /* Initialize solver */
    lbmNPneg->init();
    lbmNPpos->init();


    /* NS Solver */
    CollisionD2Q9BGKShanChenForce *cmNS = new CollisionD2Q9BGKShanChenForce();
    StreamD2Q9Periodic *smNS = new StreamD2Q9Periodic();
    Lattice2D *lmNS = new Lattice2D(nx, ny);

    cmNS->setW(wNS);
    cmNS->setC(1.0);

    LBM *lbmNS = new LBM(lmNS, cmNS, smNS);

    /* Set boundary conditions for flow */
    BounceBackNodes<CollisionD2Q9BGKShanChenForce> *bbNS =
            new BounceBackNodes<CollisionD2Q9BGKShanChenForce>();
    bbNS->setCollisionModel(cmNS);
    for(int i = 0; i < nx; i++){
        bbNS->addNode(i, 0, 0);
        bbNS->addNode(i, ny-1, 0);
    }
    lbmNS->addBoundaryNodes(bbNS);

    lbmNS->init();
    cmNS->setForce(fx, fy);

    for(int t = 0; t < tNS; t++){
        cout<<"T: "<<t<<endl;
        lbmNS->collideAndStream();
    }

    cmNS->dataToFile("vis_scripts/bench_force_poi2/");

    /* Main loops */
    for(int tt = 0; tt < tMain; tt++){
        cout<<"TT: "<<tt<<endl;

        if(tt == 120){ tNP = 1; tNS = 1;}

        /* Update net charge density */
        updateRho(rho_eps, cmNPneg, cmNPpos, lm, eps_r, V0, l0, C0);
        cmPE->reset();

        for(int t = 0; t < tPE; t++){
            //cout<<"tPE "<<t<<endl;
            lbmPE->collideAndStream();
        }
        cmPE->getDPsi(dPsix, dPsiy);

        //scale potential gradients to SI units *l0
        rescale2DArray(dPsix, V0, ny, nx);
        rescale2DArray(dPsiy, V0, ny, nx);

        for(int t = 0; t < tNP; t++){
            lbmNPneg->collideAndStream();
            lbmNPpos->collideAndStream();
        }


        updateForce(fx, fy, ux, uy, rho_eps,\
                         lmNS, eps_r, u0, l0, V0, C0,\
                         bulkConductivity, dPdx, cmNPpos, cmNPneg);
        for(int t = 0; t < tNS; t++){

            lbmNS->collideAndStream();
        }

        /* update velocities */
        cmNS->getU(ux, uy);

        /*write result to file*/
        stringstream ss;
        string base = "vis_scripts/data";
        if(tt % tMod == 0){
            //dPsiY
            ss.str("");
            ss<<base<<"PSI";
            ss<<tt/tMod<<"/";
            createDirectory(ss.str());
            ss<<"dpsiy.csv";
            write2DArray(dPsiy, NULL, ss.str(), nx, ny);

            //potential
            ss.str("");
            ss<<base<<"PE";
            ss<<tt/tMod<<"/";
            createDirectory(ss.str());
            ss<<"rho.csv";
            cmPE->dataToFile(ss.str());

            //C_neg
            ss.str("");
            ss<<base<<"NP";
            ss<<tt/tMod<<"/";
            createDirectory(ss.str());
            ss<<"ni_neg.csv";
            cmNPneg->dataToFile(ss.str());

            //C_pos
            ss.str("");
            ss<<base<<"NP";
            ss<<tt/tMod<<"/";
            ss<<"ni_pos.csv";
            cmNPpos->dataToFile(ss.str());

            //U and rho_m
            ss.str("");
            ss<<base<<"NS";
            ss<<tt/tMod<<"/";
            createDirectory(ss.str());
            cmNS->dataToFile(ss.str());
        }
    }

    cout<<"done LNP."<<endl;

    return 0;
}

void updateForce(double **fx, double **fy, double **ux, double **uy, double **rho_eps,
                 Lattice2D *lm, double eps_r, double u0, double l0, double V0, double C0,
                 double bulkCond, double dPdx, CollisionD2Q9AD *cmNPpos, CollisionD2Q9AD *cmNPneg){

    double rho0 = 1e3;
    double rs = eps_r*PHYS_EPS0*V0/l0/l0;
    double prefactor = u0*rs*rs/bulkCond *l0 / (u0 * u0 * rho0); //rescale to L.U.

    double jx = 0;
    double jy = 0;
    double prefactorJ = PHYS_E_CHARGE*C0* rs*u0 / bulkCond *l0 / (u0 * u0 * rho0);

    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            fx[j][i] = -prefactor*ux[j][i]*rho_eps[j][i]*rho_eps[j][i] + dPdx;
            //fx[j][i] = dPdx;
            //cout<<"ux: "<<ux[j][i]<<endl;
            cout<<"FX_ADV: "<<fx[j][i]<<endl;

            jx = cmNPpos->getXFlux(j, i) - cmNPneg->getXFlux(j, i);
            jy = cmNPpos->getYFlux(j, i) - cmNPneg->getYFlux(j, i);

            fx[j][i] = prefactorJ*jx*rho_eps[j][i] + dPdx;

            cout<<"FX_FLUX: "<<fx[j][i]<<endl;

            fy[j][i] = 0;//prefactorJ*jy*rho_eps[j][i];
            cout<<"FY_FLUX: "<<fy[j][i]<<endl;
        }
    }
}

/* updates rho_eps = -rho/(eps_r*eps_0)
 * return value in: lattice units.
 */
void updateRho(double **rho_eps,
               CollisionD2Q9AD *cmNPneg,
               CollisionD2Q9AD *cmNPpos,
               LatticeModel *lm,
               double eps_r,
               double V0,
               double l0,
               double C0){

    double **Cpos = cmNPpos->getNi();
    double **Cneg = cmNPneg->getNi();
    double zPos = cmNPpos->getZ();
    double zNeg = cmNPneg->getZ();
    double prefactor = -PHYS_E_CHARGE*l0*l0*C0/(eps_r*PHYS_EPS0*V0);

    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            rho_eps[j][i] = zPos*Cpos[j][i] +
                            zNeg*Cneg[j][i];
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
