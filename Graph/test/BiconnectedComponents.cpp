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
#define each(a, b) for(auto a : b)
     
const int inf = 1 << 25;
const ll INF = 1LL << 55;
     
struct UnionFind
{
  vector<int> data;
  UnionFind(int sz):data(sz, -1){};
  int size(int x) { return -data[find(x)]; }  
  int find(int x) { return (data[x] < 0 ? x : data[x] = find(data[x])); }
  int unite(int x, int y)
  {
    x = find(x), y = find(y);
    if(x != y) {
      if(data[x] < data[y]) swap(x, y);
      data[x] += data[y]; data[y] = x;
    }
    return -data[x];
  }
};
// Biconnected Components (lowlink)
struct BICC
{
  UnionFind uf;
  vector< vector<int> > graph, tree;
  vector<Pi> edges;
  vector<bool> vis;
  vector<int> ord, low, cmp;
  vector<int> articulation;
  vector<Pi> bridge;
  BICC(int sz):uf(sz), graph(sz), vis(sz, false), ord(sz), low(sz), cmp(sz){}
  void add_edge(int u, int v)
  {
    graph[u].emplace_back(v);
    graph[v].emplace_back(u);
    edges.emplace_back(minmax(u, v));
  }
  void dfs(int u, int p, int& k)
  {
    vis[u] = true;
    
    ord[u] = low[u] = k++;

    bool is_articulation = false;
    int cnt = 0;
    
    for(auto v : graph[u]) {
      if(!vis[v]) {
	cnt++;
	dfs(v, u, k);
	low[u] = min(low[u], low[v]);
	if(~p && ord[u] <= low[v]) is_articulation = true;
	if(ord[u] < low[v]) bridge.emplace_back(minmax(u, v));
	else uf.unite(u, v);
      } else if(v != p) {
	low[u] = min(low[u], ord[v]);
      }
    }
    
    if(p == -1 && cnt > 1) is_articulation = true;
    if(is_articulation) articulation.push_back(u);
  }
  void compose()
  {
    int k = 0;
    dfs(0, -1, k);

    int num = 0;
    vector<int> conn(graph.size());
    for(int i = 0; i < graph.size(); i++) {
      if(i == uf.find(i)) conn[i] = num++;
    }

    tree.resize(num);
    for(int i = 0; i < graph.size(); i++) {
      cmp[i] = conn[uf.find(i)];
    }
    for(auto e : edges) {
      int x = cmp[e.first], y = cmp[e.second];
      if(x == y) continue;
      tree[x].emplace_back(y);
      tree[y].emplace_back(x);      
    }
  }
};
     
struct LCA
{
  vector< vector<int> > G, par;
  vector<int> depth;
  int log_V;
  LCA(int V)
  {
    log_V = 1;
    while((1 << log_V) <= V) log_V++;
    G.resize(V);
    par.resize(log_V, vector<int>(V, -1));    
    depth.resize(V);
  }
  void add_edge(int f, int t)
  {
    G[f].emplace_back(t);
    G[t].emplace_back(f);    
  }
  void dfs(int u, int p, int d)
  {
    par[0][u] = p;
    depth[u] = d;
    for(auto v : G[u]) {
      if(v != p) dfs(v, u, d + 1);
    }
  }
  void init(int root = 0)
  {
    dfs(root, -1, 0);
    for(int i = 0; i + 1 < log_V; i++) {
      for(int v = 0; v < par[i].size(); v++) {
	if(par[i][v] < 0) par[i + 1][v] = -1;
	else par[i + 1][v] = par[i][par[i][v]];
      }
    }
  }
  int trace(int u, int v)
  {
    if(depth[u] > depth[v]) swap(u, v);
    for(int i = 0; i < log_V; i++) {
      if((depth[v] - depth[u]) >> i & 1) v = par[i][v];
    }
    if(u == v) return u;
    for(int i = log_V-1; i >= 0; i--) {
      if(par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
    }
    return par[0][u];
  }
  int dist(int u, int v) { return depth[u] + depth[v] - 2*depth[trace(u, v)]; }
};
     
int main()
{
  int N, M; cin >> N >> M;
  BICC bicc(N);
  rep(i, M) {
    int X, Y; cin >> X >> Y; X--, Y--;
    bicc.add_edge(X, Y);
  }
  bicc.compose();
  LCA lca(bicc.tree.size());
  lca.G = bicc.tree;
  lca.init();
  int Q; cin >> Q;
  while(Q--) {
    int A, B, C;
    cin >> A >> B >> C; --A, --B, --C;
    A = bicc.cmp[A]; B = bicc.cmp[B]; C = bicc.cmp[C];
    if(lca.dist(A, B) + lca.dist(B, C) == lca.dist(A, C)) cout << "OK" << endl;
    else cout << "NG" << endl;
  }
  return 0;
}
