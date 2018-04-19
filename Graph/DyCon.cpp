struct UndoUF {
  vint data;
  stack<Pi> stk;
  UndoUF(){}
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

using edge = Pi;

// Dynamic Connectivity
struct DyCon {
  UndoUF uf;
  int q, sz;
  vector<vector<edge> > es;

  vector<pair<Pi, edge> > pending;
  map<edge, int> cnt, appear;

  map<int, Pi> mp;

  DyCon(int n, int q):uf(n), q(q) {
    sz = 1; while(sz < q) sz <<= 1;
    es.resize(2*sz-1);
  }
  void insert(int qt, edge e) {
    if(e.first > e.second) swap(e.first, e.second);
    if(cnt[e]++ == 0) appear[e] = qt;
  }
  void erase(int qt, edge e) {
    if(e.first > e.second) swap(e.first, e.second);
    if(--cnt[e] == 0) pending.emplace_back(make_pair(appear[e], qt), e);
  }
  void add_edge(int a, int b, const edge& e, int k, int l, int r) {
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) {
      es[k].emplace_back(e);
      return;
    }
    add_edge(a, b, e, 2*k+1, l, (l+r)/2);
    add_edge(a, b, e, 2*k+2, (l+r)/2, r);
  }
  void add_edge(int a, int b, const edge& e) {
    add_edge(a, b, e, 0, 0, sz);
  }
  void build() {
    for(auto& p : cnt) {
      if(p.second > 0) pending.emplace_back(make_pair(appear[p.first], sz), p.first);
    }
    for(auto& s : pending) {
      add_edge(s.first.first, s.first.second, s.second);
    }
  }
  //void execute(const function<void(int)>& f, int k = 0) {
  void execute(int k = 0) {
    for(auto& e : es[k]) {
      uf.unite(e.first, e.second);
    }
    if(k < sz-1) {
      //execute(f, 2*k+1);
      //execute(f, 2*k+2);
      execute(2*k+1);
      execute(2*k+2);
    } else if(k-sz+1 < q) {
      int qt = k-sz+1;
      //f(qt);
      //cout<<qt<<endl;
      if(mp.count(qt)) cout << (uf.same(mp[qt].first, mp[qt].second) ? "YES" : "NO") << endl;
    }
    for(auto& e : es[k]) {
      uf.undo();
    }
  }
  void add_query(int qt, int a, int b) {
    mp[qt] = Pi(a, b);
  }
};
