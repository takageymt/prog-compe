const int MOD = 1000000007;
long long C[1010][1010];

void make_C(){
  memset(C, 0, (int)sizeof(C));
  for(int i = 0; i < 1010; i++){
    C[i][0] = C[i][i] = 1;
    for(int j = 1; j < i; j++) C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
  }
}
