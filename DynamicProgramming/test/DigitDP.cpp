// TDPC - E
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) begin(v), end(v)
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, s, n) for(int i = (int)(s); i < (int)(n); i++)

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int D, n;
  string N;
  cin >> D >> N;
  n = N.size();

  int dp[10010][2][101]{{{}}};
  dp[0][0][0] = 1;
  rep(i, n) rep(j, 2) rep(k, D) {
    int lim = j ? 9 : N[i]-'0';
    rep(d, lim+1) {
      dp[i + 1][j || d<lim][(k+d)%D] += dp[i][j][k];
      dp[i + 1][j || d<lim][(k+d)%D] %= mod;
    }
  }

  int ans = 0;
  rep(j, 2) (ans += dp[n][j][0]) %= mod;

  cout << max(0LL, ans-1) << endl;

  return 0;
}
