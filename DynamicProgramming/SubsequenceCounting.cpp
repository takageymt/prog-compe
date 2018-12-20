#include <bits/stdc++.h>

using namespace std;

int main() {
  const int mod = 1e9 + 7;
  auto add = [mod](int& x, int y) {
    x += y;
    if(x >= mod) x -= mod;
  };

  string s;
  cin >> s;
  int n = s.size();

  vector<vector<int> > nxt(26, vector<int>(n+1, n));
  for(int i = n-1; i >= 0; --i) {
    for(int j = 0; j < 26; ++j) nxt[j][i] = nxt[j][i+1];
    nxt[s[i]-'a'][i] = i;
  }

  vector<int> dp(n+1, 0); // dp[i] := no. of subseq. in [0,i) with s[i-1]
  dp[0] = 1;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < 26; ++j) {
      if(nxt[j][i] == n) continue;
      add(dp[nxt[j][i]+1], dp[i]);
    }
  }
  int ans = 0;
  for(int i = 0; i <= n; ++i) add(ans, dp[i]);
  cout << ans << endl;

  return 0;
}
