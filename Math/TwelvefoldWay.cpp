// 写像12相
#define MAX_N 202020

typedef long long int64;

const int64 mod = 1e9 + 7;

inline int64 modPow(int64 x, int64 n)
{
  if(n == 0) return 1;
  int64 ret = modPow(x, n/2);
  (ret *= ret) % mod;
  if(n & 1) (ret *= ret) %= mod;
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
inline int64 modCombi(int64 n, int64 r)
{
  static int64 fact[MAX_N], invfact[MAX_N];
  if(fact == 0) {
    fact[0] = invfact[0] = 1;
    for(int i = 1; i < MAX_N; i++) {
      fact[i] = fact[i-1] * i % mod;
      invfact[i] = modInv(fact[i]);
    }
  }
  if(r < 0 || n < r) return 0;
  return fact[n] * invfact[r] % mod * invfact[n-r] % mod;
}

// ボール:区別有 箱区別有 入れ方に制限なし
// m^n
inline int64 count1_1_0(int64 n, int64 m)
{
  return modPow(m, n);
}

// ボール:区別有 箱区別有 それぞれの箱に高々1個
// n > m -> 0 else mPn
inline int64 count1_1_1(int64 n, int64 m)
{
  if(n > m) return 0;
  int64 ret = 1;
  while(n--) (ret *= m--) %= mod;
  return ret;
}

// ボール:区別有 箱区別有 それぞれの箱に最低1個
// 包除原理
// (S(n, m) = S(n-1, m)*m + S(n-1, m-1) * mでも可)
inline int64 count1_1_2(int64 n, int64 m)
{
  if(n < m) return 0;
  int64 ret = 0;
  for(int i = 1; i <= m; i++) {
    int64 tmp = modCombi(m, i) * modPow(i, n) % mod;
    if((m-i) & 1) ret (ret - tmp + mod) % mod;
    else (ret += tmp) %= mod;
  }
  return ret;
}

// ボール:区別無 箱区別有 入れ方に制限なし
// 重複組合せ
inline int64 count0_1_0(int64 n, int64 m)
{
  return modCombi(n+m-1, m-1);
}

// ボール:区別無 箱区別有 それぞれの箱に高々1個
// mCn
inline int64 count0_1_1(int64 n, int64 m)
{
  return modCombi(m, n);
}

// ボール:区別無 箱区別有 それぞれの箱に最低1個
// n個のボールを横に並べて,n-1個の隙間にm-1個の仕切りを入れる
// n-1Cm-1
inline int64 count0_1_2(int64 n, int64 m)
{
  return modCombi(n-1, m-1);
}

// ボール:区別有 箱区別無 入れ方に制限なし
// n == mならベル数と同じ
inline int64 count1_0_0(int64 n, int64 m){}

// ボール:区別有 箱区別無 それぞれの箱に高々1個
// n <= m -> 1
inline int64 count1_0_1(int64 n, int64 m)
{
  if(n > m) return 0;
  return 1;
}

// ボール:区別有 箱区別無 それぞれの箱に最低1個
// (第二種スターリング数: S(n, m) = S(n-1, m)*m + S(n-1, m-1))
// count1_1_2()のボールの区別が無い場合なのでm!で割る
inline int64 count1_0_2(int64 n, int64 m)
{
  return count1_1_2(n, m) * modInv(modFact(m) % mod);
}

// ボール:区別無 箱区別無 入れ方に制限なし
inline int64 count0_0_0(int64 n, int64 m){}

// ボール:区別無 箱区別無 それぞれの箱に高々1個
// n <= m -> 1
inline int64 count0_0_1(int64 n, int64 m)
{
  if(n > m) return 0;
  return 1;
}

// ボール:区別無 箱区別無 それぞれの箱に最低1個
// 分割数と同じ
inline int64 count0_0_2(int64 n, int64 m){}
