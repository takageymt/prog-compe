#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
 
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
#define each(a, b) for(auto a : b)

#define int ll
 
const int inf = 1 << 25;
const ll INF = 1LL << 55;

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
  Dijkstra(int sz):graph(sz), distance(sz, INF){}
  void add_edge(int from, int to, int weight, bool is_bidirect = false)
  {
    graph[from].push_back(edge(to, weight));
    if(is_bidirect) graph[to].push_back(edge(from, weight));
  }
  int shortest_path(int source, int destination = -1)
  {
    priority_queue<Pi, vector<Pi>, greater<Pi> > que;
    que.push(Pi(0, source));
    distance[source] = 0;
    while(!que.empty()) {
      Pi p = que.top(); que.pop();
      int v = p.second;
      if(v == destination) return p.first;
      if(distance[v] < p.first) continue;
      for(edge e : graph[v]) {
	if(distance[v] + e.weight < distance[e.to]) {
	  distance[e.to] = distance[v] + e.weight;
	  que.push(Pi(distance[e.to], e.to));
	}
      }
    }
    return -1;
  }
};

signed main()
{
  int V, E, r; cin >> V >> E >> r;
  Dijkstra sssp(V);
  while(E--) {
    int s, t, d; cin >> s >> t >> d;
    sssp.add_edge(s, t, d);
  }
  sssp.shortest_path(r);
  for(int i = 0; i < V; i++) {
    if(sssp.distance[i] == INF) puts("INF");
    else cout << sssp.distance[i] << endl;
  }
  return 0;
}
