struct SAT2 : SCC {
  int N;
  SAT2(int N):SCC(N*2), N(N){}
  void AorB(int i, int j) {
    add_edge(i+N, j);
    add_edge(j+N, i);
  }
  void nAorB(int i, int j) {
    add_edge(i, j);
    add_edge(j+N, i+N);
  }
  void AornB(int i, int j) {
    add_edge(i+N, j+N);
    add_edge(j, i);
  }
  void nAornB(int i, int j) {
    add_edge(i, j+N);
    add_edge(j, i+N);
  }
  bool sat2() {
    build();
    for(int i = 0; i < N; i++) {
      if(cmp[i] == cmp[i+N]) return false;
    }
    return true;
  }
};
