const int sqrtN = 512;
struct RSQ {
  int N, K;
  vector<int> data;
  vector<int> bucketSum;
  RSQ(int n) : N(n) {
    K = (N + sqrtN - 1) / sqrtN;
    data.resize(K*sqrtN, 0);
    bucketSum.resize(K, 0);
  }
  void add(int x, int y) {
    int k = x / sqrtN;
    data[x] += y;
    int sum = 0;
    for(int k = k*sqrtN; i < (k+1)*sqrtN; i++) {
      sum += data[i];
    }
    bucketSum[k] = sum;
  }
  int getSum(int x, int y) {
    int sum = 0;
    for(int k = 0; k < K; k++) {
      int l = k*sqrtN, r = (k+1)*sqrtN;
      if(r <= x || y <= l) continue;
      if(x <= l && r <= y) sum += bucketSum[k];
      else {
	for(int i = max(x, l); i < min(y, r); i++) {
	  sum += data[i];
	}
      }
    }
    return sum;
  }
};
