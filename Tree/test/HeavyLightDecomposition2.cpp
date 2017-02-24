#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) begin(v), end(v)
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, s, n) for(int i = (int)(s); i < (int)(n); i++)
#define min(...) min({__VA_ARGS__})
#define max(...) max({__VA_ARGS__})

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

struct HLDT {
  vector< vector<int> > graph;
  // vid:分解後の頂点番号（パス上では連続）
  vector<int> vid, head, heavy, par, depth, inv;

  HLDT(){}
  HLDT(int n)
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

  void for_each(int u, int v, vector< tuple<int, int, bool> >& lr) {
    if(vid[u] < vid[v]) {
      lr.emplace_back(max(vid[head[v]], vid[u]), vid[v], true); // 閉区間
      if(head[u] != head[v]) for_each(u, par[head[v]], lr);
    } else { // 登る経路は左右逆で結合したいので（上が左なため）
      lr.emplace_back(max(vid[head[u]], vid[v]), vid[u], false); // 閉区間
      if(head[u] != head[v]) for_each(par[head[u]], v, lr);
    }
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

struct State {
  int sum, mxs, lmxs, rmxs;
  State():sum(0), mxs(-inf), lmxs(-inf), rmxs(-inf){}
  State(int sum, int mxs, int lmxs, int rmxs)
    :sum(sum), mxs(mxs), lmxs(lmxs), rmxs(rmxs){}
  State(int c, int sz) {
    int d = (c > 0 ? c*sz : c);
    sum = c*sz, mxs = lmxs = rmxs = d;
  }
  State operator + (State s) {
    State res;
    res.sum = sum + s.sum;
    res.mxs = max(mxs, s.mxs, rmxs + s.lmxs);
    res.lmxs = max(lmxs, sum + s.lmxs);
    res.rmxs = max(rmxs + s.sum, s.rmxs);
    return res;
  }
  State operator ~ () {
    State res = *this;
    swap(res.lmxs, res.rmxs);
    return res;
  }
};

// Lazy-evaluated Segment Tree
struct SegmentTree
{
  vector<State> sum;
  vector<int> lazy;
  int sz;
  SegmentTree(){}
  SegmentTree(int n)
  {
    sz = 1; while(sz < n) sz *= 2;
    sum.resize(2*sz-1, State());
    lazy.resize(2*sz-1, -inf);
  }
  inline void lazy_evaluate(int k, int l, int r)
  {
    if(lazy[k] == -inf) return;
    sum[k] = State(lazy[k], r - l);
    if(r - l > 1) {
      lazy[2*k+1] = lazy[k];
      lazy[2*k+2] = lazy[k];
    }
    lazy[k] = -inf;
  }
  void update(int a, int b, int x, int k, int l, int r)
  {
    lazy_evaluate(k, l, r);
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) {
      lazy[k] = x;
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
  State query(int a, int b, int k, int l, int r)
  {
    lazy_evaluate(k, l, r);
    if(r <= a || b <= l) return State();
    if(a <= l && r <= b) return sum[k];
    return query(a, b, 2*k+1, l, (l+r)/2) + query(a, b, 2*k+2, (l+r)/2, r);
  }
  State query(int a, int b)
  {
    return query(a, b, 0, 0, sz);
  }
};

int n, q;
vector<int> w;
HLDT hldt;
SegmentTree seg;

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  cin >> n >> q;
  w.resize(n);
  hldt = HLDT(n);
  seg = SegmentTree(n);
  rep(i, n) cin >> w[i];
  rep(i, n-1) {
    int s, e;
    cin >> s >> e;
    --s, --e;
    hldt.add_edge(s, e);
  }
  hldt.build();
  rep(i, n) {
    vector< tuple<int, int, bool> > lr;
    hldt.for_each(i, i, lr);
    for(auto p : lr) {
      int x, y; bool z;
      tie(x, y, z) = p;
      seg.update(x, y + 1, w[i]);
    }
  }

  rep(i, q) {
    int t, a, b, c;
    cin >> t >> a >> b >> c;
    --a, --b;
    vector< tuple<int, int, bool> > lr;
    hldt.for_each(a, b, lr);
    if(t == 1) {
      for(auto p : lr) {
	int x, y; bool z;
	tie(x, y, z) = p;
	seg.update(x, y + 1, c);
      }
    } else if(t == 2) {
      State ds, us;
      for(auto p : lr) {
	int x, y; bool z;
	tie(x, y, z) = p;
	if(z) ds = seg.query(x, y + 1) + ds; // 下から順番に処理していくので
	else us = seg.query(x, y + 1) + us;
      }
      cout << (~us + ds).mxs << endl;
    }
  }

  return 0;
}
