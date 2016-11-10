// AOJ GRL_5_C: Tree - Lowest Common Ancestor
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Ti = tuple<int, int, int>;
using Tl = tuple<ll, ll, ll>;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define F first
#define S second
#define Get(t, i) get<(i)>((t))
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, f, n) for(int i = (int)(f); i < (int)(n); i++)
#define each(a, b) for(auto& a : b)

const int inf = 1 << 25;
const ll INF = 1LL << 55;

// Lowest Common Ancestor (Doubling)
struct LCA
{
  vector< vector<int> > tree, parent;
  vector<int> depth;
  int log_V;
  LCA(int V)
  {
    log_V = 1;
    while((1 << log_V) <= V) log_V++;
    tree.resize(V);
    parent.resize(log_V, vector<int>(V, -1));    
    depth.resize(V);
  }
  void add_edge(int f, int t)
  {
    tree[f].emplace_back(t);
    tree[t].emplace_back(f);    
  }
  void dfs(int u, int p, int d)
  {
    parent[0][u] = p;
    depth[u] = d;
    for(auto v : tree[u]) {
      if(v != p) dfs(v, u, d + 1);
    }
  }
  void init(int root = 0)
  {
    dfs(root, -1, 0);
    for(int i = 0; i + 1 < log_V; i++) {
      for(int v = 0; v < parent[i].size(); v++) {
	if(parent[i][v] < 0) parent[i + 1][v] = -1;
	else parent[i + 1][v] = parent[i][parent[i][v]];
      }
    }
  }
  int trace(int u, int v)
  {
    if(depth[u] > depth[v]) swap(u, v);
    for(int i = 0; i < log_V; i++) {
      if((depth[v] - depth[u]) >> i & 1) v = parent[i][v];
    }
    if(u == v) return u;
    for(int i = log_V-1; i >= 0; i--) {
      if(parent[i][u] != parent[i][v]) u = parent[i][u], v = parent[i][v];
    }
    return parent[0][u];
  }
  int dist(int u, int v) {
    return depth[u] + depth[v] - 2*depth[trace(u, v)];
  }
};


int main()
{
  int n; cin >> n;
  LCA lca(n);
  rep(i, n) {
    int k; cin >> k;
    while(k--) {
      int c; cin >> c;
      lca.add_edge(i, c);
    }
  }
  lca.init();
  int q; cin >> q;
  while(q--) {
    int u, v; cin >> u >> v;
    cout << lca.trace(u, v) << endl;
  }
  return 0;
}
