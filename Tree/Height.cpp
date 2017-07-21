#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) (v).begin(), (v).end()
#define resz(v, ...) (v).clear(), (v).resize(__VA_ARGS__)
#define reps(i, m, n) for(int i = (int)(m); i < (int)(n); i++)
#define rep(i, n) reps(i, 0, n)

template<class T1, class T2> void chmin(T1 &a, T2 b){if(a>b)a=b;}
template<class T1, class T2> void chmax(T1 &a, T2 b){if(a<b)a=b;}

typedef pair<int, int> Pi;
typedef tuple<int, int, int> Ti;
typedef vector<int> vint;

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

struct edge {
  int to, cost;
  edge(){}
  edge(int to, int cost):to(to), cost(cost){}
};

int n;
vector< vector<edge> > graph;

int dp[10010];
int dp2[10010];

void dfs(int u, int p) {
  int res = 0;
  for(edge& e : graph[u]) {
    if(e.to == p) continue;
    dfs(e.to, u);
    chmax(res, dp[e.to]+e.cost);
  }
  dp[u] = res;
}

int dfs2(int u, int p, int rev) {
  vector<Pi> dist;
  dist.emplace_back(0, -1);
  for(edge& e : graph[u]) {
    if(e.to == p) dist.emplace_back(rev+e.cost, e.to);
    else dist.emplace_back(dp[e.to]+e.cost, e.to);
  }
  sort(all(dist));
  reverse(all(dist));
  int res = dist[0].first+dist[1].second;
  int mxch = dist[0].second;
  for(edge& e : graph[u]) {
    if(e.to == p) continue;
    chmax(res, dfs2(e.to, u, dist[e.to==mxch].first));
  }
  return dp2[u] = res;
}

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  cin >> n;
  resz(graph, n);
  rep(i, n-1) {
    int s, t, w;
    cin >> s >> t >> w;
    graph[s].emplace_back(t, w);
    graph[t].emplace_back(s, w);
  }
  memset(dp, -1, sizeof(dp));
  memset(dp2, -1, sizeof(dp2));
  dfs(0, -1);
  rep(i, n) cout << dp[i] << endl;

  dfs2(0, -1, 0);
  rep(i, n) cout << dp2[i] << endl;

  return 0;
}
