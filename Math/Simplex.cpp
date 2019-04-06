#include <bits/stdc++.h>

using namespace std;

using Num = long double;
using Vec = vector<Num>;
using Mat = vector<Vec>;
const Num Inf = numeric_limits<Num>::infinity();
const Num NoSolution = numeric_limits<Num>::quiet_NaN();
const Num eps = 1e-10;

Num Simplex(const Mat& A, const Vec& b, const Vec& c) {
  const int m = A.size(), n = A[0].size();
  Mat tab(m+1, Vec(n+1));
  vector<int> id(n+m+1);
  iota(id.begin(), id.end(), 0);
  for(int i = 0; i < m; ++i) {
    for(int j = 0; j < n; ++j) tab[i][j] = -A[i][j];
    tab[i][n] = b[i];
  }
  for(int j = 0; j < n; ++j) tab[m][j] = c[j];
  while(1) {
    int r = m, s = n+m;
    for(int i = 0; i < m; ++i) {
      if(tab[i][n] < -eps && id[n+i] < id[n+r]) r = i;
    }
    for(int j = 0; j < n; ++j) {
      if(tab[m][j] > eps && id[j] < id[s]) s = j;
    }
    if(r == m && s == n+m) break;
    if(id[n+r] < id[s]) {
      s = n+m;
      for(int j = 0; j < n; ++j) {
	if(tab[r][j] > eps && id[j] < id[s]) s = j;
      }
    } else {
      r = m;
      for(int i = 0; i < m; ++i) {
	if(tab[i][s] < -eps && id[n+i] < id[n+r]) r = i;
      }
    }
    if(r == m) return NoSolution;
    if(s == n+m) return NoSolution;
    swap(id[s], id[n+r]);
    tab[r][s] = 1.0/tab[r][s];
    for(int j = 0; j <= n; ++j) {
      if(j != s) tab[r][j] *= -tab[r][s];
    }
    for(int i = 0; i <= m; ++i) {
      if(i == r || abs(tab[i][s]) <= eps) continue;
      for(int j = 0; j <= n; ++j) {
	if(j != s) tab[i][j] += tab[r][j]*tab[i][s];
      }
      tab[i][s] *= tab[r][s];
    }
  }
  return tab[m][n];
}
