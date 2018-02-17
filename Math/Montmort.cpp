#include <bits/stdc++.h>

using namespace std;

#define int long long

using ull = unsigned long long;

const ull mod = 1777777777;

ull mpow(ull a, ull n) {
  ull res = 1;
  while(n > 0) {
    if(n%2 == 1) (res *= a) %= mod;
    (a *= a) %= mod;
    n /= 2;
  }
  return res;
}

ull minv(ull a) {
  return mpow(a, mod-2);
}

ull nCr(ull n, ull r) {
  ull res = 1;
  for(ull i = 0; i < r; ++i) (res *= (n-i+mod)%mod) %= mod;
  for(ull i = 1; i <= r; ++i) (res *= minv(i)) %= mod;
  return res;
}

ull Montmort(ull n) {
  // 完全順列の数
  ull x = 1;
  for(ull i = 1; i <= n; ++i) (x *= (i)) %= mod;
  ull ans = 0;
  for(ull i = 2; i <= n; ++i) {
    (x *= minv(i)) %= mod;
    if(i%2 == 1) (ans += (mod-x)) %= mod;
    else (ans += x) %= mod;
  }
  return ans;
}
