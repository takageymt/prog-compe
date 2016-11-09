// AOJ GRL_6_B: Network Flow - Minimum Cost Flow
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using Pi = pair<int, int>;
using Pl = pair<ll, ll>;
using Ti = tuple<int, int, int>;
using Tl = tuple<ll, ll, ll>;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define F first
#define S second
#define Get(t, i) get<(i)>((t))
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, f, n) for(int i = (int)(f); i < (int)(n); i++)
#define each(a, b) for(auto& a : b)

const int inf = 1 << 25;
const ll INF = 1LL << 55;

struct edge
{
  int to, capacity, cost, rev;
  edge(){}
  edge(int to, int capacity, int cost, int rev):to(to), capacity(capacity), cost(cost), rev(rev){}
};

struct PrimalDual
{
  vector< vector<edge> > graph;
  vector<int> potential, mincost, prevv, preve;
  PrimalDual(int V):graph(V), potential(V), mincost(V), prevv(V), preve(V){}
  void add_edge(int from, int to, int capacity, int cost)
  {
    graph[from].push_back(edge(to, capacity, cost, (int)graph[to].size()));
    graph[to].push_back(edge(from, 0, -cost, (int)graph[from].size()-1));
  }
  int min_cost_flow(int source, int sink, int f)
  {
    int ret = 0;
    fill(potential.begin(), potential.end(), 0);
    fill(prevv.begin(), prevv.end(), -1);
    fill(preve.begin(), preve.end(), -1);

    while(f > 0) {
      priority_queue<Pi, vector<Pi>, greater<Pi> > que;
      fill(mincost.begin(), mincost.end(), inf);
      mincost[source] = 0;
      que.push(Pi(0, source));
      while(!que.empty()) {
	Pi p = que.top(); que.pop();
	int v = p.second;
	if(mincost[v] < p.first) continue;
	for(int i = 0; i < (int)graph[v].size(); i++) {
	  edge& e = graph[v][i];
	  int dual_cost = mincost[v] + e.cost + potential[v] - potential[e.to];
	  if(e.capacity > 0 && dual_cost < mincost[e.to]) {
	    mincost[e.to] = dual_cost;
	    prevv[e.to] = v; preve[e.to] = i;
	    que.push(Pi(mincost[e.to], e.to));
	  }
	}
      }

      if(mincost[sink] == inf) return -1;
      for(int v = 0; v < (int)graph.size(); v++) potential[v] += mincost[v];
      int d = f;
      for(int v = sink; v != source; v = prevv[v]) d = min(d, graph[prevv[v]][preve[v]].capacity);
      f -= d;
      ret += d * potential[sink];
      for(int v = sink; v != source; v = prevv[v]) {
	edge& e = graph[prevv[v]][preve[v]];
	e.capacity -= d;
	graph[v][e.rev].capacity += d;
      }
    }
    return ret;
  }
};


int main()
{
  int V, E, F;
  cin >> V >> E >> F;
  PrimalDual mnf(V);
  while(E--) {
    int u, v, c, d;
    cin >> u >> v >> c >> d;
    mnf.add_edge(u, v, c, d);
  }
  cout << mnf.min_cost_flow(0, V-1, F) << endl;
  return 0;
}
