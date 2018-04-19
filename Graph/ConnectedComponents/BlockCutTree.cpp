struct BICC {
  vint ord, low, art, id;
  vint stk;
  vector<vint> cmp;
  vector<Pi> estk;
  vector<vector<Pi> > ecmp;
  BICC(){}
  void init(const Graph& graph) {
    int n = graph.size();
    ord.clear(); ord.resize(n, -1);
    low.clear(); low.resize(n, -1);
    art.clear(); art.resize(n, 0);
    id.clear(); id.resize(n, -1);
    stk.clear();
    cmp.clear();
    estk.clear();
    ecmp.clear();
  }
  void dfs(const Graph& graph, int u, int p, int& k) {
    ord[u] = low[u] = k++;
    stk.push_back(u);
    for(int v : graph[u]) {
      if(v == p) continue;
      if(ord[v] < ord[u]) {
	estk.emplace_back(min(u, v), max(u, v));
      }
      if(ord[v] == -1) {
	dfs(graph, v, u, k);
	low[u] = min(low[u], low[v]);
	if(ord[u] <= low[v]) {
	  art[u] = (ord[u] > 0 || ord[v] > 1);

	  // nodes belong to a component
	  cmp.push_back({u});
	  while(cmp.back().back() != v) {
	    cmp.back().push_back(stk.back());
	    stk.pop_back();
	  }

	  // edges belong to a component
	  ecmp.push_back({});
	  while(ecmp.back().empty() || ecmp.back().back() != Pi(min(u, v), max(u, v))) {
	    ecmp.back().push_back(estk.back());
	    estk.pop_back();
	  }
	}
      } else {
	low[u] = min(low[u], ord[v]);
      }
    }
  }
  Graph build(const Graph& graph) { // build the block cut tree
    init(graph);
    int n = graph.size(), k = 0;
    for(int u = 0; u < n; u++) {
      if(ord[u] == -1) dfs(graph, u, -1, k = 0);
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
  void print() {
    assert(cmp.size() == ecmp.size());
    for(int i = 0; i < (int)cmp.size(); ++i) {
      cout << "BLOCK " << i << endl;
      cout << "- NODES:" << endl;
      for(int v : cmp[i]) cout << " " << v;
      cout<<endl;
      cout << "- EDGES:" << endl;
      for(Pi e : ecmp[i]) cout << " ("<<e.first<<", "<<e.second<<")";
      cout<<endl;
    }
  }
};
