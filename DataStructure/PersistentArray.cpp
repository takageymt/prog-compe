// 永続配列(完全2^N分木)
#define N 3
class Array {
public:

  Array(){}
  Array(int n)
  {
    h = 0;
    for(int i = 1; i < n; i *= (1<<N)) h += N;
  }

  int* mutable_get(int k)
  {
    auto p = mutable_get(k, root, 0, h);
    root = p.first;
    return &p.second->value;
  }

  int immutable_get(int k)
  {
    node *res = immutable_get(k, root, 0, h);
    return res != nullptr ? res->value : -1;
  }

  int operator[](int k)
  {
    return immutable_get(k);
  }

private:

  struct node {
    node *ch[(1<<N)] = {};
    int value;

    node(){}
    node(int value):value(value){}
  };

  int h;
  node *root = nullptr;

  node* immutable_get(int a, node *x, int l, int d)
  {
    if(d == 0) return x;
    int id = (a - l) >> (d - N);
    return immutable_get(a, x->ch[id], l + (id << (d - N)), d - N);
  }

  pair<node*, node*> mutable_get(int a, node *x, int l, int d)
  {
    x = x != nullptr ? new node(*x) : new node();
    if(d == 0) return make_pair(x, x);
    int id = (a - l) >> (d - N);
    auto p = mutable_get(a, x->ch[id], l + (id << (d - N)), d - N);
    x->ch[id] = p.first;
    return make_pair(x, p.second);
  }

};
