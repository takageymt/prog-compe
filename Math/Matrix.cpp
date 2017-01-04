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

typedef vector<int> nvector;
typedef vector<nvector> matrix;

matrix multi(const matrix& A, const matrix& B)
{
  matrix C(A.size(), nvector(B[0].size()));
  for(int i = 0; i < A.size(); i++) {
    for(int j = 0; j < B.size(); j++) {
      for(int k = 0; k < B[0].size(); k++) {
	C[i][k] += A[i][j] * B[j][k];
      }
    }
  }
  return C;
}

matrix power(matrix A, int n)
{
  matrix B(A.size(), nvector(A.size()));
  for(int i = 0; i < A.size(); i++) B[i][i] = 1;
  while(n > 0) {
    if(n & 1) B = multi(B, A);
    A = multi(A, A);
    n >>= 1;
  }
  return B;
}

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);
  int N, M, Z;  
  while(cin >> N >> M >> Z, N) {
    vector<P> v = {{1, 1}};
    rep(i, M) {
      int s, d; cin >> s >> d;
      v.emplace_back(s, d);
      v.emplace_back(d, s);
    }

    matrix A(v.size(), nvector(v.size()));
    rep(i, v.size()) reps(j, 1, v.size()) if(i != j) {
      if(v[i].FR != v[j].SC && v[i].SC == v[j].FR) A[i][j] = 1;
    }
    
    matrix B = power(A, Z);
    bool flag = false;
    rep(i, v.size()) if(B[0][i]) {
      if(v[i].SC == N) flag = true;
      if(flag) break;
    }
    
    cout << (flag ? "yes" : "no") << endl;
  }
  return 0;
}
