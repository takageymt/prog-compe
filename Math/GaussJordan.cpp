// 連立一次方程式を解く
typedef vector<double> vec;
typedef vector<vec> mat;
const double eps = 1e-9;
vec gauss_jordan(const mat& A, const vec b) {
  int n = A.size();
  // 拡大係数行列
  mat B(n, vec(n + 1));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) B[i][j] = A[i][j];
  }
  for(int i = 0; i < n; i++) B[i][n] = b[i];

  // 解法
  for(int i = 0; i < n; i++) {
    int pivot = i;
    for(int j = i; j < n; j++) {
      if(abs(B[pivot][i]) < abs(B[j][i])) pivot = j;
    }
    swap(B[i], B[pivot]);
    if(abs(B[i][i]) < eps) return vec();
    // ピボット係数で除算
    for(int j = i+1; j < n+1; j++) B[i][j] /= B[i][i];
    // 掃き出し
    for(int j = 0; j < n; j++) {
      if(i != j) {
	for(int k = i+1; k < n+1; k++) B[j][k] -= B[j][i] * B[i][k];
      }
    }
  }

  // 解
  vec x(n);
  for(int i = 0; i < n; i++) x[i] = B[i][n];
  return x;
}
