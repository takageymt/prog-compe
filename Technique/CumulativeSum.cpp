struct CumulativeSum {
  vector<int> data;
  CumulativeSum(int sz):data(++sz, 0){}
  inline void add(int k, int x) {
    data[k] += x;
  }
  void build() {
    for(int i = 1; i < data.size(); i++) data[i] += data[i-1];
  }
  inline int query(int l, int r) { // [l, r)
    return data[r] - data[l];
  }
};

struct CumulativeSum2D {
  vector< vector<int> > data;
  CumulativeSum2D(int W, int H):data(++H, vector<int>(++W)){}
  inline add(int x, int y, int z) {
    data[++y][++x] += z;
  }
  void build() {
    for(int i = 1; i < data.size(); i++)
      for(int j = 1; j < data[i].size(); j++)
	data[i][j] += data[i][j-1] + data[i-1][j] - data[i-1][j-1];
  }
  inline int query(int sx, int sy, int gx, int gy) {
    return data[gy][gx] - data[gy][sx] - data[sy][gx] + data[sy][sx];
  }
};
