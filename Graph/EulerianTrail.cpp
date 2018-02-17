#include <bits/stdc++.h>

using namespace std;

using Graph = vector<vector<int> >;
int isEulerianGraph(const Graph& graph, const bool directed) {
  int n = graph.size();
  if(!directed) {
    vector<int> deg(n);
    for(int u = 0; u < n; ++u) {
      deg[u] = graph[u].size() % 2;
    }
    int odd = count(begin(deg), end(deg), 1);
    if(odd == 0) return 1; // Eulerian
    if(odd == 2) return 2; // semi-Eulerian
    return 0; // not Eulerian
  } else {
    vector<int> in(n), out(n);
    for(int u = 0; u < n; ++u) {
      for(int v : graph[u]) {
	++in[v];
      }
      out[u] = graph[u].size();
    }
    int s = 0, t = 0;
    for(int u = 0; u < n; ++u) {
      if(abs(in[u]-out[u]) > 1) return 0; // not Eulerian
      if(in[u]+1 == out[u]) ++s;
      else if(in[u] == out[u]+1) ++t;
    }
    if(s == 0 && t == 0) return 1; // Eulerian
    if(s == 1 && t == 1) return 2; // semi-Eulerian
    return 0; // not Eulerian
  }
}
vector<int> EulerianTrail(const int s, Graph graph, const bool directed) {
  function<void(int, vector<int>&)> dfs = [&](int u, vector<int>& trail) {
    while(!graph[u].empty()) {
      int v = graph[u].back();
      graph[u].pop_back();
      if(!directed) {
	for(int i = 0; i < (int)graph[v].size(); ++i) {
	  if(graph[v][i] == u) {
	    graph[v].erase(begin(graph[v])+i);
	    break;
	  }
	}
      }
      dfs(v, trail);
    }
    trail.push_back(u);
  };
  assert(isEulerianGraph(graph, directed));
  vector<int> trail;
  dfs(s, trail);
  reverse(begin(trail), end(trail));
  return trail;
}
