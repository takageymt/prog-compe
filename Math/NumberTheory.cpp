typedef long long int64;

const int64 mod = 1e9 + 7LL;

int64 fact[1000010], invfact[1000010];

int64 power(int64 a, int64 x)
{
  if(x == 0) return 1;
  int64 ret = pow(a, x/2LL, mod);
  ret = (ret*ret) % mod;
  if(x & 1) ret = (ret*a) % mod;
  return ret;
}

int64 inverse(int64 a)
{
  return power(a, mod-2);
}

void factorial()
{
  fact[0] = invfact[0] = 1LL;
  for(int i = 1; i < 1000000; i++) {
    fact[i] = (fact[i-1]*i) % mod;
    invfact[i] = inverse(fact[i]);
  }
}

int64 combination(int64 n, int64 r)
{
  if(r < 0 || n < r) return 0LL;
  return (((fact[n]*invfact[r]) % mod)*invfact[n-r]) % mod;
}

//--------------------------------------------------------

int64 extgcd(int64 a, int64 b, int64 &x, int64 &y)
{
  int64 d = a;
  if(b != 0) d = extgcd(b, a % b, y, x), y -= (a / b) * x;
  else x = 1, y = 0;
  return d;
}

int64 modinv(int64 a, int64 m)
{
  int64 x, y;
  extgcd(a, m, x, y);
  return (m + x % m) % m;
}

int64 f[200020];
void fact()
{
  f[0] = 1;
  for(int i = 1; i < 200020; i++) {
    f[i] = f[i-1] * i % mod;
  }
}

int64 combi(int64 n, int64 k, int64 m)
{
  if(k < 0 || n < k) return 0;
  return f[n] * modinv(f[k] * f[n - k] % m, m) % m;
}
 
