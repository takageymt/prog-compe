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
  void update(int a, int b, const M& x) {
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
  using T = int;
  static T op(const T& a, const T& b) {return a+b;}
  static T e() {return T();}
};

struct Operator {
  using T = int;
  static T op(const T& a, const T& b) {return a+b;}
  static T e() {return T();}
};

struct TreeLightMonoid {
  using OS = Data;
  using OM = Operator;
  using T = OS::T;
  using M = OM::T;
  static T act(const int& len, const M& m, const T& a) {return a+m*len;}
};
