// aoj2022
#include <bits/stdc++.h>

using namespace std;

bool cmp(const string& left, const string& right)
{
  if(left.size() != right.size()) return left.size() < right.size();
  for(int i = 0; i < left.size(); i++) {
    if(left[i] != right[i]) return left[i] < right[i];
  }
  return false;
}

string addstr(string s, string t)
{
  for(int i = 0; i < s.size(); i++) {
    if(s.substr(i) == t.substr(0, s.size()-i)) return t.substr(s.size()-i);
  }
  return t;
}

string inf()
{
  string ret = "";
  for(int i = 0; i < 1000; i++) ret += "~";
  return ret;
}

int main()
{
  int N;
  while(cin >> N, N) {
    vector<string> S(N);
    for(int i = 0; i < N; i++) cin >> S[i];
    sort(S.begin(), S.end(), cmp);
    S.erase(unique(S.begin(), S.end()), S.end());

    vector<string> T;
    for(int i = 0; i < S.size(); i++) {
      bool flag = false;
      for(int j = i+1; j < S.size(); j++) {
	if(S[j].find(S[i]) != string::npos) flag = true;
	if(flag) break;
      }
      if(!flag) T.push_back(S[i]);
    }

    int M = T.size();
    string add[11][11];
    for(int i = 0; i < M; i++) {
      for(int j = 0; j < M; j++) {
	add[i][j] = addstr(T[i], T[j]);
      }
    }

    string dp[1<<11][11];
    fill(dp[0], dp[1<<11], inf());
    for(int i = 0; i < M; i++) dp[1<<i][i] = T[i];

    string ans = inf();
    for(int i = 0; i < 1<<M; i++) {
      for(int j = 0; j < M; j++) {
	if(dp[i][j] == inf()) continue;
	if(i == (1<<M)-1) {
	  ans = min(ans, dp[i][j], cmp);
	}
	for(int k = 0; k < M; k++) {
	  if((i >> k) & 1) continue;
	  dp[i|(1<<k)][k] = min(dp[i|(1<<k)][k], dp[i][j] + add[j][k], cmp);
	}
      }
    }

    cout << ans << endl;
  }
  return 0;
}
