struct UnionFind
{
  vector<int> data;
  UnionFind(){}
  UnionFind(int sz):data(sz, -1){};
  int size(int x) { return -data[find(x)]; }
  int find(int x) {
    if(data[x] < 0) return x;
    return data[x] = find(data[x]);
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  void unite(int x, int y)
  {
    x = find(x), y = find(y);
    if(x == y) return;
    if(data[x] < data[y]) swap(x, y);
    data[x] += data[y]; data[y] = x;
    return;
  }
};
