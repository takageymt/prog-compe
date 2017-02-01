struct edge
{
  int to, weight;
};

using Pi = pair<int, int>;
using Graph = vector< vector<edge> >;

Pi dfs(const Graph& graph, int cur, int prev)
{
  Pi res = Pi(0, cur);
  for(edge& e : graph[cur]) {
    if(e.to != prev) {
      Pi dist = dfs(graph, e.to, cur);
      dist.first += e.weight;
      res = max(res, dist);
    }
  }
  return res;
}

int diameter(const Graph& tree)
{
  Pi p = dfs(tree, 0, -1);
  Pi q = dfs(tree, p.second, -1);
  return q.first;
}
