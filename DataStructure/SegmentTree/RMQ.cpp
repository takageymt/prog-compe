#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) begin(v), end(v)
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, s, n) for(int i = (int)(s); i < (int)(n); i++)
#define min(...) min({__VA_ARGS__})
#define max(...) max({__VA_ARGS__})

template<class T1, class T2> void chmin(T1 &a, T2 b){if(a>b)a=b;}
template<class T1, class T2> void chmax(T1 &a, T2 b){if(a<b)a=b;}

using pint = pair<int, int>;
using tint = tuple<int, int, int>;
using vint = vector<int>;

const int inf = (1LL<<31)-1;
const int mod = 1e9 + 7;

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
  void update(int k, T x) {
    k += sz-1;
    data[k] = x;
    while(k > 0) {
      k = (k-1)/2;
      data[k] = func(data[2*k+1], data[2*k+2]);
    }
  }
  void add(int k, T x) {
    k += sz-1;
    data[k] += x;
    while(k > 0) {
      k = (k-1)/2;
      data[k] = func(data[2*k+1], data[2*k+2]);
    }
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

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int n, q;
  cin >> n >> q;
  SegmentTree<Min<int> > seg(n, Min<int>(inf));
  rep(i, q) {
    int com, x, y;
    cin >> com >> x >> y;
    if(com == 0) seg.update(x, y);
    else cout << seg.query(x, y+1) << endl;
  }

  return 0;
}
