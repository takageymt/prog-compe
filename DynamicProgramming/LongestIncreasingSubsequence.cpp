#define MAX_N 10000
int LIS(int n, int a[], int dp[]) {
  int res = 0;
  for(int i = 0; i < n; i++) {
    dp[i] = 1;
    for(int j = 0; j < i; j++) {
      if(a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
    }
    res = max(res, dp[i]);
  }
  return res;
}

int LIS_fast(int n, int a[], int dp[]) {
  const int inf = 1<<25;
  fill(dp, dp + n, inf);
  for(int i = 0; i < n; i++) {
    *lower_bound(dp, dp + n, a[i]) = a[i];
  }
  return lower_bound(dp, dp + n, inf) - dp;
}
