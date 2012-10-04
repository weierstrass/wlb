/*
 * SlipNodes.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "SlipNodes.h"

#define HOR_NODE 2
#define VER_NODE 3
#define COR_NODE 4
#define EDG_NODE 5

template void SlipNodes<CollisionD2Q9LNP>::addNode(int x, int y, int z);
template void SlipNodes<CollisionD2Q9LNP>::init();
template void SlipNodes<CollisionD2Q9LNP>::updateF();
template SlipNodes<CollisionD2Q9LNP>::SlipNodes();

template <class T>
SlipNodes<T>::SlipNodes() {
    PRESTREAM = 0;
}

template <class T>
SlipNodes<T>::~SlipNodes() {
    // TODO Auto-generated destructor stub
}

template <class T>
void SlipNodes<T>::init(){
    cout<<"Slip nodes preprocessing NOT FULLY IMPLEMENTED"<<endl;
  //  cout<<"dlfd"<<lm->n.y<<endl;
   // slipNodes = allocate2DArrayT<char>(lm->n.y, lm->n.x);
   // cout<<"dlfd"<<lm->n.y<<endl;
    int x, y;

//    for(int i = 0; i < nodes.size(); i++){
//        slipNodes[nodes[i]->y][nodes[i]->x] = 1;
//    }
//
//    for(int i = 0; i < nodes.size(); i++){
//        x = nodes[i]->x; y = nodes[i]->y;
//        //if(slipNodes[])
//    }
}

template <class T>
void SlipNodes<T>::updateF(){
    //cout<<"Updating f on slip nodes..."<<endl;
    double *fTemp = new double[lm->UDIRS];
    Node *node;
    int x, y, z;

    //print2DArray(f[0], lm->n.x, lm->n.y, 2);
    //  print2DArray(f[0], lm->n.x, lm->n.y, 4);

    for(int i = 0; i < nodes.size(); i++){
        node = nodes[i];
        x = node->x;
        y = node->y;
        z = node->z;
    //  cout<<x<<", "<<y<<", "<<z<<endl;

        for(int j = 0; j < lm->UDIRS; j++){
            fTemp[j] = f[z][y][x][j];
        }

        for(int d = 0; d < lm->UDIRS; d++){
            f[z][y][x][d] = fTemp[lm->slipDirsH[d]];
          //  cout<<"slip: "<<lm->slipDirsH[d]<<" -> "<<d<<endl;
        }
    }

    //print2DArray(f[0], lm->n.x, lm->n.y, 2);
    //print2DArray(f[0], lm->n.x, lm->n.y, 4);
}

template <class T>
void SlipNodes<T>::addNode(int x, int y, int z){
    BoundaryNodes::addNode(new Node(x, y, z));
    cm->addNodeToSkip(x, y);
}
