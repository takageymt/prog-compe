// Stable Marriage
#include <vector>
#include <queue>
using namespace std;
using Matrix = vector<vector<int>>;
using Graph = Matrix;
struct GaleShapley {
  // optimal matching of man side
  vector<int> stable_marriage(const Graph& man, const Graph& woman) {
    int n = man.size(), m = woman.size();
    Matrix rank(m, vector<int>(n, n));
    vector<int> idx(n, 0);
    vector<int> f(n), g(m, -1);
    for(int i = 0; i < m; ++i) {
      for(int j = 0; j < (int)woman[i].size(); ++j) {
	rank[i][woman[i][j]] = j;
      }
    }
    queue<int> que;
    for(int i = 0; i < n; ++i) que.push(i);
    while(!que.empty()) {
      int x = que.front(); que.pop();
      int y = man[x][idx[x]++];
      if(g[y] == -1) {
	f[x] = y, g[y] = x;
      } else {
	if(rank[y][x] < rank[y][g[y]]) {
	  que.push(g[y]);
	  f[x] = y, g[y] = x;
	} else {
	  que.push(x);
	}
      }
    }
    return f;
  }
};
