// GRL_3_C: Connected Components - Strongly Connected Components
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

// Strongly Connected Components
struct SCC
{
  vector< vector<int> > graph, rgraph, tree;
  vector<Pi> edges;
  vector<int> order, cmp;
  vector<bool> used;
  SCC(int sz):graph(sz), rgraph(sz), cmp(sz, -1), used(sz, false){}
  SCC(vector< vector<int> > g):graph(g), rgraph(g.size()), cmp(g.size(), -1), used(g.size(), false){}
  void add_edge(int u, int v)
  {
    graph[u].push_back(v);
    edges.emplace_back(u, v);
  }
  void dfs(int u)
  {
    if(used[u]) return;
    used[u] = true;
    for(int v : graph[u]) {
      dfs(v);
    }
    order.push_back(u);
  }
  void rdfs(int u, int& cnt)
  {
    cmp[u] = cnt;
    for(int v : rgraph[u]) {
      if(cmp[v] == -1) rdfs(v, cnt);
    }
  }
  int compose()
  {
    int cnt = 0;
    for(int u = 0; u < (int)graph.size(); u++) {
      for(int v : graph[u]) {
	rgraph[v].push_back(u);
      }
    }
    for(int u = 0; u < (int)graph.size(); u++) dfs(u);
    reverse(order.begin(), order.end());
    for(int i = 0; i < (int)order.size(); i++) {
      if(cmp[order[i]] == -1) rdfs(order[i], cnt), cnt++;
    }
    tree.resize(cnt);
    for(Pi e : edges) {
      int x = cmp[e.first], y = cmp[e.second];
      if(x == y) continue;
      tree[x].push_back(y);
    }
    return cnt;
  }
};


int main()
{
  int V, E; cin >> V >> E;
  SCC graph(V);
  while(E--) {
    int s, t;
    cin >> s >> t;
    graph.add_edge(s, t);
  }
  graph.compose();
  int Q; cin >> Q;
  while(Q--) {
    int u, v;
    cin >> u >> v;
    if(graph.cmp[u] == graph.cmp[v]) puts("1");
    else puts("0");
  }
  return 0;
}
