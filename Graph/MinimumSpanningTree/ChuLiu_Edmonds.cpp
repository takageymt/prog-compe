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
