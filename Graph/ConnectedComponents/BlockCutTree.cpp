struct BICC {
  vint ord, low, art, stk, id;
  vector<vint> cmp;
  BICC(){}
  void init(const Graph& graph) {
    int n = graph.size();
    ord.clear(); ord.resize(n, -1);
    low.clear(); low.resize(n, -1);
    art.clear(); art.resize(n, 0);
    cmp.clear();
    id.clear(); id.resize(n, -1);
  }
  void dfs(const Graph& graph, int u, int p, int& k, vint& vis) {
    vis[u] = 1;
    ord[u] = low[u] = k++;
    stk.push_back(u);
    for(int v : graph[u]) {
      if(!vis[v]) {
	dfs(graph, v, u, k, vis);
	low[u] = min(low[u], low[v]);
	if(ord[u] <= low[v]) {
	  art[u] = (ord[u] > 0 || ord[v] > 1);
	  cmp.push_back({u});
	  while(cmp.back().back() != v) {
	    cmp.back().push_back(stk.back());
	    stk.pop_back();
	  }
	}
      } else if(v != p) {
	low[u] = min(low[u], ord[v]);
      }
    }
  }
  Graph build(const Graph& graph) { // build the block cut tree
    init(graph);
    int n = graph.size(), k = 0;
    vint vis(n, 0);
    for(int u = 0; u < n; u++) {
      if(ord[u] == -1) dfs(graph, u, -1, k = 0, vis);
    }

    Graph tree(0);
    int sz = 0;
    for(int u = 0; u < n; u++) {
      if(art[u]) {
	tree.push_back({});
	id[u] = sz++;
      }
    }
    for(int i = 0; i < (int)cmp.size(); i++) {
      tree.push_back({});
      int node = sz++;
      for(int u : cmp[i]) {
	if(!art[u]) id[u] = node;
	else {
	  tree[node].push_back(id[u]);
	  tree[id[u]].push_back(node);
	}
      }
    }
    return tree;
  }
  bool isarticulation(int u) {
    return art[u];
  }
  int find(int u) {
    return id[u];
  }
};
