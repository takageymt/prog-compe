// AOJ GRL_2_A: Spanning Tree - Minimum Spanning Tree
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

struct UnionFind
{
  vector<int> data;
  UnionFind(int sz):data(sz, -1){};
  int size(int x) { return -data[find(x)]; }
  int find(int x) { return data[x] < 0 ? x : data[x] = find(data[x]); }
  bool same(int x, int y) { return find(x) == find(y); }
  int unite(int x, int y)
  {
    x = find(x), y = find(y);
    if(x != y) {
      if(data[x] < data[y]) swap(x, y);
      data[x] += data[y]; data[y] = x;
    }
    return -data[x];
  }
};


struct edge{
  int u, v, weight;
  edge(){}
  edge(int u, int v, int weight):u(u), v(v), weight(weight){}
  bool operator<(const edge& e) const {
    return weight < e.weight;
  }
};

struct Kruskal
{
  vector<edge> edges;
  int V;
  Kruskal(int V):V(V){}
  void add_edge(int u, int v, int weight)
  {
    edges.push_back(edge(u, v, weight));
  }
  int build()
  {
    sort(edges.begin(), edges.end());
    UnionFind uf(V);
    int ret = 0;
    for(int i = 0; i < edges.size(); i++){
      edge& e = edges[i];
      if(!uf.same(e.u, e.v)){
	uf.unite(e.u, e.v);
	ret += e.weight;
      }
    }
    return ret;
  }
};


int main()
{
  int V, E;
  cin >> V >> E;
  Kruskal msp(V);
  while(E--) {
    int s, t, w;
    cin >> s >> t >> w;
    msp.add_edge(s, t, w);
  }
  cout << msp.build() << endl;
  return 0;
}
