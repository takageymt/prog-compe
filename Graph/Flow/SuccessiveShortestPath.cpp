// Sccessive Shortest Path: minimum cost maximum flow
struct SSP {
  struct edge {
    int to, capacity, cost, rev;
    edge(int to, int capacity, int cost, int rev):to(to), capacity(capacity), cost(cost), rev(rev){}
  };
  vector< vector<edge> > graph;
  void add_edge(int from, int to, int capacity, int cost) {
    graph[from].push_back(edge(to, capacity, cost, graph[to].size()));
    graph[to].push_back(edge(from, 0, -cost, graph[from].size()-1));
  }
  int min_cost_flow(int source, int sink, int f) {
    int res = 0;
    while(f > 0) {
      vector<int> mincost(graph.size(), inf), prevv(graph.size()), preve(graph.size());
      mincost[source] = 0;

      bool update = true;
      while(update) {
	update = false;
	for(int v = 0; v < (int)graph.size(); v++) {
	  for(int i = 0; i < (int)graph[v].size(); i++) {
	    edge& e = graph[v][i];
	    if(e.capacity > 0 && mincost[e.to] > mincost[v] + e.cost) {
	      mincost[e.to] = mincost[v] + e.cost;
	      prevv[e.to] = v; preve[e.to] = i;
	      update = true;
	    }
	  }
	}
	if(mincost[sink] == inf) return -1;

	int d = f;
	for(int v = sink; v != source; v = prevv[v]) d = min(d, graph[prevv[v]][preve[v]].capacity);
	f -= d;
	res += d * mincost[sink];
	for(int v = sink; v != source; v = prevv[v]) {
	  edge& e = graph[prevv[v]][preve[v]];
	  e.capacity -= d;
	  graph[e.to][e.rev].capacity += d;
	}
      }
    }
    return res;
  }
};
