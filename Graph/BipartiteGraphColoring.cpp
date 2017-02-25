struct BipartiteGraph : UnionFind {
  vector<int> color;
  BipartiteGraph(int V):color(V+V, -1), UnionFind(V+V){}
  void same_color(int a, int b) {
    unite(a, b);
    unite(a + color.size()/2, b + color.size()/2);
  }
  void diff_color(int a, int b) {
    unite(a, b + color.size()/2);
    unite(a + color.size()/2, b);
  }
  bool coloring() {
    for(int i = 0; i < color.size()/2; i++) {
      int a = find(i);
      int b = find(i+color.size()/2);
      if(a == b) return false;
      if(color[a] < 0) color[a] = 0, color[b] = 1;
    }
    return true;
  }
  bool operator[](int k) {
    return (bool)color[find(k)];
  }
};
