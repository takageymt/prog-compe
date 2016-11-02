struct edge
{
  int to, cap, rev, id, isrev;
  edge(){}
  edge(int to, int cap, int rev):to(to), cap(cap), rev(rev){}
};

struct Dinic
{
  vector< vector<edge> > G;
  vector<int> level, iter;
  Dinic(int V):G(V), level(V), iter(V){};
  void add_edge(int f, int t, int cap)
  {
    G[f].push_back(edge(t, cap, (int)G[t].size()));
    G[t].push_back(edge(f, cap, (int)G[f].size()-1));
  }
  void bfs(int s)
  {
    fill(level.begin(), level.end(), -1);
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty()) {
      int v = que.front(); que.pop();
      for(int i = 0; i < (int)G[v].size(); i++) {
	edge& e = G[v][i];
	if(e.cap > 0 && level[e.to] < 0) {
	  level[e.to] = level[v] + 1;
	  que.push(e.to);
	}
      }
    }
  }
  int dfs(int v, int t, int f)
  {
    if(v == t) return f;
    for(int &i = iter[v]; i < (int)G[v].size(); i++) {
      edge& e = G[v][i];
      if(e.cap > 0 && level[v] < level[e.to]) {
	int d = dfs(e.to, t, min(f, e.cap));
	if(d > 0) {
	  e.cap -= d;
	  G[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }
  int max_flow(int s, int t)
  {
    int flow = 0;
    while(1) {
      bfs(s);
      if(level[t] < 0) return flow;
      fill(iter.begin(), iter.end(), 0);
      int f; while((f = dfs(s, t, inf)) > 0) flow += f;
    }
  }
};
