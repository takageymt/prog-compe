struct edge{
  int to, weight;
  edge(){}
  edge(int to, int weight):to(to), weight(weight){}
};

struct Prim
{
  vector< vector<edge> > graph;
  Prim(int sz):graph(sz){}
  void add_edge(int u, int v, int weight)
  {
    graph[u].push_back(edge(v, weight));
    graph[v].push_back(edge(u, weight));
  }
  int build()
  {
    int total = 0;
    vector<bool> used(graph.size(), false);
    priority_queue< Pi, vector<Pi>, greater<Pi> > que;
    que.push(Pi(0, 0));
    while(!que.empty()) {
      Pi p = que.top(); que.pop();
      int curr = p.second, weight = p.first;
      if(used[curr]) continue;
      used[curr] = true;
      total += weight;
      for(int i = 0; i < graph[curr].size(); i++){
	edge& e = graph[curr][i];
	que.push(Pi(e.weight, e.to));
      }
    }
    return total;
  }
};
