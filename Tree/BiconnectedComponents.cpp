// Biconnected Components (lowlink)
struct BICC
{
  UnionFind uf;
  vector< vector<int> > G, T;
  vector<Pi> E;
  vector<bool> vis;
  vector<int> ord, low, cmp;
  BICC(int sz):uf(sz), G(sz), vis(sz, false), ord(sz), low(sz), cmp(sz){}
  void add_edge(int f, int t)
  {
    G[f].emplace_back(t);
    G[t].emplace_back(f);
    E.emplace_back(minmax(f, t));
  }
  void dfs(int u, int p, int& k)
  {
    vis[u] = true;
    ord[u] = low[u] = k++;
    for(auto v : G[u]) {
      if(!vis[v]) {
	dfs(v, u, k);
	low[u] = min(low[u], low[v]);
	if(ord[u] >= low[v]) uf.unite(u, v);
      } else if(v != p) {
	low[u] = min(low[u], ord[v]);
      }
    }
  }
  void compose()
  {
    int k = 0;
    dfs(i, -1, k);

    int num = 0;
    vector<int> conn(G.size());
    for(int i = 0; i < G.size(); i++) {
      if(i == uf.find(i)) conn[i] = num++;
    }

    T.resize(num);
    for(int i = 0; i < G.size(); i++) {
      cmp[i] = conn[uf.find(i)];
    }
    for(auto e : E) {
      int x = cmp[e.first], y = cmp[e.second];
      if(x == y) continue;
      T.emplace_back(x);
      T.emplace_back(y);
    }
  }
};
