/*
 * NeumannNodesPE.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "NeumannNodesPE.h"

NeumannNodesPE::NeumannNodesPE() {
    // TODO Auto-generated constructor stub
}

NeumannNodesPE::~NeumannNodesPE() {
    // TODO Auto-generated destructor stub
}

void NeumannNodesPE::updateF(){
    //cout<<"Updating PE Neumann nodes..."<<endl;

    double neumanValue;
    TypeValueNode *v;
    for(int i = 0; i < nodes.size(); i++){

        v = nodes[i];
        neumanValue = v->v2;// * lm->ey[(int)v->v3];
        //cout<<"neumann: "<<neumanValue<<", v_param: "<<v->v3<<endl;


        v->v1 = getDirichletValue(v->x, v->y,
                                  lm->ex[(int)v->v3],
                                  lm->ey[(int)v->v3],
                                  neumanValue) / 1.8;


//        cout<<"dirichlet_value: "<<v->v1<<", val: "<<v->v2\
//                                 <<", normal_dir:"<<v->v3<<\
//                                 ", dx: "<<lm->ex[(int)v->v3]<<", dy: "<<lm->ey[(int)v->v3]<<\
//                                 ", cu1: "<<cu(v->x + lm->ex[(int)v->v3], v->y + lm->ey[(int)v->v3])<<", cu2: "<<\
//                                 cu(v->x + 2*lm->ex[(int)v->v3], v->y + 2*lm->ey[(int)v->v3])<<endl;
       // cout<<"asdsad"<<endl;
    }
  //  cout<<"end"<<endl;
    HeZouNodes<CollisionD2Q9LPMChaiRHS>::updateF();
}

double NeumannNodesPE::fEq(int dir, int i, int j){
    CollisionD2Q9LPMChaiRHS *com = dynamic_cast<CollisionD2Q9LPMChaiRHS*>(this->cm);
    return com->fEq(dir, i, j);
}

double NeumannNodesPE::cu(int i, int j){
    CollisionD2Q9LPMChaiRHS *com = dynamic_cast<CollisionD2Q9LPMChaiRHS*>(this->cm);
    return com->getPsi(i, j);
}

