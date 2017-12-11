#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct MillerRabin {
  mt19937 mt;
  const vector<ll> witnesses = {2, 7, 61}; // n < 2^32
  MillerRabin() {mt.seed(1333);}
  ll modPow(ll x, ll n, ll mod) {
    ll res = 1;
    while(n > 0) {
      if(n&1) (res *= x) %= mod;
      n >>= 1;
      (x *= x) %= mod;
    }
    return res;
  }
  bool isPrime(ll n) {
    if(n == 2) return true;
    if(n < 2 || !(n&1)) return false;
    ll d = n-1;
    ll s = 0;
    while(!(d&1)) d >>= 1, ++s;
    /*
      for(auto&& a : witnesses) {
      if(a == n) return true;
      if(modPow(a, d, n) == 1) continue;
      bool flag = true;
      for(ll r = 0; r < s; r++) {
	if(modPow(a, d*(1ll<<r), n) == n-1) {
	  flag = false;
	  break;
	}
      }
      if(flag) return false;
    }
    */
    for(int i = 0; i < 2; i++) {
      ll a = mt()%(n-4) + 2;
      bool flag = true;
      for(ll r = 0; r < s; r++) {
	if(modPow(a, d*(1ll<<r), n) == n-1) {
	  flag = false;
	  break;
	}
      }
      if(flag) return false;
    }
    return true;
  }
};

struct Rho {
  mt19937 mt;
  MillerRabin mr;
  ll c;
  Rho() {mt.seed(1333);}
  ll f(ll x, ll n) {return (x*x + c)%n;}
  ll get_divisor(ll n) {
    if(n == 4) return 2;
    c = mt() % n;
    ll x = mt() % n;
    ll y = x;
    ll d = 1;
    while(d == 1) {
      x = f(x, n);
      y = f(f(y, n), n);
      d = __gcd(llabs(x-y), n);
    }
    if(d == n) return -1;
    return d;
  }
  void prime_factor(ll n, vector<ll>& v) {
    if(n <= 1) return;
    if(mr.isPrime(n)) {v.push_back(n); return;}
    ll d = -1;
    while(d == -1) d = get_divisor(n);
    prime_factor(d, v);
    prime_factor(n/d, v);
  }
};

Rho rho;

int main() {
  ll t;
  cin >> t;
  while(t--) {
    ll n;
    cin >> n;
    vector<ll> pf;
    rho.prime_factor(n, pf);
    sort(pf.begin(), pf.end());
    for(int i = 0; i < (int)pf.size(); i++) {
      if(i) cout << " ";
      cout << pf[i];
    }
    cout << endl;
  }
  return 0;
}
