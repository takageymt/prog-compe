vector<int> Zalgorithm(string S) {
  int n = S.size();
  vector<int> A(n);
  A[0] = n;
  int i = 1, j = 0;
  while(i < n) {
    while(i+j < n && S[j] == S[i+j]) j++;
    A[i] = j;
    if(j == 0) { i++; continue; }
    int k = 1;
    while(i+k < n && k+A[k] < j) A[i+k] = A[k], k++;
    i += k, j -= k;
  }
  return A;
}
