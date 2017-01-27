// aoj2313
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define FR first
#define SC second
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, f, n) for(int i = (int)(f); i < (int)(n); i++)
#define each(a, b) for(auto& a : b)

typedef pair<int, int> P;

const int inf = 1LL << 55;

struct Dinic
{
  struct edge
  {
    int to, cap, rev;
    edge(){}
    edge(int to, int cap, int rev):to(to), cap(cap), rev(rev){}
  };

  vector< vector<edge> > graph;
  vector<int> level, iter;

  Dinic(int V):graph(V), level(V), iter(V){}
  
  pair<int, int> add_edge(int f, int t, int cap, bool bi = false)
  {
    graph[f].push_back(edge(t, cap, graph[t].size()));
    graph[t].push_back(edge(f, (bi ? cap : 0), graph[f].size()-1));
    return make_pair(graph[f].size()-1, graph[t].size()-1);
  }
  void bfs(int s)
  {
    fill(all(level), -1);
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty()) {
      int v = que.front(); que.pop();
      for(edge& e : graph[v]) {
	if(e.cap > 0 && level[e.to] < 0) {
	  level[e.to] = level[v] + 1;
	  que.push(e.to);
	}
      }
    }
  }
  int dfs(int v, int t, int f)
  {
    if(v == t) return f;
    for(int &i = iter[v]; i < graph[v].size(); i++) {
      edge& e = graph[v][i];
      if(e.cap > 0 && level[v] < level[e.to]) {
	int d = dfs(e.to, t, min(f, e.cap));
	if(d > 0) {
	  e.cap -= d;
	  graph[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }
  int max_flow(int s, int t, int exf = inf)
  {
    int flow = 0;
    while(exf) {
      bfs(s);
      if(level[t] < 0) return flow;
      fill(all(iter), 0);
      int f;
      while(exf && (f = dfs(s, t, exf)) > 0) flow += f, exf -= (exf != inf);
    }
    return flow;
  }
};

int N, E, Q;
vector< tuple<int, int, int> > query;
int conn[505][505];

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  cin >> N >> E >> Q;
  Dinic graph(N);
  memset(conn, -1, sizeof(conn));
  while(E--) {
    int f, t;
    cin >> f >> t; f--, t--;
    tie(conn[f][t], conn[t][f]) = graph.add_edge(f, t, 1, true);
  }
  while(Q--) {
    int m, a, b;
    cin >> m >> a >> b; a--, b--;
    query.emplace_back(m, a, b);
    if(m == 1 && !~conn[a][b]) {
      tie(conn[a][b], conn[b][a]) = graph.add_edge(a, b, 0, true);
    }
  }

  int s = 0, t = N-1; 
  int mxf = graph.max_flow(s, t);
  
  for(auto q : query) {
    int m, a, b;
    tie(m, a, b) = q;
    if(m == 1) {
      graph.graph[a][conn[a][b]].cap = graph.graph[b][conn[b][a]].cap = 1;
      mxf += graph.max_flow(0, N-1);
    } else if(m == 2) {
      int cap = graph.graph[a][conn[a][b]].cap;
      graph.graph[a][conn[a][b]].cap = graph.graph[b][conn[b][a]].cap = 0;
      // cap == 1 : didn't use
      if(cap == 0) { // used a -> b
	if(!graph.max_flow(a, b, 1)) {
	  graph.max_flow(t, b, 1);
	  graph.max_flow(a, s, 1);
	  mxf--; 	  
	}
      } else if(cap == 2) { // used b -> a
	if(!graph.max_flow(b, a, 1)) {
	  graph.max_flow(t, a, 1);
	  graph.max_flow(b, s, 1);
	  mxf--; 	  
	}
      }
    }
    cout << mxf << endl;
  }
  
  return 0;
}
