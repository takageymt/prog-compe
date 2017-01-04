// aoj2698
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define FR first
#define SC second
#define all(v) (v).begin(), (v).end()
#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define reps(i, f, n) for(int i = (int)(f); i < (int)(n); i++)
#define each(a, b) for(auto& a : b)

typedef pair<int, int> P;

const int inf = 1LL << 55;

#define MAX_H 22
#define MAX_W 22
int grundy[MAX_H][MAX_W][MAX_H][MAX_W]; // 左上右下[u,d)&[l,r)

int H, W;
char board[MAX_H][MAX_W];

int calcGrundy(int u, int l, int d, int r)
{
  int& g = grundy[u][l][d][r];
  if(~g) return g;
  if(u >= d || l >= r) return g = 0;
  set<int> V;
  for(int i = u; i < d; i++) {
    for(int j = l; j < r; j++) {
      if(board[i][j] != 'X') {
	V.insert(calcGrundy(u, l, i, j) ^ calcGrundy(u, j+1, i, r)
		 ^ calcGrundy(i+1, l, d, j) ^ calcGrundy(i+1, j+1, d, r));
      }
    }
  }
  g = 0;
  while(V.count(g)) g++;
  return g;
}

signed main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cout << fixed << setprecision(12);
  cin >> H >> W;
  rep(i, H) rep(j, W) cin >> board[i][j];
  memset(grundy, -1, sizeof(grundy));
  cout << (calcGrundy(0, 0, H, W) ? "First" : "Second") << endl;
  return 0;
}
