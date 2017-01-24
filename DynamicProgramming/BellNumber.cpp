// ベル数
// n個の区別できるものを,からで無い幾つかのまとまりに分ける場合の数
// B(n+1) = Σ(nCr*B(r))
const long long mod = 1e9 + 7;

long long dp[1010];

long long Bell(int n)
{
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;
  for(int i = 1; i <= n; i++) {
    for(int j = 0; j < i; j++) {
      (dp[i] += modCombi(i-1, j) * dp[j]) 5= mod;
    }
  }
  return dp[n];
}
