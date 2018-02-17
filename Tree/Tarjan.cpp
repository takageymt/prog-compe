#include <bits/stdc++.h>

using namespace std;

struct UnionFind {
  vector<int> data;
  UnionFind(){}
  UnionFind(int n):data(n, -1){}
  int find(int x) {
    return data[x] < 0 ? x : data[x] = find(data[x]);
  }
  int size(int x) {
    return -data[find(x)];
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  void unite(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return;
    if(data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
  }
};

using Graph = vector<vector<int> >;
using Pi = pair<int, int>;
struct LCA {
  UnionFind uf;
  Graph pairs;
  vector<int> par;
  vector<bool> used;
  map<Pi, int> lca;
  LCA(){}
  vector<int> offline_query(const Graph& graph, const vector<Pi> query, int root = 0) {
    int n = graph.size();
    uf = UnionFind(n);
    pairs.clear(); pairs.resize(n);
    for(auto&& p : query) {
      pairs[p.first].push_back(p.second);
      pairs[p.second].push_back(p.first);
    }
    par.clear(); par.resize(n, -1);
    used.clear(); used.resize(n, false);
    dfs(graph, root);
    vector<int> res(query.size());
    for(int i = 0; i < (int)query.size(); ++i) {
      int u = query[i].first, v = query[i].second;
      res[i] = lca[Pi(u, v)];
    }
    return res;
  }
  void dfs(const Graph& graph, int u) {
    par[uf.find(u)] = u;
    for(auto&& v : graph[u]) {
      dfs(graph, v);
      uf.unite(u, v);
      par[uf.find(u)] = u;
    }
    used[u] = true;
    for(auto&& v : pairs[u]) {
      if(used[v]) lca[Pi(u, v)] = lca[Pi(v, u)] = par[uf.find(v)];
    }
  }
};
