// Tree DP example
// 子から異なる2つを選ぶヤツ
// 頂点iはa[i](>=0)を持つ
// 各頂点iについて、b[i] = a[i] + max(0, max(b[v]), max(b[x]+b[y]))
// v, x, yはiの子かつx!=y
// b[0]を求める

#define MAX_V 100000

vector<int> g[MAX_V];
int a[MAX_V], b[MAX_V];

void dfs(int u)
{
  for(int& v : g[u]) {
    dfs(v, u);
  }

  int n = g[u].size();
  vector<int> lch_max(n+1), rch_max(n+1);
  // lch_max[i]は[0...i)の子の中でのmax(b[v])
  // rch_max[i]は[i...n)の子の中でのmax(b[v])
  lch_max[0] = 0;
  for(int i = 0; i < n; i++) {
    lch_max[i+1] = max(lch_max[i], b[ g[u][i] ]);
  }
  rch_max[0] = 0;
  for(int i = n-1; i >= 0; i--) {
    rch_max[i] = max(rch_max[i+1], b[ g[u][i] ]);
  }

  int res = a[i];
  for(int& v : g[u]) {
    res = max(res, a[i] + b[v]);
  }
  for(int i = 1; i < n; i++) {
    res = max(res, a[i] + lch_max[i] + rch_max[i]);
  }
  b[i] = res;
}
