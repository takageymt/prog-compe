vector<int> Zalgorithm(string S) {
  vector<int> A(S.size());
  A[0] = S.size();
  int i = 1, j = 0;
  while(i < (int)S.size()) {
    while(i+j < (int)S.size() && S[j] == S[i+j]) j++;
    A[i] = j;
    if(j == 0) { i++; continue; }
    int k = 0;
    while(i+k < (int)S.size() && k+A[k] < j) A[i+k] = A[k], k++;
    i += k, j -= k;
  }
}
