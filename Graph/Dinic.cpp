struct edge
{
  int to, cap, rev, id, isrev;
  edge(){}
  edge(int to, int cap, int rev):to(to), cap(cap), rev(rev){}
};

struct Dinic
{
  vector< vector<edge> > graph;
  vector<int> level, iter;
  Dinic(int V):graph(V), level(V), iter(V){};
  void add_edge(int f, int t, int cap)
  {
    graph[f].push_back(edge(t, cap, (int)graph[t].size()));
    graph[t].push_back(edge(f, cap, (int)graph[f].size()-1));
  }
  void bfs(int source)
  {
    fill(level.begin(), level.end(), -1);
    queue<int> que;
    level[source] = 0;
    que.push(source);
    while(!que.empty()) {
      int v = que.front(); que.pop();
      for(int i = 0; i < (int)graph[v].size(); i++) {
	edge& e = graph[v][i];
	if(e.cap > 0 && level[e.to] < 0) {
	  level[e.to] = level[v] + 1;
	  que.push(e.to);
	}
      }
    }
  }
  int dfs(int v, int sink, int f)
  {
    if(v == sink) return f;
    for(int &i = iter[v]; i < (int)graph[v].size(); i++) {
      edge& e = graph[v][i];
      if(e.cap > 0 && level[v] < level[e.to]) {
	int d = dfs(e.to, sink, min(f, e.cap));
	if(d > 0) {
	  e.cap -= d;
	  graph[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }
  int max_flow(int source, int sink)
  {
    int flow = 0;
    while(1) {
      bfs(source);
      if(level[sink] < 0) return flow;
      fill(iter.begin(), iter.end(), 0);
      int f; while((f = dfs(source, sink, inf)) > 0) flow += f;
    }
  }
};
