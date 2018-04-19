#include <bits/stdc++.h>

using namespace std;

using Graph = vector<vector<int> >;

struct SCC {
  vector<int> ord, low, cmp;
  SCC(){}
  void init(const Graph& graph) {
    int n = graph.size();
    ord.clear();
    ord.resize(n, -1);
    low.clear();
    low.resize(n, -1);
    cmp.clear();
    cmp.resize(n, -1);
  }
  void dfs(const Graph& graph, int u, stack<int>& stk, vector<bool> instk, int& id) {
    static int k = 0;
    ord[u] = low[u] = k++;
    stk.push(u);
    instk[u] = true;
    for(auto&& v : graph[u]) {
      if(ord[u] == -1) {
	dfs(graph, v, stk, instk, id);
	low[u] = min(low[u], low[v]);
      } else if(instk[v]) {
	low[u] = min(low[u], ord[v]);
      }
    }
    if(ord[u] == low[u]) {
      while(stk.top() != u) {
	int w = stk.top(); stk.pop();
	cmp[w] = id;
	instk[w] = false;
      }
      stk.pop();
      cmp[u] = id;
      instk[u] = false;
      ++id;
    }
  }
  void build(const Graph& graph, int root = 0) {
    init(graph);
    int n = graph.size();
    stack<int> stk;
    vector<bool> instk(n, false);
    int id = 0;
    for(int u = 0; u < n; ++u) {
      if(ord[u] == -1) dfs(graph, root, stk, instk, id);
    }
  }
};
