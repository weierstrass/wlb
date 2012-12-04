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

//template void SlipNodes<CollisionD2Q9LNP>::addNode(int x, int y, int z, int normDir);
//template void SlipNodes<CollisionD2Q9LNP>::init();
//template void SlipNodes<CollisionD2Q9LNP>::updateF();
//template SlipNodes<CollisionD2Q9LNP>::SlipNodes();

template void SlipNodes<CollisionD2Q9AD>::addNode(int x, int y, int z, int normDir);
template void SlipNodes<CollisionD2Q9AD>::init();
template void SlipNodes<CollisionD2Q9AD>::updateF();
template SlipNodes<CollisionD2Q9AD>::SlipNodes();

template void SlipNodes<CollisionD2Q9BGKPE>::addNode(int x, int y, int z, int normDir);
template void SlipNodes<CollisionD2Q9BGKPE>::init();
template void SlipNodes<CollisionD2Q9BGKPE>::updateF();
template SlipNodes<CollisionD2Q9BGKPE>::SlipNodes();
//
//template void SlipNodes<CollisionD2Q9LPMChaiRHS>::addNode(int x, int y, int z, int normDir);
//template void SlipNodes<CollisionD2Q9LPMChaiRHS>::init();
//template void SlipNodes<CollisionD2Q9LPMChaiRHS>::updateF();
//template SlipNodes<CollisionD2Q9LPMChaiRHS>::SlipNodes();

template <class T>
SlipNodes<T>::SlipNodes() {
    PRESTREAM = 1;
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
    cout<<"Updating slip nodes..."<<endl;
    double *fTemp = new double[lm->UDIRS];
    ValueNode *node;
    int x, y, z, normalDir;

    //print2DArray(f[0], lm->n.x, lm->n.y, 2);
    //  print2DArray(f[0], lm->n.x, lm->n.y, 4);

    for(int i = 0; i < nodes.size(); i++){
        node = nodes[i];
        x = node->x;
        y = node->y;
        z = node->z;
        normalDir = node->v1;
        //cout<<x<<", "<<y<<", "<<z<<", normaldir: "<<normalDir<<endl;

        for(int j = 0; j < lm->UDIRS; j++){
            fTemp[j] = f[z][y][x][j];
        }

        if(normalDir == 2 || normalDir == 4){
            for(int d = 0; d < lm->UDIRS; d++){
                // if(lm->ey[d]*lm->ey[normalDir] <= 0){continue;}

                f[z][y][x][d] = fTemp[lm->slipDirsH[d]];

                // cout<<"slip: "<<lm->slipDirsH[d]<<" -> "<<d<<endl;
            }
        }else if(normalDir == 1 || normalDir == 3){
            for(int d = 0; d < lm->UDIRS; d++){
                // if(lm->ey[d]*lm->ey[normalDir] <= 0){continue;}

                f[z][y][x][d] = fTemp[lm->slipDirsV[d]];

                // cout<<"slip: "<<lm->slipDirsH[d]<<" -> "<<d<<endl;
            }
        }else{ //corner node
            f[z][y][x][normalDir] = 0;
            for(int d = 0; d < lm->UDIRS; d++){
                // if(lm->ey[d]*lm->ey[normalDir] <= 0){continue;}


                // cout<<"slip: "<<lm->slipDirsH[d]<<" -> "<<d<<endl;
                if(d == lm->oppDirs[normalDir]){
                    f[z][y][x][d] = fTemp[normalDir];
                    continue;
                }
                if(d == normalDir+2 || d == normalDir-2) continue;
                f[z][y][x][d] =  0.5*fTemp[lm->slipDirsV[d]];
                f[z][y][x][d] += 0.5*fTemp[lm->slipDirsH[d]];

            }

        }
        //        double sumy = 0;
        //
        //        for(int d = 0; d < 9; d++){
//            sumy += f[z][y][x][d]*lm->ey[d];
//        }
//
//        cout<<"FIRST YMOMENT: "<<sumy<<endl;
//        //f[z][y][x][0] += 0;
    }

    //print2DArray(f[0], lm->n.x, lm->n.y, 2);
    //print2DArray(f[0], lm->n.x, lm->n.y, 4);
}

template <class T>
void SlipNodes<T>::addNode(int x, int y, int z, int normaldir){
    nodes.push_back(new ValueNode(x, y, z, normaldir));
    cm->addNodeToSkip(x, y);
}
