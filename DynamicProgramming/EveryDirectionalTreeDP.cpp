#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) begin(v), end(v)
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, s, n) for(int i = (int)(s); i < (int)(n); i++)

template<class T1, class T2> void chmin(T1 &a, T2 b){if(a>b)a=b;}
template<class T1, class T2> void chmax(T1 &a, T2 b){if(a<b)a=b;}

using pint = pair<int, int>;
using tint = tuple<int, int, int>;
using vint = vector<int>;

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

#define MAX_N 150000

int N;
vector<int> G[MAX_N];

double dp[MAX_N];

void dfs(int u, int p) {
  int sz = G[u].size(), ch = sz-1;
  if(!u) ch++;

  dp[u] = 0;
  for(int v : G[u]) {
    if(v == p) continue;
    dfs(v, u);
    dp[u] += dp[v]+1;
  }

  if(ch) dp[u] /= ch;
}

double ans[MAX_N];

void dfs2(int u, int p, double rev) {
  int sz = G[u].size(), ch = sz-1;

  if(u) ans[u] = (dp[u]*ch + rev) / sz; // ch/szの確率で子へ、残りは親へ
  else ans[u] = dp[u];

  for(int v : G[u]) {
    if(v == p) continue;
    if(u) { // 根以外
      double tmp = dp[u] * ch;
      tmp -= dp[v]+1; // T(v)以外の部分は再利用
      tmp += rev;
      tmp /= ch;
      dfs2(v, u, tmp+1);
    } else { // 根
      if(sz == 1) dfs2(v, u, 1);
      else {
	double tmp = dp[u] * sz;
	tmp -= dp[v]+1;
	tmp /= ch;
	dfs2(v, u, tmp+1);
      }
    }
  }
}


signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  cin >> N;
  rep(i, N-1) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  dfs(0, -1);
  dfs2(0, -1, 0);
  rep(i, N) cout << ans[i] << endl;

  return 0;
}
