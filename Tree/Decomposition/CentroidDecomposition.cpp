#include <bits/stdc++.h>

using namespace std;

using Graph = vector<vector<int> >;
// Centroid Decomposition
vector<int> getCentroid(const Graph& graph, const vector<bool>& dead, int root) {
  int alive_cnt = 0;
  map<int, int> alive_id;
  function<void(int, int)> find_alive = [&](int u, int p) {
    alive_id[u] = alive_cnt++;
    for(auto&& v : graph[u]) {
      if(v == p || dead[v]) continue;
      find_alive(v, u);
    }
  };
  find_alive(root, -1);
  vector<int> centroid;
  vector<int> sz(alive_cnt);
  function<void(int, int)> dfs = [&](int u, int p) {
    int x = alive_id[u];
    sz[x] = 1;
    bool is_centroid = true;
    for(auto&& v : graph[u]) {
      if(v == p || dead[v]) continue;
      dfs(v, u);
      int y = alive_id[v];
      sz[x] += sz[y];
      if(sz[x] > alive_cnt/2) is_centroid = false;
    }
    if(alive_cnt-sz[x] > alive_cnt/2) is_centroid = false;
    if(is_centroid) centroid.push_back(u);
  };
  assert(centroid.size() == 1 ||  centroid.size() == 2);
  return centroid;
}

void CentroidDecomposition(const Graph& graph, int root = 0) {
  int n = graph.size();
  vector<bool> dead(n, false);
  function<void(int)> rec = [&](int u) {
    auto centroid = getCentroid(graph, dead, u);
    int c = centroid[0];
    dead[c] = true;

    // A. compute something within each subtree alone (without the centroid)
    for(auto&& v : graph[c]) {
      if(dead[v]) continue;
      rec(v);
    }

    // B. compute something with the centroid
    // ...your code here...

    dead[c] = false;
  };
  rec(root);
}

// 重心を一つ求める(重心分解による分割統治用)
int OneCentroid(const Graph& graph, vector<int>& dead, int root = 0) {
  static vector<int> sz(graph.size());
  function<void(int, int)> get_sz = [&](int u, int p) {
    sz[u] = 1;
    for(int v : graph[u]) {
      if(v == p || dead[v]) continue;
      get_sz(v, u);
      sz[u] += sz[v];
    }
  };
  get_sz(root, -1);
  int n = sz[root];
  function<int(int, int)> dfs = [&](int u, int p) {
    for(int v : graph[u]) {
      if(v == p || dead[v]) continue;
      if(sz[v] > n / 2) return dfs(v, u);
    }
    return u;
  };
  return dfs(root, -1);
}
