struct edge {
  int to, cost;
};

struct BellmanFord
{
  vector<edge> E;
  vector<int> mincost;
};
