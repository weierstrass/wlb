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
	//cout << "new streaming..." << endl;
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
//						cout << "forward: d: " << d << ",l" << l << ", a: "
//								<< a + (lm->n.x - 1) * (l == 0) << ", b: "
//								<< b + (lm->n.y - 1) * (l == 1) << ", c: "
//								<< c + (lm->n.z - 1) * (l == 2) << endl;
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
					//cout << "lååål" << endl;
					if (lm->e[l][d] < 0) {
						int cf = c;
						if (lm->DIM > 2) {
							cf = (c + (lm->n.z - 1) * (l == 2)
									+ lm->e[2][d] * (l != 2)) % lm->n.z;
							cf += lm->n.z * (cf < 0);
						}
						int bf = (b + (lm->n.y - 1) * (l == 1)
								+ lm->e[1][d] * (l != 1)) % lm->n.y;
						bf += lm->n.y * (bf < 0);
						int af = (a + (lm->n.x - 1) * (l == 0)
								+ lm->e[0][d] * (l != 0)) % lm->n.x;
						af += lm->n.x * (af < 0);

						f[cf][bf][af][d] = fb[l][j][i][d];
					} else if (lm->e[l][d] > 0) {

						int bf = (b + lm->e[1][d] * (l != 1)) % (lm->n.y)
								+ (lm->n.y)
										* (((b + lm->e[1][d] * (l != 1))
												% (lm->n.y)) < 0);
						int af = (a + lm->e[0][d] * (l != 0)) % (lm->n.x)
								+ (lm->n.x)
										* (((a + lm->e[0][d] * (l != 0))
												% (lm->n.x)) < 0);
						int cf = c;
						if (lm->DIM > 2) {
							cf = (c + lm->e[2][d] * (l != 2)) % (lm->n.z);
							cf += lm->n.z * (cf < 0);
						}
						f[cf][bf][af][d] = fb[l][j][i][d];
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
