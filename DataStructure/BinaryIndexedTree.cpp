// Binary Indexed Tree (1 indexed)
struct BIT
{
  vector<int> data;
  BIT(int n):data(n+1, 0){}
  int sum(int k)
  {
    int ret = 0;
    while(k > 0) {
      ret += data[k];
      k -= k & -k;
    }
    return ret;
  }
  void add(int k, int x)
  {
    while(k < data.size()) {
      data[k] += x;
      k += k & -k;
    }
  }
};
