#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) (v).begin(), (v).end()
#define resz(v, ...) (v).clear(), (v).resize(__VA_ARGS__)
#define reps(i, m, n) for(int i = (int)(m); i < (int)(n); i++)
#define rep(i, n) reps(i, 0, n)

template<class T1, class T2> void chmin(T1 &a, T2 b){if(a>b)a=b;}
template<class T1, class T2> void chmax(T1 &a, T2 b){if(a<b)a=b;}

using Pi = pair<int, int>;
using Tapris = tuple<int, int, int>;
using vint = vector<int>;

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

signed main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  const int sqrtN = 512;

  int n;
  cin >> n;
  vint a(n), b(n);
  rep(i, n) cin >> a[i];
  rep(i, n) cin >> b[i];

  int bucket_sz = (n+sqrtN-1)/sqrtN;
  vint bucketFlagA(bucket_sz, 0);
  vint bucketFlagB(bucket_sz, 0);
  vint bucketMinA(bucket_sz, inf);
  vint bucketMinB(bucket_sz, inf);

  rep(i, n) chmin(bucketMinA[i/sqrtN], a[i]);
  rep(i, n) chmin(bucketMinB[i/sqrtN], b[i]);

  auto push = [&](int k) {
    assert(bucketFlagA[k]+bucketFlagB[k] < 2);
    //if(!bucketFlagA[k]) return;
    if(bucketFlagA[k]) {
      reps(i, k*sqrtN, min(n, (k+1)*sqrtN)) a[i] = b[i];
      bucketMinA[k] = bucketMinB[k];
      bucketFlagA[k] = 0;
    } else if(bucketFlagB[k]) {
      reps(i, k*sqrtN, min(n, (k+1)*sqrtN)) b[i] = a[i];
      bucketMinB[k] = bucketMinA[k];
      bucketFlagB[k] = 0;
    }
  };
  auto setA = [&](int y, int z) {
    int k = y/sqrtN;
    push(k);
    a[y] = z;
    bucketMinA[k] = inf;
    reps(i, k*sqrtN, min(n, (k+1)*sqrtN)) chmin(bucketMinA[k], a[i]);
  };
  auto setB = [&](int y, int z) {
    int k = y/sqrtN;
    push(k);
    b[y] = z;
    bucketMinB[k] = inf;
    reps(i, k*sqrtN, min(n, (k+1)*sqrtN)) chmin(bucketMinB[k], b[i]);
  };
  auto getA = [&](int y, int z) {
    int res = inf;
    rep(i, bucket_sz) {
      int l = i*sqrtN, r = (i+1)*sqrtN;
      if(r <= y || z <= l) continue;
      if(y <= l && r <= z) {
	if(bucketFlagA[i]) chmin(res, bucketMinB[i]);
	else chmin(res, bucketMinA[i]);
      } else {
	push(i);
	reps(j, max(l, y), min(r, z)) chmin(res, a[j]);
      }
    }
    return res;
  };
  auto getB = [&](int y, int z) {
    int res = inf;
    rep(i, bucket_sz) {
      int l = i*sqrtN, r = (i+1)*sqrtN;
      if(r <= y || z <= l) continue;
      if(y <= l && r <= z) {
	if(bucketFlagB[i]) chmin(res, bucketMinA[i]);
	else chmin(res, bucketMinB[i]);
      } else {
	push(i);
	reps(j, max(l, y), min(r, z)) chmin(res, b[j]);
      }
    }
    return res;
  };
  auto copyA = [&]() {
    rep(i, bucket_sz) {
      if(!bucketFlagB[i]) bucketFlagA[i] = 1;
    }
  };
  auto copyB = [&]() {
    rep(i, bucket_sz) {
      if(!bucketFlagA[i]) bucketFlagB[i] = 1;
    }
  };
  int q;
  cin >> q;
  while(q--) {
    int x, y, z;
    cin >> x >> y >> z;
    if(x == 1) setA(y-1, z);
    else if(x == 2) setB(y-1, z);
    else if(x == 3) cout << getA(y-1, z) << endl;
    else if(x == 4) cout << getB(y-1, z) << endl;
    else if(x == 5) copyA();
    else if(x == 6) copyB();
  }

  return 0;
}
