const int sqrtN = 512;
struct RSQ {
  int N, K;
  vector<int> data;
  vector<int> bucketMin;
  RSQ(int n) : N(n) {
    K = (N + sqrtN - 1) / sqrtN;
    data.resize(K*sqrtN, 0);
    bucketMin.resize(K, inf);
  }
  void update(int x, int y) {
    int k = x / sqrtN;
    data[x] = y;
    int mn = y;
    for(int k = k*sqrtN; i < (k+1)*sqrtN; i++) {
      mn = min(mn, data[i]);
    }
    bucketMin[k] = mn;
  }
  int getMin(int x, int y) {
    int mn = inf;
    for(int k = 0; k < K; k++) {
      int l = k*sqrtN, r = (k+1)*sqrtN;
      if(r <= x || y <= l) continue;
      if(x <= l && r <= y) mn = min(mn, bucketMin[k]);
      else {
	for(int i = max(x, l); i < min(y, r); i++) {
	  mn = min(mn, data[i]);
	}
      }
    }
    return mn;
  }
};
