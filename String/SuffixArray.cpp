// Suffix Array
struct SuffixArray {
  int n;
  vector<int> sa, rank, temp, lcp;
  string s;
  SuffixArray(const string& str):s(str), n(str.size()) {
    sa.resize(n + 1);
    rank.resize(n + 1);
    temp.resize(n + 1);

    // initialize for one character's rank
    for(int i = 0; i <= n; i++) {
      sa[i] = i;
      rank[i] = i < n ? str[i] : -1; // including null
    }

    // build Suffix Array
    for(int k = 1; k <= n; k *= 2) {

      const auto comp = [&](int i, int j) -> bool {
	if(rank[i] != rank[j]) return rank[i] < rank[j];
	else {
	  int ri = i + k <= n ? rank[i + k] : -1;
	  int rj = j + k <= n ? rank[j + k] : -1;
	  return ri < rj;
	}
      };

      sort(sa.begin(), sa.end(), comp);

      temp[sa[0]] = 0;
      for(int i = 1; i <= n; i++) {
	temp[sa[i]] = temp[sa[i-1]] + (comp(sa[i-1], sa[i]));
      }

      for(int i = 0; i <= n; i++) {
	rank[i] = temp[i];
      }
    }
  }
  void build_lcp() {
    int h = 0;
    lcp[0] = 0;
    for(int i = 0; i < n; ++i) {
      int j = sa[rank[i]-1]; // sa[rank[i]] == i
      if(h > 0) --h;
      for(; j+h < n && i+h < n; ++h) {
	if(s[j+h] != s[i+h]) break;
      }
      lcp[rank[i]-1] = h;
    }
  }
  bool contain(const string& t) {
    int l = 0, r = n;
    while(r - l > 1) {
      int m = (l + r) / 2;
      if(s.compare(sa[m], t.size(), t) < 0) l = m;
      else r = m;
    }
    return s.compare(sa[r], t.size(), t) == 0;
  }
  int find(const string& t) {
    int l = 0, r = n;
    while(r - l > 1) {
      int m = (l + r) / 2;
      if(s.compare(sa[m], t.size(), t) < 0) l = m;
      else r = m;
    }
    return s.compare(sa[r], t.size(), t) == 0 ? r : -1;
  }
  int lower_bound(const string& t) {
    int l = 0, r = n;
    while(r - l > 1) {
      int m = (l + r) / 2;
      if(s.compare(sa[m], t.size(), t) < 0) l = m;
      else r = m;
    }
    return r;
  }
  int upper_bound(const string& t) {
    int l = 0, r = n + 1;
    while(r - l > 1) {
      int m = (l + r) / 2;
      if(s.compare(sa[m], t.size(), t) <= 0) l = m;
      else r = m;
    }
    return r;
  }
  int operator[](int k) const {
    return sa[k];
  }
};
