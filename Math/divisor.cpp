// 約数の列挙 (約数の個数は10^15でも高々256個)
vector<int> divisor(int n)
{
  vector<int> ret;
  for(int i = 1; i*i <= n; i++) {
    if(n % i == 0) {
      ret.push_back(i);
      if(i != n/i) ret.push_back(n/i);
    }
  }
  return ret;
}

// 約数の数 m = (p + 1)*(q + 1)*(r + 1)*...
int numOfDivisors(int n)
{
  auto prime = prime_factor(n);

  int ret = 1;
  for(auto&& p : prime) ans *= (p.second + 1);

  return ret;
}
