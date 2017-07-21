// SegmentTree
template<class T> struct Min {
  using Type = T;
  T nil;
  Min(){}
  Min(T nil):nil(nil){}
  T operator()(T a, T b) { return a < b ? a : b; }
};
template<class T> struct Max {
  using Type = T;
  T nil;
  Max(){}
  Max(T nil):nil(nil){}
  T operator()(T a, T b) { return a > b ? a : b; }
};
template<class T> struct Sum {
  using Type = T;
  T nil;
  Sum(){}
  Sum(T nil):nil(nil){}
  T operator()(T a, T b) { return a + b; }
};

template<class Monoid> struct SegmentTree {
  using T = typename Monoid::Type;
  vector<T> data;
  Monoid func;
  int sz;
  SegmentTree(int n, Monoid f):func(f) { init(n); }
  SegmentTree(vector<T> data_, Monoid f):func(f) {
    init(data_.size());
    build(data_);
  }
  void init(int n) {
    sz = 1; while(sz < n) sz <<= 1;
    data.resize(2*sz-1, func.nil);
  }
  void build(vector<T> data_) {
    for(int i = 0; i < (int)data_.size(); i++) data[i+sz-1] = data_[i];
    for(int i = sz-2; i >= 0; i--) data[i] = func(data[2*i+1], data[2*i+2]);
  }
  void update(int k, T x, bool add_flag = false) {
    k += sz-1;
    data[k] = add_flag ? data[k] + x : x;
    while(k > 0) {
      k = (k-1)/2;
      data[k] = func(data[2*k+1], data[2*k+2]);
    }
  }
  void add(int k, T x) {
    update(k, x, true);
  }
  T query(int a, int b, int k, int l, int r) {
    if(r <= a || b <= l) return func.nil;
    if(a <= l && r <= b) return data[k];
    return func(query(a, b, 2*k+1, l, (l+r)/2), query(a, b, 2*k+2, (l+r)/2, r));
  }
  T query(int a, int b) {
    return query(a, b, 0, 0, sz);
  }
};
