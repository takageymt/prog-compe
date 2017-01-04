#include <bits/stdc++.h>

using namespace std;

#define int long long
#define FR first
#define SC second
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, f, n) for(int i = (int)(f); i < (int)(n); i++)
#define each(a, b) for(auto& a : b)

typedef pair<int, int> P;

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

#define MAX_N 1000000
bool is_prime[MAX_N+1];
int phi[MAX_N+1];
void euler_phi()
{
  for(int i = 0; i <= MAX_N; i++) {
    is_prime[i] = true;
    phi[i] = i;
  }
  for(int i = 2; i <= MAX_N; i++) {
    if(is_prime[i]) {
      phi[i] -= phi[i] / i;
      for(int j = i+i; j <= MAX_N; j+=i) {
	is_prime[j] = false;
	phi[j] -= phi[j] / i;
      }
    }
  }
}

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  euler_phi();

  int farey[MAX_N+1];
  farey[1] = 2;
  for(int i = 2; i <= MAX_N; i++) farey[i] = farey[i-1] + phi[i];

  int t; cin >> t;
  while(t--) {
    int n; cin >> n;
    cout << farey[n] << endl;
  }
  
  return 0;
}
