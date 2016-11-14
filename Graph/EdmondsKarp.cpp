// Edmonds Karp algorithm: max flow
// TBE
struct EdmondsKarp
{
  struct edge
  {
    int to, capacity, flow, rev;
    edge(){}
    edge(int to, int capacity, int flow, int rev):to(to), capacity(capacity), flow(flow), rev(rev){}
  };
  vector< vector<edge> > graph;
  vector<int> prevv, preve;
  EdmondsKarp(int sz):graph(sz), prevv(sz, -1), preve(sz, -1){}
  void add_edge(int from, int to, int capacity)
  {
    graph[from].push_back(edge(to, capacity, 0, (int)graph[to].size()));
    graph[to].push_back(edge(from, capacity, capacity, (int)graph[from].size()-1));
  }
  int max_flow(int source, int sink)
  {
    int flow = 0;
    while(1) {
      queue<int> que;
      que.push(source);
      fill(prevv.begin(), prevv.end(), -1);
      fill(preve.begin(), preve.end(), -1);      
      while(!que.empty()) {
	int u = que.front(); que.pop();
	for(int i = 0; i < (int)graph[u].size(); i++) {
	  edge& e = graph[u][i];
	  if(prevv[e.to] == -1 && e.to != source && e.capacity > e.flow) {
	    prevv[e.to] = u; preve[e.to] = i;
	    que.push(e.to);
	  }
	}
      }
      if(prevv[sink] == -1) break;

      int df = inf;
      for(int v = sink; v != source; v = prevv[v]) {
	edge e = graph[prevv[v]][preve[v]];
	df = min(df, e.capacity - e.flow);
      }
      for(int v = sink; v != source; v = prevv[v]) {
	edge& e = graph[prevv[v]][preve[v]];
	e.flow += df;
	graph[v][e.rev].flow -= df;
      }
      flow += df;
    }
    return flow;
  }
};
