// Heavy-Light Decomposition
struct HLDecomposition
{
  vector< vector<int> > tree;
  vector<int> vid, head, heavy, parent, depth, inv;
  HLDecomposition(int sz):tree(sz), vid(sz, -1), head(sz), heavy(sz, -1), parent(sz), depth(sz), inv(sz){}
  void add_edge(int u, int v)
  {
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  int dfs(int cur, int prev)
  {
    parent[cur] = prev;
    int sub = 1, max_sub = 0;
    for(int next : tree[cur]) {
      if(next == prev) continue;
      depth[next] = depth[cur] + 1;
      int sub_next = dfs(next, cur);
      sub += sub_next;
      if(max_sub < sub_next) max_sub = sub_next, heavy[cur] = next;
    }
    return sub;
  }
  int bfs()
  {
    int k = 0;
    queue<int> que;
    que.push(0);
    while(!que.empty()) {
      int h = que.front(); que.pop();
      for(int i = h; i != -1; i = heavy[i]) {
	vid[i] = k++;
	inv[vid[i]] = i;
	head[i] = h;
	for(int child : tree[i]) {
	  if(child != parent[i] && child != heavy[i]) que.push(child);
	}
      }
    }
  }
  void build()
  {
    dfs(0, -1);
    bfs();
  }
  /* additional functions */
  // foreach with node
  void foreach(int u, int v, function<void(int, int)> f)
  {
    if(vid[u] > vid[v]) swap(u, v);
    f(max(vid[head[v]], vid[u]), vid[v]);
    if(head[u] != head[v]) foreach(u, parent[head[v]], f);
  }
  // foreach with edge
  void foreach_edge(int u, int v, function<void(int, int)> f)
  {
    if(vid[u] > vid[v]) swap(u, v);
    if(head[u] != head[v]) {
      f(vid[head[v]], vid[v]);
      foreach_edge(u, parent[head[v]], f);
    } else {
      if(u != v) f(vid[u] + 1, vid[v]);
    }
  }
  // k-th upper ancestor
  int kth_up(int u, int k)
  {
    while(1) {
      if(depth[head[u]] > depth[u] - k) {
	k -= depth[u] - depth[head[u]] + 1;
	if(head[u] == 0) return 0;
	u = parent[head[u]];
      } else {
	return inv[vid[u] - k];
      }
    }
  }
  // lowest common ancestor
  int lca(int u, int v)
  {
    if(vid[u] > vid[v]) swap(u, v);
    if(head[u] == head[v]) return u;
    return lca(u, parent[head[v]]);
  }
  int distance(int u, int v)
  {
    return depth[u] + depth[v] - 2*depth[lca(u, v)];
  }
};
