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
}

template <class T>
void NeumannNodes<T>::updateF(){
    cout<<"Updating Neumann nodes..."<<endl;

    //perform mirror reflection
    SlipNodes<T>::updateF();

   // cout<<"node size: "<<nodes.size()<<endl;
    ValueNode *node;

    for(int i = 0; i < nodes.size(); i++){
        node = nodes[i];
        cout<<"v1: "<<node->v1<<endl;
        cout<<"v2: "<<node->v2<<endl;
        if(node->v2 == 2){
            cout<<"PRE: "<<this->f[node->z][node->y][node->x][(int)node->v2]<<endl;
            this->f[node->z][node->y][node->x][(int)node->v2] +=
                node->v1; //- ?
            cout<<"POST: "<<this->f[node->z][node->y][node->x][(int)node->v2]<<endl;
        }else if(node->v2 == 4){
            this->f[node->z][node->y][node->x][(int)node->v2] +=
                node->v1;//+ ?
        }
    }

}

template <class T>
void NeumannNodes<T>::addNode(int x, int y, int z,
                              double val, double dir){
    nodes.push_back(new ValueNode(x, y, z, val, dir));
    this->cm->addNodeToSkip(x, y);
}

//high complexity, ineffective search... use ONLY for debug purposes
//template <class T>
//void NeumannNodes<T>::updateNode(int x, int y, int z, double v){
//    for(int i = 0; i < nodes.size(); i++){
//    }
//}
