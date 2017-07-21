#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) (v).begin(), (v).end()
#define resz(v, ...) (v).clear(), (v).resize(__VA_ARGS__)
#define reps(i, m, n) for(int i = (int)(m); i < (int)(n); i++)
#define rep(i, n) reps(i, 0, n)

template<class T1, class T2> void chmin(T1 &a, T2 b){if(a>b)a=b;}
template<class T1, class T2> void chmax(T1 &a, T2 b){if(a<b)a=b;}

typedef pair<int, int> Pi;
typedef tuple<int, int, int> Ti;
typedef vector<int> vint;

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

struct Johnson {
  struct edge {
    int to, weight;
    edge(){}
    edge(int to, int weight):to(to), weight(weight){}
  };
  vector< vector<edge> > graph;
  vector< vector<int> > distance;
  vector<int> potential;
  Johnson(int V):graph(V), distance(V, vector<int>(V, inf)), potential(V, 0){}
  void add_edge(int from, int to, int weight, bool is_bidirect = false) {
    graph[from].emplace_back(to, weight);
    if(is_bidirect) graph[to].emplace_back(from, weight);
  }
  void shortest_path() {
    // BellmanFord's
    int V = graph.size();
    for(int k = 0; k < V; k++) {
      for(int i = 0; i < V; i++) {
	for(edge& e : graph[i]) {
	  if(potential[i]+e.weight < potential[e.to]) {
	    potential[e.to] = potential[i] + e.weight;
	  }
	}
      }
    }

    // Dijkstra's
    typedef pair<int, int> Pi;
    for(int s = 0; s < V; s++) {
      priority_queue<Pi, vector<Pi>, greater<Pi> > que;
      distance[s][s] = 0;
      que.emplace(0, s);
      while(!que.empty()) {
	Pi p = que.top(); que.pop();
	int v = p.second;
	if(distance[s][v] < p.first) continue;
	for(edge& e : graph[v]) {
	  int dist = distance[s][v] + e.weight + potential[v] - potential[e.to];
	  if(dist < distance[s][e.to]) {
	    distance[s][e.to] = dist;
	    que.emplace(dist, e.to);
	  }
	}
      }
      for(int i = 0; i < V; i++) distance[s][i] += potential[i] - potential[s];
    }
  }
  int getDistance(int from, int to) {
    return distance[from][to];
  }
};


signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  int V, E, r;
  cin >> V >> E >> r;


  return 0;
}
