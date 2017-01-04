#include <bits/stdc++.h>

using namespace std;

#define int long long
#define FR first
#define SC second
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, f, n) for(int i = (int)(f); i < (int)(n); i++)
#define each(a, b) for(auto& a : b)

typedef pair<int, int> P;

const int inf = 1LL << 55;

// Randomized Binary Search Tree : 平衡二分探索木
int xor128()
{
  static int x = 123456789;
  static int y = 362436069;
  static int z = 521288629;
  static int w = 88675123;
  int t;

  t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

struct node
{
  int val;
  int cnt; // size of subtree
  node *lch, *rch;

  int mini, maxi; // range-query value

  node(int v = 0):val(v), cnt(1), lch(nullptr), rch(nullptr), mini(v), maxi(v){}
};

inline int count(node* t)
{
  return (t ? t->cnt : 0);
}

inline int range_min(node* t)
{
  return (t ? t->mini : inf);
}

inline int range_max(node* t)
{
  return (t ? t->maxi : -inf);
}

inline node* update(node* t)
{
  t->cnt = count(t->lch) + count(t->rch) + 1;
  t->mini = min(t->val, min(range_min(t->lch), range_min(t->rch)));
  t->maxi = max(t->val, max(range_max(t->lch), range_max(t->rch)));
  return t;
}

inline node* make_root(int val)
{
  return (new node(val));
}

node* merge(node *l, node *r)
{
  if(!l || !r) return (l ? l : r);
  int lsz = l->cnt, rsz = r->cnt;
  if(xor128() % (lsz + rsz) < lsz) {
    l->rch = merge(l->rch, r);
    return update(l);
  } else {
    r->lch = merge(l, r->lch);
    return update(r);
  }
}

// split tree in [0, k) and [k, n)
pair<node*, node*> split(node *t, int k)
{
  if(!t) return make_pair(nullptr, nullptr);
  if(k <= count(t->lch)) {
    pair<node*, node*> s = split(t->lch, k);
    t->lch = s.second;
    return make_pair(s.first, update(t));
  } else {
    pair<node*, node*> s = split(t->rch, k - count(t->lch) - 1);
    t->rch = s.first;
    return make_pair(update(t), s.second);
  }
}

node* insert(node *t, int k, int val)
{
  node *p = make_root(val);
  pair<node*, node*> s = split(t, k);
  return merge(merge(s.first, p), s.second);
}

node* erase(node *t, int k)
{
  pair<node*, node*> s = split(t, k);
  pair<node*, node*> u = split(s.second, 1);
  delete u.first;
  return merge(s.first, u.second);
}

int lower_bound(node* t, int val)
{
  if(!t) return 0;
  if(val < t->val) return lower_bound(t->lch, val);
  return lower_bound(t->rch, val) + count(t->lch) + 1;
}

node* insert(node* t, int val)
{
  return insert(t, lower_bound(t, val), val);
}

void dump(node* t)
{
  if(!t) return;
  cout << "(";
  dump(t->lch);
  cout << "" << t->val << "";
  dump(t->rch);
  cout << ")";
}

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);
  int n, q; cin >> n >> q;
  node* root = nullptr;
  vector<int> a(n);
  rep(i, n) {
    cin >> a[i];
    root = insert(root, i, a[i]);
  }
  while(q--) {
    int x, y, z;
    cin >> x >> y >> z;
    if(x == 0) {
      auto p = split(root, z); // [0,z)[z,n)
      auto q = split(p.first, y); // [0,y)[y,z)[z,n)
      auto r = split(p.second, 1); // [0,y)[y,z)[z][z+1,n)
      auto s = merge(q.first, r.first); // [0,y)[z]
      auto t = merge(q.second, r.second); // [y,z)[z+1,n)
      root = merge(s, t); // [0,y)[z][y,z)[z+1,n)
    } else if(x == 1) {
      auto s = split(root, y);
      auto t = split(s.second, z - y + 1);
      cout << range_min(t.first) << endl;
      root = merge(s.first, merge(t.first, t.second));
    } else if(x == 2) {
      root = erase(root, y);
      root = insert(root, y, z);
    }
  }
  return 0;
}
