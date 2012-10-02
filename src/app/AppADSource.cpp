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
               CollisionD2Q9LNP *cmNPneg,
               CollisionD2Q9LNP *cmNPpos,
               LatticeModel     *lm,
               double           eps_r,
               double           V0,
               double           l0,
               double           C0);

void initC(CollisionD2Q9LNP     *cmNPneg,
           CollisionD2Q9LNP     *cmNPpos,
           LatticeModel         *lm);

int main(){
    cout<<"2D NS <-> PE <-> NP ..."<<endl;

    /* Parameter definitions */
    int nx = 3;
    int ny = 50;

    int tNP = 50;
    int tPE = 10000;
    int tNS = 50;
    int tMain = 500;

    int tMod = 1;

    double l0 = 1.0e-5/(ny-1); //PE, NP
    double C0 = 1e-5*PHYS_N_A; //NP
    double u0 = 1.0e-1; //NP
    double dt = 1.0;
    double V0 = -50e-3; //PE

    double D = 1.0e-8;
    double u0x = 0.0;
    double T = 273;
    double Pe = u0*l0/D;
    cout<<"pe: "<<Pe<<endl;
    double wNP = 1/(1.5/Pe + 0.5);
    cout<<"wNP: "<<wNP<<endl;
    double wPE = 1.0;
    double eps_r = 80;


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

    /* Boundary conds. for Poission solver */
    HeZouLPMChaiNodes *bds = new HeZouLPMChaiNodes();
    bds->setCollisionModel(cmPE);
    for(int i = 0; i < nx; i++){
        bds->addNode(i, 0, 0, 1.0/1.8);
        bds->addNode(i, ny-1, 0, 1.0/1.8);
    }
    lbmPE->addBoundaryNodes(bds);

    /* init */
    lbmPE->init();
    bds->init(); //preprocessing of boundary conditions

    /* Nernst Planck solver */
    CollisionD2Q9LNP *cmNPneg = new CollisionD2Q9LNP();
    CollisionD2Q9LNP *cmNPpos = new CollisionD2Q9LNP();
    StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
    LatticeModel *lm = new Lattice2D(nx, ny);
    StreamD2Q9Periodic *sm2 = new StreamD2Q9Periodic();
    LatticeModel *lm2 = new Lattice2D(nx, ny);


    cout<<"w: "<<wNP<<endl;

    cmNPneg->setW(wNP);
    cmNPneg->setC(1);
    cmNPneg->setZ(-1);
    cmNPneg->setInitC(1.0);
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
    cmNPpos->setInitC(1.0);
    cmNPpos->setUx(ux);
    cmNPpos->setUy(uy);
    cmNPpos->setDPsix(dPsix);
    cmNPpos->setDPsiy(dPsiy);
    cmNPpos->setT(T);
    cmNPpos->setPe(Pe);
    cmNPpos->setRHS(rho_eps);

    LBM *lbmNPneg = new LBM(lm, cmNPneg, sm);
    LBM *lbmNPpos = new LBM(lm2, cmNPpos, sm2);

    /* Boundary conds for NP solver*/
    NeumannNodesNP *bbnNeg = new NeumannNodesNP();
    bbnNeg->setCollisionModel(cmNPneg);
    for(int i = 0; i < nx; i++){
        bbnNeg->addNode(i, 0, 0, 0.0, 2);
        bbnNeg->addNode(i, ny-1, 0, 0.0, 4);
    }
    bbnNeg->init();
    lbmNPneg->addBoundaryNodes(bbnNeg);


    NeumannNodesNP *bbnPos = new NeumannNodesNP();
    bbnPos->setCollisionModel(cmNPpos);

    for(int i = 0; i < nx; i++){
       bbnPos->addNode(i, 0, 0, 0.0, 2);
       bbnPos->addNode(i, ny-1, 0, 0.0, 4);
    }
    bbnPos->init();
    lbmNPpos->addBoundaryNodes(bbnPos);

//    //todo test with bounce back....
//    BounceBackNodes<CollisionD2Q9LNP> *bbTest = new BounceBackNodes<CollisionD2Q9LNP>();
//    bbTest->setCollisionModel(cmNPpos);
//
//    for(int i = 0; i < nx; i++){
//        bbTest->addNode(i, 0, 0);
//        bbTest->addNode(i, ny-1, 0);
//    }
//   /// bbTest->init();
//    lbmNPpos->addBoundaryNodes(bbTest);

    /* Initialize solver */
    lbmNPneg->init();
    lbmNPpos->init();
    initC(cmNPneg, cmNPpos, lm);
    cmNPneg->reset();
    cmNPpos->reset();

    /* Main loops */
    // double pref = PHYS_E_CHARGE/(Pe * PHYS_KB * T);
    // cout<<"pref: "<<pref<<endl;
    for(int tt = 0; tt < tMain; tt++){
        cout<<"TT: "<<tt<<endl;
       // cout<<"-------------rho_eps PRE: "<<rho_eps[1][nx/2]<<endl;

        updateRho(rho_eps, cmNPneg, cmNPpos, lm, eps_r, V0, l0, C0);

        //rescale2DArray(rho_eps, -1.0, ny, nx);
        cmPE->reset();
        for(int t = 0; t < tPE; t++){
            //cout<<"tPE "<<t<<endl;
            lbmPE->collideAndStream();
        }
        cmPE->getDPsi(dPsix, dPsiy);

        //scale gradients to SI units... l0 included in Pe
        cout<<"----------DPSIY!!: "<<dPsiy[1][nx/2]<<endl;
        //rescale2DArray(dPsix, -1.54*3*V0, ny, nx);
        //rescale2DArray(dPsiy, -1.54*3*V0, ny, nx);
        rescale2DArray(dPsix, -3.0*V0, ny, nx);
        rescale2DArray(dPsiy, -3.0*V0, ny, nx);
        //rescale2DArray(dPsix, V0, ny, nx);
        //rescale2DArray(dPsiy, V0, ny, nx);

        cout<<"----------DPSIY: "<<dPsiy[1][nx/2]<<endl;

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


        //rescale2DArray(dPsix, l0, ny, nx);
        //rescale2DArray(dPsiy, l0, ny, nx);
       // cout<<"----------DPSIY: "<<dPsiy[1][nx/2]<<endl;

        //rescale rho/eps to SI units. one l0 included in Pe V0/(l0*l0)*(l0*l0)
        rescale2DArray(rho_eps, V0, ny, nx);

        //add rescaling
       // rescale2DArray(rho_eps, -1.0, ny, nx);
        cout<<"-------------rho_eps: "<<rho_eps[1][nx/2]<<endl;

     //   cmNPneg->reset();
      //  cmNPpos->reset();

        //dPsi array will be destroyed from here!
        for(int t = 0; t < tNP; t++){
            cout<<"-------------T_NP: "<<t<<endl;
            lbmNPneg->collideAndStream();
            lbmNPpos->collideAndStream();
        }

        //rm scale by -1

    }

    cout<<"done LNP."<<endl;

    return 0;
}

/* updates rho_eps = -rho/(eps_r*eps_0)
 * returns value in lattice units
 *
 */
void updateRho(double **rho_eps,
               CollisionD2Q9LNP *cmNPneg,
               CollisionD2Q9LNP *cmNPpos,
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
    cout<<"PREFACTOR: "<<prefactor<<endl;
    cout<<"CNEG: "<<Cneg[1][lm->n.x/2]<<endl;
    cout<<"CPOS: "<<Cpos[1][lm->n.x/2]<<endl;
    for(int j = 0; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            rho_eps[j][i] = zPos*Cpos[j][i] +
                            zNeg*Cneg[j][i];
            //cout<<"sfsdf "<<Cpos[j][i]<<endl;
            rho_eps[j][i] *= prefactor;

           // rho_eps[j][i] = -l0*l0/V0*2*PHYS_E_CHARGE*C0/(eps_r*PHYS_EPS0)*\
                            (cos(j*2*M_PI/(lm->n.y-1)) + 1)*0.5*0.5;
        }
    }
    cout<<"RHS: "<<rho_eps[1][lm->n.x/2]<<endl;
}

/*TODO modified C_neg*/
void initC(CollisionD2Q9LNP *cmNPneg,
           CollisionD2Q9LNP *cmNPpos,
           LatticeModel     *lm){

    double **Cpos = cmNPpos->getNi();
    double **Cneg = cmNPneg->getNi();
    for(int j = 1; j < lm->n.y; j++){
        for(int i = 0; i < lm->n.x; i++){
            Cpos[j][i] = 1.0; //(1.0 + cos((double)(j-1)*2.0*M_PI/(lm->n.y-1-2))*0.3);
          //  cout<<"cpos: "<<Cpos[j][i]<<endl;
            Cneg[j][i] = 1.0; //(1.0 - cos((j-1)*2.0*M_PI/(lm->n.y-1-2))*0.3+0.6/(lm->n.y-2));
        }
    }
}
