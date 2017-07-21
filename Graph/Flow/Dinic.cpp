// Dinic: maximum flow
struct Dinic {
  struct edge {
    int to, capacity, rev, id, isrev;
    edge(){}
    edge(int to, int capacity, int rev):to(to), capacity(capacity), rev(rev){}
  };

  vector< vector<edge> > graph;
  vector<int> level, iter;
  Dinic(int sz):graph(sz), level(sz), iter(sz){};
  void add_edge(int from, int to, int capacity) {
    graph[from].push_back(edge(to, capacity, (int)graph[to].size()));
    graph[to].push_back(edge(from, 0, (int)graph[from].size()-1));
  }
  void bfs(int source) {
    fill(level.begin(), level.end(), -1);
    queue<int> que;
    level[source] = 0;
    que.push(source);
    while(!que.empty()) {
      int v = que.front(); que.pop();
      for(int i = 0; i < (int)graph[v].size(); i++) {
	edge& e = graph[v][i];
	if(e.capacity > 0 && level[e.to] < 0) {
	  level[e.to] = level[v] + 1;
	  que.push(e.to);
	}
      }
    }
  }
  int dfs(int v, int sink, int f) {
    if(v == sink) return f;
    for(int &i = iter[v]; i < (int)graph[v].size(); i++) {
      edge& e = graph[v][i];
      if(e.capacity > 0 && level[v] < level[e.to]) {
	int d = dfs(e.to, sink, min(f, e.capacity));
	if(d > 0) {
	  e.capacity -= d;
	  graph[e.to][e.rev].capacity += d;
	  return d;
	}
      }
    }
    return 0;
  }
  int max_flow(int source, int sink) {
    int flow = 0;
    while(1) {
      bfs(source);
      if(level[sink] < 0) return flow;
      fill(iter.begin(), iter.end(), 0);
      int f; while((f = dfs(source, sink, inf)) > 0) flow += f;
    }
  }
};
