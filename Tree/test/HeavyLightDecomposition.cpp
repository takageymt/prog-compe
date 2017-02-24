#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) begin(v), end(v)
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, s, n) for(int i = (int)(s); i < (int)(n); i++)
#define min(...) min({__VA_ARGS__})
#define max(...) max({__VA_ARGS__})

struct HLDecomposition {
  vector< vector<int> > graph;
  // vid:分解後の頂点番号（パス上では連続）
  vector<int> vid, head, heavy, par, depth, inv;

  HLDecomposition(int n)
    :graph(n), vid(n, -1), head(n), heavy(n, -1), par(n), depth(n), inv(n){}

  void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  void build() {
    dfs(0, -1);
    bfs();
  }

  int dfs(int u, int p) {
    par[u] = p;
    int subsz = 1, max_chsz = 0;
    for(int v : graph[u]) {
      if(v == p) continue;
      depth[v] = depth[u] + 1;
      int chsz = dfs(v, u);
      subsz += chsz;
      if(max_chsz < chsz) max_chsz = chsz, heavy[u] = v;
    }
    return subsz;
  }

  void bfs() {
    int id = 0;
    queue<int> que; // 分解したパスの先頭
    que.push(0);
    while(!que.empty()) {
      int h = que.front(); que.pop();
      for(int i = h; i != -1; i = heavy[i]) { // 先頭からHeavy edgeに沿って下に降りてく
	vid[i] = id++;
	inv[vid[i]] = i;
	head[i] = h;
	for(int j : graph[i]) {
	  if(j != par[i] && j != heavy[i]) que.push(j);
	}
      }
    }
  }

  void for_each(int u, int v, vector< pair<int, int> >& intr) {
    if(vid[u] > vid[v]) swap(u, v);
    intr.emplace_back(max(vid[head[v]], vid[u]), vid[v]);
    if(head[u] != head[v]) for_each(u, par[head[v]], intr);
  }

  int lca(int u, int v) {
    if(vid[u] > vid[v]) swap(u, v);
    if(head[u] == head[v]) return u;
    return lca(u, par[head[v]]);
  }

  int distance(int u, int v) {
    return depth[u] + depth[v] - 2*depth[lca(u, v)];
  }
};

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
    return query(a, b, 2*k+1, l, (l+r)/2) + query(a, b, 2*k+2, (l+r)/2, r);
  }
  int query(int a, int b)
  {
    return query(a, b, 0, 0, sz);
  }
};

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

int N, Q;

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  cin >> N >> Q;
  HLDecomposition g(N);
  rep(i, N-1) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g.add_edge(u, v);
  }

  g.build();

  SegmentTree seg(N);

  rep(i, Q) {
    int t;
    cin >> t;
    if(t == 1) {
      int u, v, w;
      cin >> u >> v >> w;
      u--, v--;
      vector<pair<int, int> > intr;
      g.for_each(u, v, intr);
      for(auto p : intr) {
	seg.update(p.first, p.second + 1, w);
      }
    } else {
      int u, v;
      cin >> u >> v;
      u--, v--;
      int ans = 0;
      vector<pair<int, int> > intr;
      g.for_each(u, v, intr);
      for(auto p : intr) {
	ans += seg.query(p.first, p.second + 1);
      }
      cout << ans << endl;
    }
  }

  return 0;
}
