struct edge
{
  int to, cap, cost, rev;
  edge(){}
  edge(int to, int cap, int cost, int rev):to(to), cap(cap), cost(cost), rev(rev){}
};

struct PrimalDual
{
  vector< vector<edge> > G;
  vector<int> potential, mincost, prevv, preve;
  PrimalDual(int V):G(V), potential(V), mincost(V), prevv(V), preve(V){}
  void add_edge(int from, int to, int cap, int cost)
  {
    G[from].push_back(edge(to, cap, cost, (int)G[to].size()));
    G[to].push_back(edge(from, 0, -cost, (int)G[from].size()-1));
  }
  int min_cost_flow(int s, int t, int f)
  {
    int ret = 0;
    fill(potential.begin(), potential.end(), 0);
    fill(prevv.begin(), prevv.end(), -1);
    fill(preve.begin(), preve.end(), -1);

    while(f > 0) {
      priority_queue<Pi, vector<Pi>, greater<Pi> > que;
      fill(mincost.begin(), mincost.end(), inf);
      mincost[s] = 0;
      que.push(Pi(0, s));
      while(!que.empty()) {
	Pi p = que.top(); que.pop();
	int v = p.second;
	if(mincost[v] < p.first) continue;
	for(int i = 0; i < (int)G[v].size(); i++) {
	  edge& e = G[v][i];
	  int dual_cost = mincost[v] + e.cost + potential[v] - potential[e.to];
	  if(e.cap > 0 && dual_cost < mincost[e.to]) {
	    mincost[e.to] = dual_cost;
	    prevv[e.to] = v; preve[e.to] = i;
	    que.push(Pi(mincost[e.to], e.to));
	  }
	}
      }

      if(mincost[t] == inf) return -1;
      for(int v = 0; v < (int)G.size(); v++) potential[v] += mincost[v];
      int d = f;
      for(int v = t; v != s; v = prevv[v]) d = min(d, G[prevv[v]][preve[v]].cap);
      f -= d;
      ret += d * potential[t];
      for(int v = t; v != s; v = prevv[v]) {
	edge& e = G[prevv[v]][preve[v]];
	e.cap -= d;
	G[v][e.rev].cap += d;
      }
    }
    return ret;
  }
};
