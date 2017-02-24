// Mo's algorithm
// 区間クエリ系問題を解くためのアルゴリズム
// > 要素が更新されない
// > クエリ先読み可
// > 区間の結果をマージできない
// > 区間[l,r)から
// >> [l-1,r),[l,r+1)が求まる(追加操作)
// >> [l+1,r),[l,r-1)が求まる(削除操作)

void Mo(int N, int Q, vector<int> &l, vector<int> &r) {
  //int N; // 数列の長さ
  //int Q; // クエリ数
  //vector<int> l, r; // クエリの区間

  // ソート
  int sqN = sqrt(N);
  vector<int> qi(q);
  for(int i = 0; i < q; i++) qi[i] = i;
  sort(begin(qi), end(qi), [&](int i, int j){
      return l[i]/sqN != l[j]/sqN ? l[i] < l[j] : r[i] < r[j];
    });


  // クエリの処理
  int nl = 0, nr = 0;
  vector<int> ans(q);
  for(int i : qi) {
    while(nl < l[i]) remove(nl++);
    while(nl > l[i]) add(--nl);
    while(nr < r[i]) add(++nr);
    while(nr > r[i]) remove(nr--);
    ans[i] = calc();
  }
  for(int i = 0; i < Q; i++) cout << ans[i] << endl;
}
