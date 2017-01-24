// 第二種スターリング数
// ボール:区別有 箱:区別無 それぞれの箱に最低1個
// S(n,m) = S(n-1, m)*m + S(n-1, m-1)
const long long mod = 1e9 + 7;

long long dp[1010][1010];

long long Stirling2(int n, int m)
{
  if(n < m) return 0;

  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      (dp[i][j] += dp[i-1][j]*j + dp[i-1][j-1]) %= mod;
    }
  }

  return dp[n][m];
}
