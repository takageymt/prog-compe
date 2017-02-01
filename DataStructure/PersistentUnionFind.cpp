struct UnionFind {
  Array uf;

  UnionFind(){}
  UnionFind(int n):uf(n){}

  int find(int x)
  {
    int nd = uf[x];
    if(nd < 0) return x;
    return find(nd);
  }

  void unite(int x, int y)
  {

  }
};
