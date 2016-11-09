// Lazy-evaluated Segment Tree
struct SegmentTree
{
  vector<int> sum, lazy;
  int sz;
  SegmentTree(int n)
  {
    sz = 1; while(sz < n) sz *= 2;
    sum.resize(2*sz-1, 0);
    lazy.resize(2*sz-1, 0);
  }
  inline void lazy_evaluate(int k, int l, int r)
  {
    sum[k] += lazy[k] * (r - l);
    if(k < sz) {
      lazy[2*k+1] += lazy[k];
      lazy[2*k+2] += lazy[k];
    }
    lazy[k] = 0;
  }
  void update(int a, int b, int x, int k, int l, int r)
  {
    lazy_evaluate(k, l, r);
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) {
      lazy[k] += x;
      lazy_evaluate(k, l, r);
      return;
    }
    update(a, b, x, 2*k+1, l, (l+r)/2);
    update(a, b, x, 2*k+2, (l+r)/2, r);
    sum[k] = sum[2*k+1] + sum[2*k+2];
  }
  void update(int a, int b, int x)
  {
    update(a, b, x, 0, 0, sz);
  }
  int query(int a, int b, int k, int l, int r)
  {
    lazy_evaluate(k, l, r);
    if(r <= a || b <= l) return 0;
    if(a <= l && r <= b) return sum[k];
    return sum[k] = query(a, b, 2*k+1, l, (l+r)/2) + query(a, b, 2*k+2, (l+r)/2, r);
  }
  int query(int a, int b)
  {
    return query(a, b, 0, 0, sz);
  }
};
