// Edmonds Karp algorithm: max flow
// TBE
struct edge
{
  int from, to, capacity, flow;
  edge(){}
  edge(int from, int to, int capacity, int flow, int rev):from(from), to(to), capacity(capacity), flow(flow), rev(rev){}
};

struct EdmondsKarp
{
  vector< vector<edge> > graph;
  vector<edge> pred;
  EdmondsKarp(int sz):graph(sz), pred(sz, edge(-1, -1, -1, -1, -1)){}
  void add_edge(int from, int to, int capacity)
  {
    graph[from].push_back(edge(from, to, capacity, 0, (int)graph[to].size()));
    graph[to].push_back(edge(to, from, capacity, capacity, (int)graph[from].size()-1));
  }
  int max_flow(int source, int sink)
  {
    int flow = 0;
    while(1) {
      queue<int> que;
      que.push(source);
      while(!que.empty()) {
	int u = que.front(); que.pop();
	for(edge e : graph[u]) {
	  if(pred[e.to] == -1 && e.to != source && e.capacity > e.flow) {
	    pred[e.to] = e;
	    que.push(e.to);
	  }
	}
      }
      if(pred[sink] == -1) break;

      int df = inf;
      for(edge e = pred[sink]; e.to != -1; e = pred[e.from]) {
	df = min(df, e.cap - e.flow);
      }
      for(edge e = pred[sink]; e.to != -1; e = pred[e.from]) {
	e.flow += df;
	graph[e.from][e.rev].flow -= df;
      }
      flow += df;
    }
    return flow;
  }
};
