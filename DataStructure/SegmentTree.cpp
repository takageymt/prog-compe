// SegmentTree for Range of Minimum query
template<class T> struct Min {
  T nil;
  Min(){}
  Min(T nil):nil(nil){}
  T operator()(T a, T b) {
    return a < b ? a : b;
  }
};
template<class T> struct Max {
  T nil;
  Max(){}
  Max(T nil):nil(nil){}
  T operator()(T a, T b) {
    return a > b ? a : b;
  }
};

template<class T, class F>
struct SegmentTree {
  vector<T> data;
  F func;
  int sz;
  SegmentTree(int n, F f) {
    func = f;
    sz = 1; while(sz < n) sz <<= 1;
    data.resize(2*sz+1, func.nil);
  }
  void update(int k, T x) {
    k += sz-1;
    data[k] = x;
    while(k > 0) {
      k = (k-1)/2;
      data[k] = func(data[2*k+1], data[2*k+2]);
    }
  }
  T query(int a, int b, int k, int l, int r) {
    if(r <= a || b <= l) return func.nil;
    if(a <= l && r <= b) return data[k];
    return func(query(a, b, 2*k+1, l, (l+r)/2),
	       query(a, b, 2*k+2, (l+r)/2, r));
  }
  T query(int a, int b) {
    return query(a, b, 0, 0, sz);
  }
};
