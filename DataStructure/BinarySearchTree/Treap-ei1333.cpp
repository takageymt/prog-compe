struct Treap {
  struct node{
    int value; // 値
    node *left, *right; // *左, *右:
    int priority; // 優先度
    int cnt; // 部分木のサイズ
    //  int sum; // 部分木の和
    int small; //部分木の最小値
    node( int v) : value(v), priority(rand()), cnt(1), /*sum(v),*/ small(v){
      left = right = NULL;
    }
  };
  
  node *root;
  Treap():root(NULL){}
  
  int count( node *t){ return !t ? 0 : t->cnt; }
  //int sum( node *t)  { return !t ? 0 : t->sum; }
  int mini( node *t) { return !t ? INF : t->small; }
  
  node* update( node* t) {
    t -> cnt = count( t -> left) + count( t -> right) + 1;
    // t -> sum = sum( t -> left) + sum( t -> right) + t -> value;
    t -> small = min( min( mini( t -> left), mini( t -> right)), t -> value);
    return t;
  }
  node* merge( node* l, node* r){
    if(!l || !r) return l? l : r;
    if(l -> priority > r -> priority) {
      l -> right = merge( l -> right, r);
      return update(l);
    } else {
      r -> left = merge( l, r -> left);
      return update(r);
    }
  }
  pair< node*, node* > split( node* t, int k){ // [0,k),[k,n)
    if(!t) return make_pair((node*)NULL,(node*)NULL);
    if(k <= count( t -> left)){
      pair< node*, node* > s = split( t -> left, k);
      t -> left = s.second;
      return make_pair( s.first, update(t));
    }else{
      pair< node*, node* > s = split( t -> right, k - count( t -> left) - 1);
      t -> right = s.first;
      return make_pair( update(t), s.second);
    }
  }
  
  node* insert( node* t, int k, int val){
    pair< node*, node* > s = split( t, k);
    t = merge( s.first, new node( val));
    return update(merge( t, s.second));
  }
  
  node* erase( node* t, int k){
    pair< node*, node* > s1, s2;
    s1 = split( t, k + 1);
    s2 = split( s1.first, k);
    t = merge( s2.first, s1.second);
    return update(t);
  }
  
  node* find( node* t, int k){
    int c = count(t -> left);
    if(k < c)       return find( t -> left, k);
    else if(k > c)  return find( t -> right, k - c - 1);
    else return t;
  }
  
  int rmq( node* t, int l, int r){
    if(l >= count(t) || r <= 0) return INF;
    if(l <= 0 && r >= count(t)) return mini(t);
  
    int size = count( t -> left);
    int ret = min( rmq( t -> left, l, r),  rmq( t -> right, l - size - 1, r - size - 1));
    if(l <= size && size < r) ret = min( ret, t -> value);
    return ret;
  }
  void insert( int k, int v){ root = insert( root, k, v);}
  void erase( int k) { root = erase( root, k);}
  node* find( int k) { return find( root, k); }
  int rmq( int l, int r){ return rmq( root, l, r); }
};
