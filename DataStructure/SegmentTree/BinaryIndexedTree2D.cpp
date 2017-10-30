struct BIT {
  vector<vector<int>> data;
  int h, w;
  BIT(int h, int w):data(h+1, vector<int>(w+1)), h(h), w(w){}
  void add(int y, int x, int a) {
    for(int i = y; i <= h; i += i & -i) {
      for(int j = x; j <= w; j += j & -j) {
	data[i][j] += a;
      }
    }
  }
  int sum(int y, int x) {
    int res = 0;
    for(int i = y; i > 0; i -= i & -i) {
      for(int j = x; j > 0; j -= j & -j) {
	res += data[i][j];
      }
    }
    return res;
  }
  int sum(int sy, int sx, int ty, int tx) {
    return sum(ty, tx) - sum(sy-1, tx) - sum(ty, sx-1) + sum(sy-1, sx-1);
  }
};
