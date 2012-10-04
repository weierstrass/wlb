/*
 * NeumannNodes.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "NeumannNodes.h"

template NeumannNodes<CollisionD2Q9LNP>::NeumannNodes();
template void NeumannNodes<CollisionD2Q9LNP>::init();
template void NeumannNodes<CollisionD2Q9LNP>::addNode(int x, int y, int z,
                                                      double v1, double v2);

template <class T>
NeumannNodes<T>::NeumannNodes() {

}

template <class T>
NeumannNodes<T>::~NeumannNodes() {
    // TODO Auto-generated destructor stub
}

template <class T>
void NeumannNodes<T>::init(){
    cout<<"Preprocessing of Neumann nodes... NYI"<<endl;
    HeZouNodes<T>::init();
}

template <class T>
void NeumannNodes<T>::updateF(){
    cout<<"Updating Neumann nodes..."<<endl;

    cout<<this->nodes.size()<<" =? "<<neumannNodes.size()<<endl;
    //perform mirror reflection
    //SlipNodes<T>::updateF();

   // cout<<"node size: "<<nodes.size()<<endl;
    ValueNode *node;
    TypeValueNode *heZouNode;
    double dirichletValue, dx, dy;
    int x, y, d;

    for(int i = 0; i < this->nodes.size(); i++){
        node = this->neumannNodes[i];
        heZouNode = this->nodes[i];
        x = node->x;
        y = node->y;
        d = (int) node->v2;
        dx = this->lm->ex[d];
        dy = this->lm->ey[d];

        dirichletValue = 4 * cu(x + dx, y + dy) -\
                         2 * node->v1 -\
                             cu(x + 2*dx, y + 2*dy);
        dirichletValue /= 3.0;
         cout<<"v1: "<<node->v1<<endl;
//        cout<<"v2: "<<node->v2<<endl;
//        cout<<"PRE: "<<this->f[node->z][node->y][node->x][(int)node->v2]<<endl;
//        if(node->v2 == 2){
//            this->f[node->z][node->y][node->x][(int)node->v2] -=
//                node->v1; //- ?
//        }else if(node->v2 == 4){
//            this->f[node->z][node->y][node->x][(int)node->v2] +=
//                node->v1;//+ ?
//        }

        //cout<<"POST: "<<this->f[node->z][node->y][node->x][(int)node->v2]<<endl;

        heZouNode->v1 = dirichletValue;
    }

    HeZouNodes<T>::updateF();

}

template <class T>
void NeumannNodes<T>::addNode(int x, int y, int z,
                              double val, double dir){
    neumannNodes.push_back(new ValueNode(x, y, z, val, dir));
    cout<<"adasdas"<<endl;
    //this->cm->addNodeToSkip(x, y);
    cout<<"adasdad"<<endl;
    HeZouNodes<T>::addNode(x, y, z, 0.0);
}

//high complexity, ineffective search... use ONLY for debug purposes
//template <class T>
//void NeumannNodes<T>::updateNode(int x, int y, int z, double v){
//    for(int i = 0; i < nodes.size(); i++){
//    }
//}
