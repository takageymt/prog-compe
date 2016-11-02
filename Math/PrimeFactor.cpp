map<int, int> prime_factor(int n)
{
  map<int, int> ret;
  for(int i = 2; i*i <= n; i++) {
    while(n % i == 0) ++ret[i], n /= i;
  }
  if(n != 1) ret[n] = 1;
  return ret;
}
