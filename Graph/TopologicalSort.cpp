// Topological sorted graph
struct TopologicalGraph {
  vector< vector<int> > graph;
  vector<int> order;
  TopologicalGraph(int sz):graph(sz){}
  TopologicalGraph(vector< vector<int> > graph):graph(graph){}
  void add_edge(int from, int to) {
    graph[from].push_back(to);
  }
  bool visit(int u, vector<int>& color) {
    color[u] = 1;
    for(int v : graph[u]) {
      if(color[v] == 2) continue;
      if(color[v] == 1) return false;
      if(!visit(v, color)) return false;
    }
    order.push_back(u);
    color[u] = 2;
    return true;
  }
  bool sort() {
    vector<int> color((int)graph.size(), 0);
    for(int i = 0; i < (int)color.size(); i++) {
      if(color[i] == 0 && !visit(i, color)) return false;
    }
    reverse(order.begin(), order.end());
    return true;
  }
  void print_order() {
    for(int i = 0; i < (int)order.size(); i++) cout << order[i] << endl;
  }
};

using Graph = vector<vint>;
struct TopoSort {
  TopoSort(){}
  void bfs(const Graph& graph, vint& in, vint& used, vint& res, int s) {
    queue<int> que;
    que.push(s);
    used[s] = 1;
    while(!que.empty()) {
      int u = que.front(); que.pop();
      res.push_back(u);
      for(int v : graph[u]) {
	--in[v];
	if(!in[v] && !used[v]) {
	  que.push(v);
	  used[v] = 1;
	}
      }
    }
  }
  vint sort(const Graph& graph) {
    vint res;
    int V = graph.size();
    vint in(V, 0), used(V, 0);
    for(int u = 0; u < V; u++) {
      for(int v : graph[u]) in[v]++;
    }
    for(int u = 0; u < V; u++) {
      if(!in[u] && !used[u]) bfs(graph, in, used, res, u);
    }
    return res;
  }
};
