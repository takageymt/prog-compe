struct BipartiteMatching
{
  vector< vector<int> > G;
  vector<int> matched;
  vector<bool> used;
  BipartiteMatching(int V):G(V), matched(V, -1), used(V, false){}
  void add_edge(int u, int v)
  {
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  bool dfs(int u)
  {
    used[u] = true;
    for(auto& v : G[u]) {
      int w = matched[v];
      if(w < 0 || !used[w] && dfs(w)) {
	matched[u] = v;
	matched[v] = u;
	return true;
      }
    }
    return false;
  }
  int match()
  {
    int res = 0;
    for(int u = 0; u < G.size(); u++) {
      if(matched[u] < 0) {
	used.clear(); used.resize(G.size(), false);
	if(dfs(u)) res++;
      }
    }
    return res;
  }
};
