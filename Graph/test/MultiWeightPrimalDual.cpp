// aoj2679
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) (v).begin(), (v).end()

// weight vector of each character
// A-Z(26) and a-z(26)
struct weight
{
  vector<int> val;

  // constructors
  weight():val(52, 0){}
  weight(int ini):val(52, ini){}
  weight(vector<int> ini):val(ini){}

  // arithmetic
  // binary
  weight operator + (weight r) {
    vector<int> ret(52);
    for(int i = 0; i < 52; i++) ret[i] = val[i] + r.val[i];
    return weight(ret);
  }
  weight operator - (weight r) {
    vector<int> ret(52);
    for(int i = 0; i < 52; i++) ret[i] = val[i] - r.val[i];
    return weight(ret);
  }
  weight operator * (int k) {
    vector<int> ret(52);
    for(int i = 0; i < 52; i++) ret[i] = val[i] * k;
    return weight(ret);
  }
  // unary
  weight& operator - () {
    for(int i = 0; i < 52; i++) val[i] = -val[i];
    return *this;
  }

  
  // comparison
  bool operator == (const weight& r) const {
    return val == r.val;
  }
  bool operator < (const weight& r) const {
    return val < r.val;
  }

  // assignment
  weight& operator += (const weight& r) {
    for(int i = 0; i < 52; i++) val[i] += r.val[i];
    return *this;
  }
};
using P = pair<weight, int>;

const weight inf = weight(1LL << 55);
const weight zero = weight(0);

// Sccessive Shortest Path(Primal Dual): minimum cost maximum flow
struct PrimalDual
{
  struct edge
  {
    int to, cap, rev;
    weight cost;
    edge(){}
    edge(int to, int cap, weight cost, int rev):to(to), cap(cap), cost(cost), rev(rev){}
  };

  vector< vector<edge> > graph;
  vector<weight> mincost;
  
  PrimalDual(int V):graph(V), mincost(V){}
  void add_edge(int s, int t, int cap, weight cost)
  {
    graph[s].emplace_back(t, cap, cost, graph[t].size());
    graph[t].emplace_back(s, 0, -cost, graph[s].size()-1);
  }
  weight min_cost_flow(int s, int t, int f)
  {
    weight ret = zero;
    vector<weight> h(graph.size(), zero);
    vector<int> pv(graph.size(), -1);
    vector<int> pe(graph.size(), -1);

    while(f > 0) {
     priority_queue< P, vector<P>, greater<P> > que;
      fill(all(mincost), inf);
      mincost[s] = zero;
      que.push(P(zero, s));
      
      while(!que.empty()) {
	P p = que.top(); que.pop();
	int v = p.second;
	if(mincost[v] < p.first) continue;
	for(int i = 0; i < graph[v].size(); i++) {
	  edge &e = graph[v][i];
	  weight cost = mincost[v] + e.cost + h[v] - h[e.to];
	  if(e.cap > 0 && cost < mincost[e.to]) {
	    mincost[e.to] = cost;
	    pv[e.to] = v, pe[e.to] = i;
	    que.push(P(mincost[e.to], e.to));
	  }
	}
      }

      if(mincost[t] == inf) return weight(-1);

      for(int i = 0; i < graph.size(); i++) h[i] += mincost[i];
      int d = f;
      for(int v = t; v != s; v = pv[v]) d = min(d, graph[pv[v]][pe[v]].cap);
      f -= d;
      ret += h[t] * d;
      for(int v = t; v != s; v = pv[v]) {
	edge& e = graph[pv[v]][pe[v]];
	e.cap -= d;
	graph[v][e.rev].cap += d;
      }
    }

    return ret;
  }
};

const string a = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int N; cin >> N;
  int s = 2*N, t = s + 1;

  PrimalDual graph(t + 1);

  for(int i = 0; i < N; i++) {
    graph.add_edge(s, i, 1, zero);
    graph.add_edge(N + i, t, 1, zero);
  }
  
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      char c; cin >> c;
      weight w; w.val[a.find(c)] = -1;
      graph.add_edge(i, N + j, 1, w);
    }
  }

  weight mcf = graph.min_cost_flow(s, t, N);
  for(int i = 0; i < 52; i++) {
    for(int j = 0; j < -mcf.val[i]; j++) cout << a[i];
  }
  cout << endl;
  
  return 0;
}
