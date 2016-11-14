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
