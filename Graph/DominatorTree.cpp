#include <bits/stdc++.h>

using namespace std;

const int MAX_V = 100000;

int par[MAX_V]; // Union-Find用 縮約した森の親を持つ
int m[MAX_V];   // Union-Find用 縮約後のsemi[u]が最小となるu

int I; // dfs木Tのid
int parent[MAX_V]; // parent[v] = Tでのvの親
int vertex[MAX_V]; // vertex[i] = dfs順がiの頂点
int semi[MAX_V];   // v
                   // sdom(v)

int U[MAX_V]; // U[w] = wに対する
int idom[MAX_V]; // idom[v] = idom(v)
vector<int> bucket[MAX_V]; // bucket[v] = 現時点での「sdom(x)=v」なるxの集合
vector<int> G[MAX_V], rG[MAX_V];

// Union-Find
void init(int N) {
  for(int i = 0; i < N; ++i) par[i] = i, m[i] = i;
}
int find(int v) {
  if(par[v] == v) return v;
  int r = find(par[v]);
  if(semi[m[v]] > semi[m[par[v]]]) m[v] = m[par[v]];
  return par[v] = r;
}

int eval(int v) {
  find(v);
  return m[v];
}
void link(int x, int y) {
  par[y] = x;
}
// UnionFind

void dfs(int v) {
  semi[v] = I;
  vertex[I++] = v;
  for(int u : G[v]) {
    if(semi[u] < 0) {
      parent[u] = v;
      dfs(u);
    }
  }
}
void make_dom_tree(int N, int r) {
  init(N);
  for(int i = 0; i < N; ++i) semi[i] = -1;
  dfs(r);
  for(int i = N-1; i > 0; --i) {
    // step2
    int w = vertex[i];
    for(int v : rG[w]) {
      int u = eval(v);
      semi[w] = min(semi[w], semi[u]);
    }
    bucket[vertex[semi[w]]].push_back(w);
    // step3
    for(int v : bucket[parent[w]]) U[v] = eval(v);
    bucket[parent[w]].clear();
    link(parent[w], w);
  }
  // step4
  for(int i = 1; i < N; ++i) {
    int w = vertex[i];
    int u = U[w];
    if(semi[w] == semi[u]) idom[w] = semi[w];
    else idom[w] = idom[u];
  }
  for(int i = 1; i < N; ++i) {
    int w = vertex[i];
    idom[w] = vertex[idom[w]];
  }
  idom[r] = -1;
}
