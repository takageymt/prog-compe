#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
  const int sqrtN = 512;
  const ll inf = (1LL<<31)-1;
  int n, q;
  cin >> n >> q;
  int bucket_sz = (n+sqrtN-1)/sqrtN;
  vector<ll> a(n, inf);
  vector<ll> bucketMin(bucket_sz, inf);
  vector<ll> bucketUp(bucket_sz, 0);
  vector<bool> bucketFlag(bucket_sz, false);
  auto push = [&](int k) {
    bucketFlag[k] = false;
    int l = k*sqrtN, r = (k+1)*sqrtN;
    for(int i = l; i < r; ++i) {
      a[i] = bucketUp[k];
    }
  };
  auto update = [&](int s, int t, int x) {
    for(int i = 0; i < bucket_sz; ++i) {
      int l = i*sqrtN, r = (i+1)*sqrtN;
      if(r <= s || t <= l) continue;
      if(s <= l && r <= t) {
	bucketMin[i] = x;
	bucketUp[i] = x;
	bucketFlag[i] = true;
      } else {
	if(bucketFlag[i]) push(i);
	for(int j = max(s, l); j < min(t, r); ++j) {
	  a[j] = x;
	}
	ll mn = inf;
	for(int j = l; j < r; ++j) mn = min(mn, a[j]);
	bucketMin[i] = mn;
      }
    }
  };
  auto query = [&](int s, int t) -> ll {
    ll mn = inf;
    for(int i = 0; i < bucket_sz; ++i) {
      int l = i*sqrtN, r = (i+1)*sqrtN;
      if(r <= s || t <= l) continue;
      if(s <= l && r <= t) {
	mn = min(mn, bucketMin[i]);
      } else {
	if(bucketFlag[i]) push(i);
	for(int j = max(s, l); j < min(t, r); ++j) {
	  mn = min(mn, a[j]);
	}
      }
    }
    return mn;
  };
  while(q--) {
    int t;
    cin >> t;
    if(t == 0) {
      ll s, t, x;
      cin >> s >> t >> x;
      update(s, t+1, x);
    } else {
      ll s, t;
      cin >> s >> t;
      cout << query(s, t+1) << endl;
    }
  }

  return 0;
}
