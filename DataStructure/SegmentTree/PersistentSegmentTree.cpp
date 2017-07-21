// 永続セグメントツリー
struct SegmentTree {
  struct node {
    node *lch, *rch;
    int val;
    node():lch(nullptr), rch(nullptr), val(inf){}
  };
  int error;
  int sz;
  vector<node*> roots;
  SegmentTree(int n) {
    error = inf;
    sz = 1;
    while(sz < n) sz *= 2;
    roots.push_back(nullptr);
  }
  int get(node* x) {
    return x ? x->val : error;
  }
  node* update(node *x, int k, int val, int l, int r) {
    x = x ? new node(*x) : new node();
    if(r - l == 1) {
      x->val = val;
      return x;
    }
    int m = (l + r) / 2;
    if(k < m) x->lch = update(x->lch, k, val, l, m);
    else x->rch = update(x->rch, k, val, m, r);
    x->val = min(get(x->lch), get(x->rch));
    return x;
  }
  void update(int k, int val) {
    roots.push_back(update(roots.back(), k, val, 0, sz));
  }
  int query(int a, int b, node *x, int l, int r) {
    if(!x) return error;
    if(r <= a || b <= l) return error;
    if(a <= l && r <= b) return get(x);
    int m = (l + r) / 2;
    return min(query(a, b, x->lch, l, m), query(a, b, x->rch, m, r));
  }
  int query(int a, int b) {
    return query(a, b, root.back(), 0, sz);
  }
};
