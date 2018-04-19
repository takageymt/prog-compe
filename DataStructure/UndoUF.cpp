struct UndoUF {
  vint data;
  stack<Pi> stk;
  UndoUF(int n):data(n, -1){}
  int find(int x) {
    return data[x] < 0 ? x : find(data[x]);
  }
  int size(int x) {
    return -data[find(x)];
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
  void unite(int x, int y) {
    x = find(x), y = find(y);
    stk.emplace(x, data[x]);
    stk.emplace(y, data[y]);
    if(x == y) return;
    if(data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
  }
  void undo() {
    Pi p = stk.top(); stk.pop();
    data[p.first] = p.second;
    p = stk.top(); stk.pop();
    data[p.first] = p.second;
  }
};
