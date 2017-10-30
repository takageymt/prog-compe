// SegmentTree
template<class T> struct Min {
  using Type = T;
  T id;
  Min(){}
  Min(T id):id(id){}
  T operator()(T a, T b) { return a < b ? a : b; }
};
template<class T> struct Sum {
  using Type = T;
  T id;
  Sum(){}
  Sum(T id):id(id){}
  T operator()(T a, T b) { return a + b; }
};

template<class Monoid> struct SegmentTree {
  using T = typename Monoid::Type;
  vector<T> data;
  Monoid op;
  int sz;
  SegmentTree(int n, Monoid f):op(f) { init(n); }
  SegmentTree(vector<T> data_, Monoid f):op(f) {
    init(data_.size());
    build(data_);
  }
  void init(int n) {
    sz = 1; while(sz < n) sz <<= 1;
    data.resize(2*sz-1, op.id);
  }
  void build(vector<T> data_) {
    for(int i = 0; i < (int)data_.size(); i++) data[i+sz-1] = data_[i];
    for(int i = sz-2; i >= 0; i--) data[i] = op(data[2*i+1], data[2*i+2]);
  }
  void set(int k, T x, bool add_flag = false) {
    k += sz-1;
    data[k] = add_flag ? data[k] + x : x;
    while(k > 0) {
      k = (k-1)/2;
      data[k] = op(data[2*k+1], data[2*k+2]);
    }
  }
  void add(int k, T x) {
    set(k, x, true);
  }
  T get(int i, int k, int l, int r) {
    if(l == r+1) return data[k];
    if(l <= i && i <= r) {
      if(i < (l+r)/2) return get(i, 2*k+1, l, (l+r)/2);
      else return get(i, 2*k+2, (l+r)/2, r);
    }
    return op.id;
  }
  T get(int i) {
    return get(i, 0, 0, sz);
  }
  T query(int a, int b, int k, int l, int r) {
    if(r <= a || b <= l) return op.id;
    if(a <= l && r <= b) return data[k];
    return op(query(a, b, 2*k+1, l, (l+r)/2), query(a, b, 2*k+2, (l+r)/2, r));
  }
  T query(int a, int b) {
    return query(a, b, 0, 0, sz);
  }
};
