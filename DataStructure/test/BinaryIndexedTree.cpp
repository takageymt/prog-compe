// 反転数
#include <bits/stdc++.h>

using namespace std;

// Binary Indexed Tree (1 indexed)
struct BIT {
  vector<int> data;
  BIT(int n):data(n+1, 0){}
  int sum(int k) {
    int ret = 0;
    while(k > 0) {
      ret += data[k];
      k -= k & -k;
    }
    return ret;
  }
  void add(int k, int x) {
    while(k < data.size()) {
      data[k] += x;
      k += k & -k;
    }
  }
};

const int MAX_N = 100000;

int main() {

  int n;
  int a[MAX_N];

  cin >> n;
  for(int i = 0; i < n; i++) cin >> a[i];

  BinaryIndexedTree bit(n);

  int cnt = 0;
  for(int i = 0; i < n; i++) {
    cnt += bit.sum(i+1);
    bit.add(a[i], 1);
  }
  cout << cnt << endl;

  return 0;
}
