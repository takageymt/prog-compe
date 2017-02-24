struct SparseTable {
  int N, logN;
  vector<int> data;
  vector< vector<int> > table;
  SparseTable(){}
  SparseTable(const vector<int> &ori)
  {
    N = ori.size();
    logN = 1;
    while((1<<logN) <= N) logN++;
    data = ori;
    for(int i )
  }
};
