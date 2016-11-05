// Dijkstra's algorithm with a heap: Single-source shoretest paths
struct edge
{
  int to, weight;
  edge(){}
  edge(int to, int weight):to(to), weight(weight){}
};

struct Dijkstra
{
  vector< vector<edge> > graph;
  vector<int> distance;
  Dijkstra(int sz):graph(sz), distance(sz, inf){}
  void add_edge(int from, int to, int weight, bool is_bidirect = false)
  {
    G[from].push_back(edge(to, weight));
    if(is_bidirect) G[to].push_back(edge(from, weight));
  }
  int shortest_path(int source, int destination)
  {
    priority_queue<Pi, vector<Pi>, greater<Pi> > que;
    que.push_back(Pi(0, source));
    distance[source] = 0;
    while(!que.empty()) {
      Pi p = que.top(); que.pop();
      int v = p.second;
      if(v == destination) return cost;
      if(distance[v] < p.first) continue;
      for(edge e : G[v]) {
	if(distance[v] + e.weight < distance[e.to]) {
	  distance[e.to] = distance[v] + e.weight;
	  que.push(Pi(distance[e.to], e.to));
	}
      }
    }
    return -1;
  }
};
