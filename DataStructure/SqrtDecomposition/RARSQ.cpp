#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
  const int sqrtN = 512;
  int n, q;
  cin >> n >> q;
  int bucket_sz = (n+sqrtN-1)/sqrtN;
  vector<ll> a(n, 0);
  vector<ll> bucketSum(bucket_sz, 0);
  vector<ll> bucketAdd(bucket_sz, 0);
  auto update = [&](int s, int t, int x) {
    for(int i = 0; i < bucket_sz; ++i) {
      int l = i*sqrtN, r = (i+1)*sqrtN;
      if(r <= s || t <= l) continue;
      if(s <= l && r <= t) bucketAdd[i] += x;
      else {
	for(int j = max(s, l); j < min(t, r); ++j) {
	  a[j] += x;
	}
	ll sum = 0;
	for(int j = l; j < r; ++j) sum += a[j];
	bucketSum[i] = sum;
      }
    }
  };
  auto query = [&](int s, int t)->ll{
    ll res = 0;
    for(int i = 0; i < bucket_sz; ++i) {
      int l = i*sqrtN, r = (i+1)*sqrtN;
      if(r <= s || t <= l) continue;
      if(s <= l && r <= t) res += bucketSum[i]+bucketAdd[i]*sqrtN;
      else {
	for(int j = max(s, l); j < min(t, r); ++j) {
	  res += a[j]+bucketAdd[i];
	}
      }
    }
    return res;
  };
  while(q--) {
    ll c, s, t;
    cin >> c >> s >> t;
    if(c == 0) {
      ll x; cin >> x;
      update(s-1, t, x);
    } else {
      cout << query(s-1, t) << endl;
    }
  }

  return 0;
}
