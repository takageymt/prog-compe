// Dual Rolling Hash
struct RollingHash
{
  using int_type = unsigned long long;
  using hash_type = vector<int_type>;
  int_type base, mod[2];
  vector<int_type> hashed[2], power[2];
  RollingHash(){
    base = 9973LL, mod[0] = 999999937LL, mod[1] = 1000000007LL; 
  }
  void init(const string& s)
  {
    int sz = s.size();

    for(int i = 0; i < 2; i++) {
      hashed[i].resize(sz + 1, 0);
      power[i].resize(sz + 1, 0);

      power[i][0] = 1;
      for(int j = 0; j < sz; j++) {
	power[i][j+1] = power[i][j] * base % mod[i];
	hashed[i][j+1] = (hashed[i][j] + s[j]) * base % mod[i];
      }
    }
  }
  hash_type get(int l, int r)
  {
    hash_type ret(2);
    for(int i = 0; i < 2; i++) {
      ret[i] = ((hashed[i][r] - hashed[i][l] * power[i][r-l]) % mod[i] + mod[i]) % mod[i];
    }
    return ret;
  }
  hash_type concat(hash_type hash1, hash_type hash2, int hash2_len)
  {
    hash_type ret(2);
    for(int i = 0; i < 2; i++) {
      ret[i] = (hash1[i] * power[i][hash2_len] + hash2[i]) % mod[i];
    }
    return ret;
  }
};
