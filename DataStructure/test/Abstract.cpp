#include <bits/stdc++.h>

using namespace std;

/*
struct Monoid {
  using T = _type_;
  static T op(const T& a, const T& b) {return _a_op_b_;}
  static constexpr T e() {return _identity_element_;};
};
*/

/*
struct M_act {
  using OS = _operand_set_(i.e. Monoid)_;
  using OM = _operator_monoid_(i.e. Monoid)_;
  using T = OS::T;
  using M = OM::T;
  static T act(const int& len, const M& m, const T& a) {return _m_act_a_}
};
*/

template<class M_act>
struct RUSegmentTree {
  using OS = typename M_act::OS;
  using OM = typename M_act::OM;
  using T = typename OS::T;
  using M = typename OM::T;
  vector<T> data;
  vector<M> lazy;
  int sz;
  RUSegmentTree(){}
  RUSegmentTree(int n){init(n);}
  RUSegmentTree(vector<T> _data) {
    init(_data.size());
    build(_data);
  }
  void init(int n) {
    sz = 1; while(sz < n) sz <<= 1;
    data.resize(2*sz-1, OS::e());
    lazy.resize(2*sz-1, OM::e());
  }
  void build(const vector<T>& _data) {
    for(int i = 0; i < (int)_data.size(); ++i) data[i+sz-1] = _data[i];
    for(int i = sz-2; i >= 0; --i) data[i] = OS::op(data[2*i+1], data[2*i+2]);
  }
  void push(int k, int len) {
    if(lazy[k] == OM::e()) return;
    if(len > 1) {
      lazy[2*k+1] = OM::op(lazy[k], lazy[2*k+1]);
      lazy[2*k+2] = OM::op(lazy[k], lazy[2*k+2]);
    }
    data[k] = M_act::act(len, lazy[k], data[k]);
    lazy[k] = OM::e();
  }
  void update(int a, int b, const M& x, int k, int l, int r) {
    push(k, r-l);
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) {
      lazy[k] = OM::op(x, lazy[k]);
      push(k, r-l);
      return;
    }
    update(a, b, x, 2*k+1, l, (l+r)/2);
    update(a, b, x, 2*k+2, (l+r)/2, r);
    data[k] = OS::op(data[2*k+1], data[2*k+2]);
  }
  void update(int a, int b, const T& x) {
    update(a, b, x, 0, 0, sz);
  }
  T query(int a, int b, int k, int l, int r) {
    push(k, r-l);
    if(r <= a || b <= l) return OS::e();
    if(a <= l && r <= b) return data[k];
    T vl = query(a, b, 2*k+1, l, (l+r)/2);
    T vr = query(a, b, 2*k+2, (l+r)/2, r);
    return OS::op(vl, vr);
  }
  T query(int a, int b) {
    return query(a, b, 0, 0, sz);
  }
};

struct Data {
  using T = array<int, 10>;
  static T op(const T& a, const T& b) {
    T res = e();
    for(int i = 0; i < 10; ++i) res[i] = a[i]+b[i];
    return res;
  }
  static T e() {
    static T ini = array<int, 10>{0};
    return ini;
  }
};

struct Operator {
  using T = array<int, 10>;
  static T op(const T& a, const T& b) {
    T res = e();
    for(int i = 0; i < 10; ++i) {
      res[i] = a[b[i]];
    }
    return res;
  }
  static T e() {
    static T ini = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    return ini;
  }
};

struct TreeLightMonoid {
  using OS = Data;
  using OM = Operator;
  using T = OS::T;
  using M = OM::T;
  static T act(const int& len, const M& m, const T& a) {
    T res = OS::e();
    for(int i = 0; i < 10; ++i) {
      res[m[i]] += a[i];
    }
    return res;
  }
};

using Graph = vector<vector<int> >;

int main() {
  int n, q;
  cin >> n >> q;
  Graph graph(n);
  for(int i = 0; i < n-1; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
  }

  vector<int> L(n), R(n);
  int idx = 0;
  function<void(int)> dfs = [&](int u) {
    L[u] = idx++;
    for(int v : graph[u]) dfs(v);
    R[u] = idx;
  };
  dfs(0);

  vector<array<int, 10> > data(n, array<int, 10>{1, 0});
  RUSegmentTree<TreeLightMonoid> seg(data);
  while(q--) {
    int t, r, x, y;
    cin >> t >> r >> x >> y;
    if(t == 1) {
      auto res = seg.query(L[r], R[r]);
      int ans = 0;
      for(int i = x; i <= y; ++i) {
	ans += res[i];
      }
      cout << ans << endl;
    } else {
      auto tmp = Operator::e();
      tmp[x] = y;
      seg.update(L[r], R[r], tmp);
    }
  }

  return 0;
}
