#include <bits/stdc++.h>

using namespace std;

#define int long long

// アイテムの種類数 N とそれぞれの価値 V_i がどちらも 50 以下のとき,
// 重みの制約によらず, 個数制限付きナップザックを O(N^2MAX_V^2logMAX_V)
// で解くことができる.

// ある二つのアイテム i,j がそれぞれ C 個以上残っているとき,
// W_i*V_j < W_j*V_i (V_i,V_j<=C) ならアイテム i を選ぶべき.
// なぜなら, どちらも V_i*V_j (V_j*V_i) だけ価値を増やすので,
// それならば軽い方を取るべきだから.

const int MAX_N = 55;
const int MAX_V = 55;

int N, X;
int v[MAX_N], w[MAX_N], l[MAX_N];

int dp[MAX_N][MAX_N*MAX_V];

signed main() {
  cin >> N >> X;
  vector<int> v(N), w(N), l(N);
  for(int i = 0; i < N; ++i) cin >> v[i] >> w[i] >> l[i];
  vector<tuple<double, int, int, int> > vec;
  for(int i = 0; i < N; ++i) {
    if(l[i] > MAX_V) {
      vec.emplace_back((double)v[i]/w[i], v[i], w[i], l[i]-MAX_V);
      l[i] = MAX_V;
    }
  }
  sort(vec.rbegin(), vec.rend());

  fill(dp[0], dp[MAX_N], LLONG_MAX/2);
  dp[0][0] = 0;
  for(int i = 0; i < N; ++i) {
    int lim = l[i];
    for(int k = 0; lim > 0; ++k) {
      int num = min(lim, 1LL<<k);
      for(int j = MAX_N*MAX_V-v[i]*num; j >= 0; --j) {
	dp[i+1][j+v[i]*num] = min(dp[i+1][j+v[i]*num], dp[i][j]+w[i]*num);
      }
      lim -= num;
    }
  }

  int ans = 0;
  for(int i = 0; i < MAX_N*MAX_V; ++i) {
    int tmp = i;
    int x = X-dp[N][i];
    for(int j = 0; j < (int)vec.size(); ++j) {
      double e;
      int a, b, c;
      tie(e, a, b, c) = vec[j];
      if(x >= b) {
	int num = min(c, x/b);
	tmp += num * a;
	x -= num;
      }
    }
    if(tmp > ans) ans = tmp;
  }

  cout << ans << endl;

  return 0;
}
