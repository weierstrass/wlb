/*
 * NeumannNodesNP.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "NeumannNodesNP.h"

NeumannNodesNP::NeumannNodesNP() {
    // TODO Auto-generated constructor stub

}

NeumannNodesNP::~NeumannNodesNP() {
    // TODO Auto-generated destructor stub
}

void NeumannNodesNP::updateF(){
    cout<<"Updating Neumann NP nodes..."<<endl;

    CollisionD2Q9LNP *com = dynamic_cast<CollisionD2Q9LNP*>(this->cm);

    double **ni = com->getNi();
    double **dPsix = com->getdPsix();
    double **dPsiy = com->getdPsiy();
    double gamma = PHYS_E_CHARGE*com->getZ()/\
                   (PHYS_KB * com->getT());

    cout<<"Z: "<<com->getZ()<<endl;
    cout<<"gamma: "<<gamma<<endl;
    int x,y;
    ValueNode *node = NULL;
    //update values of Neumann nodes
    for(int i = 0; i < neumannNodes.size(); i++){
        node = neumannNodes[i];
        if(node == NULL){
            cerr<<"Nullpointer in NeumannNodes!"<<endl;
            break;
        }
        x = node->x;// + lm->ex[(int)node->v2];
        y = node->y;// + lm->ey[(int)node->v2];
      //  cout<<"x: "<<x<<", y: "<<y<<endl;
       // cout<<"n: "<<ni[y][x]<<", dpsi: "<<dPsiy[y][x]<<endl;
        node->v1 = - gamma * ni[y][x] * dPsiy[y][x] * lm->ey[(int)node->v2];
        cout<<"updating dC/dn to: "<<node->v1<<endl;
    }

    NeumannNodes<CollisionD2Q9LNP>::updateF();

}

double NeumannNodesNP::fEq(int dir, int i, int j){
    CollisionD2Q9LNP *com = dynamic_cast<CollisionD2Q9LNP*>(this->cm);
    return com->fEq(dir, i, j);
}

double NeumannNodesNP::cu(int i, int j){
    CollisionD2Q9LNP *com = dynamic_cast<CollisionD2Q9LNP*>(this->cm);
    double **ni = com->getNi();
    return ni[j][i];
}
