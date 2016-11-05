// Ford-Fulkerson algorithm: maximum flow
struct edge
{
  int to, cap, rev;
  edge(){}
  edge(int to, int cap, int rev):to(to), cap(cap), rev(rev){}
};

struct FordFulkerson
{
  vector< vector<edge> > graph;
  vector<bool> used;
  FordFulkerson(int V):graph(V), used(V, false){}
  void add_edge(int from, int to, int cap)
  {
    G[from].push_back(edge(to, cap, (int)graph[to].size()));
    G[to].push_back(edge(from, 0, (int)graph[from].size()-1));
  }
  int dfs(int v, int sink, int f)
  {
    if(v == sink) return f;
    used[v] = true;
    for(int i = 0; i < graph[v].size(); i++) {
      edge& e = graph[v][i];
      if(!used[e.to] && e.cap > 0) {
	int d = dfs(e.to, sink, min(f, e.cap));
	if(d > 0) {
	  e.cap -= d;
	  graph[e.to][e.rev] += d;
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
      fill(used.begin(), used.end(), false);
      int f = dfs(source, sink, inf);
      if(f == 0) return flow;
      flow += f;
    }
  }
};
