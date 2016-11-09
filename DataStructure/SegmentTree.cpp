// SegmentTree for Range of Maximum query
struct SegmentTree
{
  vector<int> data;
  int sz;
  SegmentTree(int n)
  {
    sz = 1;
    while(sz < n) sz *= 2;
    data.resize(2*sz-1, 0);
  }
  void update(int k, int x)
  {
    k += sz - 1;
    data[k] = x;
    while(k > 0) {
      k = (k - 1) / 2;
      data[k] = max(data[2*k+1], data[2*k+2]);
    }
  }
  int query(int a, int b, int k, int l, int r)
  {
    if(r <= a || b <= l) return 0;
    if(a <= l && r <= b) return data[k];
    return max(query(a, b, 2*k+1, l, (l+r)/2),
	       query(a, b, 2*k+2, (l+r)/2, r));
  }
  int query(int a, int b)
  {
    return query(a, b, 0, 0, sz);
  }
};
