// Trie Tree
struct Trie {
  bool leaf;
  Trie *next[26];
  Trie(){
    leaf = false;
    fill(next, next + 26, nullptr);
  }
  int c2i(char c) {
    return islower(c) ? c - 'a' : -1;
  }
  int insert(const char *s) {
    Trie *t = this;
    for(int i = 0; i < (int)strlen(s); i++) {
      int v = c2i(s[i]);
      if(t->next[v] == nullptr) t->next[v] = new Trie();
      t = t->next[v];
    }
    t->leaf = true;
  }
  bool find(const char *s) {
    const Trie *t = this;
    for(int i = 0; i < (int)strlen(s); i++) {
      int v = c2i(s[i]);
      if(t->next[v] == nullptr) return false;
      t = t->next[v];
    }
    return t->leaf;
  }
};
