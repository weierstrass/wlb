/*
 * NeumannNodesPESlip.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "NeumannNodesPESlip.h"

NeumannNodesPESlip::NeumannNodesPESlip() {
    // TODO Auto-generated constructor stub
    PRESTREAM = 1;
}

NeumannNodesPESlip::~NeumannNodesPESlip() {
    // TODO Auto-generated destructor stub
}

void NeumannNodesPESlip::updateF(){
    //cout<<"Updating PE Neumann SLIP nodes..."<<endl;

    //SlipNodes<CollisionD2Q9LPMChaiRHS>::updateF();
    double *fTemp = new double[lm->UDIRS];
    double neumanValue;
    int x, y, normalDir;
    ValueNode *v;
    for(int i = 0; i < nodes.size(); i++){

        v = nodes[i];
        neumanValue = v->v1;// * lm->ey[(int)v->v3];
        normalDir = v->v2;
        x = v->x;
        y = v->y;
       //cout<<"x: "<<x<<", y: "<<y<<", neumann: "<<neumanValue<<", normalDir: "<<normalDir<<endl;
//        cout<<"F_4 PRE: "<<f[0][y][x][4]<<endl;
//        cout<<"F_1 PRE: "<<f[0][y][x][1]<<endl;
//        cout<<"F_0 PRE: "<<f[0][y][x][0]<<endl;

        for(int j = 0; j < lm->UDIRS; j++){
            fTemp[j] = f[0][y][x][j];
        }

        if(normalDir == 4 || normalDir == 2){
            for(int d = 0; d < lm->UDIRS; d++){
                if(lm->ey[d]*lm->ey[normalDir] <= 0){continue;}
               // cout<<"updating horizontal nodes"<<endl;
           //     if(d == lm->slipDirsH[d]) continue;
                f[0][y][x][d] = fTemp[lm->slipDirsH[d]] - neumanValue/9.0;// *\
                        lm->ey[normalDir]; //lm->ey[d]*lm->ey[normalDir];
            }
        }else if(normalDir == 1 || normalDir == 3){
            for(int d = 0; d < lm->UDIRS; d++){
               // cout<<"ugyukgkuygkug: "<<normalDir<<endl;
                if(lm->ex[d]*lm->ex[normalDir] <= 0){continue;}
              //  cout<<"updating vertical nodes"<<endl;
              //  if(d == lm->slipDirsV[d]) continue;
                f[0][y][x][d] = fTemp[lm->slipDirsV[d]] - neumanValue/9.0;// *\
                        lm->ex[normalDir]; //lm->ex[d]*lm->ex[normalDir];
            }
        }else{ //corner node..
            f[0][y][x][normalDir] = 0;
            for(int d = 0; d < lm->UDIRS; d++){
                // cout<<"ugyukgkuygkug: "<<normalDir<<endl;
           //     if(lm->ex[d]*lm->ex[normalDir] <= 0){continue;}
           //     if(lm->ey[d]*lm->ey[normalDir] <= 0){continue;}
                //  cout<<"updating vertical nodes"<<endl;
                f[0][y][x][d] = (fTemp[lm->slipDirsV[d]] - neumanValue/9.0 *\
                        1)*0.5; //lm->ex[d]*lm->ex[normalDir]
                f[0][y][x][d] += (fTemp[lm->slipDirsH[d]]  - neumanValue/9.0 *\
                        1)*0.5;//lm->ey[d]*lm->ey[normalDir]
            }
            f[0][y][x][lm->oppDirs[normalDir]] = fTemp[normalDir];
        }

//        cout<<"F_4 POST: "<<f[0][y][x][4]<<endl;
//        cout<<"F_1 POST: "<<f[0][y][x][1]<<endl;
//        cout<<"F_0 POST: "<<f[0][y][x][0]<<endl;
////        cout<<"dirichlet_value: "<<v->v1<<", val: "<<v->v2\
//                                 <<", normal_dir:"<<v->v3<<\
//                                 ", dx: "<<lm->ex[(int)v->v3]<<", dy: "<<lm->ey[(int)v->v3]<<\
//                                 ", cu1: "<<cu(v->x + lm->ex[(int)v->v3], v->y + lm->ey[(int)v->v3])<<", cu2: "<<\
//                                 cu(v->x + 2*lm->ex[(int)v->v3], v->y + 2*lm->ey[(int)v->v3])<<endl;
       // cout<<"asdsad"<<endl;
    }
  //  cout<<"end"<<endl;
}

//double NeumannNodesPESlip::fEq(int dir, int i, int j){
//    CollisionD2Q9LPMChaiRHS *com = dynamic_cast<CollisionD2Q9LPMChaiRHS*>(this->cm);
//    return com->fEq(dir, i, j);
//}
//
//double NeumannNodesPESlip::cu(int i, int j){
//    CollisionD2Q9LPMChaiRHS *com = dynamic_cast<CollisionD2Q9LPMChaiRHS*>(this->cm);
//    return com->getPsi(i, j);
//}

void NeumannNodesPESlip::addNode(int x, int y, int z,
                              double val, int dir){
    nodes.push_back(new ValueNode(x, y, z, val, dir));
    //this->cm->addNodeToSkip(x, y);
}
