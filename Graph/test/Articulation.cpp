// AOJ GRL_3_A: Connected Components - Articulation Points
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

struct UnionFind
{
  vector<int> data;
  UnionFind(int sz):data(sz, -1){};
  int size(int x) { return -data[find(x)]; }  
  int find(int x) { return data[x] < 0 ? x : data[x] = find(data[x]); }
  bool same(int x, int y) { return find(x) == find(y); }  
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


int main()
{
  int V, E; cin >> V >> E;
  BICC bicc(V);
  while(E--) {
    int s, t;
    cin >> s >> t;
    bicc.add_edge(s, t);
  }
  bicc.compose();
  sort(all(bicc.articulation));
  rep(i, bicc.articulation.size()) cout << bicc.articulation[i] << endl;
  return 0;
}
