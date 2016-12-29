// aoj2171
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define FR first
#define SC second
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, f, n) for(int i = (int)(f); i < (int)(n); i++)
#define each(a, b) for(auto& a : b)

typedef pair<int, int> P;

const int inf = 1LL << 55;

double graph[101][101];
double a[101][101];
int q[101];

typedef vector<double> vectorDBL;
typedef vector<vectorDBL> matrixDBL;
const double eps = 1e-9;
vectorDBL gauss_jordan(const matrixDBL& A, const vectorDBL b)
{
  int n = A.size();
  // 拡大係数行列  
  matrixDBL Ab(n, vectorDBL(n + 1));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) Ab[i][j] = A[i][j];
  }
  for(int i = 0; i < n; i++) Ab[i][n] = b[i];

  // 解法
  for(int i = 0; i < n; i++) {
    int pivot = i;
    for(int j = i; j < n; j++) {
      if(abs(Ab[pivot][i]) < abs(Ab[j][i])) pivot = j;
    }
    swap(Ab[i], Ab[pivot]);    
    if(abs(Ab[i][i]) < eps) return vectorDBL();
    // ピボット係数で除算
    for(int j = i+1; j < n+1; j++) Ab[i][j] /= Ab[i][i];
    // 掃き出し
    for(int j = 0; j < n; j++) {
      if(i != j) {
	for(int k = i+1; k < n+1; k++) Ab[j][k] -= Ab[j][i] * Ab[i][k];
      }
    }
  }
  
  // 解
  vectorDBL x(n);
  for(int i = 0; i < n; i++) x[i] = Ab[i][n];
  return x;
}

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int n, s, t;
  while(cin >> n >> s >> t, n) {
    s--, t--;
    rep(i, n) cin >> q[i];
    fill(graph[0], graph[101], inf);
    rep(i, n) rep(j, n) {
      cin >> a[i][j];
      if(a[i][j] == 0) a[i][j] = inf;
      graph[i][j] = (i == j ? 0 : a[i][j]);
    }
    rep(i, n) rep(j, n) rep(k, n) {
      graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]);
    }
    
    if(graph[s][t] == inf) {
      cout << "impossible" << endl;
      return 0;
    }

    matrixDBL A(n, vectorDBL(n, 0));
    vectorDBL b(n, 0);

    rep(i, n) {
      double deg = 0, c = 0;
      if(i == t) { // theater : expected x_t = 0
	deg = 1, c = 0;
      } else if(q[i] == 1) { // sign : expected x_i = x_to + a[i][to]
	rep(j, n) {
	  if(graph[i][t] == a[i][j] + graph[j][t]) A[i][j] = -1, c += a[i][j], deg++;
	}
      } else { // not : expected x_i = Σ(x_j + a[i][j])/m
	rep(j, n) {
	  if(a[i][j] != inf) A[i][j] = -1, c += a[i][j], deg++;  
	}
      }
      A[i][i] = deg, b[i] = c;      
    }

    auto x = gauss_jordan(A, b);
    cout << x[s] << endl;
  }
  
  return 0;
}
