// GRL_3_C: Connected Components - Strongly Connected Components
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

typedef vector< vector<int> > Graph;

void dfs(int idx, Graph& graph, vector<bool>& used, vector<int>& order)
{
  if(used[idx]) return;
  used[idx] = true;
  for(int i = 0; i < graph[idx].size(); i++) {
    dfs(graph[idx][i], graph, used, order);
  }
  order.push_back(idx);
}

void rdfs(int idx, Graph& rgraph, vector<int>& cmp, int& cnt)
{
  cmp[idx] = cnt;
  for(int i = 0; i < rgraph[idx].size(); i++) {
    if(cmp[rgraph[idx][i]] == -1) rdfs(rgraph[idx][i], rgraph, cmp, cnt);
  }
}

int StronglyConnectedComponents(Graph& graph, vector<int>& cmp)
{
  int cnt = 0;
  Graph rgraph(graph.size());
  for(int i = 0; i < graph.size(); i++) {
    for(int j = 0; j < graph[i].size(); j++) {
      rgraph[graph[i][j]].push_back(i);
    }
  }
  cmp.resize(graph.size(), -1);
  vector<bool> used(graph.size(), false);
  vector<int> order;
  for(int i = 0; i < graph.size(); i++) {
    dfs(i, graph, used, order);
  }
  reverse(order.begin(), order.end());
  for(int i = 0; i < order.size(); i++) {
    if(cmp[order[i]] == -1) rdfs(order[i], rgraph, cmp, cnt), cnt++;
  }
  return cnt;
}


int main()
{
  int V, E; cin >> V >> E;
  Graph graph(V);
  while(E--) {
    int s, t;
    cin >> s >> t;
    graph[s].push_back(t);
  }
  vector<int> cmp;
  StronglyConnectedComponents(graph, cmp);
  int Q; cin >> Q;
  while(Q--) {
    int u, v;
    cin >> u >> v;
    if(cmp[u] == cmp[v]) puts("1");
    else puts("0");
  }
  return 0;
}
