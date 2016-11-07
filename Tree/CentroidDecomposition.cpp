struct CentroidDecomposition
{
  using Pi = pair<int, int>;
  struct Centroid
  {
    int parent_index, parent_depth, depth;
    vector<int> node;
    int size()
    {
      return node.size();
    }
    int &operator[](int k)
    {
      return node[k];
    }
    Pi up()
    {
      return Pi(parent_index, parent_depth);
    }
  };
  
  vector<int> subtree_size, next_path;
  vector<int> tree_index, 
};
