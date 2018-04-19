#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
  const int sqrtN = 512;
  int n, q;
  cin >> n >> q;
  int bucket_sz = (n+sqrtN-1)/sqrtN;
  vector<ll> a(n, (1LL<<31)-1);
  vector<ll> bucketMin(bucket_sz, (1LL<<31)-1);
  auto update = [&](int k, int x) {
    a[k] = x;
    k /= sqrtN;
    int l = k*sqrtN, r = (k+1)*sqrtN;
    ll mn = x;
    for(int i = l; i < r; ++i) mn = min(mn, a[i]);
    bucketMin[k] = mn;
  };
  auto query = [&](int s, int t)->ll{
    ll res = (1LL<<31)-1;
    for(int i = 0; i < bucket_sz; ++i) {
      int l = i*sqrtN, r = (i+1)*sqrtN;
      if(r <= s || t <= l) continue;
      if(s <= l && r <= t) res = min(res, bucketMin[i]);
      else {
	for(int j = max(s, l); j < min(t, r); ++j) {
	  res = min(res, a[j]);
	}
      }
    }
    return res;
  };
  while(q--) {
    ll t, x, y;
    cin >> t >> x >> y;
    if(t == 0) update(x, y);
    else cout << query(x, y+1) << endl;
  }

  return 0;
}
