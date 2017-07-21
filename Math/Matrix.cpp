typedef vector<double> vec;
typedef vector<vec> mat;
const double eps = 1e-8;

mat mul(const mat& A, const mat& B) {
  mat C(A.size(), vec(B[0].size()));
  for(int i = 0; i < (int)A.size(); i++) {
    for(int j = 0; j < (int)B.size(); j++) {
      for(int k = 0; k < (int)B[0].size(); k++) {
	C[i][k] += A[i][j] * B[j][k];
      }
    }
  }
  return C;
}

mat pow(mat A, int n) {
  mat B(A.size(), vec(A.size()));
  for(int i = 0; i < (int)A.size(); i++) B[i][i] = 1;
  while(n > 0) {
    if(n & 1) B = mul(B, A);
    A = mul(A, A);
    n >>= 1;
  }
  return B;
}

double det(mat A) {
  const int n = A.size();
  double D = 1;
  for(int i = 0; i < n; i++) {
    int pivot = i;
    for(int j = i+1; j < n; j++) {
      if(abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    }
    swap(A[pivot], A[i]);
    D *= A[i][i] * (i != pivot ? -1 : 1);
    if(abs(A[i][i]) < eps) break;
    for(int j = i+1; j < n; j++) {
      for(int k = n-1; k >= i; k--) {
	A[j][k] -= A[i][k]*A[j][i] / A[i][i];
      }
    }
  }
  return D;
}

int Rank(mat A) {
  const int n = A.size(), m = A[0].size();
  int r = 0, c = 0;
  for(int i = 0; i < n; i++) {
    int pivot = -1;
    while(c < m) {
      for(int j = i; j < n; j++) {
	if(abs(A[j][c]) > eps) { pivot = j; break; }
      }
      if(~pivot) break;
      c++;
    }
    if(c >= m) break;
    r++;
    swap(A[pivot], A[i]);
    double a = A[i][c];
    for(int j = 0; j < m; j++) A[i][j] /= a;
    for(int j = i+1; j < n; j++) {
      double aa = A[j][c];
      for(int k = 0; k < m; k++) A[j][k] -= aa*A[i][k];
    }
    c++;
  }
  return r;
}
