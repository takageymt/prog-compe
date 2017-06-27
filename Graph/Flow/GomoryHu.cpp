struct edge {
  int to, cap;
  edge(){}
  edge(int to, int cap):to(to),cap(cap){}
};
struct GomoryHuTree {
  vector< vector<edge> > tree;
  GomoryHuTree(){}
  void build(const vector< vector<edge> >& graph) {
    int V = graph.size();
    vector< vector<int> > capacity(V, vector<int>(V));
    vector< vector<int> > flow(V, vector<int>(V));
    for(int u = 0; u < V; u++) {
      for(edge& e : graph[u]) capacity[u][e.to] = e.cap;
    }

    vector<int> p(V), prev(V);
    vector<int> w(V);
    for(int s = 1; s < V; s++) {
      int t = p[s];
      for(int i = 0; i < V; i++)
	for(int j = 0; j < V; j++)
	  flow[i][j] = 0;

      // Edmonds Karp
      int total = 0;
      while(1) {
	queue<int> que; que.push(s);
	fill(prev.begin(), prev.end(), -1);
	prev[s] = s;
	while(!que.empty() && prev[t] < 0) {
	  int u = que.front(); que.pop();
	  for(edge& e : graph[u]) {
	    if(prev[e.to] < 0 && capacity[u][e.to] - flow[u][e.to] > 0) {
	      prev[e.to] = u;
	      que.push(e.to);
	    }
	  }
	}
	if(prev[t] < 0) break;
	int inc = inf;
	for(int v = t; v != prev[v]; v = prev[v])
	  inc = min(inc, capacity[prev[v]][v]-flow[prev[v]][v]);
	for(int v = t; v != prev[v]; v = prev[v])
	  flow[prev[v]][v] += inc, flow[v][prev[v]] -= inc;

	total += inc;
      }

      w[s] = total;
      for(int u = 0; u < V; u++) {
	if(u != s && prev[u] != -1 && p[u] == t) p[u] = s;
      }
      if(prev[p[t]] != -1) p[s] = p[t], p[t] = s, w[s] = w[t], w[t] = total;
    }
    tree.resize(V);
    for(int s = 0; s < V; s++) {
      if(s == p[s]) continue;
      tree[s].push_back(edge(p[s], w[s]));
      tree[p[s]].push_back(edge(s, w[s]));
    }
  }
  int max_flow(int u, int t, int p = -1, int w = inf) {
    if(u == t) return w;
    int d = inf;
    for(edge& e : graph[u]) {
      if(e.to != p) d = min(d, max_flow(e.to, t, u, min(w, e.cap)));
    }
    return d;
  }
};
