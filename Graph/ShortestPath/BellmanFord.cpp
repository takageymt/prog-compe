// Bellman-Ford algorithm: Single-source shoretest paths
struct BellmanFord {
  struct edge {
    int from, to, weight;
    edge(){}
    edge(int from, int to, int weight):from(from), to(to), weight(weight){}
  };
  vector<edge> edges;
  vector<int> distance;
  BellmanFord(int sz):distance(sz, inf){}
  void add_edge(int from, int to, int weight) {
    edges.push_back(edge(from, to, weight));
  }
  bool shortest_path(int source) {
    distance[source] = 0;

    // if this graph doesn't have negative cycle,
    // the shortest path is found in |V|-1 times.
    for(int i = 0; i < (int)distance.size()-1; i++) {
      for(edge e : edges) {
	if(distance[e.from] != inf &&
	   distance[e.from] + e.weight < distance[e.to]) {
	  distance[e.to] = distance[e.from] + e.weight;
	}
      }
    }

    // check for negative-weight cycles
    for(edge e : edges) {
      if(distance[e.from] != inf &&
	 distance[e.from] + e.weight < distance[e.to]) {
	return true;
      }
    }
    return false;
  }
};
