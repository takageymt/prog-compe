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
