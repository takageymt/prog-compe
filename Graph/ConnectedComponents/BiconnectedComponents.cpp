struct BICC {
  vint low, ord, cmp;
  set<int> apt;
  set<Pi> brge;
  int root;
  void init(const Graph& g) {
    int n = g.size();
    low.clear();
    low.resize(n);
    ord.clear();
    ord.resize(n);
    cmp.clear();
    cmp.resize(n, -1);
    root = 0;
    while(root < n-1 && g[root].size() == 1) root++;
  }
  void dfs(const Graph& g, int u, int p, int& k, vint& vis) {
    vis[u] = 1;
    ord[u] = low[u] = k++;
    bool isapt = false;
    int cnt = 0;
    for(auto&& v : g[u]) {
      if(!vis[v]) {
	cnt++;
	dfs(g, v, u, k, vis);
	low[u] = min(low[u], low[v]);
	if(~p && ord[u] <= low[v]) isapt = true;
	if(ord[u] < low[v]) brge.insert(minmax(u, v));
      } else if(v != p) {
	low[u] = min(low[u], ord[v]);
      }
    }
    if(p == -1 && cnt > 1) isapt = true;
    if(isapt) apt.insert(u);
  }
  bool isarticulation(int u) {return apt.count(u) > 0;}
  bool isbridge(int u, int v) {return brge.count(minmax(u, v)) > 0;}
  void fillcmp(const Graph& g, int u, int k) {
    if(~cmp[u]) return;
    cmp[u] = k;
    for(auto&& v : g[u]) {
      if(!isbridge(u, v)) fillcmp(g, v, k);
    }
  }
  Graph build(const Graph& g) {
    init(g);
    int n = g.size(), k = 0;
    vint vis(n, 0);
    dfs(g, root, -1, k, vis);
    int sz = 0;
    fillcmp(g, root, sz++);
    for(auto&& e : brge) {
      int u = e.first, v = e.second;
      if(cmp[u] == -1) fillcmp(g, u, sz++);
      if(cmp[v] == -1) fillcmp(g, v, sz++);
    }
    Graph t(sz);
    for(auto&& e : brge) {
      int u = e.first, v = e.second;
      assert(~cmp[u] && ~cmp[v]);
      t[cmp[u]].push_back(cmp[v]);
      t[cmp[v]].push_back(cmp[u]);
    }
    return t;
  }
  int find(int u) {return cmp[u];}
};
