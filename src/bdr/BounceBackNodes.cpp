/*
 * BounceBackNodes.cpp
 * Andreas Bülling, 2012
 *
 * Full way implementation of the Bounce back rule
 * The boundary nodes are wet nodes.
 *
 * NOTE: updateF() must be called BEFORE the streaming
 * step, since the full BB rule is a modification of the
 * collision step. However this is automatically taken
 * care of if LBM::collideAndStream() is called.
 */

#include "BounceBackNodes.h"

template void BounceBackNodes<CollisionD2Q9BGKNSF>::addNode(int x, int y,
    int z);
template BounceBackNodes<CollisionD2Q9BGKNSF>::BounceBackNodes();

template void BounceBackNodes<CollisionBGKNSF>::addNode(int x, int y, int z);
template BounceBackNodes<CollisionBGKNSF>::BounceBackNodes();
template void BounceBackNodes<CollisionBGKNSF>::writeNodesToFile();

template<class T>
BounceBackNodes<T>::BounceBackNodes() {
  PRESTREAM = 1;
  cm = NULL;
}

template<class T>
BounceBackNodes<T>::~BounceBackNodes() {
}

template<class T>
void BounceBackNodes<T>::updateF() {
  //cout<<"Updating f on BB nodes..."<<endl;

  double *fTemp = new double[lm->UDIRS];
  Node *node;
  int x, y, z;

  //print2DArray(f[0], lm->n.x, lm->n.y, 2);
  //	print2DArray(f[0], lm->n.x, lm->n.y, 4);

  for (int i = 0; i < nodes.size(); i++) {
    node = nodes[i];
    x = node->x;
    y = node->y;
    z = node->z;
    //cout<<x<<", "<<y<<", "<<z<<endl;

    for (int j = 0; j < lm->UDIRS; j++) {
      fTemp[j] = f[z][y][x][j];
    }

    for (int d = 0; d < lm->UDIRS; d++) {
      f[z][y][x][d] = fTemp[lm->oppDirs[d]];
    }
  }

  //print2DArray(f[0], lm->n.x, lm->n.y, 2);
  //print2DArray(f[0], lm->n.x, lm->n.y, 4);
}

template<class T>
void BounceBackNodes<T>::addNode(int x, int y, int z) {
  if (isNull(cm)) {
    return;
  }
  nodes.push_back((new Node(x, y, z)));
  cm->addNodeToSkip(z, y, x);
}

/*
 * Debug routine for BB nodes. To be removed...
 */

template<class T>
void BounceBackNodes<T>::writeNodesToFile() {
  bool match = false;
  for (int k = 0; k < lm->n.z; k++) {
    cout << "z: " << k << endl << endl;
    for (int j = 0; j < lm->n.y; j++) {
      for (int i = 0; i < lm->n.x; i++) {
        match = false;
        for (int n = 0; n < nodes.size(); n++) {
          if (nodes[n]->x == i && nodes[n]->y == j && nodes[n]->z == k) {
            cout << "X";
            match = true;
            break;
          }
        }
        if (!match) {
          cout << "O";
        }
      }
      cout << endl;
    }
  }
}
