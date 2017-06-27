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

struct SegmentTree {
  vector<int> data;
  int sz;
  SegmentTree(int n) {
    sz = 1; while(sz < n) sz <<= 1;
    data.resize(2*sz-1, 0);
  }
  void add(int a, int b, int x, int k, int l, int r) {
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) {
      data[k] += x;
      return;
    }
    add(a, b, x, 2*k+1, l, (l+r)/2);
    add(a, b, x, 2*k+2, (l+r)/2, r);
  }
  void add(int a, int b, int x) {
    add(a, b, x, 0, 0, sz);
  }
  int query(int i, int k, int l, int r) {
    if(r - l == 1) return data[k];
    if(l <= i && i <= r) {
      if(i < (l+r)/2) return query(i, 2*k+1, l, (l+r)/2) + data[k];
      else return query(i, 2*k+2, (l+r)/2, r) + data[k];
    }
    return inf;
  }
  int query(int i) {
    return query(i, 0, 0, sz);
  }
};

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int n, q;
  cin >> n >> q;
  SegmentTree seg(n);
  rep(i, q) {
    int com, s, t, x;
    cin >> com >> s;
    if(com == 0) cin >> t >> x, seg.add(s-1, t, x);
    else cout << seg.query(s-1) << endl;
  }

  return 0;
}
