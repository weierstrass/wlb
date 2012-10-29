/*
 * AppPENeumann.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include <iostream>
#include "../LBM.h"

using namespace std;

int main(){
    cout<<"LPM Chai test.."<<endl;

    int nx = 3;
    int ny = 65;
    int tMax = 15000;
    double l0 = 2e-5/(ny-1);
    double V0 = -50e-3;
    double dt = 1.0;
    double T = 293; //temperature [K]
    double cinf = 1e-4; //ion concentration at inf. [Mol]
    double epsilon = 80*PHYS_EPS0; //absolute permittivity [F/m]
    double surface_charge = -1e-1; //l.u.

    CollisionD2Q9LPMChaiRHS *cm = new CollisionD2Q9LPMChaiRHS();
    StreamD2Q9Periodic *sm = new StreamD2Q9Periodic();
    LatticeModel *lm = new Lattice2D(nx, ny);
    UnitHandlerLPM *uh = new UnitHandlerLPM();
    double **rho_e = allocate2DArray(ny, nx);

    uh->setCharLength(l0);
    uh->setCharVoltage(V0);
    uh->setTimeStep(dt);
    cm->setUnitHandler(uh);
    cm->setW(1.0);
    cm->setC(1.0);
    cm->setRHS(rho_e);

    double prefactor = l0*l0/V0*2*PHYS_E_CHARGE*cinf*PHYS_N_A/(epsilon);
    double inSinh = PHYS_E_CHARGE*V0/PHYS_KB/T;

    LBM *lbm = new LBM(lm, cm, sm);

    /* Boundaries */
    NeumannNodesPESlip *bds = new NeumannNodesPESlip();
    lbm->addBoundaryNodes(bds);
    bds->setCollisionModel(cm);
    for(int i = 0; i < nx; i++){
        bds->addNode(i, 0, 0, surface_charge, 2);
        bds->addNode(i, ny-1, 0, surface_charge, 4);
    }
    bds->init();

    /* Initialize solver */
    lbm->init();

    /* Main loop */
    for(int t = 0; t < tMax; t++){
        cout<<t<<endl;

        /* Update RHS*/
        for(int j = 0; j < ny; j++){
            for(int i = 0; i < nx; i++){
                rho_e[j][i] = prefactor*sinh(inSinh*cm->getPsi(i, j));
            }
        }

        lbm->collideAndStream();
    }

    cm->dataToFile();
    createDirectory("vis_scripts/data1/");
    write2DArray(rho_e, NULL, "vis_scripts/data1/charge_density.csv", nx, ny);

    cout<<"Done LPM."<<endl;

    return 0;
}
