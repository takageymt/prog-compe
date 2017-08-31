#include <bits/stdc++.h>
using namespace std;

int LongestCommonSubsequence(string X, string Y);

int ShortestCommonSuperstring1(string X, string Y) {
  return X.size()+Y.size()-LongestCommonSubsequence(X, Y);
}

int ShortestCommonSuperstring2(string X, string Y) {
  int n = X.size(), m = Y.size();
  int dp[n+1][m+1];
  for(int i = 0; i <= n; i++) {
    for(int j = 0; j <= m; j++) {
      if(!i) dp[i][j] = j;
      else if(!j) dp[i][j] = i;
      else if(X[i-1] == Y[j-1]) dp[i][j] = dp[i-1][j-1]+1;
      else dp[i][j] = min(dp[i-1][j], dp[i][j-1])+1;
    }
  }
  return dp[n][m];
}
