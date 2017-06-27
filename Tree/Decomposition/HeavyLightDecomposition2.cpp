struct HLDT {
  vector< vector<int> > graph;
  // vid:分解後の頂点番号（パス上では連続）
  vector<int> vid, head, heavy, par, depth, inv;

  HLDT(){}
  HLDT(int n)
    :graph(n), vid(n, -1), head(n), heavy(n, -1), par(n), depth(n), inv(n){}

  void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  void build() {
    dfs(0, -1);
    bfs();
  }

  int dfs(int u, int p) {
    par[u] = p;
    int subsz = 1, max_chsz = 0;
    for(int v : graph[u]) {
      if(v == p) continue;
      depth[v] = depth[u] + 1;
      int chsz = dfs(v, u);
      subsz += chsz;
      if(max_chsz < chsz) max_chsz = chsz, heavy[u] = v;
    }
    return subsz;
  }

  void bfs() {
    int id = 0;
    queue<int> que; // 分解したパスの先頭
    que.push(0);
    while(!que.empty()) {
      int h = que.front(); que.pop();
      for(int i = h; i != -1; i = heavy[i]) { // 先頭からHeavy edgeに沿って下に降りてく
	vid[i] = id++;
	inv[vid[i]] = i;
	head[i] = h;
	for(int j : graph[i]) {
	  if(j != par[i] && j != heavy[i]) que.push(j);
	}
      }
    }
  }

  void for_each(int u, int v, vector< pair<int, int> >& lr) {
    if(vid[u] > vid[v]) swap(u, v);
    lr.emplace_back(max(vid[head[v]], vid[u]), vid[v]); // 閉区間
    if(head[u] != head[v]) for_each(u, par[head[v]], lr);
  }

  int lca(int u, int v) {
    if(vid[u] > vid[v]) swap(u, v);
    if(head[u] == head[v]) return u;
    return lca(u, par[head[v]]);
  }

  int distance(int u, int v) {
    return depth[u] + depth[v] - 2*depth[lca(u, v)];
  }
};
