#include <bits/stdc++.h>

using namespace std;

using Graph = vector<vector<int> >;
// Strongly Connected Components
struct SCC {
  vector<int> cmp;
  SCC(){}
  Graph init(const Graph& graph) {
    int n = graph.size();
    cmp.clear();
    cmp.resize(n, -1);
    Graph rgraph(n);
    for(int u = 0; u < n; ++u) {
      for(auto&& v : graph[u]) {
	rgraph[v].push_back(u);
      }
    }
    return rgraph;
  }
  void dfs(const Graph& graph, int u, vector<int>& ord, vector<bool>& used) {
    used[u] = true;
    for(auto&& v : graph[u]) {
      if(!used[v]) dfs(graph, v, ord, used);
    }
    ord.push_back(u);
  }
  void rdfs(const Graph& rgraph, int u, int& id) {
    cmp[u] = id;
    for(int v : rgraph[u]) {
      if(cmp[v] == -1) rdfs(rgraph, v, id);
    }
  }
  Graph build(const Graph& graph) {
    Graph rgraph = init(graph);
    int n = graph.size();
    vector<int> ord;
    vector<bool> used(n, false);
    for(int u = 0; u < n; ++u) {
      if(!used[u]) dfs(graph, u, ord, used);
    }
    reverse(ord.begin(), ord.end());
    int sz = 0;
    for(int u : ord) {
      if(cmp[u] == -1) rdfs(rgraph, u, sz), ++sz;
    }
    Graph dag(sz);
    set< pair<int, int> > st;
    for(int u = 0; u < n; ++u) {
      for(auto&& v : graph[u]) {
	int x = cmp[u], y = cmp[v];
	if(x != y && !st.count(make_pair(x, y))) {
	  dag[x].push_back(y);
	  st.emplace(x, y);
	}
      }
    }

    return dag;
  }
};
