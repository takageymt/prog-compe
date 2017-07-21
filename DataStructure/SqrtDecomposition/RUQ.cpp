const int sqrtN = 512;
struct RUQ {
  int N, K;
  vector<int> data;
  vector<bool> lazyFlag;
  vector<int> lazyUpdate;
  RSQ(int n) : N(n) {
    K = (N + sqrtN - 1) / sqrtN;
    data.resize(K*sqrtN, 0);
    lazyFlag.resize(K, false);
    lazyUpdate.resize(K, 0);
  }
  void push(int k) {
    if(lazyFlag[k]) {
      lazyFlag[k] = false;
      for(int i = k*sqrtN; i < (k+1)*sqrtN; i++) {
	data[i] = lazyUpdate[k];
      }
    }
  }
  void update(int s, int t, int x) {
    for(int k = 0; k < K; k++) {
      int l = k*sqrtN, r = (k+1)*sqrtN;
      if(r <= s || t <= l) continue;
      if(s <= l && r <= t) {
	lazyFlag[k] = true;
	lazyUpdate[k] += x;
      } else {
	push(k);
	for(int i = max(x, l); i < min(y, r); i++) {
	  data[i] = x;
	}
      }
    }
  }
  int get(int i) {
    int k = i / sqrtN;
    push(k);
    return data[i];
  }
};
