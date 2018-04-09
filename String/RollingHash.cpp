
struct RollHash {
  using ull = unsigned long long;
  using hash_t = pair<ull, ull>;
  ull base, mod[2];
  vector<ull> ha[2], pw[2];
  RollHash(const string& s) {
    base = 9973ull;
    mod[0] = 999999937ull;
    mod[1] = 1000000007ull;

    int sz = s.size();
    for(int i = 0; i < 2; ++i) {
      ha[i].resize(sz+1, 0);
      pw[i].resize(sz+1, 0);
      pw[i][0] = 1;
      for(int j = 0; j < sz; ++j) {
	pw[i][j+1] = pw[i][j]*base%mod[i];
	ha[i][j+1] = (ha[i][j]*base+s[j])%mod[i];
      }
    }
  }
  hash_t get(int l, int r) {
    hash_t res;
    res.first = (ha[0][r]-ha[0][l]*pw[0][r-l]%mod[0]+mod[0])%mod[0];
    res.second = (ha[1][r]-ha[1][l]*pw[1][r-l]%mod[1]+mod[1])%mod[1];
    return res;
  }
  hash_t concat(hash_t hash1, hash_t hash2, int hash2_len) {
    hash_t res;
    res.first = (hash1.first * pw[0][hash2_len] + hash2.first) % mod[0];
    res.second = (hash1.second * pw[1][hash2_len] + hash2.second) % mod[1];
    return res;
  }
};
