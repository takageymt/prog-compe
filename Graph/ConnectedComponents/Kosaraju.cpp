// Strongly Connected Components
struct SCC {
  vector< vector<int> > graph, rgraph, dag;
  vector< pair<int, int> > edges;
  vector<int> cmp;
  SCC(int V):graph(V), rgraph(V), cmp(V, -1){}
  void add_edge(int from, int to) {
    graph[from].push_back(to);
    rgraph[to].push_back(from);
    edges.emplace_back(from, to);
  }
  void dfs(int u, vector<int>& ord, vector<int>& used) {
    if(used[u]) return;
    used[u] = 1;
    for(int v : graph[u]) dfs(v, ord, used);
    ord.push_back(u);
  }
  void rdfs(int u, int& id) {
    if(~cmp[u]) return;
    cmp[u] = id;
    for(int v : rgraph[u]) rdfs(v, id);
  }
  int build() {
    vector<int> ord, used(graph.size(), 0);
    for(int u = 0; u < (int)graph.size(); u++) dfs(u, ord, used);
    reverse(ord.begin(), ord.end());
    int sz = 0;
    for(int u : ord) if(cmp[u] == -1) rdfs(u, sz), sz++;

    dag.resize(sz);
    set< pair<int, int> > st;
    for(auto e : edges) {
      int u = cmp[e.first], v = cmp[e.second];
      if(u == v || st.count(make_pair(u, v))) continue;
      dag[u].push_back(v);
      st.emplace(u, v);
    }

    return sz;
  }
};
