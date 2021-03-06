// Kruskal: minimum spanning tree
struct Kruskal {
  struct edge{
    int u, v, weight;
    edge(){}
    edge(int u, int v, int weight):u(u), v(v), weight(weight){}
    bool operator<(const edge& e) const {
      return weight < e.weight;
    }
  };

  vector<edge> edges;
  int V;
  Kruskal(int V):V(V){}
  void add_edge(int u, int v, int weight) {
    edges.push_back(edge(u, v, weight));
  }
  int build() {
    sort(edges.begin(), edges.end());
    UnionFind uf(V);
    int res = 0;
    for(int i = 0; i < edges.size(); i++){
      edge& e = edges[i];
      if(!uf.same(e.u, e.v)){
	uf.unite(e.u, e.v);
	res += e.weight;
      }
    }
    return res;
  }
};
