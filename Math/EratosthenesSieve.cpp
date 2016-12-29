// Sieve of Eratosthenes
// enumerate prime numbers less than or equal to N
void enum_prime(int N, vector<bool>& is_p)
{
  is_p.resize(N, true);
  is_p[0] = is_p[1] = false;
  for(int i = 2; i*i <= N; i++) {
    if(!is_p[i]) continue;
    for(int j = i+i; j <= N; j+=i) is_p[j] = false;
  }
}
