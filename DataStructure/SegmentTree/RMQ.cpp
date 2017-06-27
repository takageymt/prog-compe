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
    data.resize(2*sz-1, inf);
  }
  void update(int k, int x) {
    k += sz-1;
    data[k] = x;
    while(k > 0) {
      k = (k-1) / 2;
      data[k] = min(data[2*k+1], data[2*k+2]);
    }
  }
  int query(int a, int b, int k, int l, int r) {
    if(r <= a || b <= l) return inf;
    if(a <= l && r <= b) return data[k];
    return min(query(a, b, 2*k+1, l, (l+r)/2),
	       query(a, b, 2*k+2, (l+r)/2, r));
  }
  int query(int a, int b) {
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
  SegmentTree seg(n);
  rep(i, q) {
    int com, x, y;
    cin >> com >> x >> y;
    if(com == 0) seg.update(x, y);
    else cout << seg.query(x, y+1) << endl;
  }

  return 0;
}
