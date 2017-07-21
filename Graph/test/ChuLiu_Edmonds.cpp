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

struct SCC {
  vector< vector<int> > graph, rgraph;
  vector<int> cmp;
  SCC(int V):graph(V), rgraph(V), cmp(V, -1){}
  void add_edge(int from, int to) {
    graph[from].push_back(to);
    rgraph[to].push_back(from);
  }
  void dfs(int u, vector<int>& ord, vector<int>& used) {
    if(used[u]) return;
    used[u] = 1;
    for(int v : graph[u]) dfs(v, ord, used);
    ord.push_back(u);
  }
  void rdfs(int u, int& id) {
    if(~cmp[u]) return;
    cmp[u] = id;
    for(int v : rgraph[u]) rdfs(v, id);
  }
  int build() {
    vector<int> ord, used(graph.size(), 0);
    for(int u = 0; u < (int)graph.size(); u++) dfs(u, ord, used);
    reverse(ord.begin(), ord.end());
    int sz = 0;
    for(int u : ord) if(cmp[u] == -1) rdfs(u, sz), sz++;

    return sz;
  }
};

struct ChuLiu_Edmonds {
  struct edge {
    int to, cost;
    edge(){}
    edge(int to, int cost):to(to), cost(cost){}
  };
  typedef vector< vector<edge> > Graph;
  Graph graph;
  vector<int> indeg;

  //const int inf = 1<<25;

  ChuLiu_Edmonds(int V):graph(V), indeg(V, 0){}

  void add_edge(int from, int to, int cost) {
    graph[from].emplace_back(to, cost);
    indeg[to]++;
  }
  int get_root() {
    for(int r = 0; r < (int)graph.size(); r++) {
      if(indeg[r] == 0) return r;
    }
    return -1;
  }
  int minimum_cost_arborescence(Graph &g, int root) {
    int N = g.size();

    vector<int> into(N, -1), mincost(N, inf); // 頂点uに入るコストが最小の入る辺のfromとそのコスト
    for(int u = 0; u < N; u++) {
      for(edge& e : g[u]) {
	if(e.cost < mincost[e.to]) {
	  into[e.to] = u;
	  mincost[e.to] = e.cost;
	}
      }
    }

    int res = 0;
    SCC scc(N);
    for(int u = 0; u < N; u++) {
      if(u == root) continue;
      assert(into[u] != -1);
      assert(mincost[u] != inf);
      scc.add_edge(into[u], u);
      res += mincost[u];
    }
    int scc_sz = scc.build();
    if((int)scc_sz == N) return res;

    Graph reduce_g(scc_sz);
    for(int u = 0; u < N; u++) {
      for(edge& e : g[u]) {
	if(scc.cmp[u] == scc.cmp[e.to]) continue;
	reduce_g[scc.cmp[u]].emplace_back(scc.cmp[e.to], e.cost-mincost[e.to]);
      }
    }

    return res + minimum_cost_arborescence(reduce_g, scc.cmp[root]);
  }
  int build(int root = -1) {
    if(root == -1) root = get_root();
    return minimum_cost_arborescence(graph, root);
  }
};


signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int N, M, r;
  cin >> N >> M >> r;
  ChuLiu_Edmonds graph(N);
  rep(i, M) {
    int s, t, w;
    cin >> s >> t >> w;
    graph.add_edge(s, t, w);
  }
  cout << graph.build(r) << endl;

  return 0;
}
