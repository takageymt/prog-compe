// Least Common Ancestor (Doubling)
struct LCA
{
  vector< vector<int> > tree, parent;
  vector<int> depth;
  int log_V;
  LCA(int V)
  {
    log_V = 1;
    while((1 << log_V) <= V) log_V++;
    tree.resize(V);
    parent.resize(log_V, vector<int>(V, -1));    
    depth.resize(V);
  }
  void add_edge(int f, int t)
  {
    tree[f].emplace_back(t);
    tree[t].emplace_back(f);    
  }
  void dfs(int u, int p, int d)
  {
    parent[0][u] = p;
    depth[u] = d;
    for(auto v : tree[u]) {
      if(v != p) dfs(v, u, d + 1);
    }
  }
  void init(int root = 0)
  {
    dfs(root, -1, 0);
    for(int i = 0; i + 1 < log_V; i++) {
      for(int v = 0; v < parent[i].size(); v++) {
	if(parent[i][v] < 0) parent[i + 1][v] = -1;
	else parent[i + 1][v] = parent[i][parent[i][v]];
      }
    }
  }
  int trace(int u, int v)
  {
    if(depth[u] > depth[v]) swap(u, v);
    for(int i = 0; i < log_V; i++) {
      if((depth[v] - depth[u]) >> i & 1) v = parent[i][v];
    }
    if(u == v) return u;
    for(int i = log_V-1; i >= 0; i--) {
      if(parent[i][u] != parent[i][v]) u = parent[i][u], v = parent[i][v];
    }
    return parent[0][u];
  }
  int dist(int u, int v) {
    return depth[u] + depth[v] - 2*depth[trace(u, v)];
  }
};
