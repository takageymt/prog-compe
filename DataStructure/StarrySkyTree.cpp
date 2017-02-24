// StarrySky Tree
struct StarrySkyTree
{
  vector<int> data, addend;
  int sz;
  StarrySkyTree(int n)
  {
    sz = 1;
    while(sz < n) sz *= 2;
    data.resize(2*sz-1, inf);
    addend.resize(2*sz-1, 0);
  }
  void add(int a, int b, int x, int k, int l, int r)
  {
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) {
      addend[k] += x;
      return;
    }

    add(a, b, x, 2*k+1, l, (l+r)/2);
    add(a, b, x, 2*k+2, (l+r)/2, r);

    data[k] = min(data[2*k+1] + addend[2*k+1],
		  data[2*k+2] + addend[2*k+2]);
  }
  void add(int a, int b, int x)
  {
    add(a, b, x, 0, 0, sz);
  }
  int query(int a, int b, int k, int l, int r)
  {
    if(r <= a || b <= l) return inf;
    if(a <= l && r <= b) return data[k] + addend[k];
    return min(query(a, b, 2*k+1, l, (l+r)/2),
	       query(a, b, 2*k+2, (l+r)/2, r)) + addend[k];
  }
  int query(int a, int b)
  {
    return query(a, b, 0, 0, sz);
  }
};
