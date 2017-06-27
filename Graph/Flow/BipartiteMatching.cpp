struct BipartiteMatching
{
  vector< vector<int> > graph;
  vector<int> matched;
  vector<bool> used;
  BipartiteMatching(int V):graph(V), matched(V, -1), used(V, false){}
  void add_edge(int u, int v)
  {
    graph[u].emplace_back(v);
    graph[v].emplace_back(u);
  }
  bool dfs(int u)
  {
    used[u] = true;
    for(auto& v : graph[u]) {
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
    for(int u = 0; u < graph.size(); u++) {
      if(matched[u] < 0) {
	used.clear(); used.resize(graph.size(), false);
	if(dfs(u)) res++;
      }
    }
    return res;
  }
};
