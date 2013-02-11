/*
 * Stream.cpp
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "Stream.h"

Stream::Stream() {
    // TODO Auto-generated constructor stub

}

Stream::~Stream() {
    // TODO Auto-generated destructor stub
}

void Stream::stream() {
    cout << "general streaming" << endl;

    for (int d = 0; d < lm->UDIRS; d++) {
        if (lm->e[0][d] == 0) {
            continue;
        } else if (lm->e[0][d] > 0) {
            forwardStream(d, 0, 0, 1);
        }
    }

}

void Stream::backwardStream(int d, int sz, int sy, int sx) {
    for (int k = 0; k < lm->n.z - 1; k++) {
        for (int j = 0; j < lm->n.y - 1; j++) {
            for (int i = 0; i < lm->n.x - 1; i++) {
                f[k][j][i][d] = f[k + sz][j + sy][i + sx][d];
            }
        }
    }
}

void Stream::forwardStream(int d, int sz, int sy, int sx) {
    for (int k = lm->n.z - 1; k > 0; k++) {
        for (int j = lm->n.y - 1; j > 0; j++) {
            for (int i = lm->n.x - 1; i > 0; i++) {
                f[k - sz][j - sy][i - sx][d] = f[k][j][i][d];
            }
        }
    }
}
