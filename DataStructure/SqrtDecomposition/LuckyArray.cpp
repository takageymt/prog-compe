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

  int n, m;
  cin >> n >> m;
  vint a(n);
  rep(i, n) cin >> a[i];

  // lucky number
  vint luckyNum = {
    4, 7, 44, 47, 74, 77,
    444, 447, 474, 477, 744, 747, 774, 777,
    4444, 4447, 4474, 4477, 4744, 4747, 4774, 4777,
    7444, 7447, 7474, 7477, 7744, 7747, 7774, 7777
  };
  vint flag(11111, 0);
  rep(i, luckyNum.size()) flag[luckyNum[i]] = 1;


  int bkt_sz = (n+sqrtN-1)/sqrtN;
  vector<vint> bktNum(bkt_sz, vint(11111, 0));
  vint bktAdd(bkt_sz, 0);
  vint bktCache(bkt_sz, 0);
  vector<bool> bktFlag(bkt_sz, false);

  rep(i, n) {
    bktNum[i/sqrtN][a[i]]++;
    bktCache[i/sqrtN] += flag[a[i]];
  }

  auto add = [&](int s, int t, int x) {
    rep(i, bkt_sz) {
      int l = i*sqrtN, r = (i+1)*sqrtN;
      if(r <= s || t <= l) {
	//bktFlag[i] = false;
	continue;
      }
      if(s <= l && r <= t) {
	bktAdd[i] += x;
	bktFlag[i] = true;
      } else {
	bktFlag[i] = true;
	reps(j, max(s, l), min(t, r)) {
	  bktNum[i][a[j]]--;
	  a[j] += x;
	  bktNum[i][a[j]]++;
	}
      }
    }
  };
  auto query = [&](int s, int t) {
    int res = 0;
    rep(i, bkt_sz) {
      int l = i*sqrtN, r = (i+1)*sqrtN;
      if(r <= s || t <= l) continue;
      if(s <= l && r <= t) {
	if(bktFlag[i]) {
	  int sum = 0;
	  rep(j, luckyNum.size()) {
	    int idx = luckyNum[j]-bktAdd[i];
	    if(idx >= 0) sum += bktNum[i][idx];
	  }
	  res += sum;
	  bktCache[i] = sum;
	  bktFlag[i] = false;
	} else {
	  res += bktCache[i];
	}
      } else {
	reps(j, max(s, l), min(t, r)) {
	  //if(count(all(luckyNum), a[j]+bktAdd[i])) res++;
	  res += flag[a[j]+bktAdd[i]];
	}
      }
    }
    return res;
  };

  while(m--) {
    string s;
    cin >> s;
    if(s == "add") {
      int l, r, d;
      cin >> l >> r >> d;
      add(l-1, r, d);
    } else {
      int l, r;
      cin >> l >> r;
      cout << query(l-1, r) << endl;
    }
  }

  return 0;
}
