#define MAX_LEN 100
int LongenstCommonSubsequence(string a, string b, int dp[MAX_LEN][MAX_LEN])
{
  memset(dp, 0, sizeof(dp));
  for(int i = 1; i <= a.size(); i++) {
    for(int j = 1; j <= b.size(); j++) {
#define max3(a, b, c) max((a), max((b), (c)))
      dp[i][j] = max3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1] + (a[i-1] == b[i-1]));
    }
  }
  return dp[a.size()][b.size()];
}
