struct edge{
  int to, cost;
  edge(){}
  edge(int to, int cost):to(to), cost(cost){}
};

struct Prim
{
  vector< vector<edge> > G;
  Prim(int sz):G(sz){}
  void add_edge(int u, int v, int cost)
  {
    G[u].push_back(edge(v, cost));
    G[v].push_back(edge(u, cost));
  }
  int build()
  {
    int total = 0;
    vector<bool> used(G.size(), false);
    priority_queue< P, vector<P>, greater<P> > que;
    que.push(P(0, 0));
    while(!que.empty()){
      P p = que.top(); que.pop();
      int now = p.second, cost = p.first;
      if(used[now]) continue;
      used[now] = true;
      total += cost;
      for(int i = 0; i < G[now].size(); i++){
	edge& e = G[now][i];
	que.push(P(e.cost, e.to));
      }
    }
    return total;
  }
};
