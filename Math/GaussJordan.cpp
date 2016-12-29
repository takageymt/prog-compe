// 連立一次方程式を解く
typedef vector<double> vectorDBL;
typedef vector<vectorDBL> matrixDBL;
const double eps = 1e-9;
vectorDBL gauss_jordan(const matrixDBL& A, const vectorDBL b)
{
  int n = A.size();
  // 拡大係数行列  
  matrixDBL Ab(n, vectorDBL(n + 1));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) Ab[i][j] = A[i][j];
  }
  for(int i = 0; i < n; i++) Ab[i][n] = b[i];

  // 解法
  for(int i = 0; i < n; i++) {
    int pivot = i;
    for(int j = i; j < n; j++) {
      if(abs(Ab[pivot][i]) < abs(Ab[j][i])) pivot = j;
    }
    swap(Ab[i], Ab[pivot]);    
    if(abs(Ab[i][i]) < eps) return vectorDBL();
    // ピボット係数で除算
    for(int j = i+1; j < n+1; j++) Ab[i][j] /= Ab[i][i];
    // 掃き出し
    for(int j = 0; j < n; j++) {
      if(i != j) {
	for(int k = i+1; k < n+1; k++) Ab[j][k] -= Ab[j][i] * Ab[i][k];
      }
    }
  }
  
  // 解
  vectorDBL x(n);
  for(int i = 0; i < n; i++) x[i] = Ab[i][n];
  return x;
}
