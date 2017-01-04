#include <bits/stdc++.h>

using namespace std;

int N;
double pw, vw[100010], pf[100010], vf[100010], th[100010];

double f(double x)
{
  double ret = pw*x;
  for(int i = 0; i < N; i++) {
    double v = vw[i]*x;
    if(v >= th[i]) continue;
    ret += pf[i] * (th[i] - v)/vf[i];
  }
  return ret;
}

double ternary_search()
{
  double l = 0.0, r = 1000.0;
  for(int i = 0; i < 200; i++) {
    double c = (r - l) / 3.0;
    double a = l + c, b = r - c;
    if(f(a) >= f(b)) l = a;
    else r = b;
  }
  return f(l);
}

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  while(cin >> N, N) {
    cin >> pw;
    for(int i = 0; i < N; i++) cin >> vw[i] >> pf[i] >> vf[i] >> th[i];
    cout << ternary_search() << endl;
  }
  
  return 0;
}
