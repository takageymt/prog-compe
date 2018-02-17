// Mo's algorithm
// 区間クエリ系問題を解くためのアルゴリズム
// > 要素が更新されない
// > クエリ先読み可
// > 区間の結果をマージできない
// > 区間[l,r)から
// >> [l-1,r),[l,r+1)が求まる(追加操作)
// >> [l+1,r),[l,r-1)が求まる(削除操作)

struct Mo {
  vector<int> L, R, order;
  vector<bool> v;
  int width;
  int li, ri, ptr;
  Mo(int n):v(n, false), width((int)sqrt(n)), li(0), ri(0), ptr(0){}
  void insert(int l, int r) {
    L.push_back(l);
    R.push_back(r);
  }
  void build() {
    order.resize(L.size());
    iota(begin(order), end(order), 0);
    sort(begin(order), end(order), [&](int i, int j)->bool{
	if(L[i]/width != L[j]/width) return L[i] < L[j];
	return R[i] < R[j];
      });
  }
  int advance() {
    if(ptr == (int)order.size()) return -1;
    const int id = order[ptr++];
    while(li > L[id]) distribute(--li);
    while(ri < R[id]) distribute(ri++);
    while(li < L[id]) distribute(li++);
    while(ri > R[id]) distribute(--ri);
    return id;
  }
  void distribute(int idx) {
    v[idx].flip();
    if(v[idx]) add(idx);
    else del(idx);
  }
  void add(int idx);
  void del(int idx);
};
