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

void NeumannNodesNP::updateF() {
  cout << "Updating Neumann NP nodes..." << endl;

  CollisionD2Q9LNP *com = dynamic_cast<CollisionD2Q9LNP*>(this->cm);

  double **ni = com->getNi();
  double **dPsix = com->getdPsix();
  double **dPsiy = com->getdPsiy();
  double gamma = PHYS_E_CHARGE * com->getZ() /\
 (PHYS_KB * com->getT());

  cout << "Z: " << com->getZ() << endl;
  cout << "gamma: " << gamma << endl;
  int x, y;
  double neumanValue;
  TypeValueNode *node = NULL;
  //update values of Neumann nodes
  for (int i = 0; i < nodes.size(); i++) {
    node = nodes[i];
    if (node == NULL) {
      cerr << "Nullpointer in NeumannNodes!" << endl;
      break;
    }
    x = node->x; // + lm->ex[(int)node->v2];
    y = node->y; // + lm->ey[(int)node->v2];
    //  cout<<"x: "<<x<<", y: "<<y<<endl;
    // cout<<"n: "<<ni[y][x]<<", dpsi: "<<dPsiy[y][x]<<endl;
    neumanValue = -gamma * ni[y][x] * dPsiy[y][x] * lm->ey[(int) node->v3];
    neumanValue = -gamma * ni[y][x] * (-5e-2) * (-50e-3);
    node->v1 = getDirichletValue(x, y, lm->ex[(int) node->v3],
        lm->ey[(int) node->v3], neumanValue);

    cout << "NODe_PRE: " << node->v1 << endl;
    node->v1 -= 0.5 * com->getSourceTerm(x, y);
    node->v1 -= com->getf0(x, y);
    cout << "F_0: " << com->getf0(x, y) << endl;
    cout << "Z: " << com->getZ() << ", source: "
        << 0.5 * com->getSourceTerm(x, y) << endl;
    //node->v1 += com->getZ()*0.22;

    cout << "dirichlet_value: " << node->v1 << ", neumannval: " << neumanValue\

        << ", normal_dir:" << node->v3 <<\
 ", dx: " << lm->ex[(int) node->v3]
        << ", dy: " << lm->ey[(int) node->v3] <<\
 ", cu1: "
        << cu(node->x + lm->ex[(int) node->v3],
            node->y + lm->ey[(int) node->v3]) << ", cu2: "
        <<\
 cu(node->x + 2 * lm->ex[(int) node->v3],
            node->y + 2 * lm->ey[(int) node->v3]) << ", dpsiy: " << dPsiy[y][x]
        << ", ni: " << ni[y][x] << endl;
  }

  HeZouNodes<CollisionD2Q9LNP>::updateF();

}

double NeumannNodesNP::fEq(int dir, int i, int j) {
  CollisionD2Q9LNP *com = dynamic_cast<CollisionD2Q9LNP*>(this->cm);
  return com->fEq(dir, i, j);
}

double NeumannNodesNP::cu(int i, int j) {
  CollisionD2Q9LNP *com = dynamic_cast<CollisionD2Q9LNP*>(this->cm);
  double **ni = com->getNi();
  return ni[j][i];
}
