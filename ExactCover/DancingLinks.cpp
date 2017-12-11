#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2000;
const int MAX_M = 600;
const int MAX_NODE = 500000;

struct dlx_node {
  int left, right, up, down, row, col;
};

struct DancingLinks {
  // horizontal : elements
  // vertical   : subsets
  dlx_node node[MAX_NODE];
  int head, head_col[MAX_N];
  int count[MAX_M];
  int depth, ans[MAX_N];
  int size;
  void init(int m) { // initialize with the number of elements
    head = 0;
    depth = -1;
    memset(ans, -1, sizeof(ans));
    memset(count, 0, sizeof(count));
    for(int i = 0; i <= m; i++) {
      count[i] = 0;
      node[i].left = i-1;
      node[i].right = i+1;
      node[i].up = i;
      node[i].down = i;
    }
    node[0].left = m;
    node[m].right = 0;
    size = m;
    memset(head_col, -1, sizeof(head_col));
  }
  void link(int r, int c) {
    ++size;
    ++count[c];
    node[size].row = r;
    node[size].col = c;
    node[size].up = node[c].up;
    node[size].down = c;
    node[node[c].up].down = size;
    node[c].up = size;
    if(head_col[r] == -1) {
      head_col[r] = node[size].left = node[size].right = size;
    } else {
      node[size].right = head_col[r];
      node[size].left = node[head_col[r]].left;
      node[node[size].left].right = size;
      node[node[size].right].left = size;
    }
  }
  void remove(int c) {
    node[node[c].right].left = node[c].left;
    node[node[c].left].right = node[c].right;
    for(int i = node[c].down; i != c; i = node[i].down) {
      for(int j = node[i].right; j != i; j = node[j].right) {
	node[node[j].up].down = node[j].down;
	node[node[j].down].up = node[j].up;
	--count[node[j].col];
      }
    }
  }
  void resume(int c) {
    for(int i = node[c].up; i != c; i = node[i].up) {
      for(int j = node[i].left; j != i; j = node[j].left) {
	++count[node[j].col];
	node[node[j].down].up = j;
	node[node[j].up].down = j;
      }
    }
    node[node[c].left].right = c;
    node[node[c].right].left = c;
  }
  bool dance(int d) {
    if(node[head].right == head) {
      depth = d;
      return true;
    }
    int c = node[head].right;
    for(int i = node[head].right; i != head; i = node[i].right) {
      if(count[i] < count[c]) c = i;
    }
    if(count[c] == 0) return false;
    remove(c);
    for(int i = node[c].down; i != c; i = node[i].down) {
      ans[d] = node[i].row;
      for(int j = node[i].right; j != i; j = node[j].right) {
	remove(node[j].col);
      }
      if(dance(d+1)) return true;
      for(int j = node[i].left; j != i; j = node[j].left) {
	resume(node[j].col);
      }
    }
    resume(c);
    return false;
  }
};

DancingLinks dlx;

const int range[][2] = {
  {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5},
  {2, 2}, {2, 3}, {2, 4}, {2, 5},
  {3, 3}, {3, 4}, {3, 5},
  {4, 4}, {4, 5},
  {5, 5},
  {0, 0}
};

using vint = vector<int>;
using Graph = vector<vint>;

Graph graph;
int s[66], e[66];
int mat[MAX_N][MAX_M];
int out[66];

signed main() {
  int n, m, d;
  while(cin >> n >> m >> d) {
    graph.clear();
    graph.resize(n+1);
    for(int i = 1; i <= n; i++) graph[i].push_back(i);
    for(int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }
    for(int i = 1; i <= n; i++) cin >> s[i] >> e[i];
    int _n = n*16;
    int _m = n*d + n;
    memset(mat, 0, sizeof(mat));
    for(int u = 1; u <= n; u++) {
      for(int i = 0; i < 15; i++) {
	int id = (u-1)*16 + (i+1);
	if(s[u] <= range[i][0] && range[i][1] <= e[u]) {
	  for(int v : graph[u]) {
	    for(int k = range[i][0]; k <= range[i][1]; k++) {
	      mat[id][(v-1)*d+k] = 1;
	    }
	  }
	  // 稼働は一度だけ
	  mat[id][n*d+u] = 1;
	}
      }
      // 他の頂点にカバーされた場合、自分はカバーできない
      mat[(u-1)*16+16][n*d+u] = 1;
    }
    dlx.init(_m);
    for(int i = 1; i <= _n; i++) {
      for(int j = 1; j <= _m; j++) {
	if(mat[i][j]) dlx.link(i, j);
      }
    }
    if(!dlx.dance(0)) {
      cout << "No solution" << endl;
    } else {
      for(int i = 0; i < dlx.depth; i++) {
	assert(~dlx.ans[i]);
	int u = (dlx.ans[i]-1)/16 + 1;
	int r = (dlx.ans[i]-1)%16;
	out[u] = r;
      }
      for(int i = 1; i <= n; i++) {
	cout << range[out[i]][0] << " " << range[out[i]][1] << endl;
      }
    }
    cout << endl;
  }

  return 0;
}
