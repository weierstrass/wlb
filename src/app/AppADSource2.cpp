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

void initC(CollisionD2Q9LNP     *cmNPneg,
           CollisionD2Q9LNP     *cmNPpos,
           LatticeModel         *lm);

int main(){
    cout<<"2D, NS <-> PE <-> NP"<<endl;

    /* Parameter definitions */
    int nx = 3;
    int ny = 65;

    int tNP = 1;
    int tPE = 10000;
    int tNS = 50;
    int tMain = 300;

    int tMod = 1;

    double l0 = 1e-5/(ny-1); //PE, NP
    double C0 = 1e-4*PHYS_N_A; //NP
    double u0 = 1e-1; //NP
    double dt = 1.0;
    double V0 = -50e-3; //PE

    double D = 1.0e-8;
    double u0x = 0.0;
    double T = 293;
    double eps_r = 80;
    double rho_surface = -1e-1;//-50e-3*eps_r*PHYS_EPS0/1e-7/V0*l0;
    double bulk_charge = 1.0;
    double gamma = PHYS_E_CHARGE/(PHYS_KB*T);

    double Pe = u0*l0/D;
    double wNP = 1/(3.0/Pe + 0.5);
    double wPE = 1.0;

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
    printLine(20);

    /* Allocate memory for velocity and grad. potential arrays */
    double **ux = allocate2DArray(ny, nx);
    double **uy = allocate2DArray(ny, nx);
    double **dPsix = allocate2DArray(ny, nx);
    double **dPsiy = allocate2DArray(ny, nx);
    double **rho_eps = allocate2DArray(ny, nx);

    for(int j = 0; j < ny; j++){
        for(int i = 0; i < nx; i++){
            ux[j][i] = u0x;
            uy[j][i] = 0;
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

    /* Boundary conds. for Poission solver */
//    HeZouLPMChaiNodes *bds = new HeZouLPMChaiNodes();
//    bds->setCollisionModel(cmPE);
//    for(int i = 0; i < nx; i++){
//        bds->addNode(i, 0, 0, 1.0/1.8);
//        bds->addNode(i, ny-1, 0, 1.0/1.8);
//    }

    NeumannNodesPE *bds = new NeumannNodesPE();
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
    cmNPneg->setRHS(rho_eps);

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
    cmNPpos->setRHS(rho_eps);

    LBM *lbmNPneg = new LBM(lm, cmNPneg, sm);
    LBM *lbmNPpos = new LBM(lm2, cmNPpos, sm2);

//    /* Boundary conds for NP solver*/
//    NeumannNodesNP *bbnNeg = new NeumannNodesNP();
//    lbmNPneg->addBoundaryNodes(bbnNeg);
//    bbnNeg->setCollisionModel(cmNPneg);
//    for(int i = 0; i < nx; i++){
//        bbnNeg->addNode(i, 0, 0, 0.0, 2);
//        bbnNeg->addNode(i, ny-1, 0, 0.0, 4);
//    }
//    bbnNeg->init();
//
//    NeumannNodesNP *bbnPos = new NeumannNodesNP();
//    lbmNPpos->addBoundaryNodes(bbnPos);
//    bbnPos->setCollisionModel(cmNPpos);
//    for(int i = 0; i < nx; i++){
//       bbnPos->addNode(i, 0, 0, 0.0, 2);
//       bbnPos->addNode(i, ny-1, 0, 0.0, 4);
//    }
//    bbnPos->init();

    /* Boundary conds for NP solver*/
       SlipNodes<CollisionD2Q9AD> *bbnNeg = new SlipNodes<CollisionD2Q9AD>();
       lbmNPneg->addBoundaryNodes(bbnNeg);
       bbnNeg->setCollisionModel(cmNPneg);
       for(int i = 0; i < nx; i++){
           bbnNeg->addNode(i, 0, 0);
           bbnNeg->addNode(i, ny-1, 0);
       }
       bbnNeg->init();

       SlipNodes<CollisionD2Q9AD> *bbnPos = new SlipNodes<CollisionD2Q9AD>();
       lbmNPpos->addBoundaryNodes(bbnPos);
       bbnPos->setCollisionModel(cmNPpos);
       for(int i = 0; i < nx; i++){
          bbnPos->addNode(i, 0, 0);
          bbnPos->addNode(i, ny-1, 0);
       }
       bbnPos->init();


    /* Initialize solver */
    lbmNPneg->init();
    lbmNPpos->init();
   // initC(cmNPneg, cmNPpos, lm);
   // cmNPneg->reset();
   // cmNPpos->reset();

    /* Main loops */
    for(int tt = 0; tt < tMain; tt++){
        cout<<"TT: "<<tt<<endl;

        updateRho(rho_eps, cmNPneg, cmNPpos, lm, eps_r, V0, l0, C0);

        cmPE->reset();
        for(int t = 0; t < tPE; t++){
            //cout<<"tPE "<<t<<endl;
            lbmPE->collideAndStream();
        }
        cmPE->getDPsi(dPsix, dPsiy);

        //rescale2DArray(dPsix, V0, ny, nx);
        //rescale2DArray(dPsiy, V0, ny, nx);

        cout<<"----------DPSIY: "<<dPsiy[0][nx/2]<<endl;

        stringstream ss;
        string base = "vis_scripts/data";
        if(tt % tMod == 0){
            ss.str("");
            ss<<base<<"PSI";
            ss<<tt/tMod<<"/";
            createDirectory(ss.str());
            ss<<"dpsiy.csv";
            write2DArray(dPsiy, NULL, ss.str(), nx, ny);
            ss.str("");
            ss<<base<<"PE";
            ss<<tt/tMod<<"/";
            createDirectory(ss.str());
            ss<<"rho.csv";
            cmPE->dataToFile(ss.str());
            ss.str("");
            ss<<base<<"NP";
            ss<<tt/tMod<<"/";
            createDirectory(ss.str());
            ss<<"ni_neg.csv";
            cmNPneg->dataToFile(ss.str());
            ss.str("");
            ss<<base<<"NP";
            ss<<tt/tMod<<"/";
            ss<<"ni_pos.csv";
            cmNPpos->dataToFile(ss.str());
        }

        //rescale rho/eps to SI units. one l0 included in Pe V0/(l0*l0)*(l0*l0)
       // rescale2DArray(rho_eps, V0, ny, nx);
        rescale2DArray(dPsix, V0, ny, nx);
        rescale2DArray(dPsiy, V0, ny, nx);

        for(int t = 0; t < tNP; t++){
            cout<<"-------------T_NP: "<<t<<endl;
            lbmNPneg->collideAndStream();
            lbmNPpos->collideAndStream();
        }


    }

    cout<<"done LNP."<<endl;

    return 0;
}

/* updates rho_eps = -rho/(eps_r*eps_0)
 * returns value in lattice units
 *
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
    //cout<<"PREFACTOR: "<<prefactor<<endl;
    //cout<<"CNEG: "<<Cneg[1][lm->n.x/2]<<endl;
    //cout<<"CPOS: "<<Cpos[1][lm->n.x/2]<<endl;
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            rho_eps[j][i] = zPos*Cpos[j][i] +
                            zNeg*Cneg[j][i];
            rho_eps[j][i] *= prefactor;
        }
    }
}

/*TODO modified C_neg*/
void initC(CollisionD2Q9LNP *cmNPneg,
           CollisionD2Q9LNP *cmNPpos,
           LatticeModel     *lm){

    double **Cpos = cmNPpos->getNi();
    double **Cneg = cmNPneg->getNi();
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            Cpos[j][i] = 1.0;//(1.0 + cos((double)(j-1)*2.0*M_PI/(lm->n.y-1-2))*0.3);
          //  cout<<"cpos: "<<Cpos[j][i]<<endl;
            Cneg[j][i] = 1.0;//(1.0 - cos((j-1)*2.0*M_PI/(lm->n.y-1-2))*0.3+0.6/(lm->n.y-2));
        }
    }
}
