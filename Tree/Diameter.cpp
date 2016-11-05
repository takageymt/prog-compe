struct edge
{
  int to, weight;
};

using Pi = pair<int, int>;
using Graph = vector< vector<edge> >;
  
Pi dfs(const Graph& graph, int cur, int prev)
{
  Pi ret = Pi(0, -1);
  for(edge& e : graph[cur]) {
    if(e.to != prev) {
      Pi dist = dfs(graph, e.to, cur);
      dist.first += e.weight;
      ret = max(ret, dist);
    }
  }
  return ret;
}

int diameter(const Graph& tree)
{
  Pi p = dfs(tree, 0, -1);
  Pi q = dfs(tree, p.second, -1);
  return q.first;
}
