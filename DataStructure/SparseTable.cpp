// Sparse Table for RMinQ
struct SparseTable {
  int N;
  vector<int> data;
  vector<int> LOG;
  vector< vector<int> > table;
  SparseTable(){}
  SparseTable(const vector<int>& _data) {
    N = _data.size();
    data = _data;
    LOG.resize(N+1);
    LOG[1] = 0;
    for(int i = 2; i < N+1; i++) {
      LOG[i] = LOG[i>>1]+1;
    }
    table.resize(N, vector<int>(LOG[N]+1));
    for(int i = 0; i < N; i++) {
      table[i][0] = i;
    }
    for(int k = 1; (1<<k) <= N; k++) {
      for(int i = 0; i+(1<<k) <= N; i++) {
	int s = table[i][k-1];
	int t = table[i+(1<<(k-1))][k-1];
	table[i][k] = (data[s] <= data[t] ? s : t);
      }
    }
  }
  int query(int a, int b) {
    int len = b - a;
    int k = LOG[len];
    int s = data[table[a][k]];
    int t = data[table[b-(1<<k)+1][k]];
    return (data[s] <= data[t] ? s : t);
  }
};
