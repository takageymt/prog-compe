// Treap (insert-erase) : 平衡二分探索木
// Tree + Heap
// each node has a key and priority (priority is decided randomly).
struct node_t {
  int val; // value
  node_t *ch[2]; // 0:left-child, 1:right-child
  int pri; // priority
  int cnt; // size of subtree
  int sum; // sum of subtree
  node_t(int v, double p):val(v), pri(p), cnt(1), sum(v) {
    ch[0] = ch[1] = NULL;
  }
};

int count(node_t *t) { return !t ? 0 : t->cnt; }
int sum(node_t *t) { return !t ? 0 : t->sum; }

// 部分きに関する情報の更新. 子が変わったら必ず呼ぶ.
node_t* update(node_t *t) {
  t->cnt = count(t->ch[0]) + count(t->ch[1]) + 1;
  t->sum = sum(t->ch[0]) + sum(t->ch[1]) + t->val;
  return t;
}

// 回転
node_t* rotate(node_t *t, int b)
{
  node_t *s = t->ch[1 - b];
  t->ch[1 - b] = s->ch[b];
  s->ch[b] = t;
  update(t);
  update(s);
  return s;
}

node_t* find(nde_t *t, int key)
{
  return !t || key == t->key ? t : find(t->ch[key < t->key], key);
}

// tが根となっている木のk番目に値val、優先度priのノードを挿入
// 根のノードを返す
node_t* insert(node_t *t, int k, int val, double pri)
{
  if(!t) return new node_t(val, pri);
  int c = count(t->ch[0]), b = (k > c);
  t->ch[b] = insert(t->ch[b], k - (b ? (c+1) : 0), val, pri);
  update(t);
  if(t->pri > t->ch[b]->pri) t = rotate(t, 1 - b);
  return t;
}

// 消したいノードの優先度を最低にして回転. 一番下まで持ってきたら削除
node_t* erase(node_t *t, int key)
{
  if(!t) return NULL;
  if(key == t->key) {
    if(!t->ch[0] && !t->ch[1]) return NULL;
    else if(!t->ch[0]) t = rotate(t, 0);
    else if(!t->ch[1]) t = rotate(t, 1);
    else t = rotate(t, t->ch[0]->pri < t->ch[1]->pri);
    t = erase(t, key);
  } else {
    int b = !(key < t->key);
    t->ch[b] = erase(t->ch[b], key);
  }
  return t;
}

// merge
// split
