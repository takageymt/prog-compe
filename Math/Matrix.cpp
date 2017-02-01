
typedef vector<int> vec;
typedef vector<vec> mat;

mat multi(const mat& A, const mat& B)
{
  mat C(A.size(), vec(B[0].size()));
  for(int i = 0; i < A.size(); i++) {
    for(int j = 0; j < B.size(); j++) {
      for(int k = 0; k < B[0].size(); k++) {
	C[i][k] += A[i][j] * B[j][k];
      }
    }
  }
  return C;
}

mat power(mat A, int n)
{
  mat B(A.size(), vec(A.size()));
  for(int i = 0; i < A.size(); i++) B[i][i] = 1;
  while(n > 0) {
    if(n & 1) B = multi(B, A);
    A = multi(A, A);
    n >>= 1;
  }
  return B;
}
