#include <bits/stdc++.h>

using namespace std;

using Num = long double;
using Vec = vector<Num>;
using Mat = vector<Vec>;

const Num eps = 1e-10;
const Num Inf = numeric_limits<Num>::infinity();
const Num NoSolution = numeric_limits<Num>::quiet_NaN();

// A: 制約不等式の左辺の係数 m*n
// b: 制約不等式の右辺 m (b_i >= 0)
// c: 目的関数の係数 n
Num NaiveSimplex(const Mat& A, const Vec& b, const Vec& c) {
  int m = A.size(), n = A[0].size();
  vector<int> id(n+m+1); // 初期値 [0,n):変数,[n,n+m):スラック変数,n+m:目的変数
  iota(id.begin(), id.end(), 0);
  Mat D(m+1, Vec(n+1)); // シンプレックス表
  for(int i = 0; i < m; ++i) {
    for(int j = 0; j < n; ++j) D[i][j] = -A[i][j];
    D[i][n] = b[i];
  }
  for(int j = 0; j < n; ++j) D[m][j] = c[j];
  D[m][n] = 0;
  while(1) {
    Vec df(n, 0), dy(n, -1); // 目的関数の増分, 次の非基底変数の添字
    Num max_j = -1, zero_i = -1;
    for(int j = 0; j < n; ++j) {
      if(D[m][j] > eps) {
	Num xb = Inf; // 交換候補の非基底変数の取りうる値
	for(int i = 0; i < m; ++i) {
	  if(D[i][j] < -eps) {
	    if(xb > -D[i][n]/D[i][j]) { // ||
	      //(abs(xb+D[i][n]/D[i][j]) < eps && id[n+i] < id[n+dy[j]])) { // 退化対策？
	      xb = -D[i][n]/D[i][j];
	      df[j] = D[m][j]*xb;
	      dy[j] = i;
	    }
	  }
	}
	if(max_j == -1 || df[max_j] < df[j]) { // ||
	  //(abs(df[max_j]-df[j]) < eps && id[j] < id[max_j])) { // 退化対策？
	  max_j = j;
	  zero_i = dy[max_j];
	}
      }
    }
    if(max_j == -1) break; // 目的関数の係数が全て負
    if(zero_i == -1) return NoSolution; // 目的関数が正の係数を持ち、その変数の制約係数が全て非負
    for(int j = 0; j <= n; ++j) {
      if(j != max_j) D[zero_i][j] = -D[zero_i][j]/D[zero_i][max_j];
    }
    D[zero_i][max_j] = 1 / D[zero_i][max_j];
    for(int i = 0; i <= m; ++i) {
      if(i != zero_i && abs(D[i][max_j]) > eps) {
	for(int j = 0; j <= n; ++j) {
	  if(j != max_j) D[i][j] += D[i][max_j]*D[zero_i][j];
	}
	D[i][max_j] = D[i][max_j]*D[zero_i][max_j];
      }
    }
    swap(id[n+zero_i], id[max_j]);
  }
  return D[m][n];
}

int main() {
  if(1) {
    Mat A{{2,8},{4,4}};
    Vec b{60,60};
    Vec c{29,45};
    cout << NaiveSimplex(A, b, c) << endl;
  }
  if(1) {
    Mat A{{2,1},{1,1},{0,1}};
    Vec b{16,8,3.5};
    Vec c{150,300};
    cout << NaiveSimplex(A, b, c) << endl;
  }
  return 0;
}
