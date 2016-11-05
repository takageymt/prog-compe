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
    dfs(i, -1, k);

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
      tree.emplace_back(x);
      tree.emplace_back(y);
    }
  }
};
