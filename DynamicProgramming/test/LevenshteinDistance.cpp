#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) (v).begin(), (v).end()
#define reps(i, m, n) for(int i = (int)(m); i < (int)(n); i++)
#define rep(i, n) reps(i, 0, n)

template<class T1, class T2> void chmin(T1 &a, T2 b){if(a>b)a=b;}
template<class T1, class T2> void chmax(T1 &a, T2 b){if(a<b)a=b;}

typedef pair<int, int> Pi;
typedef tuple<int, int, int> Ti;
typedef vector<int> vint;

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

#define MAX_LEN 100
int dp[MAX_LEN][MAX_LEN];
int LevenshteinDistance(string a, string b) {
  memset(dp, 0, sizeof(dp));
  for(int i = 0; i <= (int)a.size(); i++) dp[i][0] = i;
  for(int i = 0; i <= (int)b.size(); i++) dp[0][i] = i;

  for(int i = 1; i <= (int)a.size(); i++) {
    for(int j = 1; j <= (int)b.size(); j++) {
      dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + (a[i-1] != b[j-1])});
    }
  }
  return dp[a.size()][b.size()];
}


signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  string s, t;
  cin >> s >> t;
  cout << LevenshteinDistance(s, t) << endl;

  return 0;
}
