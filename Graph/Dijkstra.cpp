// Dijkstra's algorithm with a heap: Single-source shoretest paths
struct Dijkstra
{
  struct edge
  {
    int to, weight;
    edge(){}
    edge(int to, int weight):to(to), weight(weight){}
  };

  vector< vector<edge> > graph;
  vector<int> route, prevv, preve;
  vector<int> distance;
  Dijkstra(int sz):graph(sz), prevv(sz, -1), preve(sz, -1), distance(sz, inf){}
  void add_edge(int from, int to, int weight, bool is_bidirect = false)
  {
    graph[from].push_back(edge(to, weight));
    if(is_bidirect) graph[to].push_back(edge(from, weight));
  }
  int shortest_path(int source, int destination = -1)
  {
    typedef pair<int, int> Pi;
    priority_queue<Pi, vector<Pi>, greater<Pi> > que;
    que.push(Pi(0, source));
    distance[source] = 0;
    while(!que.empty()) {
      Pi p = que.top(); que.pop();
      int v = p.second;
      if(v == destination) return p.first;
      if(distance[v] < p.first) continue;
      for(int i = 0; i < (int)graph[v].size(); i++) {
	edge& e = graph[v][i];
	if(distance[v] + e.weight < distance[e.to]) {
	  distance[e.to] = distance[v] + e.weight;
	  prevv[e.to] = v; preve[e.to] = i;
	  que.push(Pi(distance[e.to], e.to));
	}
      }
    }
    return -1;
  }
  bool restore(int source, int destination)
  {
    for(int v = destination; v != source; v = prevv[v]) {
      if(prevv[v] == -1) return false;
      route[prevv[v]].push_back(graph[prevv[v]][preve[v]]);
    }
    return true;
  }
};
