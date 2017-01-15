// 桁DP template
// A以下の非負整数の総数を求める
int CountUp(string A)
{
  int n = A.size();

  // dp[i][j] := i番目の要素の時点でA以下確定j=1/未定j=0の場合の総数
  int dp[n+1][2]{{}};
  dp[0][0][0] = 1;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < 2; j++) {
      int lim = j ? 9 : N[i]-'0';
      for(int d = 0; d < lim+1; d++) {
	dp[i + 1][j || d<lim] += dp[i][j][k];
	// dp[i + 1][j || d<lim][(k+d)%D] %= mod;
      }
    }
  }

  int ans = 0;
  rep(j, 2) (ans += dp[n][j]) %= mod;

  return ans;
}
