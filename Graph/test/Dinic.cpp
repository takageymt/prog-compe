// AOJ GRL_6_A: Network Flow - Maximum Flow
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

// Dinic: maximum flow
struct edge
{
  int to, capacity, rev, id, isrev;
  edge(){}
  edge(int to, int capacity, int rev):to(to), capacity(capacity), rev(rev){}
};

struct Dinic
{
  vector< vector<edge> > graph;
  vector<int> level, iter;
  Dinic(int sz):graph(sz), level(sz), iter(sz){};
  void add_edge(int from, int to, int capacity)
  {
    graph[from].push_back(edge(to, capacity, (int)graph[to].size()));
    graph[to].push_back(edge(from, 0, (int)graph[from].size()-1));
  }
  void bfs(int source)
  {
    fill(level.begin(), level.end(), -1);
    queue<int> que;
    level[source] = 0;
    que.push(source);
    while(!que.empty()) {
      int v = que.front(); que.pop();
      for(int i = 0; i < (int)graph[v].size(); i++) {
	edge& e = graph[v][i];
	if(e.capacity > 0 && level[e.to] < 0) {
	  level[e.to] = level[v] + 1;
	  que.push(e.to);
	}
      }
    }
  }
  int dfs(int v, int sink, int f)
  {
    if(v == sink) return f;
    for(int &i = iter[v]; i < (int)graph[v].size(); i++) {
      edge& e = graph[v][i];
      if(e.capacity > 0 && level[v] < level[e.to]) {
	int d = dfs(e.to, sink, min(f, e.capacity));
	if(d > 0) {
	  e.capacity -= d;
	  graph[e.to][e.rev].capacity += d;
	  return d;
	}
      }
    }
    return 0;
  }
  int max_flow(int source, int sink)
  {
    int flow = 0;
    while(1) {
      bfs(source);
      if(level[sink] < 0) return flow;
      fill(iter.begin(), iter.end(), 0);
      int f; while((f = dfs(source, sink, inf)) > 0) flow += f;
    }
  }
};


int main()
{
  int V, E; cin >> V >> E;
  Dinic mxf(V);
  while(E--) {
    int u, v, c;
    cin >> u >> v >> c;
    mxf.add_edge(u, v, c);
  }
  cout << mxf.max_flow(0, V-1) << endl;
  return 0;
}
