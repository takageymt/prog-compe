struct Johnson {
  struct edge {
    int to, weight;
    edge(){}
    edge(int to, int weight):to(to), weight(weight){}
  };
  vector< vector<edge> > graph;
  vector< vector<int> > distance;
  vector<int> potential;
  Johnson(int V):graph(V), distance(V, vector<int>(V, inf)), potential(V, 0){}
  void add_edge(int from, int to, int weight, bool is_bidirect = false) {
    graph[from].emplace_back(to, weight);
    if(is_bidirect) graph[to].emplace_back(from, weight);
  }
  void shortest_path() {
    // BellmanFord's
    int V = graph.size();
    for(int k = 0; k < V; k++) {
      for(int i = 0; i < V; i++) {
	for(edge& e : graph[i]) {
	  if(potential[i]+e.weight < potential[e.to]) {
	    potential[e.to] = potential[e.from] + e.weight;
	  }
	}
      }
    }

    // Dijkstra's
    typedef pair<int, int> Pi;
    for(int s = 0; s < V; s++) {
      priority_queue<Pi, vector<Pi>, greater<Pi> > que;
      dist[s][s] = 0;
      que.emplace(0, s);
      while(!que.empty()) {
	Pi p = que.top(); que.pop();
	int v = p.second;
	if(distance[s][v] < p.first) continue;
	for(edge& e : graph[v]) {
	  int dist = distance[s][v] + e.cost + potential[v] - potential[e.to];
	  if(dist < distance[s][e.to]) {
	    distance[s][e.to] = dist;
	    que.emplace(dist, e.to);
	  }
	}
      }
      for(int i = 0; i < V; i++) distance[s][i] += potential[i] - potential[s];
    }
  }
  void getDistance(int from, int to) {
    return distance[from][to];
  }
};
