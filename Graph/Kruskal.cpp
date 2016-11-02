struct edge{
  int u, v, cost;
  edge(){}
  edge(int u, int v, int cost):u(u), v(v), cost(cost){}
  bool operator<(const edge& e) const {
    return cost < e.cost;
  }
};

struct Kruskal
{
  vector<edge> E;
  int V;
  Kruskal(int V):V(V){}
  void add_edge(int u, int v, int cost)
  {
    E.push_back(edge(u, v, cost));
  }
  int build()
  {
    sort(E.begin(), E.end());
    UnionFind uf(V);
    int ret = 0;
    for(int i = 0; i < E.size(); i++){
      edge& e = E[i];
      if(!uf.same(e.u, e.v)){
	uf.unite(e.u, e.v);
	ret += e.cost;
      }
    }
    return ret;
  }
};
