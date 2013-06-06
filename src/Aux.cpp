/*
 * aux.h
 * Andreas Bülling, 2012
 * Auxiliary routines
 */

#include "Aux.h"

template bool** allocate2DArrayT<bool>(int nx, int ny);
template char** allocate2DArrayT<char>(int nx, int ny);

template bool*** allocate3DArrayT<bool>(int nz, int ny, int nx);
template char*** allocate3DArrayT<char>(int nz, int ny, int nx);

/*
 * Array print routine for debugging.
 */
void print2DArray(double **f, int ni, int nj) {
  for (int j = 0; j < nj; j++) {
    for (int i = 0; i < ni; i++) {
      cout << " " << f[j][i] << " ";
      if (f[j][i] < 10)
        cout << " ";
    }
    cout << endl;
  }
  cout << endl;
}
/*
 * Array print routine for debugging.
 */
void print2DArray(double ***f, int ni, int nj, int d) {
  cout << d << "----------------" << endl;
  for (int j = 0; j < nj; j++) {
    for (int i = 0; i < ni; i++) {
      cout << " " << f[j][i][d] << " ";
      if (f[j][i][d] < 10)
        cout << " ";
    }
    cout << endl;
  }
  cout << "-----------------" << endl;
  cout << endl;
}

void print3DArray(double ****f, int ni, int nj, int nk, int d) {
  for (int k = 0; k < nk; k++) {
    cout << k << "################" << endl;

    print2DArray(f[k], ni, nj, d);

    cout << "#################" << endl;
    cout << endl;
  }
}
void printLine(int n) {
  for (int i = 0; i < n; i++) {
    cout << "-";
  }
  cout << endl;
}

void createDirectory(string path) {
  struct stat sb;
  if (!stat(path.c_str(), &sb) == 0 || !S_ISDIR(sb.st_mode)) {
    cout << "creating directory: " << path << endl;
    mkdir(path.c_str(), 0775);
  }

}

/*
 *  Write 2D Array csv to file
 */
void write2DArray(double **a, string file, int nx, int ny) {
  cout << "Writing data to " << file << "...";
  ofstream oFile;
  cout << "asd: " << file.c_str() << endl;
  oFile.open(file.c_str());
  for (int i = 0; i < ny; i++) {
    for (int j = 0; j < nx; j++) {
      oFile << a[i][j];
      if (j < nx - 1)
        oFile << ",";
    }
    oFile << "\n";
  }
  oFile.close();
  cout << " done." << endl;
}

/*
 * Poiseuille velocity profile
 */
double poiseuilleVelocity(int x, int n1, int n2, double uMax) {
  return -uMax * (x - n1) * (x - n2)
      / (n2 * n2 / 4 - n1 * n2 / 2 - 3 * n1 * n1 / 4);
}

double**** allocate4DArray(int a, int b, int c, int d) {
  double ****ret = new double***[a];
  for (int dir = 0; dir < a; dir++) {
    ret[dir] = allocate3DArray(b, c, d);
  }
  return ret;
}

double ***allocate3DArray(int b, int c, int d) {
  double ***ret = new double**[b];
  for (int i = 0; i < b; i++) {
    ret[i] = new double*[c];
    for (int j = 0; j < c; j++) {
      ret[i][j] = new double[d];
    }
  }
  return ret;
}

double **allocate2DArray(int nx, int ny) {
  double **ret = new double*[nx];
  for (int i = 0; i < nx; i++) {
    ret[i] = new double[ny];
  }

  return ret;
}

template<typename T>
T **allocate2DArrayT(int nx, int ny) {
  T **ret = new T*[nx];
  for (int i = 0; i < nx; i++) {
    ret[i] = new T[ny];
  }

  return ret;
}

template<typename T>
T ***allocate3DArrayT(int nz, int ny, int nx) {
  T ***ret = new T**[nz];
  for (int k = 0; k < nz; k++) {
    ret[k] = allocate2DArrayT<T>(ny, nx);
  }

  return ret;
}

void rescale2DArray(double **arr, double sc, int ny, int nx) {
  for (int j = 0; j < ny; j++) {
    for (int i = 0; i < nx; i++) {
      arr[j][i] *= sc;
    }
  }
}

double csecond() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec * 1.0e-6;
}
