const int sqrtN = 512;
struct RSQ {
  int N, K;
  vector<int> data;
  vector<int> bucketAdd;
  RSQ(int n) : N(n) {
    K = (N + sqrtN - 1) / sqrtN;
    data.resize(K*sqrtN, 0);
    bucketAdd.resize(K, 0);
  }
  void add(int s, int t, int x) {
    for(int k = 0; k < K; k++) {
      int l = k*sqrtN, r = (k+1)*sqrtN;
      if(r <= s || t <= l) continue;
      if(s <= l && r <= t) bucketAdd[k] += x;
      else {
	for(int i = max(x, l); i < min(y, r); i++) {
	  data[i] += x;
	}
      }
    }
  }
  int get(int i) {
    int k = i / sqrtN;
    return data[i] + bucketAdd[k];
  }
};
