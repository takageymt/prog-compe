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
