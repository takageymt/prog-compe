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

struct BipartiteMatching
{
  vector< vector<int> > graph;
  vector<int> matched;
  vector<bool> used;
  BipartiteMatching(int V):graph(V), matched(V, -1), used(V, false){}
  void add_edge(int u, int v)
  {
    graph[u].emplace_back(v);
    graph[v].emplace_back(u);
  }
  bool dfs(int u)
  {
    used[u] = true;
    for(auto& v : graph[u]) {
      int w = matched[v];
      if(w < 0 || !used[w] && dfs(w)) {
	matched[u] = v;
	matched[v] = u;
	return true;
      }
    }
    return false;
  }
  int match()
  {
    int res = 0;
    for(int u = 0; u < graph.size(); u++) {
      if(matched[u] < 0) {
	used.clear(); used.resize(graph.size(), false);
	if(dfs(u)) res++;
      }
    }
    return res;
  }
};


int main()
{
  int X, Y, E;
  cin >> X >> Y >> E;
  BipartiteMatching bpm(X + Y);
  while(E--) {
    int x, y; cin >> x >> y;
    bpm.add_edge(x, y + X);
  }
  cout << bpm.match() << endl;
  return 0;
}
