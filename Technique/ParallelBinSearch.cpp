struct ParallelBinSearch {
  /*
   * Parallel Binary Search
   * Q回のクエリが与えられる。
   * 人i(0<=i<=N-1)がある条件を初めて満たすのは
   * どのクエリが処理されたあとか。(0<=j<=Q-1)
   */
  using INIT = function<void(void)>;
  using APPLY = function<void(int)>;
  using CHECK = function<bool(int)>;
  int N;
  int Q;
  INIT init;
  APPLY apply;
  CHECK check;
  vector<int> L, R;
  vector<vector<int> > M;
  ParallelBinSearch(int N, int Q, INIT init, APPLY apply, CHECK check)
    :N(N), Q(Q), init(init), apply(apply), check(check), L(N, -1), R(N, Q), M(Q){}
  vector<int> solve() {
    bool update = true;
    while(update) {
      update = false;
      init();
      for(int i = 0; i < N; ++i) {
	if(L[i]+1 < R[i]) M[(L[i]+R[i])>>1].emplace_back(i);
      }
      for(int j = 0; j < Q; ++j) {
	apply(j);
	if(!M[j].empty()) update = true;
	for(int i : M[j]) {
	  if(check(i)) R[i] = j;
	  else L[i] = j;
	}
	M[j].clear();
      }
    }
    return R;
  }
};
