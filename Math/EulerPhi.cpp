// 自然数 n に対して，
// 1 から n までの自然数の中で
// n と互いに素なものの数を
// 求める関数 φ(n)
#define MAX_N 1000000
int euler_phi(int n)
{
  static bool flag = false, is_prime[MAX_N+1];
  static int phi[MAX_N+1];
  if(flag) return phi[n];
  for(int i = 0; i <= n; i++) {
    is_prime[i] = true;
    phi[i] = i;
  }
  for(int i = 2; i <= n; i++) {
    if(is_prime[i]) {
      phi[i] -= phi[i] / i;
      for(int j = i+i; j <= n; j+=i) {
	is_prime[j] = false;
	phi[j] -= phi[j] / i;
      }
    }
  }
  flag = 1;
  return phi[n];
}
