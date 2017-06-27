// Euler-Tour
struct EulerTour {
  vector< vector<int> > graph;
  vector<int> tour, begins, ends;
  int idx, root;
  EulerTour(){}
  EulerTour(int n) : idx(0), root(0), graph(n), begins(2*n), ends(2*n){}
  void add_edge(int u, int v)
  {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  void dfs(int cur, int par)
  {
    begins[cur] = idx;
    tour.push_back(cur);
    idx++;
    for(int& to : graph[cur]) {
      if(to == par) continue;
      dfs(to, cur);
      tour.push_back(cur);
      idx++;
    }
    end[cur] = idx;
  }
};
