// Centroid Decomposition
struct CentroidDecomposition
{
  using Pi = pair<int, int>;
  vector< vector<int> > tree, decomposed_tree;
  vector<bool> centroid;
  vector<int> subtree_size;
  CentroidDecomposition(int sz):tree(sz), decomposed_tree(sz), centroid(sz, false), subtree_size(sz, -1){}
  void add_edge(int u, int v)
  {
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  int compute_subtree_size(int u, int parent)
  {
    subtree_size[u] = 1;
    for(int v : tree[u]) {
      if(v == p || ~subtree_size[v]) continue;
      subtree_size[u] += compute_subtree_size(v, u);
    }
    return subtree_size[u];
  }
  Pi search_centroid(int u, int parent, int t)
  {
    Pi res = Pi(inf, -1);
    int s = 1, m = 0;
    for(int v : tree[u]) {
      if(v == p || centroid[v]) continue;
      res = min(res, search_centroid(v, u, t));
      m = max(m, subtree_size[v]);
      s += subtree_size[v];
    }
    m = max(m, t - s);
    res = min(res, Pi(m, u));
    return res;
  }
  void decompose(int u)
  {
    compute_subtree_size(u, -1);
    int center = seach_centroid(u, -1, subtree_size[u]).second;
    centroid[center] = true;

    for(int v : tree[center]) {
      if(centroid[v]) continue;
      decompose(v);
      decomposed_tree[center].push_back(v);
    }
    
    centroid[center] = false;
  }
};
