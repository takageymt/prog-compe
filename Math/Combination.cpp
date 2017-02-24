#define MAX_N 202020

typedef long long int64;

const int64 mod = 1e9 + 7;

inline int64 extgcd(int64 a, int64 b, int64 &x, int64 &y)
{
  int64 d = a;
  if(b != 0) d = extgcd(b, a % b, y, x), y -= (a / b) * x;
  else x = 1, y = 0;
  return d;
}

inline int64 modPow(int64 x, int64 n)
{
  if(n == 0) return 1;
  int64 ret = modPow(x, n/2);
  (ret *= ret) %= mod;
  if(n & 1) (ret *= x) %= mod;
  return ret;
}

inline int64 modInv(int64 a)
{
  return modPow(a, mod - 2);
}

inline int64 modFact(int n)
{
  int64 ret = 1;
  while(n > 1) (ret *= n--) %= mod;
  return ret;
}

inline int64 modComb(int64 n, int64 r)
{
  static int64 fact[MAX_N], invfact[MAX_N];
  if(fact[0] == 0) {
    fact[0] = invfact[0] = 1;
    for(int i = 1; i < MAX_N; i++) {
      fact[i] = fact[i-1] * i % mod;
      invfact[i] = modInv(fact[i]);
    }
  }
  if(r < 0 || n < r) return 0;
  return fact[n] * invfact[r] % mod * invfact[n-r] % mod;
}
