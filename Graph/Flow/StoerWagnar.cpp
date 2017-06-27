// Stoer Wagnar algorithm: global minimum cut
struct StoerWagner
{
  vector< vector<int> > graph;
  StoerWagner(int sz):graph(sz, vector<int>(sz, 0)){}
  void add_edge(int from, int to, int weight)
  {
    graph[from][to] = graph[to][from] = weight;
  }
  int global_min_cut()
  {
    int res = inf;
    vector<int> idx((int)graph.size());
    for(int i = 0; i < (int)graph.size(); i++) idx[i] = i;

    for(int i = (int)graph.size(); i > 1; i--) {
      // Calculate Maximum Adjacent Order
      int u = 0, v = 0, cut = 0;
      vector<int> w(i, 0);
      for(int j = 0; j < i; j++) {
	u = v; v = max_element(w.begin(), w.end()) - w.begin();
	cut = w[v]; w[v] = -1;
	for(int k = 0; k < i; k++) {
	  if(w[k] >= 0) w[k] += graph[idx[v]][idx[p]];
	}
      }

      // Merge graph
      for(int j = 0; j < i; j++) {
	graph[idx[u]][idx[i]] += graph[idx[v]][idx[i]];
	graph[idx[i]][idx[u]] += graph[idx[i]][idx[v]];
      }
      idx.erase(idx.begin() + v);

      // update min_cut
      res = min(res, cut);
    }

    return res;
  }
};
