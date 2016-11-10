// AOJ GRL_5_A: Tree - Diameter of a Tree
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
  int to, weight;
  edge(){}
  edge(int to, int weight):to(to), weight(weight){}
};

using Pi = pair<int, int>;
using Graph = vector< vector<edge> >;
  
Pi dfs(Graph& graph, int cur, int prev)
{
  Pi ret = Pi(0, cur);
  for(edge e : graph[cur]) {
    if(e.to != prev) {
      Pi dist = dfs(graph, e.to, cur);
      dist.first += e.weight;
      ret = max(ret, dist);
    }
  }
  return ret;
}

int diameter(Graph& tree)
{
  Pi p = dfs(tree, 0, -1);
  Pi q = dfs(tree, p.second, -1);
  return q.first;
}


int main()
{
  int n; cin >> n;
  Graph graph(n);
  n--;
  while(n--) {
    int s, t, w;
    cin >> s >> t >> w;
    graph[s].push_back(edge(t, w));
    graph[t].push_back(edge(s, w));
  }
  cout << diameter(graph) << endl;
  return 0;
}
