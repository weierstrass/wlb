/*
 * NeumannNodes.cpp
 * Andreas Bülling, 2012
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "NeumannNodes.h"

template NeumannNodes<CollisionD2Q9LNP>::NeumannNodes();
template NeumannNodes<CollisionD2Q9LNP>::~NeumannNodes();
template void NeumannNodes<CollisionD2Q9LNP>::init();
template void NeumannNodes<CollisionD2Q9LNP>::addNode(int x, int y, int z,
                                                      double v1, int dir);
template double NeumannNodes<CollisionD2Q9LNP>::getDirichletValue(int, int, int, int, double);

template NeumannNodes<CollisionD2Q9LPMChaiRHS>::NeumannNodes();
template NeumannNodes<CollisionD2Q9LPMChaiRHS>::~NeumannNodes();
template void NeumannNodes<CollisionD2Q9LPMChaiRHS>::init();
template void NeumannNodes<CollisionD2Q9LPMChaiRHS>::addNode(int x, int y, int z,
                                                             double v1, int dir);
template double NeumannNodes<CollisionD2Q9LPMChaiRHS>::getDirichletValue(int, int, int, int, double);

template NeumannNodes<CollisionD2Q9LPMChai1to1>::NeumannNodes();
template NeumannNodes<CollisionD2Q9LPMChai1to1>::~NeumannNodes();
template void NeumannNodes<CollisionD2Q9LPMChai1to1>::init();
template void NeumannNodes<CollisionD2Q9LPMChai1to1>::addNode(int x, int y, int z,
                                                             double v1, int dir);
template double NeumannNodes<CollisionD2Q9LPMChai1to1>::getDirichletValue(int, int, int, int, double);

template <class T>
NeumannNodes<T>::NeumannNodes() {

}

template <class T>
NeumannNodes<T>::~NeumannNodes() {
    // TODO Auto-generated destructor stub
}

template <class T>
void NeumannNodes<T>::init(){
    cout<<"Preprocessing Neumann nodes..."<<endl;
    HeZouNodes<T>::init();
}

template <class T>
void NeumannNodes<T>::updateF(){
    cout<<"Updating Neumann nodes..."<<endl;
    cerr<<"DEPRECATED"<<endl;
//    cout<<this->nodes.size()<<" =? "<<neumannNodes.size()<<endl;
    //perform mirror reflection
    //SlipNodes<T>::updateF();

   // cout<<"node size: "<<nodes.size()<<endl;
//    TypeValueNode *node;
//    //TypeValueNode *heZouNode;
//    double dirichletValue, dx, dy;
//    int x, y, d;
//
//    for(int i = 0; i < this->nodes.size(); i++){
//        node = this->nodes[i];
//        x = node->x;
//        y = node->y;
//        d = (int) node->v3;
//        dx = this->lm->ex[d];
//        dy = this->lm->ey[d];
//
//        dirichletValue = 4 * cu(x + dx, y + dy) -\
//                         2 * node->v1 -\
//                             cu(x + 2*dx, y + 2*dy);
//        dirichletValue /= 3.0;
//        dirichletValue /= 1.8;
//
//        cout<<"dirichlet_value: "<<dirichletValue<<", val: "<<node->v1\
//                                 <<", normal_dir:"<<node->v2<<\
//                                 ", dx: "<<dx<<", dy: "<<dy<<\
//                                 ", cu1: "<<cu(x + dx, y + dy)<<", cu2: "<<\
//                                 cu(x + 2*dx, y + 2*dy)<<endl;
//
//       // cout<<"v1: "<<node->v1<<endl;
//       // cout<<"v2: "<<node->v2<<endl;
////        cout<<"PRE: "<<this->f[node->z][node->y][node->x][(int)node->v2]<<endl;
////        if(node->v2 == 2){
////            this->f[node->z][node->y][node->x][(int)node->v2] -=
////                node->v1; //- ?
////        }else if(node->v2 == 4){
////            this->f[node->z][node->y][node->x][(int)node->v2] +=
////                node->v1;//+ ?
////        }
//
//        //cout<<"POST: "<<this->f[node->z][node->y][node->x][(int)node->v2]<<endl;
//
//        node->v1 = dirichletValue;
//    }
//
//    HeZouNodes<T>::updateF();

}

template <class T>
double NeumannNodes<T>::getDirichletValue(int x, int y,
                                          int dx, int dy, double val){
    return (4 * cu(x + dx, y + dy) -\
           2 * val -\
           cu(x + 2*dx, y + 2*dy))/3.0;
}

template <class T>
void NeumannNodes<T>::addNode(int x, int y, int z,
                              double val, int dir){
    //neumannNodes.push_back(new ValueNode(x, y, z, val, dir));
    //this->cm->addNodeToSkip(x, y);
    HeZouNodes<T>::addNode(x, y, z, val, dir);
}

//high complexity, ineffective search... use ONLY for debug purposes
//template <class T>
//void NeumannNodes<T>::updateNode(int x, int y, int z, double v){
//    for(int i = 0; i < nodes.size(); i++){
//    }
//}
