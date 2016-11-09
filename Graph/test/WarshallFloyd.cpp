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
#define int long long

const int inf = 1 << 25;
const ll INF = 1LL << 55;

typedef vector< vector<int> > Graph;

bool warshallfloyd(Graph& graph)
{
  for(int i = 0; i < graph.size(); i++){
    for(int j = 0; j < graph.size(); j++){
      for(int k = 0; k < graph.size(); k++){
	graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]);
      }
      if(graph[j][j] < 0) return false;
    }
  }
  return true;
}

signed main()
{
  int V, E;
  cin >> V >> E;
  Graph graph(V, vector<int>(V, INF));
  rep(i, V) graph[i][i] = 0;
  while(E--) {
    int s, t, d;
    cin >> s >> t >> d;
    graph[s][t] = d;
  }
  if(!warshallfloyd(graph)) {
    cout << "NEGATIVE CYCLE" << endl;
    return 0;
  }
  rep(i, V) {
    rep(j, V) {
      if(j) cout << " ";
      if(graph[i][j] > (2e10)) cout << "INF";
      else cout << graph[i][j];
    }
    cout << endl;
  }
  return 0;
}
