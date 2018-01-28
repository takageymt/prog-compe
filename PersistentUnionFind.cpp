#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) (v).begin(), (v).end()
#define resz(v, ...) (v).clear(), (v).resize(__VA_ARGS__)
#define reps(i, m, n) for(int i = (int)(m); i < (int)(n); i++)
#define rep(i, n) reps(i, 0, n)

template<class T1, class T2> void chmin(T1 &a, T2 b){if(a>b)a=b;}
template<class T1, class T2> void chmax(T1 &a, T2 b){if(a<b)a=b;}

using Pi = pair<int, int>;
using Tapris = tuple<int, int, int>;
using vint = vector<int>;

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

struct UnionFind {
  int n;
  int global_time;
  vector<vint> rank, time, par;
  UnionFind(int n):n(n), global_time(0), rank(n), time(n), par(n) {
    for(int i = 0; i < n; i++) {
      rank[i].push_back(1);
      time[i].push_back(0);
      par[i].push_back(i);
    }
  }
  int find(int u, int t) {
    //if(par[u].back() == u) return u;
    //if(time[u].back() > t) return u;
    //return find(par[u].back(), t);
    int i = upper_bound(all(time[u]), t)-time[u].begin();
    if(par[u][i-1] == u) return u;
    return find(par[u][i-1], t);
  }
  void unite(int u, int v) {
    ++global_time;
    u = find(u, global_time);
    v = find(v, global_time);
    if(u == v) return;
    if(rank[u] < rank[v]) swap(u, v);
    int r = rank[u].back()+rank[v].back();
    rank[u].push_back(r);
    time[u].push_back(global_time);
    par[u].push_back(u);
    rank[v].push_back(r);
    time[v].push_back(global_time);
    par[v].push_back(u);
  }
  int size(int u, int t) {
    u = find(u, t);
    //vint temp = time[u];
    //sort(all(temp));
    int i = upper_bound(all(time[u]), t)-time[u].begin();
    return rank[u][i-1];
  }
};

signed main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int n, m;
  cin >> n >> m;
  UnionFind uf(n);
  rep(i, m) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    uf.unite(a, b);
  }
  int q;
  cin >> q;
  rep(i, q) {
    int x, y, z;
    cin >> x >> y >> z;
    --x, --y;
    int lb = 0, ub = m;
    while(lb+1 < ub) {
      int mb = (lb+ub)/2;
      int sz = -1;
      if(uf.find(x, mb) == uf.find(y, mb)) sz = uf.size(x, mb);
      else sz = uf.size(x, mb) + uf.size(y, mb);
      if(sz >= z) ub = mb;
      else lb = mb;
    }
    cout << ub << endl;
  }

  return 0;
}
