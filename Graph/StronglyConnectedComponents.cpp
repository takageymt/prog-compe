#include <algorithm>
#include <vector>

typedef vector< vector<int> > Graph;

void dfs(int idx, Graph& G, vector<bool>& used, vector<int>& order)
{
  if(used[idx]) return;
  used[idx] = true;
  for(int i = 0; i < G[idx].size(); i++) {
    dfs(G[idx][i], G, used, order);
  }
  order.push_back(idx);
}

void rdfs(int idx, Graph& rG, vector<int>& cmp, int& cnt)
{
  cmp[idx] = cnt;
  for(int i = 0; i < rG[idx].size(); i++) {
    if(cmp[rG[idx][i]] == -1) rdfs(rG[idx][i], rG, cmp, cnt);
  }
}

int StronglyConnectedComponents(Graph& G, vector<int>& cmp)
{
  int cnt = 0;
  Graph rG(G.size());
  for(int i = 0; i < G.size(); i++) {
    for(int j = 0; j < G[i].size(); j++) {
      rG[G[i][j]].push_back(i);
    }
  }
  cmp.resize(G.size(), -1);
  vector<bool> used(G.size(), false);
  vector<int> order;
  for(int i = 0; i < G.size(); i++) {
    dfs(i, G, used, order);
  }
  reverse(order.begin(), order.end());
  for(int i = 0; i < order.size(); i++) {
    if(cmp[order[i]] == -1) rdfs(order[i], G, cmp, cnt), cnt++;
  }
  return cnt;
}
