/*
 * StreamPeriodic.cpp
 * Andreas Bülling, 2013
 * andreas@bulling.se
 *
 * DESCRIPTION - TODO
 */

#include "StreamPeriodic.h"

StreamPeriodic::StreamPeriodic() {
    fb = NULL;
}

StreamPeriodic::~StreamPeriodic() {
    // delete[] fb;
}

void StreamPeriodic::stream() {

    int aLim, bLim, a, b, c, sa, sb, sc;

    for (int l = 0; l < lm->DIM; l++) {
        aLim = lm->n.z * (l < 2) + lm->n.y * (l == 2);
        bLim = lm->n.x * (l > 0) + lm->n.y * (l == 0);

        for (int j = 0; j < aLim; j++) {
            for (int i = 0; i < bLim; i++) {
                c = j * (l == 0) + j * (l == 1);
                b = i * (l == 0) + j * (l == 2);
                a = i * (l == 1) + i * (l == 2);
                for (int d = 0; d < lm->UDIRS; d++) {
                    if (lm->e[l][d] > 0) {
                        cout << "forward: d: " << d << ",l" << l << ", a: "
                                << a + (lm->n.x - 1) * (l == 0) << ", b: "
                                << b + (lm->n.y - 1) * (l == 1) << ", c: "
                                << c + (lm->n.z - 1) * (l == 2) << endl;
                        fb[l][j][i][d] = f[c + (lm->n.z - 1) * (l == 2)][b
                                + (lm->n.y - 1) * (l == 1)][a
                                + (lm->n.x - 1) * (l == 0)][d];
                    } else if (lm->e[l][d] < 0) {
                        fb[l][j][i][d] = f[c][b][a][d];
                    }
                }
            }
        }

    }

    Stream::stream();

    for (int l = 0; l < lm->DIM; l++) {
        aLim = lm->n.z * (l < 2) + lm->n.y * (l == 2);
        bLim = lm->n.x * (l > 0) + lm->n.y * (l == 0);

        for (int j = 0; j < aLim; j++) {
            for (int i = 0; i < bLim; i++) {
                c = j * (l == 0) + j * (l == 1);
                b = i * (l == 0) + j * (l == 2);
                a = i * (l == 1) + i * (l == 2);
                for (int d = 0; d < lm->UDIRS; d++) {
                    if (lm->e[l][d] < 0) {
                        f[c + (lm->n.z - 1) * (l == 2)][b
                                + (lm->n.y - 1) * (l == 1)][a
                                + (lm->n.x - 1) * (l == 0)][d] = fb[l][j][i][d];
                    } else if (lm->e[l][d] > 0) {
                        f[c][b][a][d] = fb[l][j][i][d];
                    }
                }
            }
        }

    }

}

void StreamPeriodic::init() {
    cout << "allocating memory for periodic stream array..." << endl;
    fb = new double***[lm->DIM];
    int aDim, bDim;

    for (int l = 0; l < lm->DIM; l++) {
        aDim = lm->n.z * (l < 2) + lm->n.y * (l == 2);
        bDim = lm->n.x * (l > 0) + lm->n.y * (l == 0);
        fb[l] = allocate3DArray(aDim, bDim, lm->UDIRS);
    }
}
