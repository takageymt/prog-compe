// Least Common Ancestor (Doubling)
struct LCA
{
  vector< vector<int> > G, par;
  vector<int> depth;
  int log_V;
  LCA(int V)
  {
    log_V = 1;
    while((1 << log_V) <= V) log_V++;
    G.resize(V);
    par.resize(log_V, vector<int>(V, -1));    
    depth.resize(V);
  }
  void add_edge(int f, int t)
  {
    G[f].emplace_back(t);
    G[t].emplace_back(f);    
  }
  void dfs(int u, int p, int d)
  {
    par[0][u] = p;
    depth[u] = d;
    for(auto v : G[u]) {
      if(v != p) dfs(v, u, d + 1);
    }
  }
  void init(int root = 0)
  {
    dfs(root, -1, 0);
    for(int i = 0; i + 1 < log_V; i++) {
      for(int v = 0; v < par[i].size(); v++) {
	if(par[i][v] < 0) par[i + 1][v] = -1;
	else par[i + 1][v] = par[i][par[i][v]];
      }
    }
  }
  int trace(int u, int v)
  {
    if(depth[u] > depth[v]) swap(u, v);
    for(int i = 0; i < log_V; i++) {
      if((depth[v] - depth[u]) >> i & 1) v = par[i][v];
    }
    if(u == v) return u;
    for(int i = log_V-1; i >= 0; i--) {
      if(par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
    }
    return par[0][u];
  }
  int dist(int u, int v) { return depth[u] + depth[v] - 2*depth[trace(u, v)]; }
};
