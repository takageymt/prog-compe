#include <bits/stdc++.h>

using namespace std;

using Graph = vector<vector<int> >;

struct BICC {
  vector<int> low, ord, cmp;
  vector<bool> isapt;
  void init(const Graph& g) {
    int n = g.size();
    low.clear();
    low.resize(n, -1);
    ord.clear();
    ord.resize(n, -1);
    cmp.clear();
    cmp.resize(n, -1);
    isapt.clear();
    isapt.resize(n, false);
  }
  void dfs(const Graph& g, int u, int p) {
    static int k = 0;
    ord[u] = low[u] = k++;
    int cnt = 0;
    for(auto&& v : g[u]) {
      if(ord[v] == -1) {
	cnt++;
	dfs(g, v, u);
	low[u] = min(low[u], low[v]);
	if(~p && ord[u] <= low[v]) isapt[u] = true;
      } else if(v != p) {
	low[u] = min(low[u], ord[v]);
      }
    }
    if(p == -1 && cnt > 1) isapt[u] = true;
  }
  bool isarticulation(int u) {return isapt[u];}
  bool isbridge(int u, int v) {
    if(ord[u] > ord[v]) swap(u, v);
    return ord[u] < low[v];
  }
  void fillcmp(const Graph& g, int u, int k) {
    cmp[u] = k;
    for(auto&& v : g[u]) {
      if(!isbridge(u, v) && cmp[u] == -1) fillcmp(g, v, k);
    }
  }
  Graph build(const Graph& g) {
    init(g);
    int n = g.size();
    for(int u = 0; u < n; ++u) {
      if(ord[u] == -1) dfs(g, u, -1);
    }
    int sz = 0;
    for(int u = 0; u < n; ++u) {
      if(cmp[u] == -1) fillcmp(g, u, sz++);
    }
    Graph t(sz);
    set<pair<int, int> > st;
    for(int u = 0; u < n; ++u) {
      for(auto&& v : g[u]) {
	int x = cmp[u], y = cmp[v];
	if(x != y && !st.count(make_pair(x, y))) {
	  t[x].push_back(y);
	  t[y].push_back(x);
	  st.emplace(x, y);
	  st.emplace(y, x);
	}
      }
    }

    return t;
  }
  int find(int u) {return cmp[u];}
};
