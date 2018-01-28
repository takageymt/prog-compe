struct Array {
  int n;
  int g_time;
  vector<vector<int> > data;
  vector<vector<int> > time;
  Array(int n):n(n), g_time(-1), data(n), time(n) {
    for(int i = 0; i < n; ++i) {
      data[i].push_back(-1);
      time[i].push_back(-1);
    }
  }
  void set(int i, int d) {
    ++g_time;
    data[i].push_back(d);
    time[i].push_back(g_time);
  }
  int get(int i, int t) {
    int ti = upper_bound(time[i].begin(), time[i].end(), t)-time[i].begin();
    return data[i][ti-1];
  }
};
