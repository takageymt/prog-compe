struct edge
{
  int to, cost;
  edge(){}
  edge(int to, int cost):to(to), cost(cost){}
};

struct Dijkstra
{
  vector< vector<edge> > G;
  vector<int> mincost;
  Dijkstra(int sz):G(sz), mincost(sz, inf){}
  void add_edge(int f, int t, int cost, bool bi = false)
  {
    G[f].push_back(edge(t, cost));
    if(bi) G[t].push_back(edge(f, cost));
  }
  int shortest_path(int s, int t)
  {
    priority_queue<Pi, vector<Pi>, greater<Pi> > que;
    que.push_back(Pi(0, s));
    mincost[s] = 0;
    while(!que.empty()) {
      int u = que.top().second, cost = que.top().first;
      if(u == t) return cost;
      if(mincost[u] < cost) continue;
      for(edge e : G[u]) {
	if(cost + e.cost < mincost[e.to]) {
	  mincost[e.to] = cost + e.cost;
	  que.push(Pi(mincost[e.to], e.to));
	}
      }
    }
    return -1;
  }
};
