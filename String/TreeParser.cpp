#include <bits/stdc++.h>

using namespace std;

#define int long long
#define all(v) begin(v), end(v)
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, s, n) for(int i = (int)(s); i < (int)(n); i++)

const int inf = 1LL << 55;
const int mod = 1e9 + 7;

string A, B;
int ai, bi;

int nodeval(bool isA)
{
  int ret = 0;
  if(isA) while(ai < A.size() && isdigit(A[ai])) ret = ret*10 + A[ai]-'0', ai++;
  else while(bi < B.size() && isdigit(B[bi])) ret = ret*10 + B[bi]-'0', bi++;
  return ret;
}

void parse()
{
  bool advA = (ai < A.size() && A[ai] == '(');
  bool advB = (bi < B.size() && B[bi] == '(');
  if(!advA && !advB) return;
  if(advA) ai++; // (
  if(advB) bi++; // (
  if(advA && advB) cout << "(";
  parse(); // left child
  if(advA && advB) cout << ")";
  if(advA) ai+=2; // )[
  if(advB) bi+=2; // )[
  int aval = nodeval(true);
  int bval = nodeval(false);
  if(advA && advB) cout << "[" << aval+bval << "]";
  if(advA) ai+=2; // ](
  if(advB) bi+=2; // ](
  if(advA && advB) cout << "(";
  parse(); // right child
  if(advA && advB) cout << ")";
  if(advA) ai++; // )
  if(advB) bi++; // )
}

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);

  cin >> A >> B;
  parse();
  cout << endl;

  return 0;
}
